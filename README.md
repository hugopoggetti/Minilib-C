## 🛠️ MinilibC - Custom C Library in Assembly 🚀

MinilibC is a lightweight **x86-64 Assembly** implementation of essential C standard library functions. This project aims to create a dynamic ELF library (`libasm.so`) that can replace standard C functions using **weak binding** and `LD_PRELOAD`. ⚙️💾

## 📜 Features  

✅ Optimized implementations of standard C functions 📏  
✅ Fully written in **x86-64 NASM Assembly** 🔥  
✅ Dynamically linked as `libasm.so`  
✅ Can be used with `LD_PRELOAD` for function replacement 🏴‍☠️  
✅ Includes **bonus functions** for extended functionality 🎁  

## 🛠️ Installation & Compilation  

### 📦 Build the Library  

```bash
make
make tests_run # Run unit test
```

### 🔄 Clean the Build  

```bash
make clean     # Remove object files
make fclean    # Remove object files & binary
```

### 🏗️ Rebuild Everything  

```bash
make re
```

## 📁 Project Structure  

```
📦 Minilib-C
├── 📜 Makefile      # Compilation rules
├── 📜 README.md
├── 📜 libasm.so     # Compiled dynamic library
├── 📂 src/          # Assembly source code (.asm)
├── 📂 obj/          # Compiled object files (.o)
└── 📂 tests/        # Unit tests for validation
```

## 🔧 Implemented Functions  

MinilibC includes the following standard C functions (refer to `man <function>` for details):

- `strlen`
- `strchr`
- `strrchr`
- `memset`
- `memcpy`
- `strcmp`
- `memmove`
- `strncmp`
- `strcasecmp`
- `strstr`
- `strpbrk`
- `strcspn`

## 🔥 Using MinilibC with `LD_PRELOAD`  

To override system functions with MinilibC:

```bash
LD_PRELOAD=./libasm.so your_program Minilib-C
