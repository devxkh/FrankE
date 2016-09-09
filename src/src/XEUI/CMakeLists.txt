
# XEUI


set(INCROOT ${PROJECT_SOURCE_DIR}/src/include/XEUI)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/src/XEUI)

# -------------------------------- XEUI_SOURCES---------------------------------
set(XEUI_SOURCES
   
 #    ${SRCROOT}/ElementStyle.cpp
#	 ${SRCROOT}/HealthBar.cpp
	# ${SRCROOT}/NonCopyable.cpp
	 ${SRCROOT}/Object.cpp
	 #${SRCROOT}/Panel2D.cpp
	 #${SRCROOT}/Panel3D.cpp
	 ${SRCROOT}/Widget.cpp
	 ${SRCROOT}/Signal.cpp
	 ${SRCROOT}/NonCopyable.cpp
	# ${SRCROOT}/UIManager.cpp
#	 ${SRCROOT}/UIPanel.cpp
#	 ${SRCROOT}/UISerializer.cpp
	 ${SRCROOT}/UIStateManager.cpp

	 ${SRCROOT}/Desktop.cpp
	 ${SRCROOT}/Adjustment.cpp
	 ${SRCROOT}/Alignment.cpp
	 ${SRCROOT}/Box.cpp
	 ${SRCROOT}/Container.cpp
	${SRCROOT}/Bin.cpp
	 ${SRCROOT}/Misc.cpp
		
)
source_group("src" FILES ${XEUI_SOURCES})

# -------------------------------- XEUI_Widgets_SOURCES---------------------------------
set(XEUI_Widgets_SOURCES

	 ${SRCROOT}/Widgets/OgreConsoleForGorilla.cpp
	 ${SRCROOT}/Widgets/Label.cpp
	 ${SRCROOT}/Widgets/Entry.cpp
	 ${SRCROOT}/Widgets/Button.cpp
	 ${SRCROOT}/Widgets/ToggleButton.cpp
	 ${SRCROOT}/Widgets/ProgressBar.cpp
	 ${SRCROOT}/Widgets/Image.cpp
	 ${SRCROOT}/Widgets/UIWindow.cpp
	 #${SRCROOT}/Widgets/Menu.cpp
	 #${SRCROOT}/Widgets/MenuItem.cpp
	 #${SRCROOT}/Widgets/MIButton.cpp
	 #${SRCROOT}/Widgets/MICheckBox.cpp
	 #${SRCROOT}/Widgets/Navigation.cpp
	 #${SRCROOT}/Widgets/NavItem.cpp
)
source_group("src\\Widgets" FILES ${XEUI_Widgets_SOURCES})

set(XEUI_Widgets_INCLUDES

	 ${INCROOT}/Widgets/OgreConsoleForGorilla.hpp
	 ${INCROOT}/Widgets/Label.hpp
	 ${INCROOT}/Widgets/Entry.hpp
	  ${INCROOT}/Widgets/Button.hpp
	  ${INCROOT}/Widgets/ToggleButton.hpp
	  ${INCROOT}/Widgets/ProgressBar.hpp
	  ${INCROOT}/Widgets/Image.hpp
	 ${INCROOT}/Widgets/UIWindow.hpp
	#${INCROOT}/Widgets/Menu.hpp
	 #${INCROOT}/Widgets/MenuItem.hpp
	 #${INCROOT}/Widgets/MIButton.hpp
	 #${INCROOT}/Widgets/MICheckBox.hpp
	 #${INCROOT}/Widgets/Navigation.hpp
	 #${INCROOT}/Widgets/NavItem.hpp
)
source_group("include\\Widgets" FILES ${XEUI_Widgets_INCLUDES})

# -------------------------------- XEUI_DAL_SOURCES---------------------------------
set(XEUI_DAL_SOURCES
#	${SRCROOT}/DAL/FB_UI_StyleData_generated.h
	 ${SRCROOT}/DAL/FB_UI_StateData_generated.h
 ${SRCROOT}/DAL/FB_UI_Atlas_generated.h
)
source_group("src\\DAL" FILES ${XEUI_DAL_SOURCES})

# -------------------------------- XEUI_Console_SOURCES---------------------------------
set(XEUI_Console_SOURCES

	# ${SRCROOT}/Console/OgreConsoleForGorilla.cpp
#	 ${SRCROOT}/Console/GameConsole.cpp
)
source_group("src\\Console" FILES ${XEUI_Console_SOURCES})

