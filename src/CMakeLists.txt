SET(EXE_NAME pong)

add_executable( ${EXE_NAME}
    Game.cpp
    Global_renderer.cpp
    Global_window.cpp
    Paddle.cpp
    Pong.cpp
    Vector2d.cpp
    main.cpp
    unique.cpp
)

#target_compile_options( ${TEST_NAME} PRIVATE ${ROMZ_CXX_FLAGS} )

target_link_libraries( ${EXE_NAME} 
    SDL2 
)



