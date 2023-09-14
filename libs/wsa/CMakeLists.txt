file(
	GLOB Sources
	*.cpp
)

add_library(WSA SHARED ${Sources})

target_include_directories(WSA PUBLIC .)

target_link_libraries(WSA PUBLIC
	Utils
	wsock32
	ws2_32
)