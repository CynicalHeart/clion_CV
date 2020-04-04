
add_executable(Demo_1 Demo_1.cpp header/Demo_ch6_1.h sources/Demo_ch6_1.cpp)
add_executable(Demo_3 Demo_3.cpp header/Demo_ch6_3.h sources/Demo_ch6_3.cpp)
add_executable(Demo_5 Demo_5.cpp header/Demo_ch6_5.h sources/Demo_ch6_5.cpp)
add_executable(Demo_6 Demo_6.cpp header/Demo_ch6_6.h sources/Demo_ch6_6.cpp)
add_executable(Demo_7 Demo_7.cpp header/Demo_ch6_7.h sources/Demo_ch6_7.cpp)

# Á´½ÓOpenCV¿âÎÄ¼þ
target_link_libraries(Demo_1 ${OpenCV_LIBS})
target_link_libraries(Demo_3 ${OpenCV_LIBS})
target_link_libraries(Demo_5 ${OpenCV_LIBS})
target_link_libraries(Demo_6 ${OpenCV_LIBS})
target_link_libraries(Demo_7 ${OpenCV_LIBS})