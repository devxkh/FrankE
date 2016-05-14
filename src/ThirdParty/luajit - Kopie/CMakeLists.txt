   

# Add definition for Lua and LuaJIT

message("cmakelists - luajit")


# Properties->C/C++->General->Additional Include Directories
include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/luajit/src)

add_definitions (-DSCRIPT_LUAJIT)


# Define target name for LuaJIT library
set (TARGET_NAME LuaJIT)

# Macro for generating source file
macro (generate_source name mode)
    set (GEN_SRC ${CMAKE_CURRENT_BINARY_DIR}/generated/${name})
    set (GEN_SRCS ${GEN_SRCS} ${GEN_SRC})
    add_custom_command (OUTPUT ${GEN_SRC}
        COMMAND ${CMAKE_BINARY_DIR}/bin/tool/buildvm -m ${mode} -o ${GEN_SRC} ${ARGN}
        DEPENDS buildvm ${ARGN}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating buildvm output: ${name}")
endmacro ()

# Define generated source files
file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/generated)
if (WIN32)
    set (LJVM_MODE peobj)
    set (LJVM_BOUT lj_vm.obj)
else ()
    set (LJVM_BOUT lj_vm.s)
    enable_language (ASM)
    set (CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${DASH_MBIT}")
    if (APPLE)
        set (LJVM_MODE machasm)
    else ()
        set (LJVM_MODE elfasm)
    endif ()
endif ()
set (LJLIB_C src/lib_base.c src/lib_math.c src/lib_bit.c src/lib_string.c src/lib_table.c
    src/lib_io.c src/lib_os.c src/lib_package.c src/lib_debug.c src/lib_jit.c src/lib_ffi.c)
generate_source (${LJVM_BOUT} ${LJVM_MODE})
foreach (MODE bcdef ffdef libdef recdef)
    generate_source (lj_${MODE}.h ${MODE} ${LJLIB_C})
endforeach ()
generate_source (vmdef.lua vmdef ${LJLIB_C})
generate_source (lj_folddef.h folddef src/lj_opt_fold.c)


set (LJCORE_C src/lj_gc.c src/lj_err.c src/lj_char.c src/lj_bc.c src/lj_obj.c
        src/lj_str.c src/lj_tab.c src/lj_func.c src/lj_udata.c src/lj_meta.c src/lj_debug.c
        src/lj_state.c src/lj_dispatch.c src/lj_vmevent.c src/lj_vmmath.c src/lj_strscan.c
        src/lj_api.c src/lj_lex.c src/lj_parse.c src/lj_bcread.c src/lj_bcwrite.c src/lj_load.c
        src/lj_ir.c src/lj_opt_mem.c src/lj_opt_fold.c src/lj_opt_narrow.c
        src/lj_opt_dce.c src/lj_opt_loop.c src/lj_opt_split.c src/lj_opt_sink.c
        src/lj_mcode.c src/lj_snap.c src/lj_record.c src/lj_crecord.c src/lj_ffrecord.c
        src/lj_asm.c src/lj_trace.c src/lj_gdbjit.c
        src/lj_ctype.c src/lj_cdata.c src/lj_cconv.c src/lj_ccall.c src/lj_ccallback.c
        src/lj_carith.c src/lj_clib.c src/lj_cparse.c
        src/lj_lib.c src/lj_alloc.c src/lib_aux.c
        ${LJLIB_C} src/lib_init.c)

set (SOURCE_FILES ${LJCORE_C} )

# Define dependency libs
set (INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/generated)

message("sfml_add_library(luajit)")

sfml_add_library(luajit SOURCES ${SOURCE_FILES})

set_property(TARGET luajit PROPERTY FOLDER "ThirdParty")

