
add_executable(Demo_ch9_2 Demo_2.cpp header/Demo_ch9_2.h sources/Demo_ch9_2.cpp)
add_executable(Demo_ch9_3 Demo_3.cpp)
add_executable(Demo_ch9_4 Demo_4.cpp)
add_executable(Demo_ch9_5 Demo_5.cpp)

target_link_libraries(Demo_ch9_2 ${OpenCV_LIBS})
target_link_libraries(Demo_ch9_3 ${OpenCV_LIBS})
target_link_libraries(Demo_ch9_4 ${OpenCV_LIBS})
target_link_libraries(Demo_ch9_5 ${OpenCV_LIBS})