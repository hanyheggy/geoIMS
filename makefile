##################################################################################
#                                                                                #
# Makefile for geoIMS with embeded SQL of DB2 Universal Database                 #
#                                                                                #
##################################################################################
#                                                                                #
# C programs -- LINUX operating system                                           #
#                                                                                #
# Enter one of the following commands                                            #
#                                                                                #
#   make geoIMS            - Builds geoIMS                                       #
#   make all               - Builds the all geoIMS  Modules                      #
#   make clean             - Erases intermediate files                           #
#   make cleanall          - Erases all files produced in the build process,     #
#                            except the original source files                    #
#                                                                                #
##################################################################################


##################################################################################
#                  1 -- COMPILERS + VARIABLES
##################################################################################

# This file assumes the DB2 instance path is defined by the variable HOME.
# It also assumes DB2 is installed under the DB2 instance.
# If these statements are not correct, update the variable DB2PATH.

# DB2 Path
DB2PATH = /opt/IBM/db2/V8.1

# Use the gcc compiler
CC=gcc

# Executables Directory
EXEDIR  = /home/geoinfo/bin/geoIMS


# The compiler options.
DBFLAGS = $(EXTRA_CFLAGS) -I$(DB2PATH)/include -I/usr/X11R6/include/ -g

# The compiler options.
CFLAGS    = $(EXTRA_CFLAGS) -I$(DB2PATH)/include -I/usr/X11R6/include -I/usr/include

# The compiler options. -O2
CFLAGS_O2 = $(EXTRA_CFLAGS) -I$(DB2PATH)/include -I/usr/X11R6/include -I/usr/include -O2

# The compiler options. -O2
ARFLAGS   = $(EXTRA_CFLAGS)-I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include  -O3

# The compiler options for socket
SOCKETFLAGS = -O3


# The Required Libraries
LIBS= -L$(DB2PATH)/lib -Wl,-rpath,$(DB2PATH)/lib -L/usr/X11R6/lib -lXm -lXt -lm -ldb2  \
      -L/usr/lib -L/usr/X11R6/lib -lfreetype -lz -L/usr/lib                            \
      -lWand -lMagick  -ltiff -lfreetype -ljpeg -lXext -lSM -lICE -lX11 -lXt -lbz2 -lz -lpthread -lm \
      -lglib-2.0 -lodbc


# To connect to a remote SAMPLE database cataloged on the client machine
# with another name, update the DB variable.

# Set DBname, UID and PWD if neccesary
DB=geoinfo
UID=geoinfo
PWD=fsh170405
#hfh231267

COPY=cp
ERASE=rm -f
TOUCH=touch

#############################################################################
#  2 -- MAKE CATEGORIES
#       2.1  make all
#       2.2  make clean
#       2.3  make cleanall
#############################################################################


#****************************************************************************
#                  2a - make all
#****************************************************************************

all : \
        geoIMS.exe

#****************************************************************************
#                  2g - make clean
#****************************************************************************

clean : \
        cleangen \
        cleanemb

cleangen :
	$(ERASE) OBJECT/geo*.o
	$(ERASE) *.err core
	$(TOUCH) geo*.sqc geo*.c

cleanemb :
	$(ERASE) geoIMS_main.c
	$(ERASE) geoedit.c
	$(ERASE) geoIMS_network.c
	$(ERASE) geotrace.c
	$(ERASE) geosld.c
	$(ERASE) geo*.bnd


#****************************************************************************
#                  2h - make cleanall
#****************************************************************************

cleanall : \
        clean
	        $(ERASE) *.bnd
	        $(ERASE) geoIMS gelIMS.a
	        $(TOUCH) geo*.sqc geo*.c


#****************************************************************************
#                                  geoIMS
#****************************************************************************

geoIMS_main.c :    geoIMS_main.sqc include/geoIMS.h
	             db2 connect to $(DB)
	             db2 prep geoIMS_main.sqc bindfile
	             db2 bind geoIMS_main.bnd
	             db2 connect reset
	             db2 terminate

geoedit.c :        geoedit.sqc  include/geoIMSextern.h
	             db2 connect to $(DB)
	             db2 prep geoedit.sqc bindfile
	             db2 bind geoedit.bnd
	             db2 connect reset
	             db2 terminate

geoIMS_network.c : geoIMS_network.sqc  include/geoIMSextern.h
	             db2 connect to $(DB)
	             db2 prep geoIMS_network.sqc bindfile
	             db2 bind geoIMS_network.bnd
	             db2 connect reset
	             db2 terminate

geotrace.c :       geotrace.sqc  include/geoIMSextern.h
	             db2 connect to $(DB)
	             db2 prep geotrace.sqc bindfile
	             db2 bind geotrace.bnd
	             db2 connect reset
	             db2 terminate

geomatch.c :       geomatch.sqc  include/geoIMSextern.h
	             db2 connect to $(DB)
	             db2 prep geomatch.sqc bindfile
	             db2 bind geomatch.bnd
	             db2 connect reset
	             db2 terminate



