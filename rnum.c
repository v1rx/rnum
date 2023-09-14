#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define CREATOR "Sixem LLC"
#define VERSION "0.0.8"

#define ANSI_RESET "\x1B[0m"
#define ANSI_RED "\x1B[31m"
#define ANSI_GREEN "\x1B[32m"
#define ANSI_YELLOW "\x1B[33m"
#define ANSI_BLUE "\x1B[34m"
#define ANSI_MAGENTA "\x1B[35m"
#define ANSI_CYAN "\x1B[36m"
#define ANSI_WHITE "\x1B[37m"

static int seed() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long long milliseconds = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL);
    srand(milliseconds);
    return 0;
}
static void pversion() {
    printf("Random Number %s - %s\n", VERSION, CREATOR);
}

static uint64_t random_uint64(void) {
    uint64_t high = (uint64_t)rand() << 32;
    uint64_t low = rand();
    return high | low;
}
static uint64_t random_uint64_range(uint64_t min, uint64_t max) {
    if(min > max) {
        uint64_t temp = min;
        min = max;
        max = temp;
    }

    uint64_t range = max - min + 1;

    if(range == 0) {
        return random_uint64();
    } else if (range == UINT64_MAX) {
        return UINT64_MAX;
    } else if (range == UINT64_MAX - 1) {
        uint64_t rand_val1 = random_uint64();
        uint64_t rand_val2 = random_uint64();
        return (rand_val1 > rand_val2) ? rand_val1 : rand_val2;
    } else {
        uint64_t limit = UINT64_MAX - (UINT64_MAX % range);
        uint64_t rand_val;

        do { rand_val = random_uint64(); } while (rand_val > limit);
        return min + rand_val % range;
    }
}

void printColorfulDigitArt(int digits[], int count) {
    const char* colors[] = {
        ANSI_RED,
        ANSI_GREEN,
        ANSI_YELLOW,
        ANSI_BLUE,
        ANSI_MAGENTA,
        ANSI_CYAN,
        ANSI_WHITE
    };

    char digitArt[10][40][40] = {
        {
            {" \u2588\u2588\u2588\u2588\u2588 "},
            {"\u2588\u2588   \u2588\u2588"},
            {"\u2588\u2588   \u2588\u2588"},
            {"\u2588\u2588   \u2588\u2588"},
            {" \u2588\u2588\u2588\u2588\u2588 "}
        },
        {
            {" \u2588\u2588"},
            {"\u2588\u2588\u2588"},
            {" \u2588\u2588"},
            {" \u2588\u2588"},
            {" \u2588\u2588"}
        },
        {
            {"\u2588\u2588\u2588\u2588\u2588\u2588 "},
            {"     \u2588\u2588"},
            {" \u2588\u2588\u2588\u2588\u2588 "},
            {"\u2588\u2588     "},
            {"\u2588\u2588\u2588\u2588\u2588\u2588\u2588"}
        },
        {
            {"\u2588\u2588\u2588\u2588\u2588\u2588 "},
            {"     \u2588\u2588"},
            {" \u2588\u2588\u2588\u2588\u2588 "},
            {"     \u2588\u2588"},
            {"\u2588\u2588\u2588\u2588\u2588\u2588 "}
        },
        {
            {"\u2588\u2588   \u2588\u2588"},
            {"\u2588\u2588   \u2588\u2588"},
            {"\u2588\u2588\u2588\u2588\u2588\u2588\u2588"},
            {"     \u2588\u2588"},
            {"     \u2588\u2588"}
        },
        {
            {"\u2588\u2588\u2588\u2588\u2588\u2588\u2588"},
            {"\u2588\u2588     "},
            {"\u2588\u2588\u2588\u2588\u2588\u2588\u2588"},
            {"     \u2588\u2588"},
            {"\u2588\u2588\u2588\u2588\u2588\u2588\u2588"}
        },
        {
            {" \u2588\u2588\u2588\u2588\u2588\u2588 "},
            {"\u2588\u2588      "},
            {"\u2588\u2588\u2588\u2588\u2588\u2588\u2588 "},
            {"\u2588\u2588    \u2588\u2588"},
            {" \u2588\u2588\u2588\u2588\u2588\u2588 "}
        },
        {
            {"\u2588\u2588\u2588\u2588\u2588\u2588\u2588"},
            {"     \u2588\u2588"},
            {"    \u2588\u2588 "},
            {"   \u2588\u2588  "},
            {"   \u2588\u2588  "}
        },
        {
            {" \u2588\u2588\u2588\u2588\u2588 "},
            {"\u2588\u2588   \u2588\u2588"},
            {" \u2588\u2588\u2588\u2588\u2588 "},
            {"\u2588\u2588   \u2588\u2588"},
            {" \u2588\u2588\u2588\u2588\u2588 "}
        },
        {
            {" \u2588\u2588\u2588\u2588\u2588 "},
            {"\u2588\u2588   \u2588\u2588"},
            {" \u2588\u2588\u2588\u2588\u2588\u2588"},
            {"     \u2588\u2588"},
            {" \u2588\u2588\u2588\u2588\u2588 "}
        }
    };

    for(int i = 0; i < 5; i++) {
        for(int d = 20 - count; d < 20; d++) {
            printf("%s", colors[digits[d] % 7]);
            printf("%s ", digitArt[digits[d]][i]);
        }
        putchar('\n');
    }

    printf(ANSI_RESET);
}

void iterate_digits(uint64_t num) {
    int digits[20];
    int count = 0;

    if(num == 0) {
        digits[count++] = 0;
    } else {
        int idx = 19;
        while (num > 0) {
            digits[idx] = num % 10;
            num /= 10;
            idx--;
            count++;
        }
    }

    printColorfulDigitArt(digits, count);
}
int main(int argc, char *argv[]) {
    if (argc == 2 && (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0)) {
        pversion();
        return 0;
    } else if (argc < 3) {
        fprintf(stderr, "Usage: %s <min> <max>\n", argv[0]);
        return 1;
    }

    uint64_t min = strtoull(argv[1], NULL, 10);
    uint64_t max = strtoull(argv[2], NULL, 10);
    int use_ascii = 0;
    if (argc >= 4 && strcmp(argv[3], "--ansi") == 0) {
        use_ascii = 1;
    }

    seed();
    uint64_t value = random_uint64_range(min, max);

    time_t current_time;
    struct tm *time_info;
    char time_string[30];
    time(&current_time);
    time_info = localtime(&current_time);

    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S %Z", time_info);
    printf("Random Number: %llu\n", value);
    printf("Between: %llu and %llu\n", min, max);
    printf("Generated: %s\n", time_string);

    if(use_ascii) {
        printf("ANSI Art:\n");
        iterate_digits(value);
    }

    return 0;
}
