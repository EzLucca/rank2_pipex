# Project PIPEX
## Objective
This project focuses on handling pipes.
## Functions allowed
- open;

- close;

- read;

- write;

- malloc;

- free;

- perror;
`void perror(const char *s);`
The  perror()  function  produces a message on standard error describing the last error encountered during a call to a system or library
function.

- strerror;
`char *strerror(int errnum);`
The  strerror()  function  returns a pointer to a string that describes the error code passed in the argument errnum, possibly using the
LC_MESSAGES part of the current locale to select the appropriate language.  (For example, if errnum is EINVAL, the returned  description
        will  be  "Invalid  argument".)   This  string must not be modified by the application, but may be modified by a subsequent call to str‐
error() or strerror_l().  No other library function, including perror(3), will modify this string.

The XSI-compliant strerror_r() function returns 0 on success.  On error, a (positive) error number is returned (since glibc 2.13), or -1
is returned and errno is set to indicate the error (glibc versions before 2.13).

- access;
`int access(const char *pathname, int mode);`

access() checks whether the calling process can access the file pathname.  If pathname is a symbolic link, it is dereferenced.

On success (all requested permissions granted, or mode is F_OK and the file exists), zero is returned.  On error (at least  one  bit  in
        mode  asked for a permission that is denied, or mode is F_OK and the file does not exist, or some other error occurred), -1 is returned, and errno is set appropriately.

- dup;
`int dup(int oldfd);`

The dup() system call creates a copy of the file descriptor oldfd, using the lowest-numbered unused file descriptor for the new descrip‐
tor.
On success, these system calls return the new file descriptor.  On error, -1 is returned, and errno is set appropriately.

- dup2;
`int dup2(int oldfd, int newfd);`

The  dup2()  system  call  performs the same task as dup(), but instead of using the lowest-numbered unused file descriptor, it uses the
file descriptor number specified in newfd.  If the file descriptor newfd was previously open, it is silently closed before being reused.

The steps of closing and reusing the file descriptor newfd are performed atomically.  This is important,  because  trying  to  implement
equivalent  functionality  using  close(2)  and dup() would be subject to race conditions, whereby newfd might be reused between the two
steps.  Such reuse could happen because the main program is interrupted by a signal handler that allocates a file descriptor, or because
a parallel thread allocates a file descriptor.

Note the following points:

*  If oldfd is not a valid file descriptor, then the call fails, and newfd is not closed.

*  If oldfd is a valid file descriptor, and newfd has the same value as oldfd, then dup2() does nothing, and returns newfd.

On success, these system calls return the new file descriptor.  On error, -1 is returned, and errno is set appropriately.

- execve;
`int execve(const char *pathname, char *const argv[], char *const envp[]);`

execve() executes the program referred to by pathname.  This causes the program that is currently being run by the calling process to be
replaced with a new program, with newly initialized stack, heap, and (initialized and uninitialized) data segments.

pathname must be either a binary executable, or a script starting with a line of the form:
#!interpreter [optional-arg]
argv is an array of pointers to strings passed to the new program as its command-line arguments.  By  convention,  the  first  of  these
strings  (i.e.,  argv[0])  should  contain the filename associated with the file being executed.  The argv array must be terminated by a
NULL pointer.  (Thus, in the new program, argv[argc] will be NULL.).

On success, execve() does not return, on error -1 is returned, and errno is set appropriately.

- exit;
The exit utility shall cause the shell to exit from its current execution environment with the exit status  specified  by  the  unsigned
decimal  integer  n.  If the current execution environment is a subshell environment, the shell shall exit from the subshell environment
with the specified exit status and continue in the environment from which that subshell environment was invoked;  otherwise,  the  shell
utility  shall terminate with the specified exit status. If n is specified, but its value is not between 0 and 255 inclusively, the exit
status is undefined.

- fork;
`pid_t fork(void);`

fork()  creates  a  new  process  by duplicating the calling process.  The new process is referred to as the child process.  The calling
process is referred to as the parent process.

The child process and the parent process run in separate memory spaces.  At the time of fork() both memory spaces have the same content.
Memory writes, file mappings (mmap(2)), and unmappings (munmap(2)) performed by one of the processes do not affect the other.

The child process is an exact duplicate of the parent process except for the following points:

*  The child has its own unique process ID, and this PID does not match the ID of any existing process group (setpgid(2)) or session.

*  The child's parent process ID is the same as the parent's process ID.

*  The child does not inherit its parent's memory locks (mlock(2), mlockall(2)).

*  Process resource utilizations (getrusage(2)) and CPU time counters (times(2)) are reset to zero in the child.

*  The child's set of pending signals is initially empty (sigpending(2)).

*  The child does not inherit semaphore adjustments from its parent (semop(2)).

*  The  child does not inherit process-associated record locks from its parent (fcntl(2)).  (On the other hand, it does inherit fcntl(2)
        open file description locks and flock(2) locks from its parent.).

    *  The child does not inherit timers from its parent (setitimer(2), alarm(2), timer_create(2)).

    *  The child does not inherit outstanding asynchronous I/O operations from its parent (aio_read(3), aio_write(3)), nor does  it  inherit
    any asynchronous I/O contexts from its parent (see io_setup(2)).

    - pipe;
    pipe()  creates  a pipe, a unidirectional data channel that can be used for interprocess communication.  The array pipefd is used to re‐
    turn two file descriptors referring to the ends of the pipe.  pipefd[0] refers to the read end of the pipe.   pipefd[1]  refers  to  the
    write  end  of  the pipe.

    On success, zero is returned.  On error, -1 is returned, errno is set appropriately, and pipefd is left unchanged.

    - unlink;
    Call the unlink function to remove the specified FILE.

    - wait;

    When an asynchronous list (see Section 2.9.3.1, Examples) is started by the shell, the process ID of the last command in each element of
    the asynchronous list shall become known in the current shell execution environment; see Section 2.12, Shell Execution Environment.

    If  the  wait  utility  is invoked with no operands, it shall wait until all process IDs known to the invoking shell have terminated and
    exit with a zero exit status.

    If one or more pid operands are specified that represent known process IDs, the wait utility shall wait until all of  them  have  termi‐
    nated. If one or more pid operands are specified that represent unknown process IDs, wait shall treat them as if they were known process
    IDs that exited with exit status 127. The exit status returned by the wait utility shall be the exit status of the process requested  by
    the last pid operand.

    The known process IDs are applicable only for invocations of wait in the current shell execution environment.

    wait(): on success, returns the process ID of the terminated child; on error, -1 is returned.
    - waitpid;

    The waitpid() system call suspends execution of the calling thread until a child specified by pid argument has changed  state.   By  de‐
    fault, waitpid() waits only for terminated children, but this behavior is modifiable via the options argument, as described below.

    The value of pid can be:

    < -1   meaning wait for any child process whose process group ID is equal to the absolute value of pid.

    -1     meaning wait for any child process.

    0      meaning  wait  for  any  child  process whose process group ID is equal to that of the calling process at the time of the call to
    waitpid().

    > 0    meaning wait for the child whose process ID is equal to the value of pid.

    The value of options is an OR of zero or more of the following constants:

    waitpid():  on success, returns the process ID of the child whose state has changed; if WNOHANG was specified and one or more child(ren)
    specified by pid exist, but have not yet changed state, then 0 is returned.  On error, -1 is returned.