OBJECT/geoIMS_main.o :        geoIMS_main.c
	                         $(CC) -c geoIMS_main.c    $(CFLAGS_O2)
	                         mv geo*.o  OBJECT

OBJECT/geoedit.o :       geoedit.c
	                         $(CC) -c geoedit.c    $(CFLAGS_O2)
	                         mv geo*.o  OBJECT

OBJECT/geoIMS_network.o :    geoIMS_network.c
	                         $(CC) -c geoIMS_network.c $(CFLAGS_O2)
	                         mv geo*.o  OBJECT

OBJECT/geotrace.o :      geotrace.c
	                         $(CC) -c geotrace.c   $(CFLAGS_O2)
	                         mv geo*.o  OBJECT

OBJECT/geoplot.o :       geoplot.c  include/geoIMSextern.h
	                         $(CC) -c geoplot.c    $(CFLAGS_O2)
	                         mv geo*.o  OBJECT

OBJECT/geoIMS_dxfio.o :      geoIMS_dxfio.c  include/geoIMSextern.h
	                         $(CC) -c geoIMS_dxfio.c   $(CFLAGS_O2)
	                         mv geo*.o  OBJECT

OBJECT/geomatch.o :      geomatch.c  include/geoIMSextern.h
	                         $(CC) -c geomatch.c   $(CFLAGS_O2)
	                         mv geo*.o  OBJECT

OBJECT/geolocate.o :     geolocate.c  include/geoIMSextern.h
	                         $(CC) -c geolocate.c  $(CFLAGS_O2)
	                         mv geo*.o  OBJECT

OBJECT/geodbname.o :     geodbname.c include/geoIMS.h
	                         $(CC) -c geodbname.c  $(CFLAGS_O2)
	                         mv geo*.o  OBJECT

OBJECT/geofsb.o :        geofsb.c   include/geoIMS.h
	                         $(CC) -c geofsb.c     $(CFLAGS)
	                         mv geo*.o  OBJECT

OBJECT/geotransfer.o :   geotransfer.c include/geoIMS.h
	                         $(CC) -c geotransfer.c $(CFLAGS)
	                         mv geo*.o  OBJECT

OBJECT/geoprojection.o : geoprojection.c  include/geoIMS.h
	                         $(CC) -c geoprojection.c  $(CFLAGS)
	                         mv geo*.o  OBJECT

OBJECT/geolayer.o :      geolayer.c     include/geoIMS.h
	                         $(CC) -c geolayer.c   $(CFLAGS_O2)
	                         mv geo*.o  OBJECT


OBJECT/geoIMS_web_listener.o :      geoIMS_web_listener.c    include/geoIMS.h
	                         $(CC) -c geoIMS_web_listener.c   $(SOCKETFLAGS)
	                         mv geo*.o  OBJECT

OBJECT/geoIMS_utf8_2_arabic.o :      geoIMS_utf8_2_arabic.c   include/geoIMS.h
	                         $(CC) -c geoIMS_utf8_2_arabic.c  $(ARFLAGS)
	                         mv geo*.o  OBJECT

OBJECT/geoIMS_read_db.o :      geoIMS_read_db.c   include/geoIMS.h
	                         $(CC) -c geoIMS_read_db.c  $(ARFLAGS)
	                         mv geo*.o  OBJECT

geoIMS.exe :    OBJECT/geoIMS_main.o OBJECT/geoedit.o       OBJECT/geoIMS_network.o  OBJECT/geotrace.o     \
                OBJECT/geolayer.o    OBJECT/geoprojection.o OBJECT/geotransfer.o     OBJECT/geofsb.o       \
                OBJECT/geodbname.o   OBJECT/geolocate.o     OBJECT/geomatch.o        OBJECT/geoIMS_dxfio.o \
                OBJECT/geoplot.o     OBJECT/geoIMS_web_listener.o OBJECT/geoIMS_utf8_2_arabic.o OBJECT/geoIMS_read_db.o


	          $(CC) -o geoIMS.exe                    \
	                   OBJECT/geoIMS_main.o          \
	                   OBJECT/geoIMS_web_listener.o  \
	                   OBJECT/geoIMS_network.o       \
	                   OBJECT/geoIMS_dxfio.o         \
	                   OBJECT/geoIMS_utf8_2_arabic.o \
	                   OBJECT/geoIMS_read_db.o       \
	                   OBJECT/geoedit.o              \
	                   OBJECT/geotrace.o             \
	                   OBJECT/geolayer.o             \
	                   OBJECT/geoprojection.o        \
	                   OBJECT/geotransfer.o          \
	                   OBJECT/geofsb.o               \
	                   OBJECT/geodbname.o            \
	                   OBJECT/geolocate.o            \
	                   OBJECT/geomatch.o             \
	                   OBJECT/geoplot.o              \
	                   $(CFLAGS_O2) $(LIBS)

	          cp ./geoIMS.exe $(EXEDIR)


