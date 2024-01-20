// Реализация методов класса управления ЦАП модуля USB3000
// Дата создания: 20-февраля-2013 г.

#ifndef __USB3000_H 
#define __USB3000_H

#include <QLibrary>
#include <QDateTime>
#include <QtCore>
#include <QTextStream>
#include <QMessageBox>
#include <QTime>
#include "Rtusbapi.h"
#include <math.h>

class usb3000_t: public QObject

{

Q_OBJECT

public:
	usb3000_t();
   
	// Метод проверки доступа к модулю USB3000
   
	bool checking(void);
	
public slots:

   void sl_establish_type(int);
   void sl_establish_noise(int);
   void sl_establish_amplitude(double);
   void sl_establish_lower(int);
   void sl_output_data(void);
	void sl_exit(void); // слот выход из приложения
	
private:

	IRTUSB3000  *usb3000_module;	// Указатель на модуль usb3000
	char 		    module_name[10];	// Полное название модуля
	RTUSB3000::	 DSP_INFO data_driver; // Структура данных информации о драйвере
	RTUSB3000::	 FLASH data_flash;	// Структура данных для работы с ППЗУ
	RTUSB3000::	 OUTPUT_PARS data_dac;	// Структура данных работы с ЦАП
	SHORT 		 dac; //  канал ЦАП
	QLibrary 	 usb3000_library; // Динамическая библиотека для работы с модулем USB3000	
   
   int         type;
   int         noise;
   double      amplitude;
   int         lower;
   double      x;
   
};
 #endif