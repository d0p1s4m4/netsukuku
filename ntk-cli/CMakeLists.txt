project(ntk-cli)

add_executable(${PROJECT_NAME}
	main.c
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		libntk
		$<$<PLATFORM_ID:Windows>:ws2_32 mswsock PThreads4W::PThreads4W unofficial::getopt-win32::getopt>
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)