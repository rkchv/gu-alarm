//------------------------------------------------------------------------------
// модуль методов графического интерфейса регистратора
// 
// реализует следующе функции:
//   - устанавливает основное окно приложения
//   - создаёт объект панели управления и встраивает его в 
//     основное окно приложения
//   - создаёт объект графического окна и встраивает его в основное
//     окно приложения

//------------------------------------------------------------------------------

// Верcия v0.1   11-02-2013 -  Старт разработки программы gurza_alarm
//============================================================================== 

#include <QMessageBox>
#include <QDateTime>
#include <QTextStream>

#include <stdio.h>
                     
#include "exchange.h"
#include "gui_gurza_alarm.h" 

#include "ctrl_input_field.h"

// константы делителя вертикальной шкалы
extern double list_div_y[];

// размер таблицы
extern int dsize;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------ 
// конструктор главной панели
gui_gurza_alarm::gui_gurza_alarm()
   :
      mode(true),
      current_date_time(QDateTime::currentDateTime())
{   
   // устанавливаем   Г  Л  А  В  Н  У  Ю     П  А  Н  Е  Л  Ь   приложения
   setupUi(this);
   
   sl_log(tr("Gurza Alarm ")+
   QDateTime::currentDateTime().toString("dd.MM.yyyy hh-mm-ss")+"\n"+
   "##########################################################");
   
	 adc_timer = new QTimer;      
	   	
   //	Оптимальный минимальный размер без искажения компонентов и их подписей
   setMinimumSize(875, 700);
   
   // Графическое окно отрисовки сигнала
   p_signal_plot = new signal_plot_t(centralwidget, this );

   sl_log(tr("Окно сигнала успешно создано"));  
      
   // создаем визуальный элемент управления делителем оси ординат
   sb_ampl   = new tab_spin_box_t( list_div_y, dsize, centralwidget ); 
   sb_ampl->setSuffix(QString::fromUtf8("  В"));
   sb_ampl->setValue(dsize); 
   
   sb_scale   = new QSpinBox();  // регулирует масштаб оси х
   sb_smooth  = new QSpinBox();  // регулирует окно сглаживания
   
   slider = new QSlider();
   slider->setOrientation(Qt::Horizontal);
   slider->setRange(0, CRV_SIZE);   
      
   lbl_ampl   = new QLabel(QString::fromUtf8("Амплитуда (В/деление)"));
   lbl_scale  = new QLabel(QString::fromUtf8("Масштаб"));
   lbl_smooth = new QLabel(QString::fromUtf8("Окно сглаживания"));

   // Устанавливаем шрифт меток         
   lbl_ampl->setFont(QFont(FONT));
   lbl_scale->setFont(QFont(FONT)); 
   lbl_smooth->setFont(QFont(FONT));
    
   lbl_ampl->setWordWrap(true);
   lbl_scale->setWordWrap(true); 
   lbl_smooth->setWordWrap(true);    
    
   // Заголовок окна сигнала
   lbl_sig_title = new QLabel(QString::fromUtf8("Исходный сигнал"));
   lbl_sig_title->setAlignment(Qt::AlignHCenter | Qt::AlignTop);	
   lbl_sig_title->setFont(QFont(FONT, 16) );	
   
   sl_log(tr("Созданы элементы интерфейса "));
   
   hl_lbl    = new QHBoxLayout();

   
   // Кладем визуальные компоненты в компоновщики
   
   // Регулировка масштаба у   
   hl_lbl->addWidget(lbl_ampl);
   hl_lbl->addWidget(sb_ampl);
   
   // Регулировка масштаба х
   hl_lbl->addWidget(lbl_scale);
   hl_lbl->addWidget(sb_scale);

   // Регулировка окна сглаживания
   hl_lbl->addWidget(lbl_smooth);
   hl_lbl->addWidget(sb_smooth);   
   
   vl_signal->addWidget(lbl_sig_title);
   vl_signal->addWidget(p_signal_plot);
   vl_signal->addWidget(slider);   
   vl_signal->addLayout(hl_lbl);
   
   sl_log(tr("Графические компоненты уложены в компоновщики "));  
   
   // Создаем окно событий
   p_event_plot  = new event_plot_t(centralwidget);
   p_event_plot->setRowCount(CHANNELS);
   p_event_plot->setColumnCount(0);
   p_event_plot->setAutoScroll(true);	
	 vl_events->addWidget(p_event_plot, 0, 0);
	 
   sl_log(tr("Окно событий успешно создано "));   	 	 
     
   // Устанавливает свойства прочих компонентов
	 rb_auto->setChecked(true);
	 t_e->setTime(QTime::currentTime());
   sb_scale->setMinimum(MIN_SCALE);
   sb_scale->setMaximum(MAJ_SCALE);
   sb_smooth->setMinimum(MIN_SCALE);
   sb_smooth->setMaximum(MAJ_SCALE + 1);
   sb_smooth->setSingleStep(2);
      
	 // Создаем отдельный поток, и помещаем в него наши объекты
	      
   QThread draw_thread;
   draw_thread.start();
   p_signal_plot->moveToThread(&draw_thread);                                                    
   p_event_plot->moveToThread(&draw_thread);
   
   sl_log(tr("Объекты отображения успешно перемещены в отдельный поток "));     
   
   // Создание объекта для работы с системой сбора данных   
   
   qmbox_t *device = new qmbox_t;
   QThread adc_thread; 
  
   // Старт генерации тестовых данных   
   connect(bt_start, SIGNAL(clicked()), this, SLOT(sl_start()));
   
   // Останавка чтения/генерацим данных (автоматический режим)  
   connect(bt_stop, SIGNAL(clicked()), adc_timer, SLOT(stop()));
   
   // 
   connect(bt_quit, SIGNAL(clicked()), device, SLOT(quit()));   
   
   // Устанавка режима работы(ручной/автоматический)
   connect(rb_auto, SIGNAL(toggled(bool)), this, SLOT(sl_set_mode(bool))); 
    
   // При переключении в автоматический режим посылаем имя файла
   // для последующего отображения текущего сеанса
   connect(rb_auto, SIGNAL(toggled(bool)), device, SLOT(sl_send_fn(bool))); 
       
   // Загрузка текущего сеанса (в это время время просматривается другой сеанс) 
   connect(rb_auto, SIGNAL(toggled(bool)),
	      p_event_plot, SLOT(sl_load_session(bool)));  
	      
	 // загрузка выбранного сеанса для просмотра при переключении в ручной режим
   connect(rb_manual, SIGNAL(toggled(bool)),
	      p_event_plot, SLOT(sl_load_session(bool))); 
	      
   // Перемещение таблицы к заданному timeedit'ом времени    
   connect(t_e, SIGNAL(timeChanged(const QTime &)),
           p_event_plot, SLOT(sl_move(const QTime &)));
           
   // Изменение масштаба осей координат спинбоксами            
   connect( sb_scale, SIGNAL(valueChanged(int)),
            p_signal_plot,  SLOT(sl_set_x_scale(int))); 
           
   connect( sb_ampl, SIGNAL(valueChanged(double)),
            p_signal_plot,  SLOT(sl_set_y_scale(double)));
            
   connect( sb_smooth, SIGNAL(valueChanged(int)),
            device,  SLOT(sl_establish_smooth(int))); 
            
   connect( slider, SIGNAL(valueChanged(int)),
           p_signal_plot,SLOT(scrollBotAxis(int)));             
            
   // Запуск оцифровки по таймеру
	 connect(adc_timer, SIGNAL(timeout()),
	       device, SLOT(sl_choice_mode()));          
                         	             
   // Сообщение имени файла другому классу (ручной режим)
   connect(p_event_plot, SIGNAL(sig_send_filename(QString)),
   	       p_signal_plot, SLOT(sl_set_filename(QString))); 
   	       
   // Генерация события (ручной режим)
   connect(p_event_plot, SIGNAL(sig_send_event(event_data_t)),
   	           p_event_plot, SLOT(sl_add_event(event_data_t)));   	          
 
   // Чтение данных и отображение сигнала по щелчку на ячейку   
   connect(p_event_plot, SIGNAL(cellClicked(int, int)),
           p_signal_plot, SLOT(sl_draw_sig(int, int)));                	                   
   
   // Отображение текущего значения частоты
   connect(p_signal_plot, SIGNAL(sig_set_freq(QString)),
           edit_frq, SLOT(setText(QString)));   
    
   // Отображение информации в статусбаре        
   connect(p_signal_plot, SIGNAL(sig_show_message(QString)),
               statusbar, SLOT(showMessage(QString)));             

   connect(p_event_plot, SIGNAL(sig_show_message(QString)),
                statusbar, SLOT(showMessage(QString)));
                
   connect(device, SIGNAL(sig_show_message(QString)),
               statusbar, SLOT(showMessage(QString)));
               
   // Запись в лог-файл      
   connect(p_signal_plot, SIGNAL(sig_log(QString)),
               this, SLOT(sl_log(QString)));             

   connect(p_event_plot, SIGNAL(sig_log(QString)),
               this, SLOT(sl_log(QString))); 
                
   connect(device, SIGNAL(sig_log(QString)),
               this, SLOT(sl_log(QString)));               
               
   // Отображение количества тревог
   connect(p_event_plot, SIGNAL(sig_set_lcd(int)),
                    lcd, SLOT(display(int)));
                    
   connect(p_event_plot, SIGNAL(sig_set_dig(int)),
                    this, SLOT(setDigitCount(int)));                           
               
   // В случае ручного режима вызываем файловый диалог
   connect(this, SIGNAL(sig_open_file()), p_event_plot, SLOT(sl_open_file())); 	          
	              
   // Завершение приложения (на "Крестик")
   connect(this, SIGNAL(sig_exit()), device, SLOT(quit()));
  

   // Доступ к интерфейсу системы не получен
   if (!device->checking())
   {
       
       sl_log(tr("Программа запущена в режиме имитации "));        
       
       setWindowTitle(QString::fromUtf8("Гюрза - аларм [Режим имитации] ")+
         QDateTime::currentDateTime().toString());
       // Устанавливаем режим имитатора сигнала
       device->mode = false;
       
       // Сообщение имени файла другим классам (автоматический режим)
       connect(device, SIGNAL(sig_send_filename(QString)),
       	       p_signal_plot, SLOT(sl_set_filename(QString)));
       
       connect(device, SIGNAL(sig_send_filename(QString)),
       	       p_event_plot, SLOT(sl_set_filename(QString)));   	            	       
            
       // Генерация события (автоматический режим)
       connect(device, SIGNAL(sig_send_type_event(event_data_t)),
       	          p_event_plot, SLOT(sl_add_event(event_data_t)));              
   }
   else
   {   
       setWindowTitle(QString::fromUtf8("Гюрза - аларм [Режим оцифровки] ")+
         QDateTime::currentDateTime().toString());
       // Устанавливаем нормальный режим работы
       device->mode = true;
       
       rb_manual->setEnabled(false);

       adc_thread.start();       
       device->moveToThread(&adc_thread); 
       
       sl_log(tr("Программа запущена в режиме оцифровки "));
         
       sl_log(tr("Объект оцифровки успешно перемещен в отдельный поток"));  
         
                
       
       // Сообщение имени файла другим классам (автоматический режим)
       connect(device, SIGNAL(sig_send_filename(QString)),
       	       p_signal_plot, SLOT(sl_set_filename(QString))
       	                      , Qt::BlockingQueuedConnection);
       
       connect(device, SIGNAL(sig_send_filename(QString)),
       	       p_event_plot, SLOT(sl_set_filename(QString))
       	                      , Qt::BlockingQueuedConnection);   	            	       
            
       // Генерация события (автоматический режим)
       connect(device, SIGNAL(sig_send_type_event(event_data_t)),
       	          p_event_plot, SLOT(sl_add_event(event_data_t))
       	                     , Qt::BlockingQueuedConnection);                   

   }
        
};

