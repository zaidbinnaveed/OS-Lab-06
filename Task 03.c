/* Task 3: Named Pipe - Producer
   Asks user for an integer and writes it to FIFO /tmp/myfifo
   Compile: gcc task3_producer.c -o producer
   Run producer first, then consumer in a separate terminal.
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

    mkfifo(FIFO_FILE, 0666);

    printf("Enter number: ");
    scanf("%d", &number);

    fd = open(FIFO_FILE, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    write(fd, &number, sizeof(int));
    close(fd);

    printf("Producer: sent %d to FIFO.\n", number);
    return 0;
}
