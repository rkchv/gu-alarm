#include "gui_gurza_alarm.h"
#include "adc.h"
#include "qmx.h"
#include <shellapi.h>
#include <stdio.h>
#include <conio.h> 

// Конструктор

qmbox_t::qmbox_t()
   :  
     number_event(0),
     window(1),
     current_date_time(QDateTime::currentDateTime()),
     mode(true)
{ 
   // Заполняем массив счетчиков для проверки
   // на четвертый тип события нулями
      
   for (quint8 number; number < CHANNELS; number++)
   {
      alarm_counter[number] = 0;
   }
   
};
//-----------------------//


void qmbox_t::sl_send_fn(bool checked)
{
   if(checked)
      emit sig_send_filename(events_fn);
};
//----------------------------------//

// Проверяем доступ к модулю qmbox

bool qmbox_t::checking(void)
{
   sig_log(tr("Запуск сервера генерации данных"));
   
	ShellExecuteW(NULL, TEXT("open"), TEXT("../support/qmbox_ds.exe"), 
                       TEXT("-p3"), NULL, SW_SHOWNORMAL);
   Sleep(500);
   
   //------ Получим дескриптор системы ------//
   
   // Начальное значение дескриптора
	
   sys_desc = 0;
	
	sys_desc = QMX_CircBufAttach(0);
        
   // Если дескриптор не получен
	
   if (sys_desc == NULL)
   {
      sig_log(tr("Система QMS10 не обнаружена"));
      return 0;
   }
   
   sig_log(tr("Система QMS10 обнаружена"));
   
   // Проинициализируем устройство
    
   if (QMX_InitModules(sys_desc, QMX_LOG_NONE, NULL ) == QMX_ERR)
   {
      sig_log(tr("Неудачная попытка проинициализировать устройство QMS10"));
      return 0;
   }
   
   sig_log(tr("Cистема QMS10 успешно проинициализирована"));
   
   //------ Убедимся, что в нулевом слоте устройства - модуль QMS10 ------//
    
   char name_device[64];
    
   // имя модуля запишем в массив символов 
   strncpy( name_device, configuration.ModName[0], 10 );
    
	name_device[10] = 0;
    
   // проверим, это нужный нам модуль или нет
   if(!_stricmp(name_device, "QMS10v1" ))
	{
      sig_log(tr("Устройство QMS10 не опознано"));
      return 0;  
	}   
   //--------------------------------------------------------------------// 
      
   return 1;   
};
//----------------------------------------------//


// Слот выбора режима работы

void qmbox_t::sl_choice_mode(void)
{	
   // Если флаг состояния
   if (mode == false)
      // Имитация сигнала
      sl_imit_input_data();
   else
      // Оцифровка сигнала
      sl_input_data();
};
//----------------------------//

// Слот считывания данных с АЦП

