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
            ../../renderer.hpp

SOURCES		=  ../../absface.cpp \
             ../../face.cpp \
             ../../tria.cpp \
             ../../quad.cpp \
             ../../faces.cpp \
             ../../nurbscurve.cpp \
             ../../renderer.cpp \
             ioPOV.cpp



TARGET		= ioPOV.plg
LIBS      = -lm -Wl,-E -ldl -rdynamic -shared
