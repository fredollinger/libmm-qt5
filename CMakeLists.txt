cmake_minimum_required(VERSION 2.8.8)


option(USE_QT5 "Using Qt5" OFF)

set(VERSION 0.5.0)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})

set(LIB_SUFFIX "" CACHE STRING "Define suffix of library directory name (32/64)" )

set(libraryName)

if(USE_QT5)
    project(libModemManagerQt5)
    find_package(Qt5Core REQUIRED)
    find_package(Qt5DBus REQUIRED)

    set(CMAKE_AUTOMOC ON)
    add_definitions(-std=c++11)
    set(libraryName ModemManagerQt5)
else()
    project(libModemManagerQt)
    find_package(Qt4 REQUIRED)
    add_definitions(${QT_DEFINITIONS})
    set(libraryName ModemManagerQt)
endif()


include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${QT_INCLUDES} ${CMAKE_INCLUDE_PATH})
link_directories(${CMAKE_LIBRARY_PATH})

include_directories(
   ${CMAKE_CURRENT_SOURCE_DIR}/dbus
   ${CMAKE_CURRENT_BUILD_DIR}
)

set(ModemManagerQt_HEADERS
    manager.h
    modeminterface.h
    modemlocationinterface.h
    modemcdmainterface.h
    modemgsmcardinterface.h
    modemgsmcontactsinterface.h
    modemgsmnetworkinterface.h
    modemgsmsmsinterface.h
    modemgsmhsointerface.h
    modemgsmussdinterface.h
    ModemManagerQt-export.h
)

set(ModemManagerQt_PRIVATE_HEADERS
    manager_p.h
    modemcdmainterface_p.h
    modemgsmcardinterface_p.h
    modemgsmcontactsinterface_p.h
    modemgsmhsointerface_p.h
    modemgsmnetworkinterface_p.h
    modemgsmsmsinterface_p.h
    modemgsmussdinterface_p.h
    modeminterface_p.h
    modemlocationinterface_p.h
)

set(ModemManagerQt_SRCS
   manager.cpp
   modeminterface.cpp
   modemlocationinterface.cpp
   modemcdmainterface.cpp
   modemgsmcardinterface.cpp
   modemgsmcontactsinterface.cpp
   modemgsmnetworkinterface.cpp
   modemgsmsmsinterface.cpp
   modemgsmhsointerface.cpp
   modemgsmussdinterface.cpp
)

set( DBUS_INTERFACES_FILES
   dbus/generic-types.cpp
   dbus/mm-manager-clientinterface.cpp
   dbus/mm-modeminterface.cpp
   dbus/mm-modem-simpleinterface.cpp
   dbus/mm-modem-locationinterface.cpp
   dbus/mm-modem-cdmainterface.cpp
   dbus/mm-modem-gsm-cardinterface.cpp
   dbus/mm-modem-gsm-contactsinterface.cpp
   dbus/mm-modem-gsm-networkinterface.cpp
   dbus/mm-modem-gsm-smsinterface.cpp
   dbus/mm-modem-gsm-hsointerface.cpp
   dbus/mm-modem-gsm-ussdinterface.cpp
)

if(NOT USE_QT5)
    qt4_wrap_cpp(ModemManagerQt_MOC ${ModemManagerQt_HEADERS} ${ModemManagerQt_PRIVATE_HEADERS})
    qt4_automoc(${DBUS_INTERFACES_FILES})
endif()

add_library(${libraryName} SHARED ${ModemManagerQt_MOC} ${ModemManagerQt_SRCS} ${DBUS_INTERFACES_FILES})
if(USE_QT5)
    qt5_use_modules(${libraryName} Core DBus)
endif()

target_link_libraries(${libraryName} ${QT_QTCORE_LIBRARY} ${QT_QTDBUS_LIBRARY})
install(TARGETS ${libraryName} DESTINATION lib${LIB_SUFFIX})

install( FILES
${ModemManagerQt_HEADERS}
DESTINATION
include/${libraryName} COMPONENT Devel)

set_property(TARGET ${libraryName} PROPERTY COMPILE_DEFINITIONS MAKE_QTMODEMMANAGER_LIB)
set_property(TARGET ${libraryName} PROPERTY VERSION ${VERSION})
set_property(TARGET ${libraryName} PROPERTY SOVERSION 0)

message(STATUS "Writing pkg-config file...")
configure_file(${CMAKE_SOURCE_DIR}/ModemManagerQt.pc.cmake ${CMAKE_BINARY_DIR}/${libraryName}.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/${libraryName}.pc DESTINATION "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/pkgconfig/")
