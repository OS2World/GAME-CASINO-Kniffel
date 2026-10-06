# Makefile for Kniffel (Open Watcom C on OS/2 / ArcaOS)
# wmake 2.0.1 on ArcaOS - explicit per-file rules (no pattern rules),
# all prerequisites of a target on ONE line (no continuation backslashes).

# ============================================================================
# Configuration
# ============================================================================

NAME    = Kniffel
SRCDIR  = src
BINDIR  = bin

!ifndef WATCOM
WATCOM  = C:\WATCOM
!endif

!ifndef OS2TK
OS2TK   = C:\OS2TK45
!endif

# ============================================================================
# Tools
# ============================================================================

CC      = wcc386
LINK    = wlink
RC      = wrc
WIPFC   = wipfc

# ============================================================================
# Flags (per plan.txt section 2; no -bm: it kills the PM start up)
# ============================================================================

CFLAGS  = -bt=os2 -mf -5 -fpi -Oaxt -W3 -ze -d0
CFLAGS  = $(CFLAGS) -i=$(OS2TK)\h -i=$(SRCDIR)

RCFLAGS = -r -bt=os2 -i=$(OS2TK)\h -i=$(SRCDIR) -i=$(SRCDIR)\bitmaps -i=$(SRCDIR)\icons

LFLAGS  = system os2v2_pm
LFLAGS  = $(LFLAGS) option stack=65536
LFLAGS  = $(LFLAGS) option map=$(BINDIR)\$(NAME).map

# ============================================================================
# Files
# ============================================================================

OBJS    = $(BINDIR)\kniffel.obj $(BINDIR)\lang.obj
ROBJ    = $(BINDIR)\$(NAME).res
RCFILE  = $(SRCDIR)\$(NAME).rc
DEFFILE = $(SRCDIR)\$(NAME).def

HLPS    = $(BINDIR)\help\Kniffel_en.hlp $(BINDIR)\help\Kniffel_es.hlp $(BINDIR)\help\Kniffel_nl.hlp $(BINDIR)\help\Kniffel_de.hlp $(BINDIR)\help\Kniffel_fr.hlp $(BINDIR)\help\Kniffel_it.hlp

# ============================================================================
# Targets
# ============================================================================

all : $(BINDIR)\$(NAME).exe $(HLPS) .SYMBOLIC

$(BINDIR) :
	@if not exist $(BINDIR) mkdir $(BINDIR)

$(BINDIR)\help : $(BINDIR)
	@if not exist $(BINDIR)\help mkdir $(BINDIR)\help

$(BINDIR)\$(NAME).exe : $(OBJS) $(ROBJ) $(DEFFILE)
	@echo Linking $(NAME).exe...
	@$(LINK) $(LFLAGS) name $(BINDIR)\$(NAME).exe file $(BINDIR)\kniffel.obj, $(BINDIR)\lang.obj library os2386.lib
	@echo Binding resources...
	@$(RC) -q -bt=os2 $(ROBJ) $(BINDIR)\$(NAME).exe
	@if exist $(BINDIR)\$(NAME).exe echo BUILD OK

# ============================================================================
# Objects
# ============================================================================

$(BINDIR)\kniffel.obj : $(SRCDIR)\kniffel.c $(SRCDIR)\kniffel.h $(SRCDIR)\lang.h $(BINDIR)
	@echo Compiling src\kniffel.c
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\kniffel.c

$(BINDIR)\lang.obj : $(SRCDIR)\lang.c $(SRCDIR)\lang.h $(BINDIR)
	@echo Compiling src\lang.c
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\lang.c

# ============================================================================
# Resources
# ============================================================================

$(ROBJ) : $(RCFILE) $(SRCDIR)\kniffel.h $(SRCDIR)\kniffel.ico $(BINDIR)
	@echo Compiling resources...
	@$(RC) $(RCFLAGS) -fo=$(ROBJ) $(RCFILE)

# ============================================================================
# Help files (one per language, compiled with wipfc)
# ============================================================================

$(BINDIR)\help\Kniffel_en.hlp : help\Kniffel_en.ipf $(BINDIR)\help
	@echo Compiling help\Kniffel_en.ipf
	@$(WIPFC) -o $@ help\Kniffel_en.ipf

$(BINDIR)\help\Kniffel_es.hlp : help\Kniffel_es.ipf $(BINDIR)\help
	@echo Compiling help\Kniffel_es.ipf
	@$(WIPFC) -o $@ help\Kniffel_es.ipf

$(BINDIR)\help\Kniffel_nl.hlp : help\Kniffel_nl.ipf $(BINDIR)\help
	@echo Compiling help\Kniffel_nl.ipf
	@$(WIPFC) -o $@ help\Kniffel_nl.ipf

$(BINDIR)\help\Kniffel_de.hlp : help\Kniffel_de.ipf $(BINDIR)\help
	@echo Compiling help\Kniffel_de.ipf
	@$(WIPFC) -l de_DE -o $@ help\Kniffel_de.ipf

$(BINDIR)\help\Kniffel_fr.hlp : help\Kniffel_fr.ipf $(BINDIR)\help
	@echo Compiling help\Kniffel_fr.ipf
	@$(WIPFC) -l fr_FR -o $@ help\Kniffel_fr.ipf

$(BINDIR)\help\Kniffel_it.hlp : help\Kniffel_it.ipf $(BINDIR)\help
	@echo Compiling help\Kniffel_it.ipf
	@$(WIPFC) -o $@ help\Kniffel_it.ipf

# ============================================================================
# Clean
# ============================================================================

clean : .SYMBOLIC
	@if exist $(BINDIR)\*.obj del $(BINDIR)\*.obj >nul
	@if exist $(BINDIR)\*.res del $(BINDIR)\*.res >nul
	@if exist $(BINDIR)\$(NAME).exe del $(BINDIR)\$(NAME).exe >nul
	@if exist $(BINDIR)\$(NAME).map del $(BINDIR)\$(NAME).map >nul
	@if exist $(BINDIR)\help\*.hlp del $(BINDIR)\help\*.hlp >nul
	@echo Clean complete
