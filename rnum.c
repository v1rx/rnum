#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define BOLD_GREEN_TEXT "\e[1;32m"
#define RESET_COLOR "\e[0m"

int main(int argc, char *argv[]) {
    int minRange, maxRange;

    if (argc == 3) {
        minRange = atoi(argv[1]);
        maxRange = atoi(argv[2]);

        if (minRange >= maxRange) {
            printf("Invalid input. Minimum range should be less than maximum range.\n");
            return 1;
        }
    } else if (argc == 1) {
        minRange = 0;
        maxRange = 100;
    } else {
        printf("Usage: %s [min_range max_range]\n", argv[0]);
        return 1;
    }

    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);

    srand(currentTime.tv_sec * 1000 + currentTime.tv_usec / 1000);

    int randomNumber = rand() % (maxRange - minRange + 1) + minRange;

    printf("Random Number between %d and %d: %s%d%s\n", minRange, maxRange, BOLD_GREEN_TEXT, randomNumber, RESET_COLOR);

    return 0;
}
