/*
 * =============================================
 *   search_summary.c  —  Mukta SCFU125057
 *   Search by Category and Show Summary
 * =============================================
 *
 * RESPONSIBILITIES:
 *   - searchByCategory() : Filter expenses by category name
 *   - showSummary()      : Display totals and category breakdown
 *
 * CONCEPTS USED:
 *   - for loops
 *   - if-else
 *   - String comparison (strcasecmp)
 *   - float arithmetic
 *   - Arrays of strings (category names)
 *   - Formatted printf output
 */

#include <stdio.h>
#include <string.h>
#include "expense.h"   /* Include shared header */

/* ════════════════════════════════════════
   SEARCH BY CATEGORY
   ════════════════════════════════════════ */
void searchByCategory() {

    if (totalExpenses == 0) {
        printf("\n  No expenses recorded yet!\n");
        return;
    }

    char searchCat[20];
    int  i;
    int  found    = 0;
    float catTotal = 0.0;

    getchar();   /* Clear leftover newline from input buffer */

    printf("\n--- Search by Category ---\n");
    printf("  Available: Food | Travel | Shopping | Bills | Other\n");
    printf("  Enter category: ");
    fgets(searchCat, sizeof(searchCat), stdin);
    searchCat[strcspn(searchCat, "\n")] = '\0';  /* Remove trailing newline */

    printf("\n  Results for category: \"%s\"\n", searchCat);
    printLine();

    for (i = 0; i < totalExpenses; i++) {
        /*
         * strcasecmp compares two strings ignoring case.
         * So "food", "Food", "FOOD" all match.
         * Returns 0 if they are equal (just like strcmp).
         *
         * NOTE: On Windows (MinGW), use _stricmp() instead.
         */
        if (strcasecmp(expenses[i].category, searchCat) == 0) {
            printf("  [%d] %-25s  Rs.%8.2f   %s\n",
                   expenses[i].id,
                   expenses[i].description,
                   expenses[i].amount,
                   expenses[i].date);
            catTotal += expenses[i].amount;
            found++;
        }
    }

    printLine();

    if (found == 0) {
        printf("  No expenses found under \"%s\".\n", searchCat);
    } else {
        printf("  %d record(s) found  |  Category Total: Rs.%.2f\n",
               found, catTotal);
    }
}

/* ════════════════════════════════════════
   SHOW SUMMARY
   ════════════════════════════════════════ */
void showSummary() {

    if (totalExpenses == 0) {
        printf("\n  No expenses to summarize!\n");
        return;
    }

    int   i, c;
    float grandTotal   = 0.0;
    float highest      = expenses[0].amount;
    int   highestIndex = 0;

    /*
     * We track 5 standard categories.
     * catTotals[0] = Food total
     * catTotals[1] = Travel total  ... and so on
     */
    char  *cats[]     = {"Food", "Travel", "Shopping", "Bills", "Other"};
    float  catTotals[] = {0.0, 0.0, 0.0, 0.0, 0.0};
    int    numCats     = 5;

    /* Single loop: compute grand total, highest, and category totals */
    for (i = 0; i < totalExpenses; i++) {

        grandTotal += expenses[i].amount;

        /* Check if this is the highest expense so far */
        if (expenses[i].amount > highest) {
            highest      = expenses[i].amount;
            highestIndex = i;
        }

        /* Add amount to the matching category bucket */
        for (c = 0; c < numCats; c++) {
            if (strcasecmp(expenses[i].category, cats[c]) == 0) {
                catTotals[c] += expenses[i].amount;
                break;   /* No need to check further categories */
            }
        }
    }

    /* ── Print the summary ── */
    printf("\n");
    printLine();
    printf("         EXPENSE SUMMARY\n");
    printLine();
    printf("  Total Records   : %d\n",         totalExpenses);
    printf("  Grand Total     : Rs. %.2f\n",   grandTotal);
    printf("  Average/Expense : Rs. %.2f\n",   grandTotal / totalExpenses);
    printf("  Highest Expense : Rs. %.2f  (%s)\n",
           highest, expenses[highestIndex].description);
    printLine();
    printf("  Category-wise Breakdown:\n\n");

    for (c = 0; c < numCats; c++) {
        if (catTotals[c] > 0) {
            /*
             * Show a simple text bar proportional to spending.
             * Each '#' = roughly Rs.50
             */
            int bars = (int)(catTotals[c] / 50);
            if (bars > 30) bars = 30;   /* Cap bar length */

            printf("  %-10s : Rs.%8.2f  |", cats[c], catTotals[c]);

            int b;
            for (b = 0; b < bars; b++) printf("#");
            printf("\n");
        }
    }

    printLine();
}
