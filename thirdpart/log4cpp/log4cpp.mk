##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=log4cpp
ConfigurationName      :=Debug
WorkspacePath          :=D:/me/zby_libuv
ProjectPath            :=D:/me/zby_libuv/log4cpp
IntermediateDirectory  :=./Debug/$(ProjectName)
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=zhangqi
Date                   :=04/07/2019
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=D:/mingw/mingw64/bin/g++.exe
SharedObjectLinkerName :=D:/mingw/mingw64/bin/g++.exe -shared -fPIC
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
Preprocessors          :=$(PreprocessorSwitch)LOG4CPP_HAVE_INT64_T 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="log4cpp.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=D:/mingw/mingw64/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)ws2_32 
ArLibs                 :=  "ws2_32" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := D:/mingw/mingw64/bin/ar.exe rcu
CXX      := D:/mingw/mingw64/bin/g++.exe
CC       := D:/mingw/mingw64/bin/gcc.exe
CXXFLAGS :=  -g $(Preprocessors)
CFLAGS   :=  -g $(Preprocessors)
ASFLAGS  := 
AS       := D:/mingw/mingw64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/src_LevelEvaluator.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_LoggingEvent.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_MSThreads.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_DllMain.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_NDC.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_NTEventLogAppender.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_AppenderSkeleton.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_BasicLayout.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Manipulator.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_PortabilityImpl.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/src_SyslogAppender.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_LayoutsFactory.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_CategoryStream.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_TimeStamp.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_StringQueueAppender.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Priority.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Win32DebugAppender.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Configurator.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Localtime.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_RemoteSyslogAppender.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/src_DummyThreads.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_PThreads.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_PatternLayout.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_PassThroughLayout.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_OmniThreads.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_OstreamAppender.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_FixedContextCategory.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_BufferingAppender.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_PropertyConfiguratorImpl.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_StringUtil.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/src_SimpleConfigurator.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_SmtpAppender.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_LayoutAppender.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_IdsaAppender.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Filter.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_FileAppender.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_TriggeringEventEvaluatorFactory.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_BasicConfigurator.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_HierarchyMaintainer.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_FactoryParams.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/src_DailyRollingFileAppender.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_SimpleLayout.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_PropertyConfigurator.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Category.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_AppendersFactory.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Appender.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Properties.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_AbortAppender.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_RollingFileAppender.cpp$(ObjectSuffix) 



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
	@$(MakeDirCommand) "D:\me\zby_libuv/.build-windows"
	@echo rebuilt > "D:\me\zby_libuv/.build-windows/log4cpp"

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug/$(ProjectName)"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug/$(ProjectName)"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_LevelEvaluator.cpp$(ObjectSuffix): src/LevelEvaluator.cpp $(IntermediateDirectory)/src_LevelEvaluator.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/LevelEvaluator.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_LevelEvaluator.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_LevelEvaluator.cpp$(DependSuffix): src/LevelEvaluator.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_LevelEvaluator.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_LevelEvaluator.cpp$(DependSuffix) -MM src/LevelEvaluator.cpp

$(IntermediateDirectory)/src_LevelEvaluator.cpp$(PreprocessSuffix): src/LevelEvaluator.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_LevelEvaluator.cpp$(PreprocessSuffix) src/LevelEvaluator.cpp

$(IntermediateDirectory)/src_LoggingEvent.cpp$(ObjectSuffix): src/LoggingEvent.cpp $(IntermediateDirectory)/src_LoggingEvent.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/LoggingEvent.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_LoggingEvent.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_LoggingEvent.cpp$(DependSuffix): src/LoggingEvent.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_LoggingEvent.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_LoggingEvent.cpp$(DependSuffix) -MM src/LoggingEvent.cpp

$(IntermediateDirectory)/src_LoggingEvent.cpp$(PreprocessSuffix): src/LoggingEvent.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_LoggingEvent.cpp$(PreprocessSuffix) src/LoggingEvent.cpp

$(IntermediateDirectory)/src_MSThreads.cpp$(ObjectSuffix): src/MSThreads.cpp $(IntermediateDirectory)/src_MSThreads.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/MSThreads.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_MSThreads.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_MSThreads.cpp$(DependSuffix): src/MSThreads.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_MSThreads.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_MSThreads.cpp$(DependSuffix) -MM src/MSThreads.cpp

