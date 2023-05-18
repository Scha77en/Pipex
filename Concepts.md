# System Calls

## **wait() and waitpid() functions**

Both `wait()` and `waitpid()` are system calls in C used to wait for child processes to finish execution. The key difference between them lies in the flexibility and control they provide.

## **wait()**

`wait()`: This system call suspends the execution of the calling process until any of its child processes terminate. It has the following syntax:

```c
    pid_t wait(int *status);
```

- - `status`: A pointer to an integer variable where the termination status of the child process will be stored.

With `wait()`, you don't have direct control over which child process to wait for. It waits for any child process to terminate and returns the process ID (PID) of the terminated child. If you're not interested in the termination status, you can pass `NULL` as the `status` argument.

## **waitpid()**

`waitpid()`: This system call allows you to specify which child process to wait for and provides more control over the waiting behavior. Its syntax is as follows:

```c
pid_t waitpid(pid_t pid, int *status, int options);
```

`pid`: The process ID of the child process to wait for. There are several options:

- `> 0` : Wait for the child process with the specified PID.
- `-1:` Wait for any child process.
- `0`: Wait for any child process in the same process group as the calling process.
- `< -1:` Wait for any child process whose process group ID is equal to the absolute value of `pid`.

`status`: A pointer to an integer variable where the termination status of the child process will be stored.

`options`: Additional options to control the behavior. The most commonly used option is `WNOHANG`, which makes `waitpid()` return immediately if no child process has terminated.

&nbsp; &nbsp; `waitpid()` provides more flexibility than `wait()` as you can specify which child process to wait for and handle multiple child processes simultaneously.

In summary, `wait()` waits for any child process to terminate, while `waitpid()` allows you to specify which child process to wait for and provides more control over waiting behavior.

## **unlink() function**

The `unlink()` function in C is used to delete a file from the file system. When you invoke `unlink()` on a file, it removes the directory entry associated with that file. The file itself is not immediately removed from the disk, but its link count is decremented. The file is only truly deleted from the disk when its link count reaches zero, indicating that no directory entries or file links are referencing it.

Here's how `unlink()` works in more detail:

- When you call `unlink()` with the path to a file, it checks if the file exists and if you have sufficient permissions to delete it.

- If the file exists and you have the necessary permissions, `unlink()` removes the directory entry associated with the file. This means that the file's name is no longer accessible from the file system's directory structure.

- The link count of the file is decremented. The link count represents the number of directory entries or file links pointing to the same underlying file data. If the link count reaches zero, indicating that no more directory entries or links reference the file, the file is considered deleted.

- The actual data blocks of the file on the disk are not immediately erased. They are marked as available for reuse by the file system.

- Any open file descriptors pointing to the deleted file remain valid and can still be used to access the file data. However, once the file is closed, the file data becomes inaccessible.

- The file is permanently removed from the disk when the file system's garbage collection mechanism reclaims the disk space occupied by the file's data blocks. This happens automatically by the file system, typically when the system needs space to store new files.

It's important to note that `unlink()` only removes the directory entry and decreases the link count of the file. It doesn't provide a way to recover the file once it is deleted. Therefore, caution should be exercised when using `unlink()` as it irreversibly deletes the file from the file system.

## **pipe() function**

The `pipe()` function in C is used to create a pipe, which is a unidirectional communication channel between two related processes. It provides a mechanism for interprocess communication (IPC) by connecting the standard output (stdout) of one process to the standard input (stdin) of another process.

Here's how `pipe()` works in more detail:

- When you call `pipe()`, it creates a pipe and returns two file descriptors: `pipefd[0]` and `pipefd[1]`. `pipefd[0]` refers to the read end of the pipe, and `pipefd[1]` refers to the write end of the pipe.

- The read end (`pipefd[0]`) is typically used by the process that wants to read data from the pipe. It receives the data written by the other process.

- The write end (`pipefd[1]`) is typically used by the process that wants to write data to the pipe. The data written to the write end can be read by the other process from the read end.

- The pipe operates on a first-in, first-out (FIFO) basis. Data written to the pipe is read in the order it was written.

- The pipe has a limited capacity, known as the pipe buffer. If the pipe buffer is full and a process tries to write more data, the write operation will block until there is space available in the buffer. Similarly, if the pipe buffer is empty and a process tries to read data, the read operation will block until data is available.

