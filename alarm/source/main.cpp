
//============================================================================== 
#include <QApplication>           
#include <QMainWindow> 
#include <QDateTime>
#include <QTextStream>

#include <stdio.h>
                                       
#include "gui_gurza_alarm.h"  

                                               
int main(int argc, char *argv[]) 
{

   QApplication app(argc, argv);
   QApplication::setStyle(new QPlastiqueStyle);
   QTextCodec *codec = QTextCodec::codecForName( "UTF-8" );
   QTextCodec::setCodecForTr( codec );   
   gui_gurza_alarm *gui = new gui_gurza_alarm;      
   gui->show();   
   return app.exec(); 
};