$(IntermediateDirectory)/src_MSThreads.cpp$(PreprocessSuffix): src/MSThreads.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_MSThreads.cpp$(PreprocessSuffix) src/MSThreads.cpp

$(IntermediateDirectory)/src_DllMain.cpp$(ObjectSuffix): src/DllMain.cpp $(IntermediateDirectory)/src_DllMain.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/DllMain.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_DllMain.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_DllMain.cpp$(DependSuffix): src/DllMain.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_DllMain.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_DllMain.cpp$(DependSuffix) -MM src/DllMain.cpp

$(IntermediateDirectory)/src_DllMain.cpp$(PreprocessSuffix): src/DllMain.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_DllMain.cpp$(PreprocessSuffix) src/DllMain.cpp

$(IntermediateDirectory)/src_NDC.cpp$(ObjectSuffix): src/NDC.cpp $(IntermediateDirectory)/src_NDC.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/NDC.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_NDC.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_NDC.cpp$(DependSuffix): src/NDC.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_NDC.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_NDC.cpp$(DependSuffix) -MM src/NDC.cpp

$(IntermediateDirectory)/src_NDC.cpp$(PreprocessSuffix): src/NDC.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_NDC.cpp$(PreprocessSuffix) src/NDC.cpp

$(IntermediateDirectory)/src_NTEventLogAppender.cpp$(ObjectSuffix): src/NTEventLogAppender.cpp $(IntermediateDirectory)/src_NTEventLogAppender.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/NTEventLogAppender.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_NTEventLogAppender.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_NTEventLogAppender.cpp$(DependSuffix): src/NTEventLogAppender.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_NTEventLogAppender.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_NTEventLogAppender.cpp$(DependSuffix) -MM src/NTEventLogAppender.cpp

$(IntermediateDirectory)/src_NTEventLogAppender.cpp$(PreprocessSuffix): src/NTEventLogAppender.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_NTEventLogAppender.cpp$(PreprocessSuffix) src/NTEventLogAppender.cpp

$(IntermediateDirectory)/src_AppenderSkeleton.cpp$(ObjectSuffix): src/AppenderSkeleton.cpp $(IntermediateDirectory)/src_AppenderSkeleton.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/AppenderSkeleton.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_AppenderSkeleton.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_AppenderSkeleton.cpp$(DependSuffix): src/AppenderSkeleton.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_AppenderSkeleton.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_AppenderSkeleton.cpp$(DependSuffix) -MM src/AppenderSkeleton.cpp

$(IntermediateDirectory)/src_AppenderSkeleton.cpp$(PreprocessSuffix): src/AppenderSkeleton.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_AppenderSkeleton.cpp$(PreprocessSuffix) src/AppenderSkeleton.cpp

$(IntermediateDirectory)/src_BasicLayout.cpp$(ObjectSuffix): src/BasicLayout.cpp $(IntermediateDirectory)/src_BasicLayout.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/BasicLayout.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_BasicLayout.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_BasicLayout.cpp$(DependSuffix): src/BasicLayout.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_BasicLayout.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_BasicLayout.cpp$(DependSuffix) -MM src/BasicLayout.cpp

$(IntermediateDirectory)/src_BasicLayout.cpp$(PreprocessSuffix): src/BasicLayout.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_BasicLayout.cpp$(PreprocessSuffix) src/BasicLayout.cpp

$(IntermediateDirectory)/src_Manipulator.cpp$(ObjectSuffix): src/Manipulator.cpp $(IntermediateDirectory)/src_Manipulator.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/Manipulator.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Manipulator.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Manipulator.cpp$(DependSuffix): src/Manipulator.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Manipulator.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Manipulator.cpp$(DependSuffix) -MM src/Manipulator.cpp

$(IntermediateDirectory)/src_Manipulator.cpp$(PreprocessSuffix): src/Manipulator.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Manipulator.cpp$(PreprocessSuffix) src/Manipulator.cpp

$(IntermediateDirectory)/src_PortabilityImpl.cpp$(ObjectSuffix): src/PortabilityImpl.cpp $(IntermediateDirectory)/src_PortabilityImpl.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/PortabilityImpl.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_PortabilityImpl.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_PortabilityImpl.cpp$(DependSuffix): src/PortabilityImpl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_PortabilityImpl.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_PortabilityImpl.cpp$(DependSuffix) -MM src/PortabilityImpl.cpp

