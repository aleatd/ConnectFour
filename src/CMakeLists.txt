cmake_minimum_required(VERSION 3.26.5)
project(ConnectFour C)

set(CMAKE_C_STANDARD 23)

find_package(Curses REQUIRED)

add_executable(
        ConnectFour
        main.c main.h
        sGame/sGame.c sGame/sGame.h
        vInstructions/vInstructions.c vInstructions/vInstructions.h
        vMain/vMain.c vMain/vMain.h
        vWin/vWin.c vWin/vWin.h

)

target_link_libraries(ConnectFour PRIVATE ${CURSES_LIBRARIES})
target_include_directories(ConnectFour PRIVATE ${CURSES_INCLUDE_DIRS})
