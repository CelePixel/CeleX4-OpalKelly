#############################################################################
# Makefile for building: libCeleX.so.1.0.0
# Project:  ./CeleX.pro
#############################################################################

MAKEFILE      = Makefile

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DCELEX_LIBRARY
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT -fPIC $(DEFINES)
CXXFLAGS      = -pipe -O2 -std=gnu++0x -Wall -W -D_REENTRANT -fPIC $(DEFINES)
INCPATH       = -I. -I.
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = cp -f -R
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f
DISTNAME      = CeleX1.0.0
DISTDIR       =
LINK          = g++
LFLAGS        = -Wl,-O1 -shared -Wl,-soname,libCeleX.so.1
LIBS          = $(SUBLIBS) -lokFrontPanel -lpthread `pkg-config --cflags --libs opencv`
AR            = ar cqs
RANLIB        = 
SED           = sed
STRIP         = strip

####### Output directory

OBJECTS_DIR   = ./

####### Files
SOURCES       = ./configproc/tinyxml/tinyxmlparser.cpp \
		./configproc/tinyxml/tinyxmlerror.cpp \
		./configproc/tinyxml/tinyxml.cpp \
		./configproc/tinyxml/tinystr.cpp \
		./frontpanel/frontpanel.cpp \
		./eventproc/fpgadatareader.cpp \
		./eventproc/fpgadataprocessor.cpp \
		./eventproc/eventprocessing.cpp \
		./eventproc/datareaderthread.cpp \
		./eventproc/dataprocessthread.cpp \
		./eventproc/datarecorder.cpp \
		./eventproc/celex4processeddata.cpp \
		./eventproc/celex4.cpp \
		./configproc/hhxmlreader.cpp \
		./configproc/hhwireincommand.cpp \
		./configproc/hhsequencemgr.cpp \
		./configproc/hhdelaycommand.cpp \
		./configproc/hhcommand.cpp \
		./base/xthread.cpp \
		./base/xbase.cpp \
		./base/dataqueue.cpp 
OBJECTS       = tinyxmlparser.o \
		tinyxmlerror.o \
		tinyxml.o \
		tinystr.o \
		frontpanel.o \
		fpgadatareader.o \
		fpgadataprocessor.o \
		eventprocessing.o \
		datareaderthread.o \
		dataprocessthread.o \
		datarecorder.o \
		celex4processeddata.o \
		celex4.o \
		hhxmlreader.o \
		hhwireincommand.o \
		hhsequencemgr.o \
		hhdelaycommand.o \
		hhcommand.o \
		xthread.o \
		xbase.o \
		dataqueue.o
DIST          = ./CeleX.pro frontpanel/okFrontPanelDLL.h \
		frontpanel/frontpanel.h \
		configproc/hhxmlreader.h \
		configproc/hhwireincommand.h \
		configproc/hhsequencemgr.h \
		configproc/hhdelaycommand.h \
		configproc/hhcommand.h \
		configproc/tinyxml/tinyxml.h \
		configproc/tinyxml/tinystr.h \
		base/xthread.h \
		base/xbase.h \
		base/dataqueue.h \
		eventproc/fpgadatareader.h \
		eventproc/fpgadataprocessor.h \
		eventproc/datareaderthread.h \
		eventproc/dataprocessthread.h \
		eventproc/datarecorder.h \
		include/dvslib/imgproc.h \
		include/celex4/celex4.h \
		include/celex4/celex4datamanager.h \
		include/celex4/celex4processeddata.h ./configproc/tinyxml/tinyxmlparser.cpp \
		./configproc/tinyxml/tinyxmlerror.cpp \
		./configproc/tinyxml/tinyxml.cpp \
		./configproc/tinyxml/tinystr.cpp \
		./frontpanel/frontpanel.cpp \
		./eventproc/fpgadatareader.cpp \
		./eventproc/fpgadataprocessor.cpp \
		./eventproc/eventprocessing.cpp \
		./eventproc/datareaderthread.cpp \
		./eventproc/dataprocessthread.cpp \
		./eventproc/datarecorder.cpp \
		./eventproc/celex4processeddata.cpp \
		./eventproc/celex4.cpp \
		./configproc/hhxmlreader.cpp \
		./configproc/hhwireincommand.cpp \
		./configproc/hhsequencemgr.cpp \
		./configproc/hhdelaycommand.cpp \
		./configproc/hhcommand.cpp \
		./base/xthread.cpp \
		./base/xbase.cpp \
		./base/dataqueue.cpp

