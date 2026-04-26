/* Task 3: Named Pipe - Consumer
   Reads an integer from FIFO /tmp/myfifo and checks even/odd.
   Compile: gcc task3_consumer.c -o consumer
   Run producer first, then this consumer in a separate terminal.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_FILE "/tmp/myfifo"

int main() {
    int fd;
    int number;

    fd = open(FIFO_FILE, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    read(fd, &number, sizeof(int));
    close(fd);

    if (number % 2 == 0)
        printf("%d is an Even number\n", number);
    else
        printf("%d is an Odd number\n", number);

    return 0;
}