void qmbox_t::sl_input_data(void)
{
  
   // Прочитаем каллибровочные коэффициенты
   for (int i = 0; i < 3; i++)
   {
      //Коэффициенты: x1, x16, x64
      QMX_QMS10_ReadCC(sys_desc, 0, i, &ratio[i]); 
   }
     
   // Заполним таблицу опроса модуля QMS10:
	// в сеансе сбора данных будут участвовать 8  каналов устройства 
   // Работа будет производиться в дифференциальном режиме
    
   for (int i = 0; i < CHANNELS; i++)
   {
      if (QMX_QMS10_BuildTableItem( sys_desc, i , QMX_QMS10_MODE_D, 
      QMX_QMS10_GAIN_1,  &table_channels[i]) == QMX_ERR)
      {
         sig_log(tr("Ошибка формирования таблицы опрашиваемых каналов"));
         
         // Аварийное завершение приложения
         QCoreApplication::exit(0);   
      }
   }
   
   // Запишем таблицу опроса в модуль
	if (QMX_QMS10_SetTable(sys_desc, 0, table_channels, CHANNELS) == QMX_ERR)
   {
         sig_log(tr("Ошибка установки таблицы опрашиваемых каналов"));
         
         // Аварийное завершение приложения
         QCoreApplication::exit(0); 
   };
      
   // Установим частоту сбора данных - 12 кГц (2 кГц на канал)
	QMX_QMS10_SetAdcRate(sys_desc, 0, 12000, NULL);
       
   //// Подготовимся к сбору данных
	QMX_MOD_SetActive(sys_desc, 0, QMX_ON);
   
   // Конфигурирует систему в соответствии с заданными параметрами
	if (QMX_Prepare(sys_desc, 100, &configuration) == QMX_ERR)
   {
         sig_log( tr("Ошибка конфигурации системы QMS10"));
         
         // Аварийное завершение приложения
         QCoreApplication::exit(0);
   };
   
   quint16 *data;          // указатель на слова данных
   quint32 buffer_size,    // размер буфера
           data_last,      // последнее считанное 2-х байтовое слово данных
           data_current,   // текущее 2-х байтовое слово данных
           data_help;      // последнее 2-х байтовое слово данных из прошлой порции
   
   // Размер кольцевого буфера данных, заполняемого сервером
   buffer_size = *configuration.CBInput.buf_size;
      
   // указатель на начало кольцевого буфера данных, заполняемого сервером
	data = (quint16*)configuration.CBInput.buf_start;		
    
	data_help = 0;
     
   // Начать процесс оцифровки
   if (QMX_Start(sys_desc) == QMX_ERR)
   {
         sig_log(tr("Не удалось начать сеанс передачи данных"));
         
         // Аварийное завершение приложения
         QCoreApplication::exit(0);
   };
      
	while (first_signal.size() < CHANNELS*CRV_SIZE)
   {
      // Указатель на последний полученный элемент данных
      data_last = *configuration.CBInput.buf_ptr;
      
      // Организуем цикл оцифровки данных
      for (data_current = data_help; data_current != data_last; data_current += 2)
      {
      
         // Проверка на то, что указатель не перескочил
         // за пределы буфера
         
         if (data_current >= buffer_size)
            data_current = 0;	
         
         if ( (!data_current) && (!data_last) )
            break;
         
         // Записываем данные в контейнер
         first_signal.push_back(data[data_current+1]);
      }
      
      data_help = data_last;     
   } 
   
   // Остановка принятия данных от сервера
   QMX_Stop(sys_desc, QMX_STOP_ALL);
   
   // Расчитываем на сколько мы считали больше, чем 8192 точек
   quint16 balance = first_signal.size() - CHANNELS*CRV_SIZE;
   // Редактируем до необходимого нам размера
   first_signal.remove(first_signal.lastIndexOf(first_signal.last()) - balance, balance);
   
   
   // Запуск процесса сглаживания сигнала
   
   // Если окно сглаживания
   if (window == 1)
   {  
      // Нет необходимости проводить процесс сглаживания
      for (quint16 channel = 0; channel < CHANNELS; channel++)
      {
         // Перезаписываем данные в нужной последовательности
         // в вектор под обработанный сигнал
         for (quint16 current = channel; current < first_signal.size(); current+=CHANNELS)
         {
            last_signal.push_back(first_signal.at(current));
         }
      }
      // Сразу же анализируем данные
      sl_analisis();
   }   
   else
   {
      // В противном случае
      // проводим сглаживание
      sl_processing();
   }
  
};
//-----------------------------//


// Слот имитации аналогового сигнала

void qmbox_t::sl_imit_input_data(void)
{
	// Отсчет
	double count = 0.0;
	// Частота синусоиды
	qint8 frequency = 5;
   
   // Искусственно генерируем по 1024 точки на каждый канал
   for (quint16 number = 0; number < CRV_SIZE; number++)
	{
      double noise = rand()%101-50;
      
      // На все 8 каналов
      for (int i = 1; i <= CHANNELS; i++)
      {
         first_signal.push_back((((i*100)*sin(2.*M_PI*frequency*count)+noise)/1000+10)*COEFF);
      }   
      count+=0.01;    
	}
    
   // Запуск сглаживания
   sl_processing(); 
};
//---------------------------------//


