# 💰 Expense Tracker — C Language Project

> A beginner-friendly console-based Expense Tracker built in C as a collaborative group project.

---

## 👥 Group Members & Contributions

| Member | File | Responsibility |
|--------|------|----------------|
| Advait SCFU125062 | `main.c` | Program entry point, menu system, global variables |
| Riya SCFU125059 | `expense_operations.c` | Add, View, and Delete expenses |
| Mukta SCFU125057 | `search_summary.c` | Search by category and summary report |
| Aditya SCFU125061 | `file_handler.c` | Save and Load data from file |
| All Members | `expense.h` | Shared header file (struct + declarations) |

---

## 📁 Project Structure

```
expense-tracker/
│
├── expense.h                 ← Shared header (ALL members include this)
├── main.c                    ← Advait : Entry point & menu
├── expense_operations.c      ← Riya : Add / View / Delete
├── search_summary.c          ← Mukta : Search & Summary
├── file_handler.c            ← Aditya : Save & Load from file
│
└── expenses.txt              ← Auto-generated when you save (do not edit manually)
```

---

## ✨ Features

| # | Feature | Description |
|---|---------|-------------|
| 1 | **Add Expense** | Enter description, category, amount, and date |
| 2 | **View All Expenses** | Display all expenses in a formatted table |
| 3 | **Delete Expense** | Remove any expense by its ID |
| 4 | **Search by Category** | Filter expenses (Food / Travel / Shopping / Bills / Other) |
| 5 | **Summary Report** | Grand total, average, highest expense, category-wise bar chart |
| 6 | **Save & Load** | Data is saved to `expenses.txt` and loaded on next run |

---

## 🛠️ How to Compile and Run

### On Linux / Mac (Terminal)
```bash
# Step 1 — Compile all files together
gcc main.c expense_operations.c search_summary.c file_handler.c -o expense_tracker

# Step 2 — Run the program
./expense_tracker
```

### On Windows (Command Prompt with MinGW)
```bash
# Step 1 — Compile
gcc main.c expense_operations.c search_summary.c file_handler.c -o expense_tracker.exe

# Step 2 — Run
expense_tracker.exe
```

> ⚠️ **Windows Note:** If you get an error about `strcasecmp`, replace it with `_stricmp` in `expense_operations.c` and `search_summary.c`.

---

## 📸 Sample Output

```
  *** Welcome to Group Expense Tracker! ***
  ------------------------------------------------
        EXPENSE TRACKER MENU
  ------------------------------------------------
  1. Add Expense
  2. View All Expenses
  3. Delete an Expense
  4. Search by Category
  5. Show Summary
  6. Save & Exit
  ------------------------------------------------

  ID    Description               Category         Amount  Date
  ------------------------------------------------
  1     Lunch at canteen          Food            120.00  24/05/2026
  2     Auto rickshaw             Travel           45.00  24/05/2026
  3     Electricity bill          Bills           950.00  20/05/2026

         EXPENSE SUMMARY
  ------------------------------------------------
  Total Records   : 3
  Grand Total     : Rs. 1115.00
  Average/Expense : Rs. 371.67
  Highest Expense : Rs. 950.00  (Electricity bill)

  Category-wise Breakdown:
  Food       : Rs.  120.00  |##
  Travel     : Rs.   45.00  |
  Bills      : Rs.  950.00  |###################
```

---

## 📚 C Concepts Used

| Concept | Where It's Used |
|---------|----------------|
| `struct` | `expense.h` — defines the Expense data type |
| Arrays | `main.c` — stores up to 100 expenses |
| Functions | Every file — each feature is its own function |
| `switch-case` | `main.c` — handles menu selection |
| `for` loop | `expense_operations.c`, `search_summary.c` — iterates expenses |
| File Handling | `file_handler.c` — `fopen`, `fprintf`, `fscanf`, `fclose` |
| String functions | `strcspn`, `strcasecmp`, `fgets` — throughout |
| `extern` keyword | `expense.h` — shares global variables across files |
| Header guards | `expense.h` — `#ifndef` / `#endif` |
| Pointer (FILE*) | `file_handler.c` — file pointer for I/O |

---

## 🔗 How the Files Connect

```
expense.h  ←─────────────────────────────────────────┐
   │  (included by all files)                         │
   ▼                                                  │
main.c                                                │
   │  calls → addExpense()         [expense_operations.c]
   │  calls → viewAllExpenses()    [expense_operations.c]
   │  calls → deleteExpense()      [expense_operations.c]
   │  calls → searchByCategory()   [search_summary.c]
   │  calls → showSummary()        [search_summary.c]
   │  calls → saveToFile()         [file_handler.c]
   └──calls → loadFromFile()       [file_handler.c]
```

---


---

## 📌 Limitations & Future Scope

- Currently supports up to 100 expenses (can be increased by changing `MAX_EXPENSES`)
- Date is entered as plain text (no validation)
- Future improvements: edit expense, date range filter, export to CSV

---

*Submitted as part of the 1st Year CSE Programming in C course project.*
