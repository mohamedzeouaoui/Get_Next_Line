*This project has been created as part of the 42 curriculum by mzeouaou.*

<h1 align="center">Get Next Line</h1>

<p align="center">
  <em>Reading a line from a file descriptor is way too tedious.</em><br>
  A function that returns one line at a time from any file descriptor.
</p>

<p align="center">
  <img alt="Language" src="https://img.shields.io/badge/language-C-blue">
  <img alt="Norm" src="https://img.shields.io/badge/norminette-passing-brightgreen">
  <img alt="42" src="https://img.shields.io/badge/school-42-black">
</p>

---

## Table of Contents

- [Description](#description)
- [Installation](#installation)
- [Usage](#usage)
- [Behavior](#behavior)
- [Bonus](#bonus)
- [Project Structure](#project-structure)
- [How It Works](#how-it-works)
- [Testing](#testing)
- [Author](#author)
- [Resources](#resources)

---

## Description

**Get Next Line** is a 42 project where you write a function that reads a file descriptor and returns **one line per call**. It teaches **static variables**, **buffered reading** with `read()`, and careful **memory management** in C.

```c
char *get_next_line(int fd);
```

Calling it in a loop reads the whole file, one line at a time, whether it comes from a file, the standard input or any other file descriptor.

## Installation

```bash
git clone https://github.com/mohamedzeouaoui/Get_Next_Line.git
cd Get_Next_Line
```

There is no library to build: add the source files to your own project.

## Usage

The size of the read buffer is defined at compile time with the `BUFFER_SIZE` macro:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o gnl
```

Example `main.c`:

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## Behavior

| Situation                       | Result                                                      |
|---------------------------------|-------------------------------------------------------------|
| A line is read                  | Returns the line **including** the `\n` (if there is one)  |
| Last line with no `\n` at the end | Returns the line without `\n`                             |
| End of file reached             | Returns `NULL`                                              |
| Read error or invalid `fd`      | Returns `NULL`                                              |
| `BUFFER_SIZE` of 1, 42 or 10000000 | Works the same way                                       |

The returned string is allocated with `malloc`, so the **caller must `free` it**.

## Bonus

The bonus version handles **several file descriptors at the same time**, without losing the reading position of each one, and uses **a single static variable**.

```c
int fd1 = open("a.txt", O_RDONLY);
int fd2 = open("b.txt", O_RDONLY);

char *l1 = get_next_line(fd1);   // first line of a.txt
char *l2 = get_next_line(fd2);   // first line of b.txt
char *l3 = get_next_line(fd1);   // second line of a.txt
```

> Remove this section if you did not do the bonus.

## Project Structure

```text
Get_Next_Line/
├── get_next_line.c           # Main function
├── get_next_line_utils.c     # Helper functions (strlen, strchr, strjoin...)
├── get_next_line.h           # Prototype and BUFFER_SIZE default
├── get_next_line_bonus.c     # Bonus: multiple file descriptors
├── get_next_line_utils_bonus.c
└── get_next_line_bonus.h
```

> Adjust this tree to match your own files.

## How It Works

1. **Static storage**: a static variable keeps the data that was read from the file descriptor but not yet returned. It survives between calls.
2. **Read loop**: `read()` fills a buffer of `BUFFER_SIZE` bytes, which is appended to the stored data, until a `\n` is found or the end of the file is reached.
3. **Extract the line**: everything up to and including the first `\n` is copied into a new string, which is returned.
4. **Keep the rest**: what comes after the `\n` stays in the static variable for the next call.
5. **Cleanup**: when the file is finished or an error occurs, the stored data is freed and `NULL` is returned, so there are no leaks.

For the bonus, the static storage is an array indexed by the file descriptor, so each one keeps its own remaining data.

## Testing

Check for leaks and invalid reads:

```bash
valgrind --leak-check=full ./gnl
```

Edge cases worth testing:

- An empty file, and a file with only `\n`
- A file with no `\n` at the end
- Very long lines, and very many short lines
- `BUFFER_SIZE` of `1`, `2`, `42`, `9999` and `10000000`
- Reading from the standard input (`fd` `0`)
- An invalid file descriptor (`-1`, a closed `fd`)
- Binary files
- Bonus: alternating between several file descriptors

Community testers:

- [gnlTester](https://github.com/Tripouille/gnlTester)
- [gnl-war-machine-v2021](https://github.com/Tripouille/gnl-war-machine-v2021)

## Author

- **Mohamed Zeouaoui**: [@mohamedzeouaoui](https://github.com/mohamedzeouaoui)

## Resources

- `man 2 read`
- [Static variables in C](https://en.wikipedia.org/wiki/Static_variable)
- The 42 Norm

### Use of AI

> Describe here how AI was used in this project (which tasks, which parts), and what you checked and understood yourself.
