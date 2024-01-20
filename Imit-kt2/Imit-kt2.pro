TEMPLATE = app
DESTDIR  = ./bin
CONFIG  += warn_on
TARGET   = Imit-kt

DEPENDPATH  += . source drivers/usb3000 
INCLUDEPATH += . source drivers/usb3000 

HEADERS += source/imit_kt.h \
		   source/usb3000.h
		   
SOURCES  = source/main.cpp \
		   source/imit_kt.cpp \
		   source/usb3000.cpp