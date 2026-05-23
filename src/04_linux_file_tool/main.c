#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "open failed: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    struct stat info;
    if (fstat(fd, &info) != 0) {
        fprintf(stderr, "fstat failed: %s\n", strerror(errno));
        close(fd);
        return EXIT_FAILURE;
    }

    char buffer[128];
    const ssize_t bytes = read(fd, buffer, sizeof(buffer));
    close(fd);

    if (bytes < 0) {
        fprintf(stderr, "read failed: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    printf("size=%lld first_read=%zd\n", (long long)info.st_size, bytes);
    return bytes > 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
