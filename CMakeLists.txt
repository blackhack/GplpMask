cmake_minimum_required (VERSION 2.8)
project (GplpMask)

# set macro-directory
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/macros")

include(CheckPlatform)

set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

find_package(Boost COMPONENTS system filesystem) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    
    file(GLOB_RECURSE sourcecode src/*.cpp src/*.hpp)
    add_executable(GplpMask ${sourcecode})
    
    target_link_libraries(GplpMask ${Boost_LIBRARIES})
    
    # Copiamos los StringFiles al directorio de compilacion.
    file(COPY ${CMAKE_SOURCE_DIR}/StringFiles DESTINATION ${CMAKE_BINARY_DIR})
endif()
