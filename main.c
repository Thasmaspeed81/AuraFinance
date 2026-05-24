/*
 * =============================================
 *   main.c  —  ADVAIT SCFU125062
 *   Entry point, Menu, Global variables
 * =============================================
 *
 * RESPONSIBILITIES:
 *   - Define global variables (expenses array)
 *   - Start the program (main function)
 *   - Show the menu and handle user choice
 *   - Call functions from other files
 *
 * CONCEPTS USED:
 *   - main() function
 *   - Global variables
 *   - while loop
 *   - switch-case
 *   - Calling functions
 */

#include <stdio.h>
#include "expense.h"   /* Include shared header */

/*
 * Global variables — defined HERE in main.c
 * Other files access these via "extern" in expense.h
 */
struct Expense expenses[MAX_EXPENSES];
int totalExpenses = 0;

/* ════════════════════════════════════════
   MAIN FUNCTION
   ════════════════════════════════════════ */
int main() {
    int choice;

    /* Load saved expenses when program starts */
    loadFromFile();   /* Written by Student 4 */

    printf("\n  *** Welcome to Group Expense Tracker! ***\n");

    /* Keep showing menu until user exits */
    while (1) {
        printMenu();
        printf("  Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addExpense();        /* Student 2 */
                break;
            case 2:
                viewAllExpenses();   /* Student 2 */
                break;
            case 3:
                deleteExpense();     /* Student 2 */
                break;
            case 4:
                searchByCategory();  /* Student 3 */
                break;
            case 5:
                showSummary();       /* Student 3 */
                break;
            case 6:
                saveToFile();        /* Student 4 */
                printf("\n  Data saved. Goodbye!\n\n");
                return 0;
            default:
                printf("\n  Invalid choice! Please enter 1 to 6.\n");
        }
    }
}

/* ════════════════════════════════════════
   PRINT MENU
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
   HELPER — Print a divider line
   ════════════════════════════════════════ */
void printLine() {
    printf("  ------------------------------------------------\n");
}
