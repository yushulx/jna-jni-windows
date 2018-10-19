cmake_minimum_required (VERSION 2.6)
project (dbr)
MESSAGE( STATUS "PROJECT_NAME: " ${PROJECT_NAME} )

# Check platforms
if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
    set(JAVA_HOME "E:/Program Files (x86)/Java/jdk1.8.0_191")
    set(JAVA_INCLUDE "${JAVA_HOME}/include")
    set(JAVA_INCLUDE_OS "${JAVA_HOME}/include/win32")
endif()

MESSAGE( STATUS "JAVA_INCLUDE: " ${JAVA_INCLUDE})

# Configure a header file to pass some of the CMake settings
# to the source code
configure_file (
    "${PROJECT_SOURCE_DIR}/BarcodeReaderConfig.h.in"
    "${PROJECT_BINARY_DIR}/BarcodeReaderConfig.h"
)

# Add search path for include and lib files
if(WINDOWS)
    link_directories("${PROJECT_SOURCE_DIR}/platforms/win" "${JAVA_HOME}/lib") 
    include_directories("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/include" "${PROJECT_SOURCE_DIR}" "${JAVA_INCLUDE}" "${JAVA_INCLUDE_OS}")
endif()

# Add the executable
add_library(jnidbr SHARED NativeBarcodeReader.cxx)
if(WINDOWS)
    if(CMAKE_CL_64)
        target_link_libraries (jnidbr "DBRx64")
    else()
        target_link_libraries (jnidbr "DBRx86")
    endif()
endif()

# Set installation directory
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/../")
if(WINDOWS)
    install (DIRECTORY "${PROJECT_SOURCE_DIR}/platforms/win/" DESTINATION "${CMAKE_INSTALL_PREFIX}" FILES_MATCHING PATTERN "*.dll")
    install (TARGETS jnidbr DESTINATION "${CMAKE_INSTALL_PREFIX}")
endif()




