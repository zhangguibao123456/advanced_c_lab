# Advanced C Lab

This workspace is for moving from basic C syntax into production-style C:

- pointer ownership and callback design
- arena memory management
- hash table implementation
- Linux system programming
- embedded-style protocol parsing

Build in WSL:

```bash
cd /mnt/c/00_Dev/01_C/advanced_c_lab
cmake -S . -B build -G Ninja
cmake --build build
ctest --test-dir build --output-on-failure
```

Run individual labs:

```bash
./build/01_pointer_lab
./build/02_arena_allocator
./build/03_hash_table
./build/04_linux_file_tool README.md
./build/05_protocol_parser
```