$(IntermediateDirectory)/src_PortabilityImpl.cpp$(PreprocessSuffix): src/PortabilityImpl.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_PortabilityImpl.cpp$(PreprocessSuffix) src/PortabilityImpl.cpp

$(IntermediateDirectory)/src_SyslogAppender.cpp$(ObjectSuffix): src/SyslogAppender.cpp $(IntermediateDirectory)/src_SyslogAppender.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/SyslogAppender.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_SyslogAppender.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_SyslogAppender.cpp$(DependSuffix): src/SyslogAppender.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_SyslogAppender.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_SyslogAppender.cpp$(DependSuffix) -MM src/SyslogAppender.cpp

$(IntermediateDirectory)/src_SyslogAppender.cpp$(PreprocessSuffix): src/SyslogAppender.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_SyslogAppender.cpp$(PreprocessSuffix) src/SyslogAppender.cpp

$(IntermediateDirectory)/src_LayoutsFactory.cpp$(ObjectSuffix): src/LayoutsFactory.cpp $(IntermediateDirectory)/src_LayoutsFactory.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/LayoutsFactory.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_LayoutsFactory.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_LayoutsFactory.cpp$(DependSuffix): src/LayoutsFactory.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_LayoutsFactory.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_LayoutsFactory.cpp$(DependSuffix) -MM src/LayoutsFactory.cpp

$(IntermediateDirectory)/src_LayoutsFactory.cpp$(PreprocessSuffix): src/LayoutsFactory.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_LayoutsFactory.cpp$(PreprocessSuffix) src/LayoutsFactory.cpp

$(IntermediateDirectory)/src_CategoryStream.cpp$(ObjectSuffix): src/CategoryStream.cpp $(IntermediateDirectory)/src_CategoryStream.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/CategoryStream.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_CategoryStream.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_CategoryStream.cpp$(DependSuffix): src/CategoryStream.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_CategoryStream.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_CategoryStream.cpp$(DependSuffix) -MM src/CategoryStream.cpp

$(IntermediateDirectory)/src_CategoryStream.cpp$(PreprocessSuffix): src/CategoryStream.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_CategoryStream.cpp$(PreprocessSuffix) src/CategoryStream.cpp

$(IntermediateDirectory)/src_TimeStamp.cpp$(ObjectSuffix): src/TimeStamp.cpp $(IntermediateDirectory)/src_TimeStamp.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/TimeStamp.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_TimeStamp.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_TimeStamp.cpp$(DependSuffix): src/TimeStamp.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_TimeStamp.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_TimeStamp.cpp$(DependSuffix) -MM src/TimeStamp.cpp

$(IntermediateDirectory)/src_TimeStamp.cpp$(PreprocessSuffix): src/TimeStamp.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_TimeStamp.cpp$(PreprocessSuffix) src/TimeStamp.cpp

$(IntermediateDirectory)/src_StringQueueAppender.cpp$(ObjectSuffix): src/StringQueueAppender.cpp $(IntermediateDirectory)/src_StringQueueAppender.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/StringQueueAppender.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_StringQueueAppender.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_StringQueueAppender.cpp$(DependSuffix): src/StringQueueAppender.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_StringQueueAppender.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_StringQueueAppender.cpp$(DependSuffix) -MM src/StringQueueAppender.cpp

$(IntermediateDirectory)/src_StringQueueAppender.cpp$(PreprocessSuffix): src/StringQueueAppender.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_StringQueueAppender.cpp$(PreprocessSuffix) src/StringQueueAppender.cpp

$(IntermediateDirectory)/src_Priority.cpp$(ObjectSuffix): src/Priority.cpp $(IntermediateDirectory)/src_Priority.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/Priority.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Priority.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Priority.cpp$(DependSuffix): src/Priority.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Priority.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Priority.cpp$(DependSuffix) -MM src/Priority.cpp

$(IntermediateDirectory)/src_Priority.cpp$(PreprocessSuffix): src/Priority.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Priority.cpp$(PreprocessSuffix) src/Priority.cpp

