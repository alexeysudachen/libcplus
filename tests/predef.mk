
BBK_HOME=C:\Opt\bbndk\2.1.0
!IF "$(QNX_HOST)" == ""
QNX_TARGET=$(BBK_HOME)\target\qnx6
QNX_HOST=$(BBK_HOME)\host\win32\x86
!ENDIF

!IF "$(CFG)" == "fast"
RELEASE=fast
!ELSE
RELEASE=strict
CFG=strict
!ENDIF

LCPDIR=..\..

!IF "$(PLATF)" == "bbk_x86" || "$(PLATF)" == "bbk_arm"

!IF "$(PLATF)" == "bbk_x86"
BBK_PFX=ntox86-
!ELSE
BBK_PFX=ntoarmv7-
!ENDIF

xLIB=.a
xOBJ=.o
xEXE=.bbk

!ELSEIF "$(PLATF)" == "lin_32"
xLIB=.a
xOBJ=.o
xEXE=.lin


!ELSEIF "$(PLATF)" == "droid"
xLIB=.a
xOBJ=.o
xEXE=.dro

!ELSEIF "$(PLATF)" == "win_x86"

xLIB=.lib
xOBJ=.obj
xEXE=.exe

!ELSE
!ERROR unknown platform "$(PLATF)"
!ENDIF

OUTDIR=$(LCPDIR)\bin\$(PLATF)
BINDIR=$(OUTDIR)\$(RELEASE)
INTDIR=$(OUTDIR)\$(RELEASE)\tmp
TOOLDIR=$(OUTDIR)\$(RELEASE)\tool
CPLUS=$(LCPDIR)\c+
#XTRNLS=$(LCPDIR)\xternals

HC= $(CPLUS)\C+.hc $(CPLUS)\_csupport.hc $(CPLUS)\_object.hc $(CPLUS)\_tls.hc $(CPLUS)\_algo.hc\
    $(CPLUS)\buffer.hc $(CPLUS)\string.hc $(CPLUS)\array.hc $(CPLUS)\dicto.hc \
    $(CPLUS)\program.hc $(CPLUS)\file.hc

TESTS= 
TOOLS= 

.SUFFIXES: $(EXE) .c .txt .xmli

