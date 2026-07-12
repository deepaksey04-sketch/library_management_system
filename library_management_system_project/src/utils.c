#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "lms.h"

static void clearInput(void);
static time_t parseDate(const char *dateText);

int readInt(const char *prompt, int minValue) {
    int value;
    int result;

    do {
        printf("%s", prompt);
        result = scanf("%d", &value);
        clearInput();

        if (result == 1 && value >= minValue) {
            return value;
        }

        printf("Invalid input. Enter a number greater than or equal to %d.\n", minValue);
    } while (1);
}

void readLine(const char *prompt, char *buffer, size_t size) {
    do {
        printf("%s", prompt);
        if (fgets(buffer, (int)size, stdin) == NULL) {
            buffer[0] = '\0';
            return;
        }

        buffer[strcspn(buffer, "\n")] = '\0';
        if (strlen(buffer) > 0) {
            return;
        }

        printf("Input cannot be empty.\n");
    } while (1);
}

int containsIgnoreCase(const char *text, const char *pattern) {
    size_t textLen = strlen(text);
    size_t patternLen = strlen(pattern);

    if (patternLen == 0) {
        return 1;
    }

    if (patternLen > textLen) {
        return 0;
    }

    for (size_t i = 0; i <= textLen - patternLen; i++) {
        size_t j = 0;
        while (j < patternLen &&
               tolower((unsigned char)text[i + j]) == tolower((unsigned char)pattern[j])) {
            j++;
        }
        if (j == patternLen) {
            return 1;
        }
    }

    return 0;
}

void todayString(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d", local);
}

void addDaysString(const char *dateText, int days, char *buffer, size_t size) {
    time_t date = parseDate(dateText);
    date += (time_t)days * 24 * 60 * 60;
    strftime(buffer, size, "%Y-%m-%d", localtime(&date));
}

int daysBetween(const char *fromDate, const char *toDate) {
    time_t from = parseDate(fromDate);
    time_t to = parseDate(toDate);
    double seconds = difftime(to, from);
    return (int)(seconds / (24 * 60 * 60));
}

static time_t parseDate(const char *dateText) {
    int year;
    int month;
    int day;
    struct tm date;

    memset(&date, 0, sizeof(date));
    if (sscanf(dateText, "%d-%d-%d", &year, &month, &day) != 3) {
        return time(NULL);
    }

    date.tm_year = year - 1900;
    date.tm_mon = month - 1;
    date.tm_mday = day;
    date.tm_isdst = -1;
    return mktime(&date);
}

static void clearInput(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}
