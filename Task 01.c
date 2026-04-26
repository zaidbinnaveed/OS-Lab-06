/* Task 1: Modified FIFO Program
   Modifications:
   1. Parent sends hardcoded "Hello Child" (no user input)
   2. Child prints the message TWO times
   3. Buffer size changed from 100 to 50
   4. Child prints total number of characters in the message
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_NAME "/tmp/myfifo"

int main() {
    int pid;
    int fd;
    char message[50] = "Hello Child";   /* Mod 3: buffer size changed to 50 */
                                        /* Mod 1: hardcoded message, no user input */
    mkfifo(FIFO_NAME, 0666);

    pid = fork();
    if (pid < 0) {
        printf("Fork Failed\n");
        return 1;
    }
    else if (pid == 0) {
        /* Child process */
        fd = open(FIFO_NAME, O_RDONLY);
        read(fd, message, sizeof(message));

        /* Mod 2: Print the message two times */
        printf("Child received: %s\n", message);
        printf("Child received: %s\n", message);

        /* Mod 4: Print total number of characters */
        printf("Total characters in message: %lu\n", strlen(message));

        close(fd);
    }
    else {
        /* Parent process */
        fd = open(FIFO_NAME, O_WRONLY);
        write(fd, message, strlen(message) + 1);
        close(fd);
        printf("Parent sent: %s\n", message);
    }
    return 0;
}
