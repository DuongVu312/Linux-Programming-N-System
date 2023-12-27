Directory structure:

- File Info: get file's information using struct stat.
- Open rw : basic linux system call open/write/lseek with O_APPEND open mode.

In each folder, perform below instructions:

- make: build excutable file.
- make clean: clean excutable file.

Summary:
- The O_APPEND open mode will make the file offset to be positioned at the end of the file.
- If we declare open mode just only O_APPEND the system call write() will return -1,
