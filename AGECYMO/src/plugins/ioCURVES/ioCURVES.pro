TEMPLATE	= lib

CONFIG		=  qt opengl thread warn_on debug

MOC_DIR = moc
OBJECTS_DIR = obj

INCLUDEPATH=../../
INCLUDEPATH+=../../../lib/nurbs++/ 

HEADERS		= ../../vector.hpp \
            ../../point.hpp \
            ../../nurbscurve.hpp \
            ../../renderer.hpp \
            ../../abscurve.hpp \
            ../../polyline.hpp \
            #../../nurbscurve.hpp \
            ../../polygone.hpp \
            ../../quadri.hpp \
            ../../canvas2d.hpp \
            ../../circle.hpp 

SOURCES		= ../../nurbscurve.cpp \
            ../../renderer.cpp \
            ../../abscurve.cpp \
            ../../polyline.cpp \
            #../../nurbscurve.cpp \
            ../../polygone.cpp \
            ../../quadri.cpp \
            ../../circle.cpp \
            ../../canvas2d.cpp \
            ioCURVES.cpp

TARGET		= ioCURVES.plg
LIBS      = -lm -Wl,-E -ldl -rdynamic -shared
