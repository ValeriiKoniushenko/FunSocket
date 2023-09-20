add_executable(Example1Server Example1Server.cpp)
target_link_libraries(Example1Server PUBLIC WSA Socket)

add_executable(Example1Client Example1Client.cpp)
target_link_libraries(Example1Client PUBLIC WSA Socket)


add_executable(Example2Server Example2Server.cpp)
target_link_libraries(Example2Server PUBLIC WSA Socket)

add_executable(Example2Client Example2Client.cpp)
target_link_libraries(Example2Client PUBLIC WSA Socket)
