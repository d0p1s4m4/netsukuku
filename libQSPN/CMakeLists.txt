project(libQSPN)

add_library(${PROJECT_NAME}
	dummy.c
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
)

if(UNIT_TESTING)
	add_subdirectory(tests)
endif()