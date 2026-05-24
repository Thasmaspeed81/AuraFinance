/*
 * =============================================
 *   file_handler.c  —  Aditya SCFU125061 
 *   Save and Load Expenses from a File
 * =============================================
 *
 * RESPONSIBILITIES:
 *   - saveToFile()   : Write all expenses to expenses.txt
 *   - loadFromFile() : Read expenses from expenses.txt on startup
 *
 * CONCEPTS USED:
 *   - File handling (fopen, fclose, fprintf, fscanf, fgets)
 *   - File modes: "r" for read, "w" for write
 *   - NULL check for file open errors
 *   - for loop to read/write multiple records
 *
 * WHY FILE HANDLING?
 *   Without saving to a file, all expenses disappear
 *   when the program closes. Files give us persistence —
 *   data stays even after the program exits.
 */

#include <stdio.h>
#include <string.h>
#include "expense.h"   /* Include shared header */

/* ════════════════════════════════════════
   SAVE TO FILE
   ════════════════════════════════════════ */
void saveToFile() {
    int i;

    /*
     * fopen(filename, mode)
     * "w" = write mode: creates the file if it doesn't exist,
     *       or OVERWRITES it if it does.
     * Returns NULL if the file could not be opened.
     */
    FILE *fp = fopen(FILE_NAME, "w");

    if (fp == NULL) {
        printf("\n  ERROR: Could not open file '%s' for saving!\n", FILE_NAME);
        printf("  Make sure the program has write permissions.\n");
        return;
    }

    /*
     * File format:
     * Line 1     → total number of expenses (e.g. 3)
     * Then for each expense, 5 lines:
     *   id
     *   description
     *   category
     *   amount
     *   date
     */
    fprintf(fp, "%d\n", totalExpenses);

    for (i = 0; i < totalExpenses; i++) {
        fprintf(fp, "%d\n",   expenses[i].id);
        fprintf(fp, "%s\n",   expenses[i].description);
        fprintf(fp, "%s\n",   expenses[i].category);
        fprintf(fp, "%.2f\n", expenses[i].amount);
        fprintf(fp, "%s\n",   expenses[i].date);
    }

    /*
     * ALWAYS close the file after you're done!
     * Not closing can cause data loss or corruption.
     */
    fclose(fp);

    printf("\n  All expenses saved to '%s'.\n", FILE_NAME);
}

/* ════════════════════════════════════════
   LOAD FROM FILE
   ════════════════════════════════════════ */
void loadFromFile() {

    /*
     * "r" = read mode
     * If the file doesn't exist (first time running),
     * fopen returns NULL — that's okay, we just skip loading.
     */
    FILE *fp = fopen(FILE_NAME, "r");

    if (fp == NULL) {
        /* File not found — first run, nothing to load */
        return;
    }

    int i;

    /* Read how many expenses were saved */
    fscanf(fp, "%d\n", &totalExpenses);

    /*
     * Safety check: if the saved count is invalid,
     * reset and stop loading to avoid crashes.
     */
    if (totalExpenses < 0 || totalExpenses > MAX_EXPENSES) {
        printf("\n  Warning: Corrupted save file. Starting fresh.\n");
        totalExpenses = 0;
        fclose(fp);
        return;
    }

    /* Read each expense record from the file */
    for (i = 0; i < totalExpenses; i++) {
        fscanf(fp, "%d\n", &expenses[i].id);

        fgets(expenses[i].description, sizeof(expenses[i].description), fp);
        expenses[i].description[strcspn(expenses[i].description, "\n")] = '\0';

        fgets(expenses[i].category, sizeof(expenses[i].category), fp);
        expenses[i].category[strcspn(expenses[i].category, "\n")] = '\0';

        fscanf(fp, "%f\n", &expenses[i].amount);

        fgets(expenses[i].date, sizeof(expenses[i].date), fp);
        expenses[i].date[strcspn(expenses[i].date, "\n")] = '\0';
    }

    fclose(fp);

    printf("  Loaded %d expense(s) from previous session.\n", totalExpenses);
}
