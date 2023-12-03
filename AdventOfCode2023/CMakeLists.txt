# CMakeList.txt : CMake project for AdventOfCode2023, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (AdventOfCode2023 "AdventOfCode2023.cpp" "AdventOfCode2023.h" "Helpers/GetInput.h" "Helpers/GetInput.cpp" "ICodeChallange.h" "CodeChallange.cpp" "1.h" "1.cpp" "2.h" "2.cpp" "3.h" "3.cpp")

# TODO: Add tests and install targets if needed.
