Bank Management System
A robust, console-based banking application built in C++. This system allows for comprehensive management of bank clients, users, and transactions, featuring a secure login system with permission controls.

Project Description
This project allows administrators to manage bank clients and system users efficiently. It utilizes a custom file-based database for data persistence and implements a permission-based access control system, allowing the main administrator to restrict specific functionalities for different users.

Key Features
1. Client Management
Add New Clients: Register new accounts with unique account numbers.

Show Client List: View all clients in a formatted table.

Find & Update: Search for clients by account number and modify their details.

Delete Account: Remove client records safely.

2. Transaction System
Deposit & Withdraw: Perform balance operations with validation checks.

Total Balances: View the aggregate balance of all clients in the bank.

3. User Management & Security
Admin Dashboard: Manage system users (Add, List, Delete, Update).

Authentication: Secure login screen for users.

Access Control: Granular permissions system. The Admin can grant or revoke access to specific features (e.g., a user can be allowed to "Show Clients" but restricted from "Deleting Clients").

 Technical Highlights
Language: C++

Data Persistence: Custom file handling using fstream to read/write Client and User data to text files.

Data Structure: Uses structs and vectors for efficient data management in memory.

Bitwise Permissions: Utilizes bitwise operators (AND/OR) to manage user permissions efficiently, allowing multiple access rights to be stored in a single integer.

Input Validation: Robust validation functions to ensure data integrity (e.g., preventing duplicate account numbers).