set(XEUI_Console_INCLUDE

	# ${INCROOT}/Widgets/OgreConsoleForGorilla.hpp
#	 ${SRCROOT}/Console/GameConsole.cpp
)
source_group("src\\Console" FILES ${XEUI_Console_INCLUDE})


# -------------------------------- XEUI_HEADER ---------------------------------
set(XEUI_HEADER
	
	 ${INCROOT}/Export.hpp
#	${INCROOT}/UIManager.hpp
#	${INCROOT}/UIPanel.hpp
	${INCROOT}/Signal.hpp
	${INCROOT}/NonCopyable.hpp
	${INCROOT}/Object.hpp
#	${INCROOT}/FastDelegate.hpp
#	${INCROOT}/ElementBase.hpp
#	
	${INCROOT}/UIStateManager.hpp
#	${INCROOT}/PanelElementCallback.hpp
#
	${INCROOT}/Desktop.hpp
	
	 ${INCROOT}/Widget.hpp
	 #${INCROOT}/Panel2D.hpp
#	 ${INCROOT}/Panel3D.hpp
#${INCROOT}/ElementStyle.hpp
#
#	 ${INCROOT}/Font.hpp
	 ${INCROOT}/Glyph.hpp
	 ${INCROOT}/Adjustment.hpp
	 ${INCROOT}/Alignment.hpp
	 ${INCROOT}/Box.hpp
	 ${INCROOT}/Container.hpp
		${INCROOT}/Bin.hpp
	 ${INCROOT}/Misc.hpp
	
	#	 ${INCROOT}/ScreenComponent.hpp
)


# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
source_group("include" FILES ${XEUI_HEADER})




# ----------------------- XEGraphics_SOURCES -------------------------------
set(XEGraphics_SOURCES
    #${SRCROOT}/Graphics/UIGraphic.cpp
)
source_group("src\\Graphics" FILES ${XEGraphics_SOURCES})

# ----------------------- header files -------------------------------
set(XEGraphics_HEADER
#	 ${INCROOT}/Graphics/UIGraphic.hpp
)
source_group("include\\Graphics" FILES ${XEGraphics_HEADER}) # Create named folders for the sources within the .vcproj


# Properties->C/C++->General->Additional Include Directories
include_directories (${PROJECT_SOURCE_DIR}/src/include)
include_directories (${PROJECT_SOURCE_DIR}/src)
#include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty)
include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/sfml/include)
include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty)
include_directories (${PROJECT_SOURCE_DIR}/src/Ogre/OgreMain/include)

include_directories(${PROJECT_SOURCE_DIR}/src/ThirdParty/rapidjson/include)
include_directories (${PROJECT_SOURCE_DIR}/extlibs/headers/luajit)


# Properties->C/C++->General->Additional Include Directories
#include_directories (.)


# Also adds sources to the Solution Explorer ------------------------------
#add_library(XEUI STATIC ${XEUI_SOURCES} ${XEUI_HEADER} ${XEUI_Widgets_SOURCES} ${XEUI_Console_SOURCES} )
sfml_add_library(XEUI 
	SOURCES ${XEUI_SOURCES} ${XEUI_HEADER} ${XEUI_Widgets_SOURCES} ${XEUI_Console_SOURCES} ${XEUI_Console_INCLUDE} ${XEGraphics_SOURCES} ${XEGraphics_HEADER} ${XEUI_Widgets_INCLUDES} ${XEUI_DAL_SOURCES}
	DEPENDS OgreMain XERenderer XEDAL
	EXTERNAL_LIBS ${XERenderer_EXT_LIBS})

# define the sfml-graphics target
#sfml_add_library(XEUI
#	SOURCES ${XEUI_SOURCES} ${XEUI_HEADER} ${XEUI_Widgets_SOURCES} ${XEUI_Console_SOURCES} ${XEGraphics_HEADER} ${XEGraphics_SOURCES}
#	DEPENDS OgreMain
#	EXTERNAL_LIBS ${XEUI_EXT_LIBS})
target_compile_definitions(XEUI PUBLIC XEUI_EXPORTS)

# Creates folder "libraries" and adds target project (XEngine.vcproj)
set_property(TARGET XEUI PROPERTY FOLDER "libraries")
# set the output directory for SFML libraries
#set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")


# Adds logic to INSTALL.vcproj to copy XEngine.lib to destination directory
#install (TARGETS XEUI
#		ARCHIVE DESTINATION lib
#        LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/bin
#		COMPONENT library)