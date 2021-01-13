set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(
	game_sources
		${SRC_DIR}/Bustout.h
		${SRC_DIR}/Bustout.cpp
		${SRC_DIR}/Shapes.h
		${SRC_DIR}/Ball.h
		${SRC_DIR}/Ball.cpp
		${SRC_DIR}/Paddle.h
		${SRC_DIR}/Paddle.cpp
		${SRC_DIR}/BlockGrid.h
		${SRC_DIR}/BlockGrid.cpp
		${SRC_DIR}/PowerUp.h
		${SRC_DIR}/collision.h
		${SRC_DIR}/collision.cpp
	PARENT_SCOPE
)