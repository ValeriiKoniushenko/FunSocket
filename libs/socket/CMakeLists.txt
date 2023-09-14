file(
	GLOB Sources
	*.cpp
	*.h
)

add_library(Socket SHARED ${Sources})

target_include_directories(Socket PUBLIC .)

target_link_libraries(Socket PUBLIC
	WSA
)