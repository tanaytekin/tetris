cmake_minimum_required(VERSION 3.12)


file(MAKE_DIRECTORY assets)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)

string(REPLACE " " "_" PROJECT_NAME ${PROJECT_NAME})


project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)


file(GLOB SOURCES
	"*.hh"
	"*.cc"
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image SDL2_ttf )
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