//------------------------------------------------------------------------------
// деструктор 
gui_gurza_alarm::~gui_gurza_alarm( void )
{
};

// Устанавливаем режим работы (автоматический/ручной)
void gui_gurza_alarm::sl_set_mode(bool checked)
{
   if(checked)
       mode = true;  
   else
      {
       mode = false;
       adc_timer->stop();
       sig_open_file();
      }    
};

// Устанавливает число знаков счётчика тревог
void gui_gurza_alarm::setDigitCount(int numDigits)
{
   lcd->setDigitCount(numDigits);
}

// Начало работы (выбор режима)
void gui_gurza_alarm::sl_start(void)
{
	if (mode)
	  {      
	   adc_timer->start(1000);
	  } 
	else
	  { 
	   adc_timer->stop();
	  }  	
};

// Запись в лог-файл
void gui_gurza_alarm::sl_log(QString s)
{

   QString fn = "../logs/system ["+
   current_date_time.toString("dd.MM.yyyy hh-mm-ss")+"].log";
   
   QFile ldb(fn);
      
   if(!ldb.open(QIODevice::Append))
      statusbar->showMessage(tr("File write Error!"));
   
   // Единственная безопасная функция записи в файл
   else
    {  
      QTextStream	out(&ldb);
      out<<"[" + QTime::currentTime().toString("hh:mm:ss:zzz") + "] "+s+"\n";
      ldb.close();
    }
}

// Корректное завершение работы приложения
void gui_gurza_alarm::closeEvent(QCloseEvent *event)
{
   
   sig_exit();
   event->accept();
}