cmake_minimum_required(VERSION 3.14)

project(Bustout)

add_subdirectory(vendor)

set(
	main_sources
		src/main.cpp
		
		src/maths.h
		
		src/Layer.h
		src/Layer.cpp
		
		src/Shapes.h
		
		src/Ball.h
		src/Ball.cpp
		
		src/Paddle.h
		src/Paddle.cpp
		
		src/BlockGrid.h
		src/BlockGrid.cpp
		src/PowerUp.h
		src/collision.h
		src/collision.cpp
)

set(
	gfx_sources
		src/Sprite.h
		src/Sprite.cpp
		src/AnimatedSprite.h
		src/AnimatedSprite.cpp
)


set(
	scenes_sources
		src/Scene.h
		src/Scene.cpp
		src/SceneManager.h
		src/SceneManager.cpp
		
		src/MainMenuScene.h
		src/MainMenuScene.cpp
)

set(
	ui_sources
		src/Canvas.h
		src/Canvas.cpp
)

set(
	debug_sources
		src/DebugDraw.h
		src/DebugDraw.cpp
)

add_executable(
	Bustout
		${main_sources}
		${scenes_sources}
		${ui_sources}
		${gfx_sources}
		$<$<CONFIG:Debug>:${debug_sources}>
)

set_target_properties(Bustout PROPERTIES CXX_STANDARD 17)

source_group(main FILES ${main_sources})
source_group(scenes FILES ${scenes_sources})
source_group(ui FILES ${ui_sources})
source_group(gfx FILES ${gfx_sources})
source_group(debug FILES $<$<CONFIG:Debug>:${debug_sources}>)

macro(add_sfml_dependency my_target sfml_target)
	add_custom_command(
		TARGET ${my_target}
		PRE_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
			$<TARGET_FILE:${sfml_target}>
			$<TARGET_FILE_DIR:${my_target}>/$<TARGET_FILE_NAME:${sfml_target}>
	)

	target_link_libraries(
		${my_target}
			PRIVATE
				${sfml_target}
	)
endmacro()

add_sfml_dependency(Bustout sfml-graphics)
add_sfml_dependency(Bustout sfml-window)
add_sfml_dependency(Bustout sfml-system)

target_compile_definitions(Bustout PRIVATE ASSET_DIR="${CMAKE_SOURCE_DIR}/assets" $<$<CONFIG:Debug>:BUSTOUT_DEBUG>)

# set max warning level and VS startup project
if(MSVC)
	add_compile_options(/W4 /WX)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Bustout)
else()
	add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()