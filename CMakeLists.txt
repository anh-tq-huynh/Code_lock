cmake_minimum_required(VERSION 3.12)

# 1. Set Pico Board & C/C++ Standards
set(PICO_BOARD pico_w)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)

# 2. Set Kernel Path
set(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/rp2040-freertos-minimal/FreeRTOS-KernelV10.6.2)

# 3. Import SDK & FreeRTOS CMake setup
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

# 4. Declare Project (Must come after imports, before targets)
project(Lab2 C CXX ASM)

# 5. Initialize Pico SDK
pico_sdk_init()

# 6. Add Executable & Sources
add_executable(Lab2
        main.cpp
        GPIOPin.cpp
        GPIOPin.h
        Button.cpp
        Button.h
        LED.cpp
        LED.h
        taskButtonRead.cpp
        taskButtonRead.h
        taskPressProcess.cpp
        taskPressProcess.h
        vPrintString.cpp
        vPrintString.h

)

# 7. Include Directories
target_include_directories(Lab2 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/rp2040-freertos-minimal
        ${CMAKE_CURRENT_SOURCE_DIR}/rp2040-freertos-minimal/src
        ${CMAKE_CURRENT_SOURCE_DIR}/rp2040-freertos-minimal/FreeRTOS-KernelV10.6.2/include
)

# 8. Link Libraries
target_link_libraries(Lab2
        pico_stdlib
        hardware_gpio
        FreeRTOS-Kernel
        FreeRTOS-Kernel-Heap4
)

pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 1)