# Console Bank Management System

## Project Overview

A robust, console-based banking application developed in C++. This system provides comprehensive management for bank clients, system users, and financial transactions. It features a secure login system with granular permission controls, allowing administrators to restrict access to specific functionalities based on user roles.

The project utilizes a custom file-based database for data persistence and has been refactored from a monolithic codebase into a modular architecture using C++ namespaces and header libraries.

## System Architecture

The project follows a **Modular Procedural** design pattern. While the core logic remains procedural, the codebase has been reorganized into distinct header libraries to adhere to the Separation of Concerns principle.

* **ClientFunctions.h**: Handles all CRUD (Create, Read, Update, Delete) operations, file I/O, and business logic for bank clients.
* **UserFunctions.h**: Manages system users, authentication, and the bitwise permission system.
* **MenuOptions.h**: Acts as the controller, linking user input from the UI to specific business logic functions.
* **MenuScreens.h**: Contains the void functions responsible for rendering the console UI and menus.
* **HelperFunctions.h**: A shared utility library for input validation, string manipulation (splitting/trimming), and formatting.
* **main.cpp**: Serves as the application entry point and initialization layer.

## Key Features

### 1. Client Management

* **Add New Clients**: Register new accounts with automated checks for duplicate account numbers.
* **View Client List**: Display all active clients in a formatted, paginated table.
* **Search & Update**: Locate clients by unique Account Number and modify personal or financial details.
* **Delete Account**: Securely remove client records and update the database file immediately.

### 2. Transaction System

* **Deposit & Withdraw**: Execute balance adjustments with real-time validation (e.g., insufficient funds checks).
* **Total Balances**: Calculate and display the aggregate funds of all clients in the bank.

### 3. User Management & Security

* **Admin Dashboard**: Full control to Add, List, Delete, and Update system users.
* **Authentication**: Secure login mechanism requiring username and password verification.
* **Access Control**: A granular permission system allowing the administrator to grant or revoke access to specific features (e.g., a user may be permitted to "Show Clients" but restricted from "Deleting Clients").

## Technical Implementation

### Language and Standard Library

* **C++ Standard**: Built using standard C++11/14 features.
* **File I/O**: Custom implementation using `fstream` to read and write data to `Clients.txt` and `Users.txt`. Data is serialized using a custom delimiter (`#//#`).

### Data Structures

* **Structs**: Custom structures (`stClient`, `stUser`) are used to model data entities.
* **Vectors**: `std::vector` is utilized for dynamic memory management of client and user lists, allowing for efficient traversal and manipulation during runtime.

### Bitwise Permission System

The application uses bitwise operators (AND, OR) to manage user permissions efficiently. This allows multiple access rights to be stored in a single integer variable.

* Permissions are assigned using powers of two (e.g., 1, 2, 4, 8, 16).
* Access checks are performed using bitwise AND operations: `(UserPermissions & RequiredPermission) == RequiredPermission`.

### Input Validation

The system includes a robust validation layer (`HelperFunctions.h`) that ensures data integrity by:

* Preventing input stream failures (e.g., entering text when a number is expected).
* Validating ranges for menu selections.
* Ensuring logical consistency (e.g., withdraw amount cannot exceed balance).

## File Structure

```text
/BankManagementSystem
│
├── main.cpp              # Entry point
├── ClientFunctions.h     # Client logic and File I/O
├── UserFunctions.h       # User logic and Permissions
├── MenuOptions.h         # Menu control logic
├── MenuScreens.h         # UI display functions
├── HelperFunctions.h     # Utility and Validation functions
├── Clients.txt           # Database file for client records
└── Users.txt             # Database file for system users

```

## Installation and Usage

1. **Compile**: Ensure all header files are in the same directory as `main.cpp`. Compile using a standard C++ compiler.
```bash
g++ main.cpp -o BankSystem

```


2. **Run**: Execute the compiled binary.
```bash
./BankSystem

```


3. **Data Files**: The application will look for `Clients.txt` and `Users.txt` in the working directory. If they do not exist, the file handling logic will handle the creation or error reporting as defined in `HelperFunctions.h`.

## default Login Credentials

* **Username**: Admin
* **Password**: 1233
* *(Note: These credentials allow full access to all system features).*
