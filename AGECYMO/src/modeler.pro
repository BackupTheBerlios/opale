TEMPLATE	= app
CONFIG		+= qt opengl thread warn_on debug
#CONFIG		+= qt opengl thread warn_off release

MOC_DIR = moc
OBJECTS_DIR = obj 

INCLUDEPATH += ../lib/nurbs++/
LIBS      += -L../lib/ -lmatrixI -lmatrixN -lmatrix -lnurbsd -lnurbsf
LIBS      += -lm -Wl,-E -ldl -rdynamic


HEADERS		= absVector.hpp \
            abscurve.hpp \
            point.hpp \
            polyline.hpp \
            curves.hpp \
            vector.hpp \
            matrix.hpp \
            absface.hpp \
            face.hpp \
            tria.hpp \
            quad.hpp \
            faces.hpp \
            cylinderGenerator.hpp \
            renderer.hpp \
            testVector.hpp \
            camera.hpp \
            abscanvas.hpp \
            canvas2d.hpp \
            canvas3d.hpp \
            window3d.hpp \
            pluginmanager.hpp \
            controlpanel.hpp \
            mainwindow.hpp 

SOURCES		= testVector.cpp \
            abscurve.cpp \
            polyline.cpp \
            curves.cpp \
            matrix.cpp \
            absface.cpp \
            face.cpp \
            tria.cpp \
            quad.cpp \
            faces.cpp \
            cylinderGenerator.cpp \
            renderer.cpp \
            camera.cpp \
            abscanvas.cpp \
            canvas2d.cpp \
            canvas3d.cpp \
            window3d.cpp \
            pluginmanager.cpp \
            controlpanel.cpp \
            mainwindow.cpp \
            main.cpp

TARGET		= modeler


#Optimisation for Pentium 4
#QMAKE_CFLAGS= -O4 -march=pentium4 -fomit-frame-pointer -ffast-math -fforce-addr -falign-functions=4 -fprefetch-loop-arrays -funroll-loops -pipe -fforce-mem
#QMAKE_CXXFLAGS= -O4 -march=pentium4 -fomit-frame-pointer -ffast-math -fforce-addr -falign-functions=4 -fprefetch-loop-arrays -funroll-loops -pipe -fforce-mem
