// $Id$
#ifndef __GUI_GURZA_ALARM_H
#define __GUI_GURZA_ALARM_H

#include <QtGui>
#include <QGraphicsView>
#include <QGraphicsScene>
//#include "serv_diag.h"
#include "exchange.h"
//#include "mmb_usb3000.h" 
#include "draw.h"
#include "adc.h"
//#include "cycle_timer.h"                  
#include "ui_gurza_alarm.h"

//------------------------------------------------------------------------------
// класс основного GUI программы управления стенда 
class gui_gurza_alarm
: 
	    public  QMainWindow,
	    private Ui::MainWindow
{
    Q_OBJECT
    
signals:

   // сигнал на открытие файлового диалога
   void sig_open_file();
   
   // сигнал на корректное завершение работы приложения
   void sig_exit();   
      
public slots:
   
   // Слот начала работы
   void sl_start(void);
   
   // Режим работы (ручной/автоматический)
   void sl_set_mode(bool checked); 
   
   // Установка размера счетчика тревог
   void setDigitCount(int numDigits);
   
   // Запись в лог-файл
   void sl_log(QString s);
   


public:
   
   // конструктор основной формы стенда  
   gui_gurza_alarm( void );
   
   // деструктор 
   ~gui_gurza_alarm( void );
   
private:
         
   // управление представлением графических данных о сигнале
   signal_plot_t     *p_signal_plot;
     
   QDoubleSpinBox    *sb_ampl;         // регулировка амплитуды
   QSpinBox          *sb_scale;        // регулировка масштаба
   QSpinBox          *sb_smooth;       // регулировка окна сглаживания
   QSlider           *slider;           // прокрутка окна первичного сигнала
      
   QHBoxLayout       *hl_lbl;          // компоновщик элементов управления 
   //QSpacerItem       *spacer;
        
   QLabel            *lbl_ampl;        //подписи спинбоксов
   QLabel            *lbl_scale;
   QLabel            *lbl_smooth;
   
   QLabel            *lbl_sig_title;   // заголовок окна сигнала
   
   // управление представлением графических данных о событиях  
   QTableWidget      *p_event_plot; 
   
  
   // органы управления панелью каналов
   

   QScrollBar    *scroll;              // скролл управления окном событий 
   QTimer        *adc_timer;           // Таймер запуска оцифровки данных
   
   bool          mode;                 // флаг режима (Ручной/Автоматический) 
   
   QDateTime  current_date_time;       // дата/время текущего сеанса   
   
protected:
   
   void closeEvent(QCloseEvent *event);
     
};
#endif   //__GUI_LOGGER_H
