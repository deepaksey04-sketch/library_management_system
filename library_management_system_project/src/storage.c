#include <stdio.h>

#include "lms.h"

Book books[MAX_BOOKS];
IssueRecord issues[MAX_ISSUES];
int bookCount = 0;
int issueCount = 0;
int nextBookId = 1;
int nextIssueId = 1;

void loadData(void) {
    FILE *file = fopen(BOOKS_FILE, "rb");
    if (file != NULL) {
        fread(&bookCount, sizeof(bookCount), 1, file);
        if (bookCount < 0 || bookCount > MAX_BOOKS) {
            bookCount = 0;
        } else {
            fread(books, sizeof(Book), (size_t)bookCount, file);
        }
        fclose(file);
    }

    file = fopen(ISSUES_FILE, "rb");
    if (file != NULL) {
        fread(&issueCount, sizeof(issueCount), 1, file);
        if (issueCount < 0 || issueCount > MAX_ISSUES) {
            issueCount = 0;
        } else {
            fread(issues, sizeof(IssueRecord), (size_t)issueCount, file);
        }
        fclose(file);
    }

    recomputeNextIds();
}

void saveData(void) {
    FILE *file = fopen(BOOKS_FILE, "wb");
    if (file == NULL) {
        printf("Error: could not save books file.\n");
        return;
    }
    fwrite(&bookCount, sizeof(bookCount), 1, file);
    fwrite(books, sizeof(Book), (size_t)bookCount, file);
    fclose(file);

    file = fopen(ISSUES_FILE, "wb");
    if (file == NULL) {
        printf("Error: could not save issued books file.\n");
        return;
    }
    fwrite(&issueCount, sizeof(issueCount), 1, file);
    fwrite(issues, sizeof(IssueRecord), (size_t)issueCount, file);
    fclose(file);
}

void recomputeNextIds(void) {
    nextBookId = 1;
    nextIssueId = 1;

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id >= nextBookId) {
            nextBookId = books[i].id + 1;
        }
    }

    for (int i = 0; i < issueCount; i++) {
        if (issues[i].issueId >= nextIssueId) {
            nextIssueId = issues[i].issueId + 1;
        }
    }
}
