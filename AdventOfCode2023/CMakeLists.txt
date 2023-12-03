# CMakeList.txt : CMake project for AdventOfCode2023, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)



# Add source to this project's executable.
add_executable (AdventOfCode2023 "AdventOfCode2023.cpp" "AdventOfCode2023.h" "Helpers/GetInput.h" "Helpers/GetInput.cpp" "ICodeChallange.h" "CodeChallange.cpp" "1.h" "1.cpp" "2.h" "2.cpp" "3.h" "3.cpp" "4.h" "4.cpp" "5.h" "5.cpp" "6.h" "6.cpp"  "7.h" "7.cpp" "8.h" "8.cpp" "9.h" "9.cpp" "10.h" "10.cpp" "11.h" "11.cpp" "12.h" "12.cpp" "13.h" "13.cpp" "14.h" "14.cpp" "15.h" "15.cpp" "16.h" "16.cpp" "17.h" "17.cpp" "18.h" "18.cpp" "19.h" "19.cpp" "20.h" "20.cpp" "21.h" "21.cpp" "22.h" "22.cpp" "23.h" "23.cpp" "24.h" "24.cpp" "25.h" "25.cpp" )

# TODO: Add tests and install targets if needed.
set_property(TARGET AdventOfCode2023 PROPERTY CXX_STANDARD 20)
set_property(TARGET AdventOfCode2023 PROPERTY CXX_STANDARD_REQUIRED ON)