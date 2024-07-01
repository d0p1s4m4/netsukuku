project(ntkd)

option(${PROJECT_NAME}_ENABLE_WEBUI "" OFF)

find_package(libconfig CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
	main.c
	config/cfg.c
	config/opt.c
	network/server.c
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		libntk libconfig::libconfig
		$<$<PLATFORM_ID:Windows>:ws2_32 mswsock PThreads4W::PThreads4W unofficial::getopt-win32::getopt>
)

if(${PROJECT_NAME}_ENABLE_WEBUI)
	target_link_libraries(${PROJECT_NAME}
		PRIVATE
			microhttpd)
	target_compile_definitions(${PROJECT_NAME}
		-DENABLE_WEBUI)
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)