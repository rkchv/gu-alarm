//------------------------------------------------------------------------------
// Модуль методов графического отображения событий и аналогового сигнала тревоги
// Реализует следующе функции:
//   - Отображение событий в графическом окне (таблице)
//   - Чтение из файла данных об исходном сигнале события "Тревога"
//     в регламентированном виде двубайтовых слов данных
//   - Преобразование данных о сигнале в удобную для отображения форму
//   - Отображение сигнала в виде графика
//   - Вывод текущего уровня шумов для собтия "Охрана" поканально

//------------------------------------------------------------------------------

// Верcия v0.1   11-02-2013 -  Старт разработки программы gurza_alarm
//============================================================================== 
#include <QtAlgorithms>
#include <QFileDialog>
#include <QMessageBox>

#include <stdlib.h>

#include <qwt_painter.h>
#include <qwt_plot_canvas.h>
#include <qwt_scale_widget.h>
#include <qwt_plot_grid.h>
#include <qwt_legend.h>
//#include <qwt_scale_draw.h>
#include <qwt_text_label.h>
#include <qwt_slider.h>

#include "draw.h"


// константы делителя вертикальной шкалы
double list_div_y[] = { 0.001, 0.002, 0.003, 0.004, 0.005,
                        0.01,  0.02,  0.03,  0.04,  0.05,
                        0.1,   0.2,   0.3,   0.4,   0.5,
                        1,     2,     3};
                        
// размер таблицы                              
int dsize = sizeof( list_div_y )/sizeof( double ); 

//##############################################################################
//##                    РЕАЛИЗАЦИЯ КЛАССА ОТОБРАЖЕНИЯ СИГНАЛА                 ##
//##############################################################################

// Чтение данных о событии из файла
QVector<int> signal_plot_t::read_buffer_data(int row, int col)
{
   // Считываем данные о событии из файла
   // для определения его положения относительно таблицы событий     
   
   buffer_fn = "../data/buffer.dat";
     
   QFile edb(buffer_fn);  
   if(!edb.open(QIODevice::ReadOnly))
     sig_show_message("File read Error! "+buffer_fn);
   
      
   QDataStream	in(&edb);	  
   
   // инициализируем вектор
   
   QVector<int> misc(4, -1); 

    
//####################################################################
//###################   Структура   вектора  misc  ###################
//###################       (вектор буфера)        ###################
//####################################################################
//#                                                                  #
//#   	               misc[0];   // № события                       #
//#   	               misc[1];   // уровень шума                    #
//#   	               misc[2];	  // строка                          #
//#   	               misc[3];   // столбец                         #
//#                                                                  #
//####################################################################
    
   while((misc[2]!=row)||(misc[3]!=col))
   {      
   	
   	
   	in >> misc[0];   // № события
   	in >> misc[1];   // уровень шума
   	in >> misc[2];	 // строка
   	in >> misc[3];   // столбец
   }

   return misc;	       		
};

// Слот отображения сигнала
void signal_plot_t::sl_draw_sig(int row, int col)
{
   // Создаем указатель на таблицу-sender, сгенерировавшую сигнал  
   event_plot_t *p_event_plot = (event_plot_t *)sender();   
   
   // Считываем данные о событии из файла
   // для определения его положения относительно таблицы событий
   clear();
   replot();
   sig_set_freq("");
   
   if((p_event_plot->item(row, col)!=0)&&
      (p_event_plot->item(row, col)->backgroundColor()!=Qt::black))
         
      {  
  
         QVector<int> misc;
   	     
   	     misc = read_buffer_data(row, col);
   	     
   	     // Считываем данные для кривой события из файла
   	     //read_sig_data(read_buffer_data(row, col));
   	     
         read_sig_data(misc[0]);
   	     sig_set_freq(QString::number(misc[1]));
      
   	     // Создаем объект-кривую
   	     sig = new QwtPlotCurve();
   	      
   	     // привязываем её к графическому окну, задаем ей цвет
   	     sig->attach(this);
   	     
         if(p_event_plot->item(row, col)->backgroundColor()==Qt::red)   

             // Карминово-красный цвет 
   	         sig->setPen(QPen(QColor(255, 0, 51)));
   	     else
   	      
   	         // Цвет влюбленной жабы
   	         sig->setPen(QPen(QColor(60, 170, 60)));        
   	          
   	     // задаем данные для кривой  
   	     sig->setData(dtx, dty, CRV_SIZE);  
   	         
   	     replot(); 

      }        
};

