/*
 * =============================================
 *   expense_tracker.c  —  Combined Single File
 *   Group Expense Tracker
 * =============================================
 *
 * AUTHORS:
 *   - Advait  SCFU125062  (main, menu, helpers)
 *   - Riya    SCFU125059  (add, view, delete)
 *   - Mukta   SCFU125057  (search, summary)
 *   - Aditya  SCFU125061  (save, load)
 *
 * CONCEPTS USED:
 *   - Structs, Arrays, Global variables
 *   - for loops, while loop, switch-case, if-else
 *   - fgets / scanf for input
 *   - String comparison (strcasecmp)
 *   - Float arithmetic, printf formatting
 *   - File handling (fopen, fclose, fprintf, fscanf, fgets)
 *
 * COMPILE:
 *   gcc expense_tracker.c -o expense_tracker
 *
 * RUN:
 *   ./expense_tracker
 * =============================================
 */

#include <stdio.h>
#include <string.h>

/* ════════════════════════════════════════
   CONSTANTS
   ════════════════════════════════════════ */
#define MAX_EXPENSES 100
#define FILE_NAME    "expenses.txt"

/* ════════════════════════════════════════
   STRUCT: One Expense Record
   ════════════════════════════════════════ */
struct Expense {
    int   id;
    char  description[50];
    char  category[20];   /* Food, Travel, Shopping, Bills, Other */
    float amount;
    char  date[15];       /* Format: DD/MM/YYYY */
};

/* ════════════════════════════════════════
   GLOBAL VARIABLES
   ════════════════════════════════════════ */
struct Expense expenses[MAX_EXPENSES];
int totalExpenses = 0;

/* ════════════════════════════════════════
   FUNCTION DECLARATIONS (Prototypes)
   ════════════════════════════════════════ */

/* Helper */
void printMenu();
void printLine();

/* Expense Operations */
void addExpense();
void viewAllExpenses();
void deleteExpense();

/* Search & Summary */
void searchByCategory();
void showSummary();

/* File Handling */
void saveToFile();
void loadFromFile();


/* ════════════════════════════════════════
   MAIN FUNCTION  —  Advait SCFU125062
   ════════════════════════════════════════ */
int main() {
    int choice;

    /* Load saved expenses when program starts */
    loadFromFile();

    printf("\n  *** Welcome to Group Expense Tracker! ***\n");

    /* Keep showing menu until user exits */
    while (1) {
        printMenu();
        printf("  Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addExpense();
                break;
            case 2:
                viewAllExpenses();
                break;
            case 3:
                deleteExpense();
                break;
            case 4:
                searchByCategory();
                break;
            case 5:
                showSummary();
                break;
            case 6:
                saveToFile();
                printf("\n  Data saved. Goodbye!\n\n");
                return 0;
            default:
                printf("\n  Invalid choice! Please enter 1 to 6.\n");
        }
    }
}

/* ════════════════════════════════════════
   PRINT MENU  —  Advait SCFU125062
   ════════════════════════════════════════ */
void printMenu() {
    printLine();
    printf("        EXPENSE TRACKER MENU\n");
    printLine();
    printf("  1. Add Expense\n");
    printf("  2. View All Expenses\n");
    printf("  3. Delete an Expense\n");
    printf("  4. Search by Category\n");
    printf("  5. Show Summary\n");
    printf("  6. Save & Exit\n");
    printLine();
}

/* ════════════════════════════════════════
   HELPER: Print a Divider Line  —  Advait SCFU125062
   ════════════════════════════════════════ */
void printLine() {
    printf("  ------------------------------------------------\n");
}


/* ════════════════════════════════════════
   ADD EXPENSE  —  Riya SCFU125059
   ════════════════════════════════════════ */
