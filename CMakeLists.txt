cmake_minimum_required(VERSION 3.15)  #设置cmake的最低版本要求
project(clion_CV) #设置项目的名称，还将其存储在内置变量CMAKE_PROJECT_NAME中

set(CMAKE_CXX_STANDARD 17) #设置C++标准的版本。

# 设置OpenCV目录所在
set(OpenCV_DIR "E:\\openCV\\opencv\\minGW-build\\install")

# 搜索OpenCV目录
find_package(OpenCV REQUIRED)
# 添加OpenCV头文件目录
include_directories(${OpenCV_INCLUDE_DIRS})

#添加一个可执行文件类型的构建目标到项目中。CMakeLearnDemo是文件名，后面是生成这个可执行文件所需要的源文件列表。
add_executable(clion_CV main.cpp)

add_subdirectory(Demo_ch6)
add_subdirectory(Demo_ch7)
add_subdirectory(Demo_ch8)
add_subdirectory(Demo_ch9)
add_subdirectory(Demo_ch10)
add_subdirectory(Demo_ch11)






