TEMPLATE	= app
CONFIG		+= qt opengl thread warn_on debug
#CONFIG		+= qt opengl thread warn_off release

MOC_DIR = moc
OBJECTS_DIR = obj

#  ../lib/libmatrixI.a ../lib/libmatrixN.a ../lib/libmatrix.a/ ../lib/libnurbsd.a ../lib/libnurbsf.a

INCLUDEPATH += ../lib/nurbs++/


#uncomment this if you need core
# LEVEL 3 is CORE precision
#DEFINES = CORE_LEVEL=3

# Comment or uncomment this to use CORE precision library 
INCLUDEPATH += ../lib/core/ ../lib/gmp/


#LIBS +=  ../lib/libmatrixI.a ../lib/libmatrixN.a ../lib/libmatrix.a ../lib/libnurbsd.a ../lib/libnurbsf.a
#LIBS      +=  -lmatrixI -lmatrixN -lmatrix -lnurbsd -lnurbsf

LIBS      += -L../lib/ -lmatrixI -lmatrixN -lmatrix -lnurbsd -lnurbsf

# Comment or uncomment this to use CORE precision library 
LIBS      += -L../lib/ -lcore++ -lgmp


LIBS      += -lm -Wl,-E -ldl -rdynamic

LD_LIBRARY_PATH += ../lib/

HEADERS		= precision.hpp \
            absVector.hpp \
            abscurve.hpp \
            point.hpp \
            polyline.hpp \
            circle.hpp \
            quadri.hpp \
            polygone.hpp \
            nurbscurve.hpp \
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
            helpwindow.hpp \
            eventswindow.hpp \
            mainwindow.hpp

#testVector.cpp

SOURCES		= precision.cpp \
            abscurve.cpp \
            polyline.cpp \
            circle.cpp \
            polygone.cpp \
            nurbscurve.cpp \
            quadri.cpp \
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
            helpwindow.cpp \
            eventswindow.cpp \
            mainwindow.cpp \
            main.cpp

TARGET		= modeler


#Optimisation for Pentium 4
#QMAKE_CFLAGS= -O4 -march=pentium4 -fomit-frame-pointer -ffast-math -fforce-addr -falign-functions=4 -fprefetch-loop-arrays -funroll-loops -pipe -fforce-mem
#QMAKE_CXXFLAGS= -O4 -march=pentium4 -fomit-frame-pointer -ffast-math -fforce-addr -falign-functions=4 -fprefetch-loop-arrays -funroll-loops -pipe -fforce-mem
