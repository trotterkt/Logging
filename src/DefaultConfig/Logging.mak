
############# Target type (Debug/Release) ##################
############################################################
CPPCompileDebug= /Zi /Od /D "_DEBUG" $(LIBCRT_FLAG)d  /Fd"$(TARGET_NAME)" 
CPPCompileRelease= /Ox /D"NDEBUG" $(LIBCRT_FLAG) /Fd"$(TARGET_NAME)" 
LinkDebug=
LinkRelease=
BuildSet=Debug
SUBSYSTEM=/SUBSYSTEM:console
RPFrameWorkDll=False
SimulinkLibName=

ConfigurationCPPCompileSwitches=   /I . /I . /I $(OMROOT)\LangCpp /I $(OMROOT)\LangCpp\oxf /nologo /W3 $(ENABLE_EH) $(CRT_FLAGS) $(CPPCompileDebug) /D "_AFXDLL" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "_WINDOWS" $(INST_FLAGS) $(INCLUDE_PATH) $(INST_INCLUDES) /c   

!IF "$(RPFrameWorkDll)" == "True"
ConfigurationCPPCompileSwitches=$(ConfigurationCPPCompileSwitches) /D "FRAMEWORK_DLL"
!ENDIF

################### Compilation flags ######################
############################################################
INCLUDE_QUALIFIER=/I
DEFINE_QUALIFIER=/D

!IF "False" == "True"
MT_PREFIX=MT
LIBCRT_FLAG=/MT
!ELSE
MT_PREFIX=
LIBCRT_FLAG=/MD
!ENDIF

LIB_PREFIX=MSVC10x86$(MT_PREFIX)

CRT_FLAGS=$(DEFINE_QUALIFIER)_CRT_SECURE_NO_DEPRECATE $(DEFINE_QUALIFIER)_CRT_SECURE_NO_WARNINGS
ENABLE_EH=/EHa

WINMM_LIB=winmm.lib

################### Commands definition #########################
#################################################################
RMDIR = rmdir
LIB_CMD=link.exe -lib
LINK_CMD=link.exe
LIB_FLAGS=$(LinkDebug)  /NOLOGO   
LINK_FLAGS=$(LinkDebug)  /NOLOGO    $(SUBSYSTEM) /MACHINE:x86 

############### Generated macros #################
##################################################

FLAGSFILE=
RULESFILE=
OMROOT="c:\Apps\IBM\rational\Rhapsody\8.1.3\Share"
RHPROOT="c:\Apps\IBM\rational\Rhapsody\8.1.3"

CPP_EXT=.cpp
H_EXT=.h
OBJ_EXT=.obj
EXE_EXT=.exe
LIB_EXT=.lib

INSTRUMENTATION=None

TIME_MODEL=RealTime

TARGET_TYPE=Executable

TARGET_NAME=Logging

all : $(TARGET_NAME)$(EXE_EXT) Logging.mak

TARGET_MAIN=MainLogging

LIBS=

INCLUDE_PATH= \
  $(INCLUDE_QUALIFIER)$(OMROOT)/LangCpp/osconfig/WIN32

ADDITIONAL_OBJS=

OBJS= \
  Default\PFWBroker.obj \
  Default\PFWFileBroker.obj \
  Default\PFWXmlBroker.obj \
  Default\TestEquipmentBroker.obj




OBJ_DIR=

!IF "$(OBJ_DIR)"!=""
CREATE_OBJ_DIR=if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
CLEAN_OBJ_DIR= if exist $(OBJ_DIR) $(RMDIR) $(OBJ_DIR)
!ELSE
CREATE_OBJ_DIR=
CLEAN_OBJ_DIR=
!ENDIF

######################## Predefined macros ############################
#######################################################################
!IF "$(OBJS)" != ""
$(OBJS) : $(INST_LIBS) $(OXF_LIBS)
!ENDIF

LIB_POSTFIX=
!IF "$(BuildSet)"=="Release"
LIB_POSTFIX=R
!ENDIF

