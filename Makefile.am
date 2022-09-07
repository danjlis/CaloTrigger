AUTOMAKE_OPTIONS = foreign

AM_CPPFLAGS = \
  -I$(includedir) \
  -I$(OFFLINE_MAIN)/include \
  -I$(ROOTSYS)/include

AM_LDFLAGS = \
  -L$(libdir) \
  -L$(OFFLINE_MAIN)/lib

pkginclude_HEADERS = \
  CaloTrigger.h \
	CaloTriggerElement.h \
	CaloTriggerElementMap.h \
	CaloTriggerTower.h

pcmdir = $(libdir)

lib_LTLIBRARIES = \
  libcalotrigger.la

libcalotrigger_la_SOURCES = \
  CaloTrigger.cc \
	CaloTriggerElement.cc \
	CaloTriggerElementMap.cc \
	CaloTriggerTower.cc 

libcalotrigger_la_LIBADD = \
  -lphool \
  -lcalo_io \
  -lgsl \
  -lgslcblas \
  -lphg4hit \
  -lg4jets_io \
  -lSubsysReco

%_Dict.cc: %.h %LinkDef.h
	rootcint -f $@ @CINTDEFS@ $(DEFAULT_INCLUDES) $(AM_CPPFLAGS) $^

#just to get the dependency
%_Dict_rdict.pcm: %_Dict.cc ;

BUILT_SOURCES = testexternals.cc

noinst_PROGRAMS = \
  testexternals

testexternals_SOURCES = testexternals.cc
testexternals_LDADD   = libcalotrigger.la

testexternals.cc:
	echo "//*** this is a generated file. Do not commit, do not edit" > $@
	echo "int main()" >> $@
	echo "{" >> $@
	echo "  return 0;" >> $@
	echo "}" >> $@

clean-local:
	rm -f $(BUILT_SOURCES)
