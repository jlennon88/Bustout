# Bustout
A simple breakout clone

## Building (Windows)

1. Run `generate_win64.bat` from the root Bustout directory.
2. IDE solution/project files will be in the newly created `build` folder.

*Should* work on other platforms, just follow the platform-equivalent steps in the `generate_win64.bat`, but I haven't tested. I've only tested with Visual Stdio + MSVC.

## Dependencies

Needs CMake (Version 3.14+) and SFML, which is available as a submodule: use `git submodule init` followed by `git submodule update` before generating.
