##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=hiredis
ConfigurationName      :=Debug
WorkspacePath          :=D:/code/windows_develop/code
ProjectPath            :=D:/code/windows_develop/lib/hiredis-mingw-master
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=zhangqi
Date                   :=17/04/2020
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=D:/msys64/mingw64/bin/g++.exe
SharedObjectLinkerName :=D:/msys64/mingw64/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=../lib/lib$(ProjectName).dll
Preprocessors          :=$(PreprocessorSwitch)_WIN32_WINNT=0x0600 $(PreprocessorSwitch)NO_OLDNAMES 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="hiredis.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=D:/msys64/mingw64/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)ws2_32 
ArLibs                 :=  "ws2_32" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := D:/msys64/mingw64/bin/ar.exe rcu
CXX      := D:/msys64/mingw64/bin/g++.exe
CC       := D:/msys64/mingw64/bin/gcc.exe
CXXFLAGS :=  -g $(Preprocessors)
CFLAGS   :=  -g -std=c99 $(Preprocessors)
ASFLAGS  := 
AS       := D:/msys64/mingw64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/dict.c$(ObjectSuffix) $(IntermediateDirectory)/hiredis.c$(ObjectSuffix) $(IntermediateDirectory)/net.c$(ObjectSuffix) $(IntermediateDirectory)/net_win32.c$(ObjectSuffix) $(IntermediateDirectory)/sds.c$(ObjectSuffix) $(IntermediateDirectory)/read.c$(ObjectSuffix) $(IntermediateDirectory)/crossplatform.c$(ObjectSuffix) $(IntermediateDirectory)/async.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(SharedObjectLinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)
	@$(MakeDirCommand) "D:\code\windows_develop\code/.build-debug"
	@echo rebuilt > "D:\code\windows_develop\code/.build-debug/hiredis"

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/dict.c$(ObjectSuffix): dict.c $(IntermediateDirectory)/dict.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/code/windows_develop/lib/hiredis-mingw-master/dict.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/dict.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dict.c$(DependSuffix): dict.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/dict.c$(ObjectSuffix) -MF$(IntermediateDirectory)/dict.c$(DependSuffix) -MM dict.c

$(IntermediateDirectory)/dict.c$(PreprocessSuffix): dict.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dict.c$(PreprocessSuffix) dict.c

$(IntermediateDirectory)/hiredis.c$(ObjectSuffix): hiredis.c $(IntermediateDirectory)/hiredis.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/code/windows_develop/lib/hiredis-mingw-master/hiredis.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/hiredis.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/hiredis.c$(DependSuffix): hiredis.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/hiredis.c$(ObjectSuffix) -MF$(IntermediateDirectory)/hiredis.c$(DependSuffix) -MM hiredis.c

$(IntermediateDirectory)/hiredis.c$(PreprocessSuffix): hiredis.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/hiredis.c$(PreprocessSuffix) hiredis.c

$(IntermediateDirectory)/net.c$(ObjectSuffix): net.c $(IntermediateDirectory)/net.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/code/windows_develop/lib/hiredis-mingw-master/net.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/net.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/net.c$(DependSuffix): net.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/net.c$(ObjectSuffix) -MF$(IntermediateDirectory)/net.c$(DependSuffix) -MM net.c

$(IntermediateDirectory)/net.c$(PreprocessSuffix): net.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/net.c$(PreprocessSuffix) net.c

$(IntermediateDirectory)/net_win32.c$(ObjectSuffix): net_win32.c $(IntermediateDirectory)/net_win32.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/code/windows_develop/lib/hiredis-mingw-master/net_win32.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/net_win32.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/net_win32.c$(DependSuffix): net_win32.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/net_win32.c$(ObjectSuffix) -MF$(IntermediateDirectory)/net_win32.c$(DependSuffix) -MM net_win32.c

$(IntermediateDirectory)/net_win32.c$(PreprocessSuffix): net_win32.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/net_win32.c$(PreprocessSuffix) net_win32.c

$(IntermediateDirectory)/sds.c$(ObjectSuffix): sds.c $(IntermediateDirectory)/sds.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/code/windows_develop/lib/hiredis-mingw-master/sds.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sds.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sds.c$(DependSuffix): sds.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sds.c$(ObjectSuffix) -MF$(IntermediateDirectory)/sds.c$(DependSuffix) -MM sds.c

$(IntermediateDirectory)/sds.c$(PreprocessSuffix): sds.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sds.c$(PreprocessSuffix) sds.c

$(IntermediateDirectory)/read.c$(ObjectSuffix): read.c $(IntermediateDirectory)/read.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/code/windows_develop/lib/hiredis-mingw-master/read.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/read.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/read.c$(DependSuffix): read.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/read.c$(ObjectSuffix) -MF$(IntermediateDirectory)/read.c$(DependSuffix) -MM read.c

$(IntermediateDirectory)/read.c$(PreprocessSuffix): read.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/read.c$(PreprocessSuffix) read.c

$(IntermediateDirectory)/crossplatform.c$(ObjectSuffix): crossplatform.c $(IntermediateDirectory)/crossplatform.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/code/windows_develop/lib/hiredis-mingw-master/crossplatform.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/crossplatform.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/crossplatform.c$(DependSuffix): crossplatform.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/crossplatform.c$(ObjectSuffix) -MF$(IntermediateDirectory)/crossplatform.c$(DependSuffix) -MM crossplatform.c

$(IntermediateDirectory)/crossplatform.c$(PreprocessSuffix): crossplatform.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/crossplatform.c$(PreprocessSuffix) crossplatform.c

$(IntermediateDirectory)/async.c$(ObjectSuffix): async.c $(IntermediateDirectory)/async.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/code/windows_develop/lib/hiredis-mingw-master/async.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/async.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/async.c$(DependSuffix): async.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/async.c$(ObjectSuffix) -MF$(IntermediateDirectory)/async.c$(DependSuffix) -MM async.c

$(IntermediateDirectory)/async.c$(PreprocessSuffix): async.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/async.c$(PreprocessSuffix) async.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


