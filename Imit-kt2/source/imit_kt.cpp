#include "imit_kt.h"
#include <QMessageBox>

// Конструктор главного окна *OK
main_window_t::main_window_t(QWidget *parent):QMainWindow(parent)
{	

	////// Установка параметров главного окна ///////
	
	setGeometry(480,320,300,230);
	
	// Заголовок главного окна
	QString title = trUtf8("Имитатор сигнала контрольной точки");
    
	// Установка заголовка
	setWindowTitle(title);
    
	// Установка максимального и минимального размера формы
	setMaximumSize(300,230);
	setMinimumSize(300,230);
    
    ///////////////////////////////////////////////////
	
    
	///// Прорисовка панели группировки и установка её свойств //////
    
	gb_group = new QGroupBox(trUtf8("Ввод параметров"),this);
	// Размер, координаты
	gb_group->setGeometry(10,15,275,160);
	// и шрифта
	gb_group->setFont(QFont("Linux libertine G",11,QFont::Bold));
	
    ////////////////////////////////////////////////////
    
	//////////// Прорисовка надписей ///////////////////////////////
	
	// Тип сигнала
	lb_type_signal = new QLabel(trUtf8("Тип сигнала:"),gb_group);
	
	// Размер, координаты
	lb_type_signal->setGeometry(20,25,143,24);
	
	// Уровень шума
	lb_level_noise= new QLabel(trUtf8("Уровень шума:"),gb_group);
	
	// Размер, координаты
	lb_level_noise->setGeometry(20,60,143,24);
	
	// Амплитуда сигнала
	lb_amplitude = new QLabel(trUtf8("Амплитуда:"),gb_group);
	
	// Размер, координаты
	lb_amplitude->setGeometry(20,95,153,24);
	
	// Затухающий сигнал или нет
	lb_lower = new QLabel(trUtf8("Затухающий:"),gb_group);
	lb_lower->setGeometry(20,130,143,24);
	
   ///////////////////////////////////////////////////////////////
    
	
	//////////// Прорисовка полей ввода ///////////////////////////
		
	// Поле выбора значения типа сигнала
	cb_signal_type = new QComboBox(gb_group);

	// Размер, координаты
	cb_signal_type->setGeometry(150,25,110,20);
	
	// Создание списка
	QStringList list_signals;
	
	// Запись данных о типе сигнала
	list_signals<<trUtf8("Шум")<<trUtf8("Синус");

	// Запись данных в cb_signal_type
	cb_signal_type->addItems(list_signals);
   cb_signal_type->setCurrentIndex(1);
	
	// Поле для ввода значения уровня шума
	sp_level_noise = new QSpinBox(gb_group);
	
	// Размер, координаты
	sp_level_noise->setGeometry(150,60,110,20);
   sp_level_noise->setMinimum(1.00);
   sp_level_noise->setValue(100.00);
	
	// Значение суффикса
	sp_level_noise->setSuffix(trUtf8(" мВ"));
	
	// Установка допустимого числа знаков устанавливаемого значения
	sp_level_noise->setMaximum(10000);
	
    ///////////////////////////////////////////////////////////////
    
	
	///// Поле для ввода значения амплитуды сигнала /////
	
	dsp_amplitude = new QDoubleSpinBox(gb_group);	
	// Размер, координаты
	dsp_amplitude->setGeometry(150,95,110,20);
	// Суффикс к значению
	dsp_amplitude->setSuffix(trUtf8(" мВ"));
	// Шаг
	dsp_amplitude->setSingleStep(10);
	// Минимальное значение
	dsp_amplitude->setMinimum(-20.00);
	// Максимальное значение
	dsp_amplitude->setMaximum(10000);
   // Значение по-умолчанию
	dsp_amplitude->setValue(600.00);
    
	/////////////////////////////////////////////////
    
	
	///// Выбор затухает сигнал или нет /////////
	
	ch_lower = new QCheckBox(gb_group);
	ch_lower->setGeometry(150,130,40,20);
	
	/////////////////////////////////////////////
     
	
	/////// Кнопка запуска генерации сигнала ///////
    
	bt_start = new QPushButton(trUtf8("Запуск"),this);
	// Размер, координаты
	bt_start->setGeometry(10,190,50,24);
   
   /////// Кнопка остановки генерации сигнала ///////
    
   bt_stop = new QPushButton(trUtf8("Остановка"),this);
	// Размер, координаты
	bt_stop->setGeometry(70,190,80,24);
    
	//////// Кнопка выхода из приложения ////////
    
	bt_exit = new QPushButton(trUtf8("Выход"),this);
	// Размер, координаты
	bt_exit->setGeometry(160,190,50,24);
    
   /////////////////////////////////////////////
   
   usb3000_t *usb_device = new usb3000_t;
   
	// Если модуль не инициализированн
	if (!usb_device->checking())
	{
	// Выводим сообщение об ошибке
	QMessageBox::warning(0,trUtf8("Ошибка"), 
						trUtf8("Модуль работает некорректно!" 
						"\n Подробнее в log-файле!"),
						trUtf8("Ok"),
						QString(), 
						0, 
						1);
	// Завершаем приложение
	exit(0);					
	}
   
   QTimer *timer = new QTimer;
   
   connect( timer, SIGNAL(timeout()), usb_device, SLOT(sl_output_data(void)));
   
   connect( bt_start, SIGNAL(clicked()), timer, SLOT(start()));
   connect( bt_stop, SIGNAL(clicked()), timer, SLOT(stop()));
   connect( bt_exit, SIGNAL(clicked()), usb_device, SLOT(sl_exit()));
   
   connect( cb_signal_type, SIGNAL(currentIndexChanged(int)), 
            usb_device, SLOT(sl_establish_type(int)));
            
   connect( sp_level_noise, SIGNAL(valueChanged(int)), 
            usb_device, SLOT(sl_establish_noise(int))); 

   connect( dsp_amplitude, SIGNAL(valueChanged(double)), 
            usb_device, SLOT(sl_establish_amplitude(double)));
   
   connect( ch_lower, SIGNAL(stateChanged(int)), 
            usb_device, SLOT(sl_establish_lower(int)));
}