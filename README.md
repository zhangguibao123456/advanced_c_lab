# Advanced C Lab

This workspace is for moving from basic C syntax into production-style C:

- pointer ownership and callback design
- arena memory management
- hash table implementation
- Linux system programming
- embedded-style protocol parsing
- ring buffers and state machines
- memory-bug diagnosis
- minimal test framework design
- stream protocol parsing
- allocator internals
- process and pipe basics

Build in WSL:

```bash
cd ~/code/advanced_c_lab
cmake -S . -B build -G Ninja
cmake --build build
ctest --test-dir build --output-on-failure
```

Run the full quality gate:

```bash
bash scripts/check.sh
```

Run individual labs:

```bash
./build/01_pointer_lab
./build/02_arena_allocator
./build/03_hash_table
./build/04_linux_file_tool README.md
./build/05_protocol_parser
./build/06_ring_buffer
./build/07_state_machine
./build/08_memory_bugs
./build/09_unit_test_framework
./build/10_serial_protocol_parser
./build/11_mini_malloc
./build/12_linux_process_pipe
```

Training order:

1. Read each lab's code and run it.
2. Break one assumption intentionally.
3. Rebuild with `bash scripts/check.sh`.
4. Use `gdb`, `valgrind`, or log prints to explain the failure.
5. Commit a small improvement.

Useful debugging commands:

```bash
gdb --args ./build/06_ring_buffer
valgrind --leak-check=full ./build/08_memory_bugs
ctest --test-dir build --output-on-failure
```
