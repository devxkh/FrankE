
set(INCROOT ${PROJECT_SOURCE_DIR}/fbxtoogre/Exec)
set(SRCROOT ${PROJECT_SOURCE_DIR}/fbxtoogre/Exec)

set(FBXTOOGRE_Exec_INCLUDES

  #  ${INCROOT}/animation.h
)
source_group("include" FILES ${FBXTOOGRE_Exec_INCLUDES})

set(FBXTOOGRE_Exec_SOURCES
  
	 ${SRCROOT}/ExecFxOgreFBX.cpp
)
source_group("src" FILES ${FBXTOOGRE_Exec_SOURCES})


add_executable(ExecFxOgreFBX ${FBXTOOGRE_Exec_SOURCES})

target_link_libraries(ExecFxOgreFBX FBXTOOGRE)
