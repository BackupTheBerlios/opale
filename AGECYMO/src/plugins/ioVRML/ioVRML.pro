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
            ../../renderer.hpp

SOURCES		=  ../../absface.cpp \
             ../../face.cpp \
             ../../tria.cpp \
             ../../quad.cpp \
             ../../faces.cpp \
             ../../eventswindow.cpp \
             ../../renderer.cpp \
             ioVRML.cpp

#SOURCES		=  readWriteVRML.cpp

TARGET		= ioVRML.plg
LIBS      = -lm -Wl,-E -ldl -rdynamic -shared
