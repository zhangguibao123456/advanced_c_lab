cmake_minimum_required(VERSION 3.20)
project(advanced_c_lab C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()

enable_testing()

add_executable(01_pointer_lab src/01_pointer_lab/main.c)
add_test(NAME pointer_lab COMMAND 01_pointer_lab)

add_executable(02_arena_allocator
  src/02_arena_allocator/main.c
  src/02_arena_allocator/arena.c
)
target_include_directories(02_arena_allocator PRIVATE src/02_arena_allocator)
add_test(NAME arena_allocator COMMAND 02_arena_allocator)

add_executable(03_hash_table
  src/03_hash_table/main.c
  src/03_hash_table/hash_table.c
)
target_include_directories(03_hash_table PRIVATE src/03_hash_table)
add_test(NAME hash_table COMMAND 03_hash_table)

add_executable(04_linux_file_tool src/04_linux_file_tool/main.c)
add_test(NAME linux_file_tool COMMAND 04_linux_file_tool ${CMAKE_CURRENT_SOURCE_DIR}/README.md)

add_executable(05_protocol_parser
  src/05_protocol_parser/main.c
  src/05_protocol_parser/protocol_parser.c
)
target_include_directories(05_protocol_parser PRIVATE src/05_protocol_parser)
add_test(NAME protocol_parser COMMAND 05_protocol_parser)

