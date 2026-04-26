/* Task 4: Named Pipe - Receiver
   Receives messages from FIFO until "exit" is received.
   Compile: gcc task4_receiver.c -o receiver
   Run sender and receiver in two separate terminals.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_FILE "/tmp/myfifo4"
#define BUFFER_SIZE 256

int main() {
    int fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    fd = open(FIFO_FILE, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("Receiver ready. Waiting for messages...\n");

    while (1) {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0)
            break;

        printf("Receiver: %s\n", buffer);

        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Receiver: exit signal received. Closing.\n");
            break;
        }
    }

    close(fd);
    return 0;
}
