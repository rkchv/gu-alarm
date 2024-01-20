#ifndef __draw_H
#define __draw_H

#include <QtCore>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QtGui>

#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>  	

#include "exchange.h"	

class   QwtPlotGrid;
class   QwtSlider;

// Определение класса представления сигнала
class  signal_plot_t: public QwtPlot
{
   Q_OBJECT
    
signals:

   // Показывает значение текущего уровня шума
   void sig_set_freq(QString s);
   
   // Отображает сообщение в статусбаре
   void sig_show_message(QString s);
   
   // сообщает соседнему классу о том, что нужны данные о шуме
   void sig_get_data();
   
   // Запись в лог-файл
   void sig_log(QString s);   
   
public slots:
   
   // визуализация  оцифрованных данных
   void sl_draw_sig(int row, int col);
   
   // изменяем ось ординат и абсцисс по отдельности, т.к логически это верно
   void sl_set_y_scale(double index);
   
   void sl_set_x_scale(int scale);
   
   // устанавливает имя файла сеанса
   void sl_set_filename(QString s);
   
   // scroll
   void scrollBotAxis(int value);   
      
public:
   
   // конструктор
   signal_plot_t( QWidget *c_widget, QObject *aparent ); 

   // Чтение внутренних данных о событии
   // для корректного считывания данных о сигнале   
   QVector<int>  read_buffer_data(int row, int col);   
    
   // Чтение данных о сигнале из файла в массив
   // с заданной позиции pos
   void     read_sig_data(int pos);     

private:
   
   QObject       *parent;   
   
   QwtPlotGrid   *grid;           // координатная сетка
   QwtPlotCurve  *sig;            // отрисовка сигнала 
                                  
   short  ord[CRV_SIZE];          // массив ординат в виде двубайтовых слов  
   double dtx[CRV_SIZE];          // массив абцисс  кривой сигнала
   double dty[CRV_SIZE];          // массив ординат кривой сигнала
   
   QDateTime  current_date_time;  // дата/время текущего сеанса
   QString    events_fn;          // имя файла сеанса  
   QString    signals_fn;         // имя файла сигнала
   QString    buffer_fn;          // имя файла буффера
   
   QwtSlider *slider;
   double    scl;
   
};   

//Определение класса представления событий 
class event_plot_t : public QTableWidget
{
   Q_OBJECT
   
signals:
	
	 // сигнал с тестовыми данными
   void sig_test(event_data_t event_data);

   // Отображает сообщение в статусбаре
   void sig_show_message(QString s);
   
   // присылает событие (ручной режим)
   void sig_send_event(event_data_t);
   
   // посылает filename другому классу
   void sig_send_filename(QString s);
   
   // устанавливает счётчик тревог
   void sig_set_lcd(int n);
   
   // устанавливает количество символов счетчика
   void sig_set_dig(int n);
   
   // Запись в лог-файл
   void sig_log(QString s);    
  
         
public slots:  
   
   // Добавление события
   void sl_add_event(event_data_t p_event_data);
   
   // Перемещающение бегунка по таблице
   void sl_move(const QTime &time);
   
   // устанавливает флаги отрисовки по состояниям чекбоксов
   //void sl_set_fl_draw(bool state);
   
   // Открывает файловый диалог
   void sl_open_file();   
   
   // Загрузка сеанса
   void sl_load_session(bool checked); 
   
   // Установка имен файлов
   void sl_set_filename(QString s);  
            

public:
	 
   event_plot_t ( QWidget *parent ); 
   
   // Запись внутренних данных о событии
   // для корректного считывания данных о сигнале
   void write_buffer_data(int ev_num, int noise_lvl, int row, int col);
   
   // Чтение данных о сеансе (ручной режим)
   void read_event_data(); 
   
   // Проверка количества символов
   void check_dig();     
   
private:

   QStringList   list;                // список времен для подписи колонок
   QDateTime     current_date_time;   // дата/время текущего сеанса
   QString       events_fn;           // имя файла сеанса   
   QString       buffer_fn;           // имя файла сигнала
   int           al_count;            // счётчик тревог
   
protected:

   //void timerEvent(QTimerEvent* event);
      
};	

    
#endif 