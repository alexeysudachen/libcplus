TOPDIR = ..
SRCDIR = .
PROJECT=test_system

!INCLUDE $(XTERNAL)\Make.rules.mak

INCL = -I $(TOPDIR)\.. -I $(SRCDIR)
CFLAGS = $(CFLAGS) -D_THREADS -D_BUILTIN

TESTS = \
	$(TSTDIR)\threads.exe

!INCLUDE $(XTERNAL)\Make.tests.mak


