/* Task 4: Named Pipe - Sender
   Sends multiple messages through FIFO until user types "exit".
   Compile: gcc task4_sender.c -o sender
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

    mkfifo(FIFO_FILE, 0666);

    fd = open(FIFO_FILE, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("Sender ready. Type messages (type 'exit' to quit):\n");

    while (1) {
        printf("Sender: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        /* Remove trailing newline */
        buffer[strcspn(buffer, "\n")] = '\0';

        /* Send message including null terminator */
        write(fd, buffer, strlen(buffer) + 1);

        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Sender: exiting.\n");
            break;
        }
    }

    close(fd);
    unlink(FIFO_FILE);
    return 0;
}