DESTDIR       = 
TARGET        = libCeleX.so.1.0.0
TARGETA       = libCeleX.a
TARGET0       = libCeleX.so
TARGETD       = libCeleX.so.1.0.0
TARGET1       = libCeleX.so.1
TARGET2       = libCeleX.so.1.0


first: all
####### Build rules

$(TARGET):  $(OBJECTS) $(SUBLIBS) $(OBJCOMP)  
	-$(DEL_FILE) $(TARGET) $(TARGET0) $(TARGET1) $(TARGET2)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS) $(OBJCOMP)
	-ln -s $(TARGET) $(TARGET0)
	-ln -s $(TARGET) $(TARGET1)
	-ln -s $(TARGET) $(TARGET2)



staticlib: $(TARGETA)

$(TARGETA):  $(OBJECTS) $(OBJCOMP) 
	-$(DEL_FILE) $(TARGETA) 
	$(AR) $(TARGETA) $(OBJECTS)

all: Makefile $(TARGET)

dist: distdir FORCE
	(cd `dirname $(DISTDIR)` && $(TAR) $(DISTNAME).tar $(DISTNAME) && $(COMPRESS) $(DISTNAME).tar) && $(MOVE) `dirname $(DISTDIR)`/$(DISTNAME).tar.gz . && $(DEL_FILE) -r $(DISTDIR)

distdir: FORCE
	@test -d $(DISTDIR) || mkdir -p $(DISTDIR)
	$(COPY_FILE) --parents $(DIST) $(DISTDIR)/


clean: compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	#-$(DEL_FILE) *~ core *.core


distclean: clean 
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) $(TARGET0) $(TARGET1) $(TARGET2) $(TARGETA)
	-$(DEL_FILE) Makefile


####### Sub-libraries

check: first

benchmark: first

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: 

####### Compile

tinyxmlparser.o: ./configproc/tinyxml/tinyxmlparser.cpp ./configproc/tinyxml/tinyxml.h \
		./configproc/tinyxml/tinystr.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tinyxmlparser.o ./configproc/tinyxml/tinyxmlparser.cpp

tinyxmlerror.o: ./configproc/tinyxml/tinyxmlerror.cpp ./configproc/tinyxml/tinyxml.h \
		./configproc/tinyxml/tinystr.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tinyxmlerror.o ./configproc/tinyxml/tinyxmlerror.cpp

tinyxml.o: ./configproc/tinyxml/tinyxml.cpp ./configproc/tinyxml/tinyxml.h \
		./configproc/tinyxml/tinystr.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tinyxml.o ./configproc/tinyxml/tinyxml.cpp

tinystr.o: ./configproc/tinyxml/tinystr.cpp ./configproc/tinyxml/tinystr.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tinystr.o ./configproc/tinyxml/tinystr.cpp

frontpanel.o: ./frontpanel/frontpanel.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o frontpanel.o ./frontpanel/frontpanel.cpp

fpgadatareader.o: ./eventproc/fpgadatareader.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o fpgadatareader.o ./eventproc/fpgadatareader.cpp

fpgadataprocessor.o: ./eventproc/fpgadataprocessor.cpp ./eventproc/fpgadatareader.h \
		./include/celex4/celex4processeddata.h \
		./include/celex4/celex4.h \
		./include/celex4/celex4datamanager.h \
		./base/xbase.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o fpgadataprocessor.o ./eventproc/fpgadataprocessor.cpp

eventprocessing.o: ./eventproc/eventprocessing.cpp \
		./include/dvslib/eventproc.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o eventprocessing.o ./eventproc/eventprocessing.cpp

datareaderthread.o: ./eventproc/datareaderthread.cpp ./include/celex4/celex4.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o datareaderthread.o ./eventproc/datareaderthread.cpp

dataprocessthread.o: ./eventproc/dataprocessthread.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o dataprocessthread.o ./eventproc/dataprocessthread.cpp