// Реализация конструктора
signal_plot_t::signal_plot_t(QWidget *c_widget, QObject *aparent)
 :
   QwtPlot        ( c_widget   ),
   parent         ( aparent    ),
   scl(1024),
   current_date_time(QDateTime::currentDateTime())
{
   
   setCanvasBackground( QColor( Qt::white ));
   grid = new QwtPlotGrid;
   grid->setMajPen ( QPen(Qt::gray,  0, Qt::DotLine ));         
   grid->attach(this);
   
   // We don't need the cache here
   canvas()->setPaintAttribute( QwtPlotCanvas::PaintCached, false );
   canvas()->setPaintAttribute( QwtPlotCanvas::PaintPacked, false );
   		
   // устанавливаем геометрию вспомогательного графического окна
   setObjectName( QString::fromUtf8( "Signal_plot" ));
      
   setFrameShape( QFrame::Panel );
   setLineWidth ( 2 );
          
   setAxisTitle( QwtPlot::yLeft,   tr("Амплитуда, В") );
   setAxisTitle( QwtPlot::xBottom, tr("Время, мс") );

   // инициализируем шкалу значением, которое изначально установлено в спинбоксе
   setAxisScale( QwtPlot::yLeft, -list_div_y[dsize-1]*DIVIZOR_Y,
   							   list_div_y[dsize-1]*DIVIZOR_Y); 
   							   
   setAxisScale( QwtPlot::xBottom, 0, CRV_SIZE);   							   
 
   							   
};

void signal_plot_t::scrollBotAxis(int value)
{
    setAxisScale(xBottom, value, value+scl);
    replot();
}

void signal_plot_t::sl_set_filename(QString s)
{
   events_fn = s;
     
   signals_fn = s.replace("events", "signal");
   
   signals_fn.replace("gal", "dat");
        
};   

// Изменение оси абсцисс
void signal_plot_t::sl_set_x_scale(int scale)
{

	scl = (double)CRV_SIZE/(double)scale;
	// т.к параметр xbot - масштаб, умножаем на размер шкалы
	setAxisScale( QwtPlot::xBottom, 0, scl);
	   
	updateAxes();
	replot();
};

// Изменение оси ординат
void signal_plot_t::sl_set_y_scale(double index)
{   	             
	double yleft=list_div_y[(int)index]*DIVIZOR_Y;
	
	setAxisScale( QwtPlot::yLeft, -yleft, yleft);
	updateAxes();
	replot();
};


//Метод чтения оцифрованных данных из файла в массив
void signal_plot_t::read_sig_data(int pos)
{   
    
	QFile sdb(signals_fn);  
	
	if(!sdb.open(QIODevice::ReadOnly))
   sig_show_message("File read Error! "+signals_fn);
   
	sdb.seek(sizeof(short)*CRV_SIZE*pos);   
	
	QDataStream	in(&sdb);

	double x = COEFF;
	for(int i=0; i<CRV_SIZE; i++)
	{
		in>>ord[i];
		dtx[i]=i;
		dty[i]=(double)ord[i]/(double)x-10;
	}	
};

//##############################################################################
//##                    РЕАЛИЗАЦИЯ КЛАССА ОТОБРАЖЕНИЯ СОБЫТИЙ                 ##
//##############################################################################


// Конструктор
event_plot_t::event_plot_t( QWidget *parent )
	:
		current_date_time(QDateTime::currentDateTime()),
		al_count(0)
{
   //setMaximumHeight(250);
};

//
void event_plot_t::sl_set_filename(QString s)
{
   events_fn = s;
     
   // Передаем имя файла сеанса классу отображения сигнала
   //emit sig_send_filename(s);       
};   

// Установка количества символов для тревоги
void event_plot_t::check_dig()
{
   // Нехорошая конструкция, но как сделать по-другому я не придумал   
   switch(al_count)
      {
          case 10:     sig_set_dig(2); break;
          case 100:    sig_set_dig(3); break;
          case 1000:   sig_set_dig(4); break;
          case 10000:  sig_set_dig(5); break;
          case 100000: sig_set_dig(6); break;              
      }   
};

// Перемещает скроллбар к столбцу с заданным временем
void event_plot_t::sl_move(const QTime &time)
{
    int i=list.indexOf(time.toString());
    scrollToItem(item(0, i));
};

// Открывает файловый диалог выбора сеанса
void event_plot_t::sl_open_file()
{
    QMessageBox::about(this, tr("Файл сеанса"), tr("Выберите файл сеанса!"));
      
    events_fn = QString(QFileDialog::getOpenFileName(this,
     tr("Загрузить сеанс"), tr("../data"), tr("Файлы сеанса (*.gal)")));
     
    // Передаем имя файла сеанса классу отображения сигнала
    sig_send_filename(events_fn);
};