!IF "$(TARGET_TYPE)" == "Executable"
LinkDebug=$(LinkDebug) /DEBUG
LinkRelease=$(LinkRelease) /OPT:NOREF
!ELSEIF "$(TARGET_TYPE)" == "Library"
LinkDebug=$(LinkDebug)
!ENDIF


!IF "$(INSTRUMENTATION)" == "Animation"
INST_FLAGS=/D "OMANIMATOR"
INST_INCLUDES=/I $(OMROOT)\LangCpp\aom /I $(OMROOT)\LangCpp\tom
!IF "$(RPFrameWorkDll)" == "True"
INST_LIBS= 
OXF_LIBS=$(OMROOT)\LangCpp\lib\$(LIB_PREFIX)oxfanimdll$(LIB_POSTFIX)$(LIB_EXT) 
!ELSE
INST_LIBS= $(OMROOT)\LangCpp\lib\$(LIB_PREFIX)aomanim$(LIB_POSTFIX)$(LIB_EXT) $(OMROOT)\LangCpp\lib\$(LIB_PREFIX)oxsiminst$(LIB_POSTFIX)$(LIB_EXT)
OXF_LIBS=$(OMROOT)\LangCpp\lib\$(LIB_PREFIX)oxfinst$(LIB_POSTFIX)$(LIB_EXT) $(OMROOT)\LangCpp\lib\$(LIB_PREFIX)omComAppl$(LIB_POSTFIX)$(LIB_EXT) $(SimulinkLibName)
!ENDIF
SOCK_LIB=wsock32.lib

!ELSEIF "$(INSTRUMENTATION)" == "Tracing"
INST_FLAGS=/D "OMTRACER"
INST_INCLUDES=/I $(OMROOT)\LangCpp\aom /I $(OMROOT)\LangCpp\tom
!IF "$(RPFrameWorkDll)" == "True"
INST_LIBS=
OXF_LIBS= $(OMROOT)\LangCpp\lib\$(LIB_PREFIX)oxftracedll$(LIB_POSTFIX)$(LIB_EXT) 
!ELSE
INST_LIBS=$(OMROOT)\LangCpp\lib\$(LIB_PREFIX)tomtrace$(LIB_POSTFIX)$(LIB_EXT) $(OMROOT)\LangCpp\lib\$(LIB_PREFIX)aomtrace$(LIB_POSTFIX)$(LIB_EXT) $(OMROOT)\LangCpp\lib\$(LIB_PREFIX)oxsiminst$(LIB_POSTFIX)$(LIB_EXT)
OXF_LIBS= $(OMROOT)\LangCpp\lib\$(LIB_PREFIX)oxfinst$(LIB_POSTFIX)$(LIB_EXT) $(OMROOT)\LangCpp\lib\$(LIB_PREFIX)omComAppl$(LIB_POSTFIX)$(LIB_EXT) $(SimulinkLibName)
!ENDIF
SOCK_LIB=wsock32.lib

!ELSEIF "$(INSTRUMENTATION)" == "None" 
INST_FLAGS=
INST_INCLUDES=
INST_LIBS=
!IF "$(RPFrameWorkDll)" == "True"
OXF_LIBS=$(OMROOT)\LangCpp\lib\$(LIB_PREFIX)oxfdll$(LIB_POSTFIX)$(LIB_EXT) $(OMROOT)\LangCpp\lib\$(LIB_PREFIX)oxsim$(LIB_POSTFIX)$(LIB_EXT)
!ELSE
OXF_LIBS=$(OMROOT)\LangCpp\lib\$(LIB_PREFIX)oxf$(LIB_POSTFIX)$(LIB_EXT) $(SimulinkLibName) $(OMROOT)\LangCpp\lib\$(LIB_PREFIX)oxsim$(LIB_POSTFIX)$(LIB_EXT)
!ENDIF
SOCK_LIB=

!ELSE
!ERROR An invalid Instrumentation $(INSTRUMENTATION) is specified.
!ENDIF



################## Generated dependencies ########################
##################################################################






Default\PFWBroker.obj : Default\PFWBroker.cpp Default\PFWBroker.h    Default\Cache.h 
	$(CREATE_OBJ_DIR)
	$(CPP) $(ConfigurationCPPCompileSwitches)  /Fo"Default\PFWBroker.obj" "Default\PFWBroker.cpp" 



