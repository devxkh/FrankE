
# XEAnimation


set(INCROOT ${PROJECT_SOURCE_DIR}/src/include/XEngine/Animation)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/src/XEngine/Animation)

# all source files
set(XEAnimation_SOURCES
   
     ${SRCROOT}/AnimationTriggerSystem.cpp
     ${SRCROOT}/HandleAnimation.cpp
	
#	 ${SRCROOT}/ExampleAnimationSystem.cpp
	# ${SRCROOT}/ExampleDummyAnimation.cpp
	 ${SRCROOT}/Node.cpp
#	 ${SRCROOT}/NodeContainer.cpp
#	 ${SRCROOT}/NodeFactory.cpp
#	 ${SRCROOT}/Parameter.cpp
#	 ${SRCROOT}/ParameterContainer.cpp
	 ${SRCROOT}/Port.cpp
#	 ${SRCROOT}/SharedData.cpp
	 ${SRCROOT}/Trigger.cpp 
	 PARENT_SCOPE


)

set(XEAnimationHelper_SOURCES

	 ${SRCROOT}/Helper/SmoothValue.cpp 
	 PARENT_SCOPE
)

#-------------------- XEAnimation_Ogre_SOURCES -------------------------------
#set(XEAnimation_Ogre_INCLUDES
#
#	 ${INCROOT}/Ogre/Animation.h
#	 ${INCROOT}/Ogre/AnimationSystem.h
#)
#source_group("include\\Ogre" FILES ${XEAnimation_Ogre_INCLUDES})
#
#set(XEAnimation_Ogre_SOURCES
#
#	 ${SRCROOT}/Ogre/Animation.cpp
#	 ${SRCROOT}/Ogre/AnimationSystem.cpp
#)
#source_group("src\\Ogre" FILES ${XEAnimation_Ogre_SOURCES})


set(XEAnimationProp_SOURCES
#	 ${SRCROOT}/Property/Property.cpp
#	 ${SRCROOT}/Property/Xml/PropertyBuilder.cpp 
#	 PARENT_SCOPE
)


set(XEAnimationNodes_SOURCES
	 ${SRCROOT}/Nodes/AnimationNode.cpp
     ${SRCROOT}/Nodes/AverageNode.cpp
     ${SRCROOT}/Nodes/BlendNode.cpp
     ${SRCROOT}/Nodes/LookAtNode.cpp
     ${SRCROOT}/Nodes/MaskAddNode.cpp
     ${SRCROOT}/Nodes/MaskBaseNode.cpp
     ${SRCROOT}/Nodes/MaskMulNode.cpp
     ${SRCROOT}/Nodes/MaskSetNode.cpp
     ${SRCROOT}/Nodes/MaskSubNode.cpp
     ${SRCROOT}/Nodes/MathAbsNode.cpp
     ${SRCROOT}/Nodes/MathCeilNode.cpp
     ${SRCROOT}/Nodes/MathClampNode.cpp
     ${SRCROOT}/Nodes/MathDivNode.cpp
     ${SRCROOT}/Nodes/MathMapNode.cpp
     ${SRCROOT}/Nodes/MathMaxNode.cpp
     ${SRCROOT}/Nodes/MathMinNode.cpp
     ${SRCROOT}/Nodes/MathMinusNode.cpp
     ${SRCROOT}/Nodes/MathMulNode.cpp
     ${SRCROOT}/Nodes/MathPlusNode.cpp
     ${SRCROOT}/Nodes/MixNode.cpp
     ${SRCROOT}/Nodes/OutputNode.cpp
     ${SRCROOT}/Nodes/ParameterNode.cpp
     ${SRCROOT}/Nodes/RandomSelectNode.cpp
     ${SRCROOT}/Nodes/SmoothValueNode.cpp
     ${SRCROOT}/Nodes/TransitionSelectNode.cpp    
	 PARENT_SCOPE
)
   

# all header files
set(XEAnimation_HEADER
	
	#${INCROOT}/Export.hpp 
#	${INCROOT}/IAnimation.h
	${INCROOT}/HandleAnimation.h
#	${INCROOT}/ExampleAnimationSystem.h 
	PARENT_SCOPE
)


# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj


# ----------------------- header files -------------------------------
set(XEScripts_TINYXML_HEADER
#     ${INCROOT}/XML/tinyxml/tinyxml.h
#     ${INCROOT}/XML/tinyxml/tinystr.h
#     ${INCROOT}/XML/tinyxml/tinystr.cpp
#     ${INCROOT}/XML/tinyxml/tinyxml.cpp
#     ${INCROOT}/XML/tinyxml/tinyxmlerror.cpp
#     ${INCROOT}/XML/tinyxml/tinyxmlparser.cpp 
#	 PARENT_SCOPE
)


#---------------- Animation ----------------------
# all source files
set(XEEngineAnimation_SOURCES
   
  #   ${SRCROOT}/Animation.cpp
  #   ${SRCROOT}/AnimationSystem.cpp
  PARENT_SCOPE
)

# all header files
set(XEEngineAnimation_HEADER
#	 ${INCROOT}/Animation.h
#	 ${INCROOT}/AnimationSystem.h 
	 PARENT_SCOPE
)




# Properties->C/C++->General->Additional Include Directories
#-------------- include_directories (${PROJECT_SOURCE_DIR}/src/include/XEAnimation)
#-------------- include_directories (${PROJECT_SOURCE_DIR}/src/include)
#-------------- include_directories (${PROJECT_SOURCE_DIR}/src/include/XEScripts/XML/tinyxml)
#-------------- include_directories (${PROJECT_SOURCE_DIR}/src)
#include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty)
#-------------- include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/sfml/include)
#-------------- include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty)




# Set Properties->General->Configuration Type to Dynamic Library(.lib)
# Creates math.dll with the listed sources collected in the variables
# Also adds sources to the Solution Explorer
#add_library(XEAnimation ${XEAnimation_SOURCES} ${XEAnimation_HEADER} ${XEAnimationNodes_SOURCES} ${XEAnimationProp_SOURCES} ${XEAnimation_Ogre_SOURCES} ${XEAnimationHelper_SOURCES})


# define the sfml-graphics target
#-------------- sfml_add_library(XEAnimation 
#-------------- 	SOURCES ${XEAnimation_SOURCES} ${XEAnimation_HEADER} ${XEAnimationNodes_SOURCES} ${XEAnimationProp_SOURCES}
#-------------- 	 #${XEAnimation_Ogre_SOURCES} 	${XEAnimation_Ogre_INCLUDES}
#-------------- 	 ${XEAnimationHelper_SOURCES} ${XEScripts_TINYXML_HEADER} 
#	DEPENDS  # OgreMain 
#-------------- 	EXTERNAL_LIBS ${XEAnimation_EXT_LIBS})



#-------------- target_compile_definitions(XEAnimation PUBLIC XEANIMATION_EXPORTS)
#-------------- target_compile_definitions(XEAnimation PUBLIC OGRE_STATIC_LIB)


# Creates folder "libraries" and adds target project (XEngine.vcproj)
#-------------- set_property(TARGET XEAnimation PROPERTY FOLDER "libraries")
# set the output directory for SFML libraries
#set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")


# Adds logic to INSTALL.vcproj to copy XEngine.lib to destination directory
#install (TARGETS XEAnimation
#		ARCHIVE DESTINATION lib
#        LIBRARY DESTINATION lib
#		COMPONENT library)