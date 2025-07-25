# Project PIPEX
## Objective
This project focuses on handling pipes.
## Functions allowed
🧰 File & I/O Operations
- open: Opens a file and returns a file descriptor.

- close: Closes an open file descriptor.

- read: Reads data from a file descriptor into a buffer.

- write: Writes data from a buffer to a file descriptor.

- access: Checks a file’s accessibility (read/write/execute/existence).

- unlink: Deletes a name from the filesystem (removes a file).

🧠 Memory Management
- malloc: Allocates memory dynamically from the heap.

- free: Deallocates memory previously allocated by malloc.

🐛 Error Handling
- perror: Prints a system error message based on errno.

- strerror: Returns a string describing an error code.

🔁 File Descriptor Manipulation
- dup: Duplicates a file descriptor to the lowest available number.

- dup2: Duplicates a file descriptor to a specific target number.

🔧 Process Control
- execve: Replaces current process image with a new executable.

- exit: Terminates the current process and returns a status.

- fork: Creates a new process by duplicating the current one.

- pipe: Creates a unidirectional data channel for interprocess communication.

- wait: Waits for any child process to terminate.

- waitpid: Waits for a specific child process to terminate.
## Commands
The following command will show all the system calls happening.
```
strace -f -e trace=process,write,read bash -c 'cat file.txt | grep "error"'
```
`pstree` shows all the process in a tree format
```
pstree
```
For gdb debugging
```
set follow-fork-mode child
```
## Fonts
`https://reactive.so/post/42-a-comprehensive-guide-to-pipex/`
`https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY`
