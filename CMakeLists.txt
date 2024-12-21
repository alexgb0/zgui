# CMakeList.txt : CMake project for zgui, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("zgui")

find_package(raylib CONFIG REQUIRED)
# Add source to this project's executable.
add_executable (zgui "src/main.cpp" "src/zgui.h" "src/component.h" "src/calc.cpp" "src/component.cpp" "src/gui.cpp" "src/builder.h" "src/builder.cpp"  "src/draw.cpp")
target_link_libraries(zgui PRIVATE raylib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET zgui PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
