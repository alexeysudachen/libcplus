
ALL: $(BINDIR) $(INTDIR) $(TOOLDIR) printflags tools tests

$(BINDIR) $(INTDIR) $(TOOLDIR):
   if not exist $@ md $@

!IF "$(PLATF)" == "win_x86"

INCS= 

CL_FLAGS1= -I $(LCPDIR) -D_BUILTIN -FC -nologo $(INCS)

!IF "$(CFG)" == "fast"
CL_FLAGS= -Oy- -GF -Gy -MT -O2 $(CL_FLAGS1)
SUFFIX_D=
!ELSE
CL_FLAGS= -GF -Gy -Gs -Od -MTd -Zi -D_STRICT $(CL_FLAGS1)  
SUFFIX_D=d
!ENDIF

LIBRARIES= kernel32.lib user32.lib gdi32.lib winmm.lib \
           $(XTERNAL)\lib\libpng-mt10$(SUFFIX_D).lib \
           $(XTERNAL)\lib\zlib-mt10$(SUFFIX_D).lib \

#			opengl32.lib \
#           libjpeg-mt10$(SUFFIX_D).lib \
#           $(XTRNLS)\_win32\openal32-mt10$(SUFFIX_D).lib \
#           $(XTRNLS)\_win32\libeay32-mt10.lib \
#           $(XTRNLS)\_win32\ssleay32-mt10.lib \
#           $(XTRNLS)\_win32\mysql55-mt10$(SUFFIX_D).lib \

tools: $(TOOLS)
tests: $(TESTS)

printflags:
   @echo FLAGS: 
   @echo . $(CL_FLAGS)
   @echo . -Fo$(INTDIR)\ 
   @echo . -Fd$(INTDIR)\=F 
   @echo . -Fm$(INTDIR)\=F 
   @echo . -Fe$(BINDIR)\=F.exe

#$(TESTS): makefile $(HC)

{}.c{$(BINDIR)}.exe:
   @cl @<<
   $(CL_FLAGS) $<
   -Fo$(INTDIR)\ -Fd$(INTDIR)\$(*F) -Fm$(INTDIR)\$(*F) -Fe$(BINDIR)\$(*F).exe
   $(LIBRARIES) 
   -link -incremental:no -pdb:$(INTDIR)\$(*F).pdb
<<

{}.c{$(TOOLDIR)}.exe:
   @cl @<<
   $(CL_FLAGS) $<
   -Fo$(INTDIR)\ -Fd$(INTDIR)\$(*F)_ -Fm$(INTDIR)\$(*F) -Fe$(TOOLDIR)\$(*F).exe
   $(LIBRARIES) 
   -link -incremental:no -pdb:$(INTDIR)\$(*F).pdb
<<

{}.txt{$(BINDIR)}.txt:
   copy $< $@

clean:
   -@erase /s $(TESTS) 2>nul
   -@for %i in ($(TESTS)) do @erase /s $(INTDIR)\%~ni.* 2>nul
   -@erase /s $(TOOLS) 2>nul
   -@for %i in ($(TOOLS)) do @erase /s $(INTDIR)\%~ni.* 2>nul

!ELSEIF "$(PLATF)" == "bbk_x86" || "$(PLATF)" == "bbk_arm" 

LIBRARIES= -lpng -ljpeg -lbz2 -lz -lbps -lscreen -lm -lGLESv1_CM -lEGL

INCS= -I $(QNT_TARGET)\usr\include
GCC=$(QNX_HOST)\usr\bin\$(BBK_PFX)gcc.exe
CL_FLAGS1= -DUSING_GL11 -I $(LCPDIR) -D_BUILTIN $(INCS) \
           -Wno-deprecated -Wno-deprecated-declarations \
           -funwind-tables \
           -fstack-protector-all -fPIE -frecord-gcc-switches

!IF "$(CFG)" == "fast"
CL_FLAGS= -O2 $(CL_FLAGS1)
SUFFIX_D=
!ELSE
CL_FLAGS= -O0 -g -D_STRICT $(CL_FLAGS1)  
SUFFIX_D=d
!ENDIF

tools:
tests: $(TESTS) $(TESTS:.bbk=.xml) $(TESTS:.bbk=.bar) $(TESTS:.bbk=.cmd)

