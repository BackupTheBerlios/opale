TEMPLATE	= lib

CONFIG		=  qt opengl thread warn_on debug

MOC_DIR = moc
OBJECTS_DIR = obj

INCLUDEPATH=../../

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
             mantilla.cpp

TARGET		= mantilla.plg
LIBS      = -lm -Wl,-E -ldl -rdynamic -shared
