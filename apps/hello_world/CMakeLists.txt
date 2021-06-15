project(HELLO_WORLD C)

include_directories(fsw/mission_inc)
include_directories(fsw/platform_inc)

# Create the app module
add_cfe_app(hw fsw/src/hw.c)