printflags:
   @echo FLAGS: 
   @echo . $(CL_FLAGS)
    
{}.c{$(BINDIR)}.bbk:
	set QNX_TARGET=$(QNX_TARGET)
	set QNX_HOST=$(QNX_HOST)
	$(GCC) $(CL_FLAGS) $< $(LIBRARIES) -o $(BINDIR)/$@

!IF "$(PLATF)" == "bbk_x86"
BBK_CONFIG_ID=com.qnx.qcc.configuration.exe.debug.711273645 
BBK_CONFIG_NAME=Simulator-Debug
BBK_CONFIG_DEVICE=SIMULATOR
BBK_CONFIG_ARCH=x86
BBK_CONFIG_DEVMODE=
#-devMode
!ELSEIF "$(PLATF)" == "bbk_arm"
BBK_CONFIG_ID=com.qnx.qcc.configuration.exe.release.333104124 
BBK_CONFIG_NAME=Device-Release
BBK_CONFIG_DEVICE=PLAYBOOK
BBK_CONFIG_ARCH=armle-v7
BBK_CONFIG_DEVMODE=
!ELSE
!ERROR unknown bbk platform $(PLATF)
!ENDIF

{}.c{$(BINDIR)}.xml:
	type > $@ <<
<?xml version="1.0" encoding="utf-8" standalone="no"?>
<qnx xmlns="http://www.qnx.com/schemas/application/1.0">
    <id>com.desanova.q2.$(*F)</id>
    <name>Q2 redbox</name>
    <versionNumber>1.0.0</versionNumber>
    <buildId>1</buildId>
    <description>Libcplus Q2 $(*F)</description>
    <author>Alexey Sudachen (alexey@sudachen.name)</author>
    <platformVersion>2.1.0.0</platformVersion>
    <initialWindow>
        <systemChrome>none</systemChrome>
        <transparent>false</transparent>
        <aspectRatio>landscape</aspectRatio>
        <autoOrients>false</autoOrients>
    </initialWindow>
    <category>core.games</category>
    <asset path="$(LCPDIR)\tests\Q2.png">icon.png</asset>
    <configuration id="$(BBK_CONFIG_ID)" name="$(BBK_CONFIG_NAME)">
       <platformArchitecture>$(BBK_CONFIG_ARCH)</platformArchitecture>
       <asset path="$(*F).bbk" entry="true" type="Qnx/Elf">$(*F).bbk</asset>
    </configuration>
    <icon>
       <image>icon.png</image>
    </icon>
    <permission system="true">run_native</permission>
    <env var="LD_LIBRARY_PATH" value="app/native/lib"/>
</qnx>
<<

{}.c{$(BINDIR)}.bar:
	$(QNX_HOST)\usr\bin\blackberry-nativepackager.bat $(CONFIG_DEVMODE) -package $@ $(BINDIR)\$(*F).xml  	
#!IF "$(PLATF)"=="bbk_arm" && "$(BBK_STORE_PASS)" != ""
!IF "$(BBK_STORE_PASS)" != ""
	$(QNX_HOST)\usr\bin\blackberry-signer.bat -storepass $(BBK_STORE_PASS) $@ 
!ENDIF

{}.c{$(BINDIR)}.cmd:
	type > $@ <<
cd %~dp0
set DEVICE=%1
set QNX_HOST=$(QNX_HOST)
set QNX_TARGET=$(QNX_TARGET)
if "%DEVICE%"=="" set DEVICE=%BBK_$(BBK_CONFIG_DEVICE)_IP%
if not "%BBK_$(BBK_CONFIG_DEVICE)_PASSWORD%" == "" set PASSWORD=-password %BBK_$(BBK_CONFIG_DEVICE)_PASSWORD%
$(QNX_HOST)\usr\bin\blackberry-deploy.bat -installApp %PASSWORD% -device %DEVICE% $(*F).bar 
<<

clean:
   -@erase $(TESTS) 2>nul
   -@erase $(TESTS:.bbk=.xml) 2>nul
   -@erase $(TESTS:.bbk=.bar) 2>nul
   -@erase $(TESTS:.bbk=.cmd) 2>nul

!ENDIF
