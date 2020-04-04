
add_executable(Demo_ch7_1 Demo_1.cpp header/Demo_ch7_1.h sources/Demo_ch7_1.cpp)
add_executable(Demo_ch7_2 Demo_2.cpp header/Demo_ch7_2.h sources/Demo_ch7_2.cpp)
add_executable(Demo_ch7_3 Demo_3.cpp header/Demo_ch7_3.h sources/Demo_ch7_3.cpp)
add_executable(Demo_ch7_5 Demo_5.cpp)

target_link_libraries(Demo_ch7_1 ${OpenCV_LIBS})
target_link_libraries(Demo_ch7_2 ${OpenCV_LIBS})
target_link_libraries(Demo_ch7_3 ${OpenCV_LIBS})
target_link_libraries(Demo_ch7_5 ${OpenCV_LIBS})