$(IntermediateDirectory)/src_Win32DebugAppender.cpp$(ObjectSuffix): src/Win32DebugAppender.cpp $(IntermediateDirectory)/src_Win32DebugAppender.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/Win32DebugAppender.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Win32DebugAppender.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Win32DebugAppender.cpp$(DependSuffix): src/Win32DebugAppender.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Win32DebugAppender.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Win32DebugAppender.cpp$(DependSuffix) -MM src/Win32DebugAppender.cpp

$(IntermediateDirectory)/src_Win32DebugAppender.cpp$(PreprocessSuffix): src/Win32DebugAppender.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Win32DebugAppender.cpp$(PreprocessSuffix) src/Win32DebugAppender.cpp

$(IntermediateDirectory)/src_Configurator.cpp$(ObjectSuffix): src/Configurator.cpp $(IntermediateDirectory)/src_Configurator.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/Configurator.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Configurator.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Configurator.cpp$(DependSuffix): src/Configurator.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Configurator.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Configurator.cpp$(DependSuffix) -MM src/Configurator.cpp

$(IntermediateDirectory)/src_Configurator.cpp$(PreprocessSuffix): src/Configurator.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Configurator.cpp$(PreprocessSuffix) src/Configurator.cpp

$(IntermediateDirectory)/src_Localtime.cpp$(ObjectSuffix): src/Localtime.cpp $(IntermediateDirectory)/src_Localtime.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/Localtime.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Localtime.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Localtime.cpp$(DependSuffix): src/Localtime.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Localtime.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Localtime.cpp$(DependSuffix) -MM src/Localtime.cpp

$(IntermediateDirectory)/src_Localtime.cpp$(PreprocessSuffix): src/Localtime.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Localtime.cpp$(PreprocessSuffix) src/Localtime.cpp

$(IntermediateDirectory)/src_RemoteSyslogAppender.cpp$(ObjectSuffix): src/RemoteSyslogAppender.cpp $(IntermediateDirectory)/src_RemoteSyslogAppender.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/RemoteSyslogAppender.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_RemoteSyslogAppender.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_RemoteSyslogAppender.cpp$(DependSuffix): src/RemoteSyslogAppender.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_RemoteSyslogAppender.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_RemoteSyslogAppender.cpp$(DependSuffix) -MM src/RemoteSyslogAppender.cpp

$(IntermediateDirectory)/src_RemoteSyslogAppender.cpp$(PreprocessSuffix): src/RemoteSyslogAppender.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_RemoteSyslogAppender.cpp$(PreprocessSuffix) src/RemoteSyslogAppender.cpp

$(IntermediateDirectory)/src_DummyThreads.cpp$(ObjectSuffix): src/DummyThreads.cpp $(IntermediateDirectory)/src_DummyThreads.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/DummyThreads.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_DummyThreads.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_DummyThreads.cpp$(DependSuffix): src/DummyThreads.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_DummyThreads.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_DummyThreads.cpp$(DependSuffix) -MM src/DummyThreads.cpp

$(IntermediateDirectory)/src_DummyThreads.cpp$(PreprocessSuffix): src/DummyThreads.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_DummyThreads.cpp$(PreprocessSuffix) src/DummyThreads.cpp

$(IntermediateDirectory)/src_PThreads.cpp$(ObjectSuffix): src/PThreads.cpp $(IntermediateDirectory)/src_PThreads.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/PThreads.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_PThreads.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_PThreads.cpp$(DependSuffix): src/PThreads.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_PThreads.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_PThreads.cpp$(DependSuffix) -MM src/PThreads.cpp

$(IntermediateDirectory)/src_PThreads.cpp$(PreprocessSuffix): src/PThreads.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_PThreads.cpp$(PreprocessSuffix) src/PThreads.cpp

$(IntermediateDirectory)/src_PatternLayout.cpp$(ObjectSuffix): src/PatternLayout.cpp $(IntermediateDirectory)/src_PatternLayout.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/PatternLayout.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_PatternLayout.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_PatternLayout.cpp$(DependSuffix): src/PatternLayout.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_PatternLayout.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_PatternLayout.cpp$(DependSuffix) -MM src/PatternLayout.cpp

$(IntermediateDirectory)/src_PatternLayout.cpp$(PreprocessSuffix): src/PatternLayout.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_PatternLayout.cpp$(PreprocessSuffix) src/PatternLayout.cpp

