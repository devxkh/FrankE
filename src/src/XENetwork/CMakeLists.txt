

set(INCROOT ${PROJECT_SOURCE_DIR}/src/include/XENetwork)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/src/XENetwork)


# all source files
set(XNetwork_SFNUL_SOURCES
    ${SRCROOT}/Message.cpp
)
source_group("src" FILES ${XNetwork_SFNUL_SOURCES})

# all header files
set(XNetwork_SFNUL_HEADER
    ${INCROOT}/Message.hpp 
    ${INCROOT}/Message.inl 
	   ${INCROOT}/DataTypes.hpp 
)

source_group("include" FILES ${XNetwork_SFNUL_HEADER})


# all source files
set(XNetwork_SOURCES
    ${SRCROOT}/NetworkManager.cpp
    ${SRCROOT}/NetObserver.cpp
)
source_group("src" FILES ${XNetwork_SOURCES})

# all header files
set(XNetwork_HEADER
    ${INCROOT}/NetworkManager.hpp 
    ${INCROOT}/NetObserver.hpp 
)

source_group("include" FILES ${XNetwork_HEADER})

#set(INCROOTSFMLNET ${PROJECT_SOURCE_DIR}/src/ThirdParty/sfml/include/SFML/Network)
#set(SRCROOTSFMLNET ${PROJECT_SOURCE_DIR}/src/ThirdParty/sfml/src/SFML/Network)
#
## all source files
#set(SRC
#    ${SRCROOTSFMLNET}/Ftp.cpp
#    ${INCROOTSFMLNET}/Ftp.hpp
#    ${SRCROOTSFMLNET}/Http.cpp
#    ${INCROOTSFMLNET}/Http.hpp
#    ${SRCROOTSFMLNET}/IpAddress.cpp
#    ${INCROOTSFMLNET}/IpAddress.hpp
#    ${SRCROOTSFMLNET}/Packet.cpp
#    ${INCROOTSFMLNET}/Packet.hpp
#    ${SRCROOTSFMLNET}/Socket.cpp
#    ${INCROOTSFMLNET}/Socket.hpp
#    ${SRCROOTSFMLNET}/SocketImpl.hpp
#    ${INCROOTSFMLNET}/SocketHandle.hpp
#    ${SRCROOTSFMLNET}/SocketSelector.cpp
#    ${INCROOTSFMLNET}/SocketSelector.hpp
#    ${SRCROOTSFMLNET}/TcpListener.cpp
#    ${INCROOTSFMLNET}/TcpListener.hpp
#    ${SRCROOTSFMLNET}/TcpSocket.cpp
#    ${INCROOTSFMLNET}/TcpSocket.hpp
#    ${SRCROOTSFMLNET}/UdpSocket.cpp
#    ${INCROOTSFMLNET}/UdpSocket.hpp
#)
#source_group("sfml\\network" FILES ${SRC})
#
## add platform specific sources
#if(SFML_OS_WINDOWS)
#    set(SRC
#        ${SRC}
#        ${SRCROOTSFMLNET}/Win32/SocketImpl.cpp
#        ${SRCROOTSFMLNET}/Win32/SocketImpl.hpp
#    )
#else()
#    set(SRC
#        ${SRC}
#        ${SRCROOTSFMLNET}/Unix/SocketImpl.cpp
#        ${SRCROOTSFMLNET}/Unix/SocketImpl.hpp
#    )
#endif()
#
#source_group("sfml\\network\\os" FILES ${SRC})


#set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/headers") #has no influence!??
#include_directories(${PROJECT_SOURCE_DIR}/extlibs/headers)
#
#message("FindEnet.cmake - start " ${CMAKE_MODULE_PATH}) 
## findet Physfs nicht !!????
#find_package(enet REQUIRED)
##find_package(Sndfile REQUIRED)
#message("FindEnet.cmake - end")

# build the list of external libraries to link
#set(NETWORK_EXT_LIBS)
#if(SFML_OS_WINDOWS)
#    set(NETWORK_EXT_LIBS ${NETWORK_EXT_LIBS} ws2_32)
#endif()


# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
source_group("src" FILES ${XENetwork_SOURCES})
source_group("include" FILES ${XENetwork_HEADER})
#source_group("simple" FILES ${SIMPLE_FUNCTION_SOURCES})
#source_group("advanced" FILES ${ADVANCED_FUNCTION_SOURCES})


# Properties->C/C++->General->Additional Include Directories
# add sfml Network headers
#include_directories(${PROJECT_SOURCE_DIR}/src/ThirdParty/sfml/src)
#include_directories(${PROJECT_SOURCE_DIR}/src/ThirdParty/sfml/include)

include_directories(${PROJECT_SOURCE_DIR}/src/ThirdParty/enet)

# Set Properties->General->Configuration Type to Dynamic Library(.lib)
# Creates math.dll with the listed sources collected in the variables
# Also adds sources to the Solution Explorer
#add_library(XENetwork 
#                 ${XENetwork_SOURCES} ${SRC} ${PLATFORM_SRC})
#                # EXTERNAL_LIBS ${Network_EXT_LIBS}) 
 



# define the sfml-Network target
sfml_add_library(XENetwork
                 SOURCES ${XENetwork_SOURCES} ${XENetwork_HEADER}  ${PLATFORM_SRC} ${XNetwork_SOURCES} ${XNetwork_HEADER} #${SRC}
				 ${XNetwork_SFNUL_SOURCES} 
				 # ${XNetwork_SFNUL_HEADER}
                 EXTERNAL_LIBS ${Network_EXT_LIBS})

#add_definitions(-SFML_Network_EXPORTS)
#set_target_properties(XENetwork PROPERTIES DEFINE_SYMBOL SFML_Network_EXPORTS)



# Creates folder "libraries" and adds target project (XEngine.vcproj)
set_property(TARGET XENetwork PROPERTY FOLDER "libraries")
# set the output directory for SFML libraries
#set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")


# Adds logic to INSTALL.vcproj to copy XEngine.lib to destination directory
#install (TARGETS XENetwork
#		ARCHIVE DESTINATION lib
#        LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/bin
#		COMPONENT library)

