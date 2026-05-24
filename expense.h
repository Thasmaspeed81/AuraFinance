/*
 * =============================================
 *   expense.h  —  Shared Header File
 *   ALL students must include this file
 * =============================================
 *
 * This file contains:
 *   1. Constants (MAX_EXPENSES, FILE_NAME)
 *   2. The Expense struct (shared data type)
 *   3. Declarations of all functions
 *
 * Think of this as the "table of contents"
 * that connects all 4 files together.
 *
 * "#ifndef" guard prevents the file from
 * being included more than once accidentally.
 */

#ifndef EXPENSE_H
#define EXPENSE_H

/* ── Constants ── */
#define MAX_EXPENSES 100
#define FILE_NAME    "expenses.txt"

/* ── Struct: one expense record ── */
struct Expense {
    int   id;
    char  description[50];
    char  category[20];   /* Food, Travel, Shopping, Bills, Other */
    float amount;
    char  date[15];       /* Format: DD/MM/YYYY */
};

/*
 * ── Global array and counter ──
 * "extern" means: these variables are DEFINED
 * in main.c but are shared with all other files.
 */
extern struct Expense expenses[MAX_EXPENSES];
extern int totalExpenses;

/* ── Function declarations ──
 *
 * Student 1  (main.c)
 */
void printMenu();
void printLine();

/*
 * Student 2  (expense_operations.c)
 */
void addExpense();
void deleteExpense();
void viewAllExpenses();

/*
 * Student 3  (search_summary.c)
 */
void searchByCategory();
void showSummary();

/*
 * Student 4  (file_handler.c)
 */
void saveToFile();
void loadFromFile();

#endif /* EXPENSE_H */