$(IntermediateDirectory)/src_PassThroughLayout.cpp$(ObjectSuffix): src/PassThroughLayout.cpp $(IntermediateDirectory)/src_PassThroughLayout.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/PassThroughLayout.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_PassThroughLayout.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_PassThroughLayout.cpp$(DependSuffix): src/PassThroughLayout.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_PassThroughLayout.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_PassThroughLayout.cpp$(DependSuffix) -MM src/PassThroughLayout.cpp

$(IntermediateDirectory)/src_PassThroughLayout.cpp$(PreprocessSuffix): src/PassThroughLayout.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_PassThroughLayout.cpp$(PreprocessSuffix) src/PassThroughLayout.cpp

$(IntermediateDirectory)/src_OmniThreads.cpp$(ObjectSuffix): src/OmniThreads.cpp $(IntermediateDirectory)/src_OmniThreads.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/OmniThreads.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_OmniThreads.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_OmniThreads.cpp$(DependSuffix): src/OmniThreads.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_OmniThreads.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_OmniThreads.cpp$(DependSuffix) -MM src/OmniThreads.cpp

$(IntermediateDirectory)/src_OmniThreads.cpp$(PreprocessSuffix): src/OmniThreads.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_OmniThreads.cpp$(PreprocessSuffix) src/OmniThreads.cpp

$(IntermediateDirectory)/src_OstreamAppender.cpp$(ObjectSuffix): src/OstreamAppender.cpp $(IntermediateDirectory)/src_OstreamAppender.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/OstreamAppender.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_OstreamAppender.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_OstreamAppender.cpp$(DependSuffix): src/OstreamAppender.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_OstreamAppender.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_OstreamAppender.cpp$(DependSuffix) -MM src/OstreamAppender.cpp

$(IntermediateDirectory)/src_OstreamAppender.cpp$(PreprocessSuffix): src/OstreamAppender.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_OstreamAppender.cpp$(PreprocessSuffix) src/OstreamAppender.cpp

$(IntermediateDirectory)/src_FixedContextCategory.cpp$(ObjectSuffix): src/FixedContextCategory.cpp $(IntermediateDirectory)/src_FixedContextCategory.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/FixedContextCategory.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_FixedContextCategory.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_FixedContextCategory.cpp$(DependSuffix): src/FixedContextCategory.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_FixedContextCategory.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_FixedContextCategory.cpp$(DependSuffix) -MM src/FixedContextCategory.cpp

$(IntermediateDirectory)/src_FixedContextCategory.cpp$(PreprocessSuffix): src/FixedContextCategory.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_FixedContextCategory.cpp$(PreprocessSuffix) src/FixedContextCategory.cpp

$(IntermediateDirectory)/src_BufferingAppender.cpp$(ObjectSuffix): src/BufferingAppender.cpp $(IntermediateDirectory)/src_BufferingAppender.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/BufferingAppender.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_BufferingAppender.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_BufferingAppender.cpp$(DependSuffix): src/BufferingAppender.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_BufferingAppender.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_BufferingAppender.cpp$(DependSuffix) -MM src/BufferingAppender.cpp

$(IntermediateDirectory)/src_BufferingAppender.cpp$(PreprocessSuffix): src/BufferingAppender.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_BufferingAppender.cpp$(PreprocessSuffix) src/BufferingAppender.cpp

$(IntermediateDirectory)/src_PropertyConfiguratorImpl.cpp$(ObjectSuffix): src/PropertyConfiguratorImpl.cpp $(IntermediateDirectory)/src_PropertyConfiguratorImpl.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/PropertyConfiguratorImpl.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_PropertyConfiguratorImpl.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_PropertyConfiguratorImpl.cpp$(DependSuffix): src/PropertyConfiguratorImpl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_PropertyConfiguratorImpl.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_PropertyConfiguratorImpl.cpp$(DependSuffix) -MM src/PropertyConfiguratorImpl.cpp

$(IntermediateDirectory)/src_PropertyConfiguratorImpl.cpp$(PreprocessSuffix): src/PropertyConfiguratorImpl.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_PropertyConfiguratorImpl.cpp$(PreprocessSuffix) src/PropertyConfiguratorImpl.cpp

