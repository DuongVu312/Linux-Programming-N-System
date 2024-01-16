Directory structure:

- PID n PPID    : Create program A to create process B and print their PID.
- wait-waitpid  : Use system call waitpid() to get the ending status of a child process.
- safe-fork     : Use signal SIGCHLD to prevent zombie process.

In each folder, perform the following instructions bellow:

- make: build excutable file.
- make clean: clean everything.