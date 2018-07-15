
set(synth_sources
    include/lakewoodController.h
    source/lakewoodController.cpp
    #---
    include/lakewoodIDs.h
    #---
    include/lakewoodProcessor.h
    source/lakewoodProcessor.cpp
    #---
    include/lakewoodVersion.h
    #---
    source/lakewoodFactory.cpp
    #---
    #---https://github.com/micknoise/Maximilian
    include/maximilian.h
    include/maximilian.cpp
)

#--- HERE change the target Name for your plug-in (for ex. set(target myDelay))-------
if(MAC)
	set(target Lakewood)
elseif((WIN) AND (CMAKE_SIZEOF_VOID_P EQUAL "8"))
    set(target Lakewood_x64)
elseif(WIN)
	set(target Lakewood_x86)
endif()

smtg_add_vst3plugin(${target} ${SDK_ROOT} ${synth_sources})
set_target_properties(${target} PROPERTIES ${SDK_IDE_MYPLUGINS_FOLDER})
target_link_libraries(${target} PRIVATE base sdk)

if(MAC)
    smtg_set_bundle(${target} INFOPLIST "${CMAKE_CURRENT_LIST_DIR}/resource/Info.plist" PREPROCESS)
elseif(WIN)
    target_sources(${target} PRIVATE resource/plug.rc)
endif()