datarecorder.o: ./eventproc/datarecorder.cpp ./eventproc/datarecorder.h \
		./base/xbase.h 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o datarecorder.o ./eventproc/datarecorder.cpp

celex4processeddata.o: ./eventproc/celex4processeddata.cpp ./include/celex4/celex4.h \
		./include/celex4/celex4processeddata.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o celex4processeddata.o ./eventproc/celex4processeddata.cpp

celex4.o: ./eventproc/celex4.cpp ./include/celex4/celex4.h \
		./frontpanel/frontpanel.h \
		./frontpanel/okFrontPanelDLL.h \
		./base/xbase.h \
		./configproc/hhsequencemgr.h \
		./include/celex4/celex4processeddata.h \
		./eventproc/dataprocessthread.h \
		./base/dataqueue.h \
		./base/xthread.h \
		./eventproc/fpgadataprocessor.h \
		./eventproc/datareaderthread.h \
		./eventproc/fpgadatareader.h\
		./eventproc/datarecorder.h 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o celex4.o ./eventproc/celex4.cpp

hhxmlreader.o: ./configproc/hhxmlreader.cpp ./configproc/hhxmlreader.h \
		./base/xbase.h \
		./configproc/hhwireincommand.h \
		./configproc/hhcommand.h \
		./configproc/hhdelaycommand.h \
		./configproc/hhsequencemgr.h \
		./configproc/tinyxml/tinyxml.h \
		./configproc/tinyxml/tinystr.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o hhxmlreader.o ./configproc/hhxmlreader.cpp

hhwireincommand.o: ./configproc/hhwireincommand.cpp ./frontpanel/frontpanel.h \
		./frontpanel/okFrontPanelDLL.h \
		./base/xbase.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o hhwireincommand.o ./configproc/hhwireincommand.cpp

hhsequencemgr.o: ./configproc/hhsequencemgr.cpp ./configproc/hhcommand.h \
		./configproc/hhxmlreader.h \
		./configproc/tinyxml/tinyxml.h \
		./configproc/tinyxml/tinystr.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o hhsequencemgr.o ./configproc/hhsequencemgr.cpp

hhdelaycommand.o: ./configproc/hhdelaycommand.cpp ./configproc/hhdelaycommand.h \
		./configproc/hhcommand.h \
		./frontpanel/frontpanel.h \
		./frontpanel/okFrontPanelDLL.h \
		./base/xbase.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o hhdelaycommand.o ./configproc/hhdelaycommand.cpp

hhcommand.o: ./configproc/hhcommand.cpp ./configproc/hhcommand.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o hhcommand.o ./configproc/hhcommand.cpp

xthread.o: ./base/xthread.cpp ./base/xthread.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o xthread.o ./base/xthread.cpp

xbase.o: ./base/xbase.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o xbase.o ./base/xbase.cpp

dataqueue.o: ./base/dataqueue.cpp /
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o dataqueue.o ./base/dataqueue.cpp

####### Install

install_target: first FORCE
	@test -d $(INSTALL_ROOT)/usr/lib || mkdir -p $(INSTALL_ROOT)/usr/lib
	-$(INSTALL_PROGRAM) $(TARGET) $(INSTALL_ROOT)/usr/lib/$(TARGET)
	-$(STRIP) --strip-unneeded $(INSTALL_ROOT)/usr/lib/$(TARGET)
	-$(SYMLINK) $(TARGET) $(INSTALL_ROOT)/usr/lib/$(TARGET0)
	-$(SYMLINK) $(TARGET) $(INSTALL_ROOT)/usr/lib/$(TARGET1)
	-$(SYMLINK) $(TARGET) $(INSTALL_ROOT)/usr/lib/$(TARGET2)

uninstall_target: FORCE
	-$(DEL_FILE) $(INSTALL_ROOT)/usr/lib/$(TARGET) 
	 -$(DEL_FILE) $(INSTALL_ROOT)/usr/lib/$(TARGET0) 
	 -$(DEL_FILE) $(INSTALL_ROOT)/usr/lib/$(TARGET1) 
	 -$(DEL_FILE) $(INSTALL_ROOT)/usr/lib/$(TARGET2)
	-$(DEL_DIR) $(INSTALL_ROOT)/usr/lib/ 


install: install_target  FORCE

uninstall: uninstall_target  FORCE

FORCE:

