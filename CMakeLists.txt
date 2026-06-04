cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_FETCH_FROM_GIT ON)

include(pico_sdk_import.cmake)

project(CCCC_PicoTest1)

project(MyPicoProject C CXX ASM)

# 2. Initialize the Pico SDK
pico_sdk_init()

# 3. Tell it which C file to use (your actual file name)
add_executable(CCCC_PicoTest1 main.c)

# 4. Link the standard Pico library
target_link_libraries(CCCC_PicoTest1 pico_st)

# 5. Enable the generation of the .uf2 file
pico_add_extra_outputs(CCCC_PicoTest1)