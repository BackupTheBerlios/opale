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
            ../../nurbscurve.hpp \
            ../../renderer.hpp \
            ../../abscurve.hpp \
            ../../polyline.hpp \
            ../../quadri.hpp \
            ../../circle.hpp 

SOURCES		=  ../../absface.cpp \
             ../../face.cpp \
             ../../tria.cpp \
             ../../quad.cpp \
             ../../faces.cpp \
             ../../nurbscurve.cpp \
             ../../renderer.cpp \
             ../../abscurve.cpp \
             ../../polyline.cpp \
             ../../quadri.cpp \
             ../../circle.cpp \
             ioCURVES.cpp

TARGET		= ioCURVES.plg
LIBS      = -lm -Wl,-E -ldl -rdynamic -shared
