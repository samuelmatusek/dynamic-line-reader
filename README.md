# Dynamic Line Reader & Reverse Output (C)

A C program designed to read an arbitrary number of lines of arbitrary length from standard input (`stdin`) and print them in reverse order. This project demonstrates robust low-level dynamic memory management, safe reallocation patterns, and edge-case handling without memory leaks.

---

## Overview

The program reads characters sequentially using `getchar()` and manages dynamic memory on two levels:

1. **Outer Pointer Array (`char **text`):** Holds pointers to individual lines. Initialized to hold 8 pointers and doubles its capacity dynamically using `realloc`. Newly expanded pointer slots are safely zeroed out (`NULL`) to prevent reading invalid memory.
2. **Line Buffers (`char *text[i]`):** Each line starts with an 8-byte allocation and doubles in size via the helper function `realokuj_text()` whenever the character limit is reached.
3. **Delimiter & EOF Handling:** Distinguishes between newline characters (`\n`), end-of-file (`EOF`), and ensures all stored strings are null-terminated (`\0`).
4. **Reversed Output:** Traverses lines in reverse order from the last line entered to the first, maintaining correct 1-based index labels.
5. **Deterministic Cleanup:** The `uvolni_text()` function deallocates every individual row before freeing the top-level pointer array.

---

## Key Features & Safety Mechanisms

- **Arbitrary Input Sizes:** No fixed buffer sizes; handles lines and line counts of any length, bounded only by system memory.
- **Safe Realloc Pattern:** All reallocations assign to a temporary pointer (`temp`) first, preventing memory leaks if allocation fails.
- **Zeroed Pointer Slots:** Prevents invalid frees and segmentation faults during error recovery or unexpected EOF sequences.
- **Strict Pointer Arithmetic & Sizing:** Distinguishes between dereferenced pointer sizes (`sizeof(*text)`) and character types (`sizeof(*text[radky])`).
- **Valgrind-Clean:** Free of memory leaks, double frees, and out-of-bounds reads/writes.

---

## Compilation & Usage

### Compilation
Recommended compilation flags with GCC:
```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o reverse_text
```

### Running the Program
Interactive input mode:
```bash
./reverse_text
```
*(Press `Ctrl + D` on a new line on Linux/macOS or `Ctrl + Z` followed by Enter on Windows to signal EOF).*

### Check for Memory Leaks (Valgrind)
```bash
valgrind --leak-check=full --show-leak-kinds=all ./reverse_text
```

---

## Example

### Input:
```text
Napis nejaky text:
First line
Second longer line of text
Third line
```

### Output:
```text
--- Obracene poradi ---
[3]: Third line
[2]: Second longer line of text
[1]: First line
```

---

## Project Structure

- `main.c` – Full source code containing memory allocation logic, input parsing, and cleanup.
- `README.md` – Project documentation.
