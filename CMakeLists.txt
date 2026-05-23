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

add_executable(06_ring_buffer
  src/06_ring_buffer/main.c
  src/06_ring_buffer/ring_buffer.c
)
target_include_directories(06_ring_buffer PRIVATE src/06_ring_buffer)
add_test(NAME ring_buffer COMMAND 06_ring_buffer)

add_executable(07_state_machine
  src/07_state_machine/main.c
  src/07_state_machine/state_machine.c
)
target_include_directories(07_state_machine PRIVATE src/07_state_machine)
add_test(NAME state_machine COMMAND 07_state_machine)

add_executable(08_memory_bugs src/08_memory_bugs/main.c)
add_test(NAME memory_bugs COMMAND 08_memory_bugs)

add_executable(09_unit_test_framework
  src/09_unit_test_framework/main.c
  src/09_unit_test_framework/mini_test.c
)
target_include_directories(09_unit_test_framework PRIVATE src/09_unit_test_framework)
add_test(NAME unit_test_framework COMMAND 09_unit_test_framework)

add_executable(10_serial_protocol_parser
  src/10_serial_protocol_parser/main.c
  src/10_serial_protocol_parser/serial_parser.c
)
target_include_directories(10_serial_protocol_parser PRIVATE src/10_serial_protocol_parser)
add_test(NAME serial_protocol_parser COMMAND 10_serial_protocol_parser)

add_executable(11_mini_malloc
  src/11_mini_malloc/main.c
  src/11_mini_malloc/mini_malloc.c
)
target_include_directories(11_mini_malloc PRIVATE src/11_mini_malloc)
add_test(NAME mini_malloc COMMAND 11_mini_malloc)

add_executable(12_linux_process_pipe src/12_linux_process_pipe/main.c)
add_test(NAME linux_process_pipe COMMAND 12_linux_process_pipe)
