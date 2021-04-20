include(CheckCCompilerFlag)

if(MSVC)
  add_compile_options(/FS)
  add_compile_definitions(_CRT_SECURE_NO_WARNINGS) # necessary to compile for UWP
endif()

if (NOT MSVC)
  check_c_compiler_flag("-Wno-varargs" COMPILER_SUPPORTS_NO_VARARGS_FLAG)
endif()

macro(use_all_warnings TARGET_NAME)
  if(MSVC)
    target_compile_options(${TARGET_NAME} PRIVATE 
      /W4 # enable most warnings, then disable:
      /wd4244 # 'conversion' conversion from 'type1' to 'type2', possible loss of data
      /wd4267 # 'var' : conversion from 'size_t' to 'type', possible loss of data 
      /wd4996 # deprecated functions, e.g. 'sprintf': This function or variable may be unsafe. Consider using sprintf_s instead.
      /wd4456 # declaration of 'identifier' hides previous local declaration
      /wd4800 # forcing value to 'true' or 'false' (performance warning)
      /wd4204 # nonstandard extension used: non-constant aggregate initializer
      /wd4701 # potentially uninitialized local variable
    )
  else()
    target_compile_options(${TARGET_NAME} PRIVATE 
      # GCC-style compilers:
      $<$<C_COMPILER_ID:GCC,Clang,AppleClang,Intel>:
        -Wall -Wextra -pedantic -Werror -Wno-unused-function -Wno-unused-parameter -Wno-sign-compare
      >
      $<$<BOOL:${COMPILER_SUPPORTS_NO_VARARGS_FLAG}>:-Wno-varargs>
      # Intel compiler:
      $<$<C_COMPILER_ID:Intel>:
        # disable #279: controlling expression is constant; affecting assert(condition && "message")
        # disable #188: enumerated type mixed with another type; affecting IGRAPH_CHECK
        # disable #592: variable "var" is used before its value is set; affecting IGRAPH_UNUSED
        -wd279 -wd188 -wd592 -diag-disable=remark
      >
    )
  endif()
endmacro()