$(IntermediateDirectory)/src_StringUtil.cpp$(ObjectSuffix): src/StringUtil.cpp $(IntermediateDirectory)/src_StringUtil.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/StringUtil.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_StringUtil.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_StringUtil.cpp$(DependSuffix): src/StringUtil.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_StringUtil.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_StringUtil.cpp$(DependSuffix) -MM src/StringUtil.cpp

$(IntermediateDirectory)/src_StringUtil.cpp$(PreprocessSuffix): src/StringUtil.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_StringUtil.cpp$(PreprocessSuffix) src/StringUtil.cpp

$(IntermediateDirectory)/src_SimpleConfigurator.cpp$(ObjectSuffix): src/SimpleConfigurator.cpp $(IntermediateDirectory)/src_SimpleConfigurator.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/SimpleConfigurator.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_SimpleConfigurator.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_SimpleConfigurator.cpp$(DependSuffix): src/SimpleConfigurator.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_SimpleConfigurator.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_SimpleConfigurator.cpp$(DependSuffix) -MM src/SimpleConfigurator.cpp

$(IntermediateDirectory)/src_SimpleConfigurator.cpp$(PreprocessSuffix): src/SimpleConfigurator.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_SimpleConfigurator.cpp$(PreprocessSuffix) src/SimpleConfigurator.cpp

$(IntermediateDirectory)/src_SmtpAppender.cpp$(ObjectSuffix): src/SmtpAppender.cpp $(IntermediateDirectory)/src_SmtpAppender.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/SmtpAppender.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_SmtpAppender.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_SmtpAppender.cpp$(DependSuffix): src/SmtpAppender.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_SmtpAppender.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_SmtpAppender.cpp$(DependSuffix) -MM src/SmtpAppender.cpp

$(IntermediateDirectory)/src_SmtpAppender.cpp$(PreprocessSuffix): src/SmtpAppender.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_SmtpAppender.cpp$(PreprocessSuffix) src/SmtpAppender.cpp

$(IntermediateDirectory)/src_LayoutAppender.cpp$(ObjectSuffix): src/LayoutAppender.cpp $(IntermediateDirectory)/src_LayoutAppender.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/LayoutAppender.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_LayoutAppender.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_LayoutAppender.cpp$(DependSuffix): src/LayoutAppender.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_LayoutAppender.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_LayoutAppender.cpp$(DependSuffix) -MM src/LayoutAppender.cpp

$(IntermediateDirectory)/src_LayoutAppender.cpp$(PreprocessSuffix): src/LayoutAppender.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_LayoutAppender.cpp$(PreprocessSuffix) src/LayoutAppender.cpp

$(IntermediateDirectory)/src_IdsaAppender.cpp$(ObjectSuffix): src/IdsaAppender.cpp $(IntermediateDirectory)/src_IdsaAppender.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/IdsaAppender.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_IdsaAppender.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_IdsaAppender.cpp$(DependSuffix): src/IdsaAppender.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_IdsaAppender.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_IdsaAppender.cpp$(DependSuffix) -MM src/IdsaAppender.cpp

$(IntermediateDirectory)/src_IdsaAppender.cpp$(PreprocessSuffix): src/IdsaAppender.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_IdsaAppender.cpp$(PreprocessSuffix) src/IdsaAppender.cpp

$(IntermediateDirectory)/src_Filter.cpp$(ObjectSuffix): src/Filter.cpp $(IntermediateDirectory)/src_Filter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/Filter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Filter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Filter.cpp$(DependSuffix): src/Filter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Filter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Filter.cpp$(DependSuffix) -MM src/Filter.cpp

$(IntermediateDirectory)/src_Filter.cpp$(PreprocessSuffix): src/Filter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Filter.cpp$(PreprocessSuffix) src/Filter.cpp

$(IntermediateDirectory)/src_FileAppender.cpp$(ObjectSuffix): src/FileAppender.cpp $(IntermediateDirectory)/src_FileAppender.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/FileAppender.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_FileAppender.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_FileAppender.cpp$(DependSuffix): src/FileAppender.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_FileAppender.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_FileAppender.cpp$(DependSuffix) -MM src/FileAppender.cpp

$(IntermediateDirectory)/src_FileAppender.cpp$(PreprocessSuffix): src/FileAppender.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_FileAppender.cpp$(PreprocessSuffix) src/FileAppender.cpp

