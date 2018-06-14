CC = g++
CFLAGS = -Wall -c -g -fpermissive 

#ROOFIT_INCLUDE := $(shell cd $(CMSSW_BASE); scram tool info roofitcore | grep INCLUDE= | sed 's|INCLUDE=||')
#ROOFIT_LIBDIR := $(shell cd $(CMSSW_BASE); scram tool info roofitcore | grep LIBDIR= | sed 's|LIBDIR=||')

INCLUDES = -I. -I.. -I$(ROOTSYS)/include #-I$(ROOFIT_INCLUDE)/ C-I$(CMSSW_BASE)/src -I$(CMSSW_BASE)/src/CommonTools  

ROOTSYS ?= ERROR_RootSysIsNotDefined

ROOTFLAG = `${ROOTSYS}/bin/root-config --cflags --libs`

EXTRALIBS := -L$(ROOTSYS)/lib -lHtml -lMathCore -lGenVector -lMinuit -lEG  -lPhysics -lTreePlayer -lRooFitCore -lRooFit #-L$(ROOFIT_LIBDIR)/ 


drawFrame: drawFrame.cpp MPHit.o MPDrawStuff.o
	$(CC) -Wall $(INCLUDES) -o drawFrame drawFrame.cpp MPHit.o MPDrawStuff.o $(ROOTFLAG) $(EXTRALIBS)

MPHit.o: ../src/MPHit.cc
	$(CC) -Wall $(INCLUDES) -c ../src/MPHit.cc $(ROOTFLAG) 

MPDrawStuff.o: ../src/MPDrawStuff.cc
	$(CC) -Wall $(INCLUDES) -c ../src/MPDrawStuff.cc $(ROOTFLAG) 

