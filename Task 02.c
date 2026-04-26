/* Task 2: Ordinary Pipe - Word Counter
   - Parent asks user for a sentence (max 100 chars)
   - Parent sends sentence to child via pipe
   - Child counts words and prints the total
*/

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 100
#define READ_END  0
#define WRITE_END 1

int count_words(char *str) {
    int count = 0;
    int in_word = 0;
    while (*str) {
        if (*str == ' ' || *str == '\n' || *str == '\t') {
            in_word = 0;
        } else {
            if (!in_word) {
                count++;
                in_word = 1;
            }
        }
        str++;
    }
    return count;
}

int main(void) {
    char sentence[BUFFER_SIZE];
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed\n");
        return 1;
    }

    /* Parent reads sentence before forking */
    printf("Enter a sentence (max 100 characters): ");
    fgets(sentence, BUFFER_SIZE, stdin);

    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }

    if (pid > 0) {
        /* Parent: write sentence to pipe */
        close(fd[READ_END]);
        write(fd[WRITE_END], sentence, strlen(sentence) + 1);
        close(fd[WRITE_END]);
    }
    else {
        /* Child: read sentence and count words */
        char buffer[BUFFER_SIZE];
        close(fd[WRITE_END]);
        read(fd[READ_END], buffer, BUFFER_SIZE);
        close(fd[READ_END]);

        int words = count_words(buffer);
        printf("Total words: %d\n", words);
    }

    return 0;
}
