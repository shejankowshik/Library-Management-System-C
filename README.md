# Library Management System

A C-based Library Management System developed as a Data Structures project. 
The system uses a **Singly Linked List, Binary Search Tree (BST), and Stack**
to efficiently manage books, search for books, and track recently issued books.

## Features

- Add new books
- Display all books
- Search books by Book ID
- Issue books to students
- Return issued books
- Track recently issued books
- Display available books
- Display issued books
- Search books borrowed by Student ID
- Store issue and return dates
- Prevent duplicate Book IDs

## Data Structures Used

### 1. Singly Linked List

A singly linked list is used to store and manage the complete collection of books.

Each book node contains:

- Book ID
- Book name
- Author name
- Availability status
- Student ID
- Issue date
- Return date
- Pointer to the next book

### 2. Binary Search Tree (BST)

A Binary Search Tree is used to store Book IDs and perform efficient book ID searching.

The BST helps determine whether a particular Book ID exists in the library.

### 3. Stack

A stack is used to maintain a list of recently issued books.

When a book is issued, its ID is pushed onto the stack. When a book is returned, its ID is removed from the stack.

## Main Operations

```text
Add Book
    ↓
Store Book in Linked List
    ↓
Insert Book ID into BST
    ↓
Issue Book
    ↓
Push Book ID into Stack
    ↓
Return Book
    ↓
Remove Book ID from Stack
