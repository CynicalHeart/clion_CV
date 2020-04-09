
add_executable(Demo_ch8_1 Demo_1.cpp)
add_executable(Demo_ch8_2 Demo_2.cpp)
add_executable(Demo_ch8_3 Demo_3.cpp header/Demo_ch8_3.h sources/Demo_ch8_3.cpp)
add_executable(Demo_ch8_4 Demo_4.cpp)
add_executable(Demo_ch8_5 Demo_5.cpp)
add_executable(Demo_ch8_6 Demo_6.cpp)


target_link_libraries(Demo_ch8_1 ${OpenCV_LIBS})
target_link_libraries(Demo_ch8_2 ${OpenCV_LIBS})
target_link_libraries(Demo_ch8_3 ${OpenCV_LIBS})
target_link_libraries(Demo_ch8_4 ${OpenCV_LIBS})
target_link_libraries(Demo_ch8_5 ${OpenCV_LIBS})
target_link_libraries(Demo_ch8_6 ${OpenCV_LIBS})