// Слот, выполняющий процедуру сглаживания сигнала
// В программе будет использоваться алгоритм "скользящей средней"

void qmbox_t::sl_processing(void)
{      
   // Расчет пределов справа/слева "текущей" позиции 
   quint8 width_window = (window - 1)/2;
   // Окно с учетом всех каналов
   quint16 width_all = CHANNELS*width_window;
	 
	// Индекс последней оцифрованной точки
	quint16 last_index = first_signal.lastIndexOf(first_signal.last());
  
  
   for (quint8 number = 0; number < CHANNELS; number++)
   {
      last_signal.push_back(first_signal.at(number));
		qint16 counter = 1;
		
		// В начальной стадии делаем максимально-допустимое для текущей точки окно
		
      for (quint16 current = CHANNELS + number; current < width_all; current+=CHANNELS)
      {
         counter++;
         quint32 sum = 0;
         for (quint16 limit = number; limit <= (current + (counter-1)*CHANNELS); limit+=CHANNELS)
         {
            sum += first_signal.at(limit);
         }
         last_signal.push_back((quint16)(sum/((counter*2) - 1)));
      }
		//------------------------------------------------------------------------
		
		// Здесь используем заданное окно усреднения
		
		for (quint16 current = width_all + number; current <= last_index - width_all ; current+=CHANNELS)
      {
         quint32 sum = 0;
         for (quint16 limit = current - width_all; limit <= current + width_all; limit+=CHANNELS)
         {
            sum += first_signal.at(limit);
         }
         last_signal.push_back((quint16)(sum/window));
		}

		//---------------------------------------------
		
		// В конечной стадии делаем максимально-допустимое для текущей точки окно
		
		for ( quint16 current = last_index - width_all + 1; current < last_index; current+=CHANNELS)
		{
         counter--;
			quint32 sum = 0;
			for (quint16 limit = current - (counter*CHANNELS) + number; limit <= last_index ; limit+=CHANNELS)
			{
				sum += first_signal.at(limit);
			}
			last_signal.push_back((quint16)(sum/((counter*2) + 1)));
		}
		//-----------------------------------------------------------------------	
   }
     
   sl_analisis();
};
//-----------------------------------------------------------//


// Слот анализа, поступающих с АЦП устройства QMS10 сигналов

void qmbox_t::sl_analisis(void)
{
   // Очищаем контейнер с исходным сигналом (освобождаем память)
	first_signal.clear();
   
   QTime time = QTime::currentTime();
   
   // Проверяем данные по-канально
	for ( quint8 number = 0; number < CHANNELS; number++)
   {
      // Максимальной устанавливаем первую точку на
      // текущем канале
      double max = (((last_signal.at(number*CRV_SIZE)+1)/COEFF)-10)*MVOLT;
      bool check = false;
		for (quint16 current = (number*CRV_SIZE)+1; current < (number+1)*CRV_SIZE - 1; current++)
      {
         // Проверка на событие "Тревога"
         if (fabs(((last_signal.at(current)/COEFF)-10)*MVOLT) >= 500.00)
         {
            // Флаг события на данном канале
            check = true;
            // Увеличиваем счетчик событий тревог на канале
            alarm_counter[number]+=1;
            // Вызов слота для анализа события "Тревога"
            sl_event(time, number_event, number, (last_signal.at(current)/COEFF-10)*MVOLT);
            // Увеличиваем счетчик событий тревог
            number_event++;
            break;
			}
         // Проверка на событие "Охрана"
         else
         {  
            // Найдём пиковое значение шума
            // на канале
            if (fabs((last_signal.at(current)/COEFF-10)*MVOLT) > fabs(max))
               max = (last_signal.at(current)/COEFF-10)*MVOLT;
         } 
        
      }
      
      // Если "тревоги" на канале не было
      if (check == false)
      {
         // Восстанавливаем счетчик подсчета событий тревог
         // по каналу в исходное состояние.
         alarm_counter[number] = 0;
         // Если превысило 100 мВ
         if (fabs(max) >= 100.00)
         {
            // Передаем максисальное значение амплитуды, номер канала
            // для определения типа события
            sl_event(time, number_event, number, max);
            number_event++;
         }
      }
      
   }
   
   // Очищаем данные
   last_signal.clear(); 
};
//------------------------------------------


