// $Id $
// ���������� ������� ������ �������� � �������������� ����� ����� � 
// ���������� �����, ����������� �������� � ��������������� ������� QLineEdit 
//
// ����� � ���������� ���� �������������� � �����: 000 000 000.00
//
// �� ��������� ���������������:
//   ���������� ������ ����� ������� ������ 2
//   �������� ������ ��������.
//
// ���� ��������: 12-���-2009�.
//
// �����������:
//   ������� �.�.
// (�) fan, 2009, ��� "�������� ��"
//
//******************************************************************************
#include <iostream>
#include <QLineEdit>
#include <QTextStream>

#include "ctrl_input_field.h"

// ���������� ������������� ����� ����������� � ��������� ����������
extern  FILE  *file_log;

//------------------------------------------------------------------------------
//     ����� ������������� ��������� ����� �������
//==============================================================================
tab_spin_box_t::tab_spin_box_t(const double *atab, int elems, QWidget *parent )
:
   QDoubleSpinBox( parent ),
   tabd          ( atab   ),
   elements      ( elems  )
{                
   setRange( 0, elements-1 ); 
}; 
//------------------------------------------------------------------------------
//    
QString tab_spin_box_t::textFromValue( double value ) const
{     
   QString str;
   return str.setNum( *( tabd +(int)value ), 'g', 4 );
};
//------------------------------------------------------------------------------
// �������� ��������� ������
int  tab_spin_box_t::get_index( double dd )
{
   for( int i = 0; i < elements; i++ )
   {
      if( dd < *(tabd + i ) )
         return( i - 1 );
   };   
   return (elements - 1 );
}; 
//------------------------------------------------------------------------------