// Запись буферных данных в файл
void event_plot_t::write_buffer_data(int ev_num, int noise_lvl,
                                     int row, int col)
{

   buffer_fn = "../data/buffer.dat";
   
   QFile edb(buffer_fn);   
   if(!edb.open(QIODevice::Append))
      sig_show_message("File write Error!");
       
   QDataStream	out(&edb);
   out << ev_num;
   out << noise_lvl;
   out << row;
   out << col;
};

// обнуление таблицы
void event_plot_t::sl_load_session(bool checked)
{
    if(checked) 
      {
         setColumnCount(0);
         list.clear();
         QFile("../data/buffer.dat").remove();
         al_count = 0;
         check_dig();          
         read_event_data();
      }
};
   
// В ручном режиме считывает из файла события и отображает их
void event_plot_t::read_event_data()
{
        
   event_data_t p_event_data;
     
   QFile edb(events_fn);
   
   QDataStream	in(&edb);
   
	 if(!edb.open(QIODevice::ReadOnly))
      sig_show_message("File read Error! "+events_fn);
           
   while (!edb.atEnd())
     {
      
      in >> p_event_data.ev_number;
      
      in >> p_event_data.noise_level;
      
      in >> p_event_data.ch_number;
      
      in >> p_event_data.ev_type;
      
      in >> p_event_data.ev_time;   
      
             
      sig_send_event(p_event_data);
      
      sig_show_message(tr("Идёт загрузка данных..."));
                             
     }    
   edb.close(); 
   
   sig_show_message(tr("Сеанс от ")+
   events_fn.remove(0, events_fn.indexOf("[")).remove(".gal")+
   tr(" успешно загружен "));
        
   sig_log(tr("Сеанс от ")+
   events_fn.remove(0, events_fn.indexOf("[")).remove(".gal")+
   tr(" успешно загружен"));
       
};
	

// Слот отрисовки события
void event_plot_t::sl_add_event(event_data_t p_event_data)
{
   
   // Если нет колонки с таким временем
   int i=list.indexOf(p_event_data.ev_time.toString());
   if (i==-1)
   {	
     // Добавляем колонку
     setColumnCount(columnCount()+1);   
      
     // Добавляем текущее время в список подписей колонок
     // и сразу присваиваем колонкам все имещиеся подписи
     list<<p_event_data.ev_time.toString();
     setHorizontalHeaderLabels(list);
     
     // делаем столбец readonly
     setEditTriggers(QAbstractItemView::NoEditTriggers);
     resizeRowsToContents();
     resizeColumnsToContents(); 
       
   }     
   
   // Закрашиваем цветом , зависящим от режима события
   switch(p_event_data.ev_type)
   {
    case 0:
     {	        	        		  
       // Создаем пустой итем, т.к. только у итема есть
       // свойство backgroundColor
       
       // (Примечание: В будущем можно создавать не пустую текстовую строку,
       //  а, например, со словами "Охрана", "Тревога" и "Отказ" соответственно)
       
       setItem(p_event_data.ch_number, columnCount()-1, new QTableWidgetItem(""));
       
    	 item(p_event_data.ch_number,
    	 columnCount()-1)->setBackgroundColor(Qt::green);  
    	 	
    	 // Записываем в файл уровень шума, и столбец/строку
    	 // для определения положения события относительно таблицы в будущем
       write_buffer_data(p_event_data.ev_number, p_event_data.noise_level,
                           p_event_data.ch_number, columnCount()-1); 
                           		       	
      break; 
     } 
    case 1:
     {                               	   
       setItem(p_event_data.ch_number,
               columnCount()-1, new QTableWidgetItem(""));
               
       item(p_event_data.ch_number,
            columnCount()-1)->setBackgroundColor(Qt::red);
              	   	
    	 // Записываем в файл № события и столбец/строку
    	 // для определения положения события относительно таблицы в будущем         
       write_buffer_data(p_event_data.ev_number, p_event_data.noise_level,
                         p_event_data.ch_number, columnCount()-1);
                         
       al_count++;
       check_dig();                     
       sig_set_lcd(al_count);
          	
    	break;
     }	
    case 2:
     { 	
    	   setItem(p_event_data.ch_number, columnCount()-1, new QTableWidgetItem(""));
    	   item(p_event_data.ch_number,
    	   columnCount()-1)->setBackgroundColor(Qt::black);
         break;
     } 	
     		
   }	
   
   //	прокручиваем таблицу вперед                                  	
   scrollToItem(item(p_event_data.ch_number, columnCount()-1));
   
};