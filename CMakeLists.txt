cmake_minimum_required(VERSION 2.8.9)
project (LNWaterMark)

#Bring the headers, such as Student.h into the project
include_directories(/home/atish/Downloads/opencv-3.2.0/modules/core/include)
include_directories(/home/atish/Downloads/opencv-3.2.0/build)
include_directories(/home/atish/Downloads/opencv-3.2.0/modules/highgui/include)
include_directories(/home/atish/Downloads/opencv-3.2.0/modules/imgcodecs/include)
include_directories(/home/atish/Downloads/opencv-3.2.0/modules/videoio/include)
include_directories(/home/atish/Downloads/opencv-3.2.0/modules/imgproc/include)
include_directories(/home/atish/Downloads/ImageMagick-7.0.4-4/Magick++/lib)
include_directories(/home/atish/Downloads/ImageMagick-7.0.4-4)
 
#the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "LectureNotesWaterMark/*.cpp")
 
add_executable(LNWaterMark ${SOURCES})

target_compile_options(LNWaterMark PRIVATE -std=c++11)

link_directories(/home/atish/Downloads/opencv-3.2.0/build/lib)

#file(GLOB MYLIBS "${BOOST_PATH}/libboost*.a")

target_link_libraries(LNWaterMark PRIVATE opencv_core)
target_link_libraries(LNWaterMark PRIVATE opencv_imgproc)
target_link_libraries(LNWaterMark PRIVATE opencv_highgui)
target_link_libraries(LNWaterMark PRIVATE opencv_objdetect)
target_link_libraries(LNWaterMark PRIVATE opencv_imgcodecs)

#image magic k libraries ie in /usr/local/lib
target_link_libraries(LNWaterMark PRIVATE Magick++-7.Q16HDRI)
target_link_libraries(LNWaterMark PRIVATE MagickCore-7.Q16HDRI)
target_link_libraries(LNWaterMark PRIVATE MagickWand-7.Q16HDRI)


