#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int fds[2];
    if (pipe(fds) != 0) {
        fprintf(stderr, "pipe failed: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    pid_t child = fork();
    if (child < 0) {
        fprintf(stderr, "fork failed: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    if (child == 0) {
        close(fds[0]);
        const char message[] = "child-to-parent";
        const ssize_t written = write(fds[1], message, sizeof(message));
        close(fds[1]);
        _exit(written == (ssize_t)sizeof(message) ? EXIT_SUCCESS : EXIT_FAILURE);
    }

    close(fds[1]);
    char buffer[64] = {0};
    const ssize_t n = read(fds[0], buffer, sizeof(buffer));
    close(fds[0]);

    int status = 0;
    waitpid(child, &status, 0);

    printf("received=%s bytes=%zd\n", buffer, n);
    return WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS &&
                   strcmp(buffer, "child-to-parent") == 0
               ? EXIT_SUCCESS
               : EXIT_FAILURE;
}