void addExpense() {

    /* Check if storage is full */
    if (totalExpenses >= MAX_EXPENSES) {
        printf("\n  Cannot add more. Storage is full! (Max: %d)\n", MAX_EXPENSES);
        return;
    }

    struct Expense e;       /* Temporary expense to fill in */
    e.id = totalExpenses + 1;   /* Auto ID: 1, 2, 3... */

    printf("\n--- Add New Expense ---\n");

    /*
     * getchar() clears the leftover '\n' character
     * in the input buffer from the previous scanf.
     * Without this, fgets() would skip the input.
     */
    getchar();

    printf("  Description (e.g. Lunch at canteen): ");
    fgets(e.description, sizeof(e.description), stdin);
    /* Remove the newline '\n' that fgets captures at the end */
    e.description[strcspn(e.description, "\n")] = '\0';

    printf("  Category (Food/Travel/Shopping/Bills/Other): ");
    fgets(e.category, sizeof(e.category), stdin);
    e.category[strcspn(e.category, "\n")] = '\0';

    printf("  Amount (in Rs.): ");
    scanf("%f", &e.amount);

    /* Basic validation — amount cannot be negative */
    if (e.amount < 0) {
        printf("\n  Invalid amount! Expense not added.\n");
        return;
    }

    getchar();  /* Clear buffer before next fgets */

    printf("  Date (DD/MM/YYYY): ");
    fgets(e.date, sizeof(e.date), stdin);
    e.date[strcspn(e.date, "\n")] = '\0';

    /* Save the filled expense into the global array */
    expenses[totalExpenses] = e;
    totalExpenses++;

    printf("\n  Expense added! (ID: %d)\n", e.id);
}

/* ════════════════════════════════════════
   VIEW ALL EXPENSES  —  Riya SCFU125059
   ════════════════════════════════════════ */
void viewAllExpenses() {

    if (totalExpenses == 0) {
        printf("\n  No expenses recorded yet!\n");
        return;
    }

    int i;

    printf("\n");
    printLine();
    /* %-4s means: left-align in 4 characters wide */
    printf("  %-4s  %-24s  %-12s  %9s  %s\n",
           "ID", "Description", "Category", "Amount", "Date");
    printLine();

    for (i = 0; i < totalExpenses; i++) {
        printf("  %-4d  %-24s  %-12s  %8.2f  %s\n",
               expenses[i].id,
               expenses[i].description,
               expenses[i].category,
               expenses[i].amount,
               expenses[i].date);
    }

    printLine();
    printf("  Total records: %d\n", totalExpenses);
}

/* ════════════════════════════════════════
   DELETE AN EXPENSE  —  Riya SCFU125059
   ════════════════════════════════════════ */
void deleteExpense() {

    if (totalExpenses == 0) {
        printf("\n  No expenses to delete!\n");
        return;
    }

    int id, i;
    int found      = 0;
    int foundIndex = -1;

    viewAllExpenses();   /* Show the list so user knows which ID to pick */

    printf("\n  Enter the ID of the expense to delete: ");
    scanf("%d", &id);

    /* Search for the matching ID */
    for (i = 0; i < totalExpenses; i++) {
        if (expenses[i].id == id) {
            found      = 1;
            foundIndex = i;
            break;
        }
    }

    if (!found) {
        printf("\n  Expense with ID %d not found!\n", id);
        return;
    }

    /* Show what we are about to delete */
    printf("\n  Deleting: \"%s\" — Rs.%.2f\n",
           expenses[foundIndex].description,
           expenses[foundIndex].amount);

    /*
     * Deletion by shifting:
     * Before: [A, B, C, D]   (delete index 1 = B)
     * After:  [A, C, D]
     *
     * We copy each element one step to the left
     * starting from the deleted position.
     */
    for (i = foundIndex; i < totalExpenses - 1; i++) {
        expenses[i]    = expenses[i + 1];
        expenses[i].id = i + 1;   /* Fix the IDs to stay in order */
    }

    totalExpenses--;
    printf("  Expense deleted successfully!\n");
}


/* ════════════════════════════════════════
   SEARCH BY CATEGORY  —  Mukta SCFU125057
   ════════════════════════════════════════ */
void searchByCategory() {

    if (totalExpenses == 0) {
        printf("\n  No expenses recorded yet!\n");
        return;
    }

    char  searchCat[20];
    int   i;
    int   found    = 0;
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
   SHOW SUMMARY  —  Mukta SCFU125057
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
    char  *cats[]      = {"Food", "Travel", "Shopping", "Bills", "Other"};
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
    printf("  Total Records   : %d\n",        totalExpenses);
    printf("  Grand Total     : Rs. %.2f\n",  grandTotal);
    printf("  Average/Expense : Rs. %.2f\n",  grandTotal / totalExpenses);
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


/* ════════════════════════════════════════
   SAVE TO FILE  —  Aditya SCFU125061
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
   LOAD FROM FILE  —  Aditya SCFU125061
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
