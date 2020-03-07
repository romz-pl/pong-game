SET(EXE_NAME pong)

add_executable( ${EXE_NAME}
    Game.cpp
    Pong.cpp
    Vector2d.cpp
    main.cpp
    unique.cpp
)

#target_compile_options( ${TEST_NAME} PRIVATE ${ROMZ_CXX_FLAGS} )

target_link_libraries( ${EXE_NAME} 
    SDL2 
)



