# This file is NOT licensed under the GPLv3, which is the license for the rest
# of YouCompleteMe.
#
# Here's the license text for this file:
#
# This is free and unencumbered software released into the public domain.
#
# Anyone is free to copy, modify, publish, use, compile, sell, or
# distribute this software, either in source code form or as a compiled
# binary, for any purpose, commercial or non-commercial, and by any
# means.
#
# In jurisdictions that recognize copyright laws, the author or authors
# of this software dedicate any and all copyright interest in the
# software to the public domain. We make this dedication for the benefit
# of the public at large and to the detriment of our heirs and
# successors. We intend this dedication to be an overt act of
# relinquishment in perpetuity of all present and future rights to this
# software under copyright law.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
# OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#
# For more information, please refer to <http://unlicense.org/>

import os
import ycm_core

# These are the compilation flags that will be used in case there's no
# compilation database set (by default, one is not set).
# CHANGE THIS LIST OF FLAGS. YES, THIS IS THE DROID YOU HAVE BEEN LOOKING FOR.
flags = [
    '-wall',
    '-wextra',
    '-werror',
    # '-wc++98-compat',
    '-wno-long-long',
    '-wno-variadic-macros',
    '-fexceptions',
    '-dndebug',
    # you 100% do not need -duse_clang_completer in your flags; only the ycm
    # source code needs it.
    '-duse_clang_completer',
    # this is important! without a "-std=<something>" flag, clang won't know which
    # language to use when compiling headers. so it will guess. badly. so c++
    # headers will be compiled as c headers. you don't want that so always specify
    # a "-std=<something>".
    # for a c project, you would set this to something like 'c99' instead of
    # 'c++11'.
    '-std=c++11',
    # ...and the same thing goes for the magic -x option which specifies the
    # language that the files to be compiled are written in. this is mostly
    # relevant for c++ headers.
    # for a c project, you would set this to 'c' instead of 'c++'.
    '-x',
    'c++',
    '-isystem',
    '../boostparts',
    '-isystem',
    # this path will only work on os x, but extra paths that don't exist are not
    # harmful
    '/system/library/frameworks/python.framework/headers',
    '-isystem',
    '../llvm/include',
    '-isystem',
    '../llvm/tools/clang/include',
    '-I/usr/include/nodejs/src',
    '-I./',
    '-isystem',
    './clangcompleter',
    '-isystem',
    './tests/gmock/gtest',
    '-isystem',
    './tests/gmock/gtest/include',
    '-isystem',
    './tests/gmock',
    '-isystem',
    './tests/gmock/include'
    ]

"""
flags = [
'-Wall ',
'-Wextra ',
'-Werror ',
'-x', 'c++ ',
'-std=c++11 ',
'-isystem ',
'/usr/include/nodejs/src/'
]
"""

# Set this to the absolute path to the folder (NOT the file!) containing the
# compile_commands.json file to use that instead of 'flags'. See here for
# more details: http://clang.llvm.org/docs/JSONCompilationDatabase.html
#
# You can get CMake to generate this file for you by adding:
#   set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
# to your CMakeLists.txt file.
#
# Most projects will NOT need to set this to anything; you can just change the
# 'flags' list of compilation flags. Notice that YCM itself uses that approach.


def FlagsForFile( filename, **kwargs ):

  return {
    'flags': flags,
    'do_cache': False
  }
