// $Id $
#ifndef __CTRL_INPUT_FIELD_H
   #define __CTRL_INPUT_FIELD_H
//
// заголовочный файл класса реализации вспомогательных служебных классов
//
//    ctrl_input_field_t  - класс контроля и форматирования полей ввода/вывода с 
//                          фиксированной запятой с выделением триад, 
//                          разделенных пробелом
//
// разработчик:
//
//   Федотов А.Н.
// (с) fan, 2009, ООО "ФРАКТАЛЬ-СБ"
//
//============================================================================== 
#include <iostream>
#include <sstream>
#include <string>
#include <QtCore>

//==============================================================================
#include <QDoubleSpinBox>

// файл заголовков класса табличного spinbox tab_spin_box_t 
class tab_spin_box_t : public QDoubleSpinBox
{
   Q_OBJECT
   
public: 
   
   // конструктор
   tab_spin_box_t( const double *atab, int elems, QWidget *aparent = 0 );
   
   // формирует табличное значение на основе double 
   virtual QString textFromValue( double value ) const;
   
   // преобразует табличное символьное представление в double
//   virtual double valueFromText( const QString &text ) const;
   
   // выборка из таблицы
   int  get_index( double dd );
      
private:
      
   const double *tabd; 
   int           elements;
   int           index;

};
 
#endif  //__CTRL_INPUT_FIELD_H