- Once data is read from the pipe, it is removed from the pipe, and subsequent reads will not retrieve that data again. Similarly, once data is written to the pipe, it is consumed by the reader, and subsequent writes will overwrite the previous data.

- Both ends of the pipe should be closed in the processes that no longer need them. Closing the pipe ends ensures that the processes receive an end-of-file (EOF) signal when they attempt to read from an empty pipe or write to a closed pipe, indicating that there is no more data to read or the data written won't be received.

- the `pipe()` function in C creates a unidirectional pipe with exactly two file descriptors: one for the read end and one for the write end. It establishes communication between two related processes.

The `pipe()` function provides a simple and efficient way to establish communication between related processes. It is often used in scenarios where the output of one process needs to be passed as input to another process, allowing them to work together in a coordinated manner.

## **dup( function**)

The `dup()` function, short for "duplicate," is a system call in Unix-like operating systems. It allows a process to duplicate an existing file descriptor, creating a new file descriptor that refers to the same open file or socket.

Here's how `dup()` works in detail:

- The `dup()` system call takes an existing file descriptor `oldfd` as an argument.

- It finds the lowest-numbered unused file descriptor (let's call it `newfd`) in the process's file descriptor table.

- It creates a new entry in the file descriptor table at position `newfd`, which is a duplicate of the file descriptor entry at position `oldfd`. This means both `oldfd` and `newfd` will refer to the same open file or socket.

- If `newfd` was previously open, it is closed implicitly before duplicating `oldfd`.

- The `dup()` system call returns `newfd`, which can be used to read from or write to the same open file or socket as `oldfd`.

In essence, `dup()` allows you to create a new file descriptor that points to the same open file or socket as an existing file descriptor. This can be useful for redirecting input/output or managing multiple references to the same resource.

## **dup2() function**

The `dup2()` function is a system call in Unix-like operating systems that allows a process to duplicate an existing file descriptor to a specific desired file descriptor number. It provides more control over the duplication process compared to the `dup()` function.

Here's how `dup2()` works in detail:

- The `dup2()` system call takes two arguments: `oldfd` and `newfd`.

- If `newfd` is already a valid open file descriptor, it is first closed.

- The `dup2()` system call creates a new entry in the file descriptor table at position `newfd`, which is a duplicate of the file descriptor entry at position `oldfd`. This means both `oldfd` and `newfd` will refer to the same open file or socket.

- The new file descriptor `newfd` has the same properties (e.g., flags, access mode) as the original file descriptor `oldfd`.

- If `oldfd` and `newfd` are the same, `dup2()` has no effect, and it simply returns `newfd` without closing it.

- If an error occurs during the duplication process, `dup2()` returns -1, and an appropriate error code is set.

- In summary, `dup2()` allows you to duplicate an existing file descriptor to a specific desired file descriptor number. This can be useful for redirecting input/output to a specific file descriptor or ensuring a specific file descriptor is associated with a particular resource.

## **dup() and dup2()**

The `dup()` and `dup2()` functions in Unix-like operating systems both serve the purpose of duplicating a file descriptor, but they have some differences in functionality. Here are the key differences between `dup()` and `dup2()`:

**Arguments**:

- `dup()`: Takes a single argument, which is the file descriptor to be duplicated.
- `dup2()`: Takes two arguments: the first is the file descriptor to be duplicated, and the second is the desired file descriptor number for the duplication.

**Control over the new file descriptor number**:

- `dup()`: The operating system automatically assigns the lowest available file descriptor number to the duplicated file descriptor.
- `dup2()`: Allows you to specify the desired file descriptor number for the duplicated file descriptor. If the desired file descriptor is already open, it is first closed before the duplication.

**Error handling**:

- `dup()`: If an error occurs during the duplication process, it returns -1, and an appropriate error code is set.
- `dup2()`: If an error occurs during the duplication process, it returns -1, and an appropriate error code is set. Additionally, if `newfd` is already a valid file descriptor, it is closed before the duplication.

In summary, `dup()` automatically assigns the lowest available file descriptor number to the duplicated file descriptor, while `dup2()` allows you to specify the desired file descriptor number. The choice between `dup()` and `dup2()` depends on the level of control you need over the file descriptor duplication process.