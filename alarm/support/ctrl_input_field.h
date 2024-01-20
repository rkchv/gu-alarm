// $Id $
#ifndef __CTRL_INPUT_FIELD_H
   #define __CTRL_INPUT_FIELD_H
//
// ������������ ���� ������ ���������� ��������������� ��������� �������
//
//    ctrl_input_field_t  - ����� �������� � �������������� ����� �����/������ � 
//                          ������������� ������� � ���������� �����, 
//                          ����������� ��������
//
// �����������:
//
//   ������� �.�.
// (�) fan, 2009, ��� "��������-��"
//
//============================================================================== 
#include <iostream>
#include <sstream>
#include <string>
#include <QtCore>

//==============================================================================
#include <QDoubleSpinBox>

// ���� ���������� ������ ���������� spinbox tab_spin_box_t 
class tab_spin_box_t : public QDoubleSpinBox
{
   Q_OBJECT
   
public: 
   
   // �����������
   tab_spin_box_t( const double *atab, int elems, QWidget *aparent = 0 );
   
   // ��������� ��������� �������� �� ������ double 
   virtual QString textFromValue( double value ) const;
   
   // ����������� ��������� ���������� ������������� � double
//   virtual double valueFromText( const QString &text ) const;
   
   // ������� �� �������
   int  get_index( double dd );
      
private:
      
   const double *tabd; 
   int           elements;
   int           index;

};
 
#endif  //__CTRL_INPUT_FIELD_H



