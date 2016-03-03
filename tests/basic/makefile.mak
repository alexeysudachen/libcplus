TOPDIR = ..
SRCDIR = .
PROJECT=test_basic

!INCLUDE $(XTERNAL)\Make.rules.mak

INCL = -I $(TOPDIR)\.. -I $(SRCDIR)
CFLAGS = $(CFLAGS) -D_THREADS -D_BUILTIN

TESTS = \
    $(TSTDIR)\program.exe \
    $(TSTDIR)\safeformat.exe \

_TESTS = \
    $(TSTDIR)\bigint.exe \
    $(TSTDIR)\bigint.txt \
    $(TSTDIR)\re.exe \
    $(BINDIR)\safeformat$(xEXE) \
    $(BINDIR)\program$(xEXE) \
    $(BINDIR)\buffer$(xEXE) \
    $(BINDIR)\string$(xEXE) \
    $(BINDIR)\dicto$(xEXE) \
    $(BINDIR)\array$(xEXE) \
    $(BINDIR)\program$(xEXE) \
    $(BINDIR)\file$(xEXE) \
    $(BINDIR)\bigint$(xEXE) \
    $(BINDIR)\bigint.txt \

!INCLUDE $(XTERNAL)\Make.tests.mak