$(IntermediateDirectory)/src_TriggeringEventEvaluatorFactory.cpp$(ObjectSuffix): src/TriggeringEventEvaluatorFactory.cpp $(IntermediateDirectory)/src_TriggeringEventEvaluatorFactory.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/TriggeringEventEvaluatorFactory.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_TriggeringEventEvaluatorFactory.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_TriggeringEventEvaluatorFactory.cpp$(DependSuffix): src/TriggeringEventEvaluatorFactory.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_TriggeringEventEvaluatorFactory.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_TriggeringEventEvaluatorFactory.cpp$(DependSuffix) -MM src/TriggeringEventEvaluatorFactory.cpp

$(IntermediateDirectory)/src_TriggeringEventEvaluatorFactory.cpp$(PreprocessSuffix): src/TriggeringEventEvaluatorFactory.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_TriggeringEventEvaluatorFactory.cpp$(PreprocessSuffix) src/TriggeringEventEvaluatorFactory.cpp

$(IntermediateDirectory)/src_BasicConfigurator.cpp$(ObjectSuffix): src/BasicConfigurator.cpp $(IntermediateDirectory)/src_BasicConfigurator.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/BasicConfigurator.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_BasicConfigurator.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_BasicConfigurator.cpp$(DependSuffix): src/BasicConfigurator.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_BasicConfigurator.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_BasicConfigurator.cpp$(DependSuffix) -MM src/BasicConfigurator.cpp

$(IntermediateDirectory)/src_BasicConfigurator.cpp$(PreprocessSuffix): src/BasicConfigurator.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_BasicConfigurator.cpp$(PreprocessSuffix) src/BasicConfigurator.cpp

$(IntermediateDirectory)/src_HierarchyMaintainer.cpp$(ObjectSuffix): src/HierarchyMaintainer.cpp $(IntermediateDirectory)/src_HierarchyMaintainer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/HierarchyMaintainer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_HierarchyMaintainer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_HierarchyMaintainer.cpp$(DependSuffix): src/HierarchyMaintainer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_HierarchyMaintainer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_HierarchyMaintainer.cpp$(DependSuffix) -MM src/HierarchyMaintainer.cpp

$(IntermediateDirectory)/src_HierarchyMaintainer.cpp$(PreprocessSuffix): src/HierarchyMaintainer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_HierarchyMaintainer.cpp$(PreprocessSuffix) src/HierarchyMaintainer.cpp

$(IntermediateDirectory)/src_FactoryParams.cpp$(ObjectSuffix): src/FactoryParams.cpp $(IntermediateDirectory)/src_FactoryParams.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/FactoryParams.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_FactoryParams.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_FactoryParams.cpp$(DependSuffix): src/FactoryParams.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_FactoryParams.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_FactoryParams.cpp$(DependSuffix) -MM src/FactoryParams.cpp

$(IntermediateDirectory)/src_FactoryParams.cpp$(PreprocessSuffix): src/FactoryParams.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_FactoryParams.cpp$(PreprocessSuffix) src/FactoryParams.cpp

$(IntermediateDirectory)/src_DailyRollingFileAppender.cpp$(ObjectSuffix): src/DailyRollingFileAppender.cpp $(IntermediateDirectory)/src_DailyRollingFileAppender.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/DailyRollingFileAppender.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_DailyRollingFileAppender.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_DailyRollingFileAppender.cpp$(DependSuffix): src/DailyRollingFileAppender.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_DailyRollingFileAppender.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_DailyRollingFileAppender.cpp$(DependSuffix) -MM src/DailyRollingFileAppender.cpp

$(IntermediateDirectory)/src_DailyRollingFileAppender.cpp$(PreprocessSuffix): src/DailyRollingFileAppender.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_DailyRollingFileAppender.cpp$(PreprocessSuffix) src/DailyRollingFileAppender.cpp

$(IntermediateDirectory)/src_SimpleLayout.cpp$(ObjectSuffix): src/SimpleLayout.cpp $(IntermediateDirectory)/src_SimpleLayout.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/SimpleLayout.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_SimpleLayout.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_SimpleLayout.cpp$(DependSuffix): src/SimpleLayout.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_SimpleLayout.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_SimpleLayout.cpp$(DependSuffix) -MM src/SimpleLayout.cpp

$(IntermediateDirectory)/src_SimpleLayout.cpp$(PreprocessSuffix): src/SimpleLayout.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_SimpleLayout.cpp$(PreprocessSuffix) src/SimpleLayout.cpp

