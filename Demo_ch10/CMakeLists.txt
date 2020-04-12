
add_executable(Demo_ch10_1 Demo_1.cpp )
add_executable(Demo_ch10_2 Demo_2.cpp)

target_link_libraries(Demo_ch10_1 ${OpenCV_LIBS})
target_link_libraries(Demo_ch10_2 ${OpenCV_LIBS})
