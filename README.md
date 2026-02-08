<img width="2000" height="1000" alt="image" src="https://github.com/user-attachments/assets/649ce55d-ee8e-4c0c-8412-c4c60a8fe189" />

# get_next_line

A function that reads a single line from a file descriptor, implementing efficient file reading as part of the 42 School curriculum.

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Function Prototype](#function-prototype)
- [Implementation Details](#implementation-details)
- [Project Structure](#project-structure)
- [Compilation](#compilation)
- [Testing](#testing)
- [Key Concepts](#key-concepts)
- [Author](#author)

## Description

`get_next_line` is a function that allows you to read a file line by line from any file descriptor. This project introduces important concepts like static variables, dynamic memory allocation, and file descriptor manipulation. The function handles files of any size and can read from multiple file descriptors simultaneously (bonus part).

## Features

- ✅ Reads one line at a time from any file descriptor
- ✅ Handles files of any size efficiently
- ✅ Works with standard input, files, and pipes
- ✅ Memory-efficient with configurable buffer size
- ✅ Static variable usage for maintaining state between calls
- ✅ Proper memory management and leak-free implementation
- ✅ Bonus: Multiple file descriptor support

## Installation

1. Clone the repository:
```bash
git clone git@github.com:wees-s/get_next_line_42.git
cd get_next_line_42
```

2. The project doesn't require compilation of a library - include the source files directly in your project.

## Usage

Include the header file in your C program:

```c
#include "get_next_line.h"
```

Compile with your program and define BUFFER_SIZE:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 your_program.c get_next_line.c get_next_line_utils.c -o your_program
```

Example usage:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;
    
    // Open a file
    fd = open("example.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    
    // Read line by line
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);  // Don't forget to free!
    }
    
    close(fd);
    return (0);
}
```

## Function Prototype

```c
char *get_next_line(int fd);
```

**Parameters:**
- `fd`: The file descriptor to read from

**Return Value:**
- Returns the line read including the terminating `\n` character (except for the last line if it doesn't end with `\n`)
- Returns `NULL` when there is nothing more to read or if an error occurs

## Implementation Details

### Core Algorithm

```c
char *get_next_line(int fd)
{
    static char *buffer;
    char *line;
    
    // Error checking
    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
        return (NULL);
    
    // Read from file and update buffer
    buffer = read_file(fd, buffer);
    if (!buffer)
        return (NULL);
    
    // Extract line from buffer
    line = extract_line(buffer);
    
    // Update buffer for next call
    buffer = update_buffer(buffer);
    
    return (line);
}
```

### Key Functions

| Function | Description | Purpose |
|----------|-------------|---------|
| `get_next_line` | Main function | Coordinates reading and line extraction |
| `read_file` | Reads from fd into buffer | Handles file reading with BUFFER_SIZE chunks |
| `extract_line` | Gets line from buffer | Extracts line up to `\n` or EOF |
| `update_buffer` | Updates static buffer | Removes extracted line from buffer |

### Utility Functions

| Function | Description | Usage |
|----------|-------------|-------|
| `ft_strlen` | Calculate string length | String manipulation |
| `ft_strchr` | Find character in string | Locate `\n` character |
| `ft_strjoin` | Join two strings | Concatenate buffer with new reads |
| `ft_substr` | Extract substring | Create line and update buffer |

## Project Structure

```
get_next_line/
├── get_next_line.c          # Main implementation
├── get_next_line_utils.c    # Utility functions
├── get_next_line.h          # Header file with prototypes
├── get_next_line_bonus.c    # Bonus: multiple fd support
├── get_next_line_bonus.h    # Bonus header
└── README.md               # This file
```

### Bonus Files
For multiple file descriptor support:
- `get_next_line_bonus.c`
- `get_next_line_bonus.h`

## Compilation

### Basic Compilation
```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c
```

### With Different Buffer Sizes
```bash
# Small buffer
gcc -D BUFFER_SIZE=1 main.c get_next_line.c get_next_line_utils.c

# Medium buffer
gcc -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c

# Large buffer  
gcc -D BUFFER_SIZE=9999 main.c get_next_line.c get_next_line_utils.c
```

### Bonus Compilation
```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line_bonus.c get_next_line_utils.c
```

## Testing

### Basic Test Program

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int fd;
    char *line;
    int line_count = 0;
    
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return (1);
    }
    
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file\n");
        return (1);
    }
    
    printf("Reading file: %s\n", argv[1]);
    printf("BUFFER_SIZE: %d\n\n", BUFFER_SIZE);
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d: %s", ++line_count, line);
        if (line[strlen(line) - 1] != '\n')
            printf(" (no newline at end)");
        printf("\n");
        free(line);
    }
    
    printf("\nTotal lines read: %d\n", line_count);
    close(fd);
    return (0);
}
```

### Test Cases to Consider

1. **Empty file**
2. **File with only one line (with/without `\n`)**
3. **File with multiple lines**
4. **Very long lines**
5. **Binary files**
6. **Standard input**
7. **Invalid file descriptors**
8. **Different BUFFER_SIZE values**

### Sample Test Files

Create test files:
```bash
# Empty file
touch empty.txt

# Single line without newline
echo -n "Single line without newline" > single_no_nl.txt

# Single line with newline
echo "Single line with newline" > single_with_nl.txt

# Multiple lines
printf "Line 1\nLine 2\nLine 3\n" > multiple_lines.txt

# Very long line
python -c "print('A' * 10000)" > long_line.txt
```

## Key Concepts

### Static Variables
The function uses static variables to maintain state between function calls, allowing it to remember where it left off in the file.

```c
static char *buffer; // Persists between function calls
```

### File Descriptors
The function works with any valid file descriptor:
- `0` (stdin)
- File descriptors from `open()`
- Pipe file descriptors

### Memory Management
- **Caller responsibility**: The returned line must be freed by the caller
- **Internal management**: Static buffer is managed internally
- **Leak prevention**: Proper cleanup on errors and EOF

### Buffer Size Optimization
The `BUFFER_SIZE` macro affects performance:
- **Small buffer**: More system calls, less memory usage
- **Large buffer**: Fewer system calls, more memory usage
- **Optimal**: Usually between 32-1024 depending on use case

## Implementation Challenges

### Edge Cases Handled
1. **File doesn't end with newline**
2. **Empty lines**
3. **Very large files**
4. **Multiple consecutive newlines**
5. **Binary data with null bytes**

### Error Conditions
- Invalid file descriptor
- Read errors
- Memory allocation failures
- Invalid BUFFER_SIZE (≤ 0)

## Bonus Features

The bonus version supports reading from multiple file descriptors simultaneously:

```c
int main(void)
{
    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    char *line1, *line2;
    
    line1 = get_next_line(fd1);  // Read from file1
    line2 = get_next_line(fd2);  // Read from file2
    line1 = get_next_line(fd1);  // Read next line from file1
    
    // Each fd maintains its own buffer state
}
```

## Performance Notes

- **Time Complexity**: O(n) where n is the length of the line
- **Space Complexity**: O(BUFFER_SIZE + line_length)
- **System Calls**: Minimized by buffering
- **Memory Usage**: Efficient with static buffer management

## Author

**wedos-sa** - Cadet at 42 São Paulo

---

*This project teaches fundamental concepts of file I/O, memory management, and static variables in C programming. It's an essential stepping stone toward more complex system programming projects.*
