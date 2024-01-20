################################################################################
# for building release / debug version of application? change 1-2-3 points
# Install paths
################################################################################
# версия QWT (устанавливается вручную для однозначной ссылки к библиотекам)

VER_MAJ      = 5
VER_MIN      = 2
VER_PAT      = 1

VERSION      = $${VER_MAJ}.$${VER_MIN}.$${VER_PAT}

QWT_ROOT = c:/qwt-$$VERSION

unix {
   INSTALLBASE = /usr/local/qwt-$$VERSION
}

win32 {
   INSTALLBASE = C:/Qwt-$$VERSION
}

target.path  = $$INSTALLBASE/lib
headers.path = $$INSTALLBASE/include
doc.path     = $$INSTALLBASE/doc
################################################################################
# destination path

DESTDIR      = ./bin

################################################################################
# qmake internal options
################################################################################

TEMPLATE     = app

# point for SET transfert to debug or release  mode
#CONFIG      += qt debud thread exceptions windows 
CONFIG      += qt release thread exceptions windows 

CONFIG      += warn_on
################################################################################
# If you want to have different names for the debug and release 
# versions you can add a suffix rule below.
################################################################################

DEBUG_SUFFIX     = 
RELEASE_SUFFIX   = 

win32 {
    DEBUG_SUFFIX = d
}
################################################################################
# Build the static/shared libraries.
# If QwtDll is enabled, a shared library is built, otherwise
# it will be a static library.
################################################################################

CONFIG       += QwtDll

################################################################################
# QwtPlot enables all classes, that are needed to use the QwtPlot 
# widget. 
################################################################################

CONFIG       += QwtPlot

################################################################################
# QwtWidgets enables all classes, that are needed to use the all other
# widgets (sliders, dials, ...), beside QwtPlot. 
################################################################################

#CONFIG     += QwtWidgets

################################################################################
SUFFIX_STR =

    CONFIG(debug, debug|release) {
        SUFFIX_STR = $${DEBUG_SUFFIX}
    }
    else {
        SUFFIX_STR = $${RELEASE_SUFFIX}
    }
INCLUDEPATH  += $${QWT_ROOT}/src
DEPENDPATH   += $${QWT_ROOT}/src
OBJECTS_DIR   = obj$${SUFFIX_STR}

QWTLIB        = qwt$${SUFFIX_STR}

win32 {
    contains(CONFIG, QwtDll) {
     DEFINES += QT_DLL QWT_DLL
     QWTLIB   = $${QWTLIB}$${VER_MAJ}
    }

    win32-msvc:LIBS     += $${QWT_ROOT}/lib/$${QWTLIB}.lib
    win32-msvc.net:LIBS += $${QWT_ROOT}/lib/$${QWTLIB}.lib
    win32-msvc2002:LIBS += $${QWT_ROOT}/lib/$${QWTLIB}.lib
    win32-msvc2003:LIBS += $${QWT_ROOT}/lib/$${QWTLIB}.lib
    win32-msvc2005:LIBS += $${QWT_ROOT}/lib/$${QWTLIB}.lib
    win32-msvc2008:LIBS += $${QWT_ROOT}/lib/$${QWTLIB}.lib
    win32-g++:LIBS      += -L$${QWT_ROOT}/lib -l$${QWTLIB}
}
else {
    LIBS        += -L$${QWT_ROOT}/lib -l$${QWTLIB}
}

# include link to libriry QWT_PLOT
INCLUDEPATH += $${QWT_ROOT}/include

LIBS         += -L$${QWT_ROOT}/lib -lqwt$${SUFFIX_STR}$${VER_MAJ} source/qmx.lib



################################################################################
#                                                                              #
#**************      Р Е С У Р С Ы   П Р И Л О Ж Е Н И Я       ****************#
#                                                                              #
################################################################################

TARGET       = gurza_alarm

DEPENDPATH += . source support
INCLUDEPATH += . source . dll support

# Input files

HEADERS +=  source/draw.h              \
		        source/exchange.h          \
		        source/gui_gurza_alarm.h   \
            source/adc.h               \
            dll/qmx.h                  \
            source/qms10.h             \
		        support/ctrl_input_field.h
                                            
FORMS  += gurza_alarm.ui     
                                            
# Source files
                                            
SOURCES +=  source/draw.cpp             \
		        source/gui_gurza_alarm.cpp  \
		        source/main.cpp             \
            source/adc.cpp              \
		        support/ctrl_input_field.cpp

#===============================================================================


