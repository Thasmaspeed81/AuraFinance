/*
 * =============================================
 *   expense_operations.c  —  Riya SCFU125059
 *   Add, View, and Delete Expenses
 * =============================================
 *
 * RESPONSIBILITIES:
 *   - addExpense()      : Take input and store a new expense
 *   - viewAllExpenses() : Print all stored expenses as a table
 *   - deleteExpense()   : Remove an expense by its ID
 *
 * CONCEPTS USED:
 *   - structs
 *   - arrays
 *   - for loop
 *   - if-else
 *   - fgets / scanf for input
 *   - printf formatting
 */

#include <stdio.h>
#include <string.h>
#include "expense.h"   /* Include shared header */

/* ════════════════════════════════════════
   ADD EXPENSE
   ════════════════════════════════════════ */
void addExpense() {

    /* Check if storage is full */
    if (totalExpenses >= MAX_EXPENSES) {
        printf("\n  Cannot add more. Storage is full! (Max: %d)\n", MAX_EXPENSES);
        return;
    }

    struct Expense e;   /* Temporary expense to fill in */
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
   VIEW ALL EXPENSES
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
   DELETE AN EXPENSE
   ════════════════════════════════════════ */
void deleteExpense() {

    if (totalExpenses == 0) {
        printf("\n  No expenses to delete!\n");
        return;
    }

    int id, i;
    int found = 0;
    int foundIndex = -1;

    viewAllExpenses();   /* Show the list so user knows which ID to pick */

    printf("\n  Enter the ID of the expense to delete: ");
    scanf("%d", &id);

    /* Search for the matching ID */
    for (i = 0; i < totalExpenses; i++) {
        if (expenses[i].id == id) {
            found = 1;
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
        expenses[i] = expenses[i + 1];
        expenses[i].id = i + 1;   /* Fix the IDs to stay in order */
    }

    totalExpenses--;
    printf("  Expense deleted successfully!\n");
}
