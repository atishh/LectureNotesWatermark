cmake_minimum_required(VERSION 2.8.9)
project (CreatePost)

#Bring the headers, such as Student.h into the project
include_directories(/usr/local/include/ImageMagick-7) 

#the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "*.cpp")
 
add_executable(CreatePost ${SOURCES})

target_compile_options(CreatePost PRIVATE -std=c++11)

