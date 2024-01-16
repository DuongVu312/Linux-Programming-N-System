#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>
  
int main (int argc, char *argv[]) 
{
    struct stat sb;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (lstat(argv[1], &sb) == -1)
    {
        perror("lstat");
        exit(EXIT_FAILURE);
    }

    printf("File type:                ");
    switch (sb.st_mode & S_IFMT)
    {
    case S_IFBLK:  printf("block device\n");            break;
    case S_IFCHR:  printf("character device\n");        break;
    case S_IFDIR:  printf("directory\n");               break;
    case S_IFIFO:  printf("FIFO/pipe\n");               break;
    case S_IFLNK:  printf("symlink\n");                 break;
    case S_IFREG:  printf("regular file\n");            break;
    case S_IFSOCK: printf("socket\n");                  break;
    default:       printf("unknown?\n");                break;
    }

    printf("\nI-node number: %ju, sizeof(uintmax_t): %jd\n\n", (uintmax_t)sb.st_ino, sizeof(uintmax_t));
    printf("File size: %jd bytes\n\n", (intmax_t)sb.st_size);

    printf("Last status change:     %s\n", ctime(&sb.st_ctim.tv_sec));
    printf("Last file access:       %s\n", ctime(&sb.st_atim.tv_sec));
    printf("Last file modification: %s\n", ctime(&sb.st_mtim.tv_sec));

    return 0;
}