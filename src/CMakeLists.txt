SET(EXE_NAME pong)

add_executable( ${EXE_NAME}
    Game.cpp
    main.cpp
)

#target_compile_options( ${TEST_NAME} PRIVATE ${ROMZ_CXX_FLAGS} )

target_link_libraries( ${EXE_NAME} 
    SDL2 
)



