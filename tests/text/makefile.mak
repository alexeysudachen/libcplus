TOPDIR = ..
SRCDIR = .
PROJECT=test_text

!INCLUDE $(XTERNAL)\Make.rules.mak

INCL = -I $(TOPDIR)\.. -I $(SRCDIR)
CFLAGS = $(CFLAGS) -D_THREADS -D_BUILTIN

TESTS = \
    $(TSTDIR)\re.exe \

!INCLUDE $(XTERNAL)\Make.tests.mak



