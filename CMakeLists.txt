cmake_minimum_required(VERSION 2.6)
project(monitor)

<<<<<<< HEAD
set(CURSES_NEED_NCURSES TRUE)
=======
>>>>>>> 59bf69ccd5ae6ec23629570447b64d6eac5941ce
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(monitor ${SOURCES})

set_property(TARGET monitor PROPERTY CXX_STANDARD 17)
target_link_libraries(monitor ${CURSES_LIBRARIES})
# TODO: Run -Werror in CI.
target_compile_options(monitor PRIVATE -Wall -Wextra)
