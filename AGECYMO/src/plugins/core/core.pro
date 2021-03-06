TEMPLATE	= lib

CONFIG		=  qt opengl thread warn_on debug

MOC_DIR = moc
OBJECTS_DIR = obj

INCLUDEPATH  =../../

INCLUDEPATH +=../../../lib/core/
INCLUDEPATH +=../../../lib/gmp/

HEADERS		= ../../point.hpp \
            ../../vector.hpp \
            ../../absface.hpp \
            ../../face.hpp \
            ../../tria.hpp \
            ../../quad.hpp \
            ../../faces.hpp \
            ../../eventswindow.hpp \
            ../../mainwindow.hpp \
            ../../precision.hpp

SOURCES		=  ../../absface.cpp \
             ../../face.cpp \
             ../../tria.cpp \
             ../../quad.cpp \
             ../../faces.cpp \
             ../../eventswindow.cpp \
             ../../mainwindow.cpp \
             ../../precision.cpp \
             core.cpp

# LEVEL 3 is CORE precision
DEFINES = CORE_LEVEL=3

LIBS      = -lm -Wl,-E -ldl -rdynamic -shared

# Comment or uncomment this to use CORE precision library 
LIBS      += -L../../../lib/ -lcore++ -lgmp

TARGET		= core.plg