$(IntermediateDirectory)/src_PropertyConfigurator.cpp$(ObjectSuffix): src/PropertyConfigurator.cpp $(IntermediateDirectory)/src_PropertyConfigurator.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/PropertyConfigurator.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_PropertyConfigurator.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_PropertyConfigurator.cpp$(DependSuffix): src/PropertyConfigurator.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_PropertyConfigurator.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_PropertyConfigurator.cpp$(DependSuffix) -MM src/PropertyConfigurator.cpp

$(IntermediateDirectory)/src_PropertyConfigurator.cpp$(PreprocessSuffix): src/PropertyConfigurator.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_PropertyConfigurator.cpp$(PreprocessSuffix) src/PropertyConfigurator.cpp

$(IntermediateDirectory)/src_Category.cpp$(ObjectSuffix): src/Category.cpp $(IntermediateDirectory)/src_Category.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/Category.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Category.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Category.cpp$(DependSuffix): src/Category.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Category.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Category.cpp$(DependSuffix) -MM src/Category.cpp

$(IntermediateDirectory)/src_Category.cpp$(PreprocessSuffix): src/Category.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Category.cpp$(PreprocessSuffix) src/Category.cpp

$(IntermediateDirectory)/src_AppendersFactory.cpp$(ObjectSuffix): src/AppendersFactory.cpp $(IntermediateDirectory)/src_AppendersFactory.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/AppendersFactory.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_AppendersFactory.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_AppendersFactory.cpp$(DependSuffix): src/AppendersFactory.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_AppendersFactory.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_AppendersFactory.cpp$(DependSuffix) -MM src/AppendersFactory.cpp

$(IntermediateDirectory)/src_AppendersFactory.cpp$(PreprocessSuffix): src/AppendersFactory.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_AppendersFactory.cpp$(PreprocessSuffix) src/AppendersFactory.cpp

$(IntermediateDirectory)/src_Appender.cpp$(ObjectSuffix): src/Appender.cpp $(IntermediateDirectory)/src_Appender.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/Appender.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Appender.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Appender.cpp$(DependSuffix): src/Appender.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Appender.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Appender.cpp$(DependSuffix) -MM src/Appender.cpp

$(IntermediateDirectory)/src_Appender.cpp$(PreprocessSuffix): src/Appender.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Appender.cpp$(PreprocessSuffix) src/Appender.cpp

$(IntermediateDirectory)/src_Properties.cpp$(ObjectSuffix): src/Properties.cpp $(IntermediateDirectory)/src_Properties.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/Properties.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Properties.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Properties.cpp$(DependSuffix): src/Properties.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Properties.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Properties.cpp$(DependSuffix) -MM src/Properties.cpp

$(IntermediateDirectory)/src_Properties.cpp$(PreprocessSuffix): src/Properties.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Properties.cpp$(PreprocessSuffix) src/Properties.cpp

$(IntermediateDirectory)/src_AbortAppender.cpp$(ObjectSuffix): src/AbortAppender.cpp $(IntermediateDirectory)/src_AbortAppender.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/AbortAppender.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_AbortAppender.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_AbortAppender.cpp$(DependSuffix): src/AbortAppender.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_AbortAppender.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_AbortAppender.cpp$(DependSuffix) -MM src/AbortAppender.cpp

$(IntermediateDirectory)/src_AbortAppender.cpp$(PreprocessSuffix): src/AbortAppender.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_AbortAppender.cpp$(PreprocessSuffix) src/AbortAppender.cpp

$(IntermediateDirectory)/src_RollingFileAppender.cpp$(ObjectSuffix): src/RollingFileAppender.cpp $(IntermediateDirectory)/src_RollingFileAppender.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/me/zby_libuv/log4cpp/src/RollingFileAppender.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_RollingFileAppender.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_RollingFileAppender.cpp$(DependSuffix): src/RollingFileAppender.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_RollingFileAppender.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_RollingFileAppender.cpp$(DependSuffix) -MM src/RollingFileAppender.cpp

$(IntermediateDirectory)/src_RollingFileAppender.cpp$(PreprocessSuffix): src/RollingFileAppender.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_RollingFileAppender.cpp$(PreprocessSuffix) src/RollingFileAppender.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/$(ProjectName)/