Default\PFWFileBroker.obj : Default\PFWFileBroker.cpp Default\PFWFileBroker.h    Default\PFWBroker.h Default\Cache.h 
	$(CREATE_OBJ_DIR)
	$(CPP) $(ConfigurationCPPCompileSwitches)  /Fo"Default\PFWFileBroker.obj" "Default\PFWFileBroker.cpp" 



Default\PFWXmlBroker.obj : Default\PFWXmlBroker.cpp Default\PFWXmlBroker.h    Default\PFWBroker.h Default\Cache.h 
	$(CREATE_OBJ_DIR)
	$(CPP) $(ConfigurationCPPCompileSwitches)  /Fo"Default\PFWXmlBroker.obj" "Default\PFWXmlBroker.cpp" 



Default\TestEquipmentBroker.obj : Default\TestEquipmentBroker.cpp Default\TestEquipmentBroker.h    Default\PFWFileBroker.h Default\Singleton.h Default\PFWBroker.h Default\Cache.h 
	$(CREATE_OBJ_DIR)
	$(CPP) $(ConfigurationCPPCompileSwitches)  /Fo"Default\TestEquipmentBroker.obj" "Default\TestEquipmentBroker.cpp" 






$(TARGET_MAIN)$(OBJ_EXT) : $(TARGET_MAIN)$(CPP_EXT) $(OBJS) 
	$(CPP) $(ConfigurationCPPCompileSwitches) /Fo"$(TARGET_MAIN)$(OBJ_EXT)" $(TARGET_MAIN)$(CPP_EXT)

########################## Linking instructions ###############################
###############################################################################
$(TARGET_NAME)$(EXE_EXT): $(OBJS) $(ADDITIONAL_OBJS) $(TARGET_MAIN)$(OBJ_EXT) Logging.mak 
	@echo Linking $(TARGET_NAME)$(EXE_EXT)
	$(LINK_CMD)  $(TARGET_MAIN)$(OBJ_EXT) $(OBJS) $(ADDITIONAL_OBJS) \
	$(LIBS) \
	$(INST_LIBS) \
	$(OXF_LIBS) \
	$(SOCK_LIB) \
	$(WINMM_LIB) \
	$(LINK_FLAGS) /out:$(TARGET_NAME)$(EXE_EXT)
	if exist $(TARGET_NAME)$(EXE_EXT).manifest mt.exe -manifest $@.manifest -outputresource:$(TARGET_NAME)$(EXE_EXT);1



$(TARGET_NAME)$(LIB_EXT) : $(OBJS) $(ADDITIONAL_OBJS) Logging.mak
	@echo Building library $@
	$(LIB_CMD) $(LIB_FLAGS) /out:$(TARGET_NAME)$(LIB_EXT) $(OBJS) $(ADDITIONAL_OBJS) $(LIBS)

clean:
	@echo Cleanup
	if exist Default\PFWBroker.obj erase Default\PFWBroker.obj
	if exist Default\PFWFileBroker.obj erase Default\PFWFileBroker.obj
	if exist Default\PFWXmlBroker.obj erase Default\PFWXmlBroker.obj
	if exist Default\TestEquipmentBroker.obj erase Default\TestEquipmentBroker.obj
	if exist $(TARGET_MAIN)$(OBJ_EXT) erase $(TARGET_MAIN)$(OBJ_EXT)
	if exist *$(OBJ_EXT) erase *$(OBJ_EXT)
	if exist $(TARGET_NAME).pdb erase $(TARGET_NAME).pdb
	if exist $(TARGET_NAME)$(LIB_EXT) erase $(TARGET_NAME)$(LIB_EXT)
	if exist $(TARGET_NAME).ilk erase $(TARGET_NAME).ilk
	if exist $(TARGET_NAME)$(EXE_EXT) erase $(TARGET_NAME)$(EXE_EXT)
	if exist $(TARGET_NAME)$(EXE_EXT).manifest erase $(TARGET_NAME)$(EXE_EXT).manifest
	$(CLEAN_OBJ_DIR)
	
