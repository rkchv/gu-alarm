// Главное графическое окно программы "Имитатор сигнала контрольной точки"
// Дата создания: 15-февраля-2013 г.

#ifndef __IMIT_KT_H
#define __IMIT_KT_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QComboBox>
#include <QSpinBox> 
#include <QProgressBar>
#include <QDoubleSpinBox>
#include <QRadioButton>
#include <QTimer>
#include <QCheckBox>

#include "usb3000.h"
 
class main_window_t : public QMainWindow
{

Q_OBJECT

public:

	// Конструктор
	main_window_t(QWidget *parent = 0);
		
private:
	
   QLabel 			*lb_type_signal; // Надпись "Тип сигнала"
	QLabel 			*lb_level_noise; // Надпись "Уровень шума"
	QLabel 			*lb_amplitude;   // Надпись "Амплитуда"
	QLabel			*lb_lower;		 // Надпись "Снижать амплитуду"
   QComboBox 		*cb_signal_type; // Список "Тип сигнала"
	QSpinBox 		*sp_level_noise; // Счетчик "Уровень шума"
	QDoubleSpinBox *dsp_amplitude;  // Счетчик "Амплитуда"
	QGroupBox 		*gb_group;	     // Группирующая панель
   QPushButton 	*bt_start;		 // Кнопка старта генерации
   QPushButton 	*bt_stop;
	QPushButton		*bt_exit;	   // Кнопка остановки выхода из приложения
	QCheckBox	   *ch_lower;	   // Флаг выбора затухания сигнала
};
 #endif