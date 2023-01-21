cmake_minimum_required(VERSION 3.24)
project(Micetopia C)

set(CMAKE_C_STANDARD 11)

include_directories(c:\\Dev\\smd_dev\\devkit\\sgdk180dev\\inc)
include_directories(c:\\Dev\\smd_dev\\devkit\\sgdk180dev\\inc\\ext)
include_directories(c:\\Dev\\smd_dev\\devkit\\sgdk180dev\\inc\\ext\\flash-save)
include_directories(c:\\Dev\\smd_dev\\devkit\\sgdk180dev\\res)

include_directories(inc)
include_directories(res)
include_directories(src/pfsm)
include_directories(src/pfsm/states)

add_executable(Micetopia
        inc/camera.h
        inc/colmap.h
        inc/debug.h
        inc/defs.h
        inc/entities.h
        inc/gfx.h
        inc/global.h
        inc/hud.h
        inc/level.h
        inc/lvl_gen.h
        inc/obj_debug.h
        inc/physics.h
        inc/player.h
        inc/chars.h
        inc/types.h
        res/sounds.h
        res/sprites.h
        res/tilemaps.h
        src/boot/rom_head.c
        src/pfsm/states/attack.c
        src/pfsm/states/attack.h
        src/pfsm/states/idle.c
        src/pfsm/states/idle.h
        src/pfsm/states/jump.c
        src/pfsm/states/jump.h
        src/pfsm/states/fall.h
        src/pfsm/states/fall.c
        src/pfsm/states/walk.c
        src/pfsm/states/walk.h
        src/pfsm/fsm.c
        src/pfsm/fsm.h
        src/pfsm/state.c
        src/pfsm/state.h
        src/camera.c
        src/colmap.c
        src/debug.c
        src/entities.c
        src/gfx.c
        src/global.c
        src/hud.c
        src/level.c
        src/lvl_gen.c
        src/main.c
        src/obj_debug.c
        src/physics.c
        src/player.c
        src/chars.c
        src/types.c
        src/pfsm/states/fall.c
        src/pfsm/states/fall.h
        src/pfsm/states/air_attack.h
        src/pfsm/states/air_attack.c
        inc/input.h
        src/input.c
        inc/tile.h
        src/tile.c
        src/collision.c
        inc/collision.h
        src/colchar.c inc/colchar.h)