// Слот отправки данных о событии "Тревога"

void qmbox_t::sl_event(QTime time, quint32 number_event, quint8 number, double max)
{

   // Структура с данными о событии
   event_data_t alarm_signal;
   bool flag = false;
   
   // Если событие "Охрана"
   if (fabs(max) < 500.00)
   {  
      alarm_signal.ev_type = 0;
   }
   else
   {
      // Если события "Тревога" длятся < 60 секунд
      if (alarm_counter[number] < 60)
         // Событие "Тревога"
         alarm_signal.ev_type = 1;
      else
      {
         // Cобытие "Тревога > 60 секунд"
         alarm_signal.ev_type = 2;
         flag = true;
      }
   }
   
   alarm_signal.noise_level = max;
   alarm_signal.ev_number = number_event;
   alarm_signal.ch_number = number;
   alarm_signal.ev_time = time;
   
   
   if (signals_fn.isEmpty())
   {
      // Имя в файла под аналоговый сигнал
      signals_fn = "../data/signal["+
      current_date_time.toString("dd.MM.yyyy hh-mm-ss")+"].dat";
   }
   
   if (!flag)
   {
      // Создаем файл
      QFile sdb(signals_fn);
      // Создаём поток вывода
      QDataStream	out(&sdb);
      // Режим работы "Добавлять в конец файла"
      sdb.open(QIODevice::Append);
      
      // Осуществляем потоковый вывод в файл
      // аналогово сигнала по текущему каналу
      for (quint16 current = number*CRV_SIZE; current < (number+1)*CRV_SIZE; current++)
      {    
         out << last_signal.at(current);
      }
      
      // Завершаем работу с файлом
      sdb.close();
   }
  
   if (events_fn.isEmpty())
   events_fn="../data/events["+
   current_date_time.toString("dd.MM.yyyy hh-mm-ss")+"].gal";
   
   // Инициализирует имя загруженного сеанса 
   emit sig_send_filename(events_fn);
    
   // Создаём файл
   QFile edb(events_fn);
   // Создаём поток вывода
   QDataStream	out_event(&edb);
   // Режим работы "Добавлять в конец файла"
   edb.open(QIODevice::Append);
   
   // Осуществляем потоковый вывод 
   // в файл структуры данных о событии
   
   out_event << alarm_signal.ev_number;
   out_event << alarm_signal.noise_level;
   out_event << alarm_signal.ch_number;
   out_event << alarm_signal.ev_type;
   out_event << alarm_signal.ev_time;     
   
   // Завершаем работу с файлом
   edb.close(); 
    
   // Испускаем сигнал на отрисовку события
   emit sig_send_type_event(alarm_signal);
   
};
//------------------------------------------

// Слот установки окна сглаживания

void qmbox_t::sl_establish_smooth(int window_smooth)
{
   window = window_smooth;
};
//---------------------------------

// Выход из программы
void qmbox_t::quit(void)
{	
   // Задаем режим запуска сеанса передачи данных и отдельно взятых модулей - ручной.
	QMX_MOD_SetStartMode(sys_desc, 0xFF, QMX_START_MODE_MANUAL);
   
   // Освобождает ресурсы USB перед выходом из программы.
	QMX_CircBufDetach(sys_desc);
 	
   // Удаляем файл буфера
   QFile("../data/buffer.dat").remove();
   
   // Завершаем работу сервера
   ShellExecute(NULL, TEXT("open"), TEXT("../support/qmbox_ds.exe"),
                      TEXT("-s0"), NULL, SW_SHOWNORMAL);
   
   sig_log(tr("Завершение работы программы"));
           
   // Выходим из программы
   QCoreApplication::exit(0);
   	
};
//-----------------------------------------------------------