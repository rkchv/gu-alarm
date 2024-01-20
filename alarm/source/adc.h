// Класс управления многоканальным АЦП

#ifndef __ADC_H 
#define __ADC_H

#include <QLibrary>
#include <QTextStream>
#include <QMessageBox>
#include <QFile>

#include "qmx.h"
#include "gui_gurza_alarm.h"
#include "exchange.h"

class qmbox_t: public QThread

{

Q_OBJECT

public:

   // Конструктор
   qmbox_t();
      
   // Доступ к модулю qmbox
   bool checking(void);

public slots:

   // Слот установки режима работы программы
   void sl_choice_mode(void);
      
   // Слот имитации ввода данных с АЦП
   void sl_imit_input_data(void);
   
   // Слот ввода данных с АЦП
   void sl_input_data(void);
   
   // Слот сглаживания сигнала
   void sl_processing(void);
    
   // Слот анализа полученных данных
   void sl_analisis(void);
   
   // Слот записи события тревоги в бинарный файл
   void sl_event(QTime time, quint32 number_event, quint8 number, double max);
   
   // Завершение работы приложения
   void quit(void);   
   
   // Сообщение имени файла другим модулям
   void sl_send_fn(bool checked); 

   // Установка окна сглаживания
   void sl_establish_smooth(int);

signals:

   // Сигнал отправки данных о событии
   void sig_send_type_event(event_data_t data_signal);
   
   // Сигнал о выводе сообщения в статусную строку
   void sig_show_message(QString);
   
   // посылает filename другому классу 
   void sig_send_filename(QString s);
   
   // Запись в лог-файл
   void sig_log(QString s);       
  
private:

   HANDLE             sys_desc;             // Дескриптор системы
   QMX_CONFIG         configuration;        // Конфигурация системы
   QMX_CC_F           ratio[3];             // Массив для калибровочных коэффициентов
   WORD               table_channels[16];   // Таблица опроса каналов
   QVector<quint16>   first_signal;         // Вектор для хранения исходного сигнала
   QVector<quint16>   last_signal;          // Вектор для хранения сглаженного сигнала

   quint32            number_event;         // Абсолютный номер события тревоги
   quint32            alarm_counter[8];     // Массив для хранения 
                                            // количества идущих подряд событий
                                            // тревоги для каждого канала
   
   quint8             window;
   QDateTime          current_date_time;    // Дата/время текущего сеанса
   QString            signals_fn;           // имя файла сигнала 
   QString            events_fn;            // имя файла сигнала      
   
public:
    
   bool               mode;                      // Режим работы
    
   
};
 #endif