# BankAccount
# Mini-Project: Multithreaded Banking System

## Overview
This repository contains the implementation of a multithreaded banking system simulation. The system models basic banking operations such as deposits, withdrawals, and balance inquiries, performed concurrently by multiple customers. It uses multithreading and synchronization techniques to maintain the integrity of shared resources.

---

## Software Requirements Specification (SRS)

### **1. Introduction**

#### **1.1 Purpose**
This project defines the requirements for a multithreaded banking system. The system simulates basic banking operations to demonstrate multithreaded programming in C++.

#### **1.2 Scope**
- Simulates a banking environment with multiple customer accounts.
- Allows concurrent customer transactions using threads.
- Ensures synchronization of shared data to prevent race conditions.
- Outputs clear and detailed logs of all operations.

---

### **2. System Overview**

#### **2.1 Features**
- **Account Management**: Supports multiple bank accounts.
- **Multithreaded Transactions**: Simulates concurrent customer transactions.
- **Synchronization**: Uses mutexes for thread-safe operations.
- **Logging**: Logs all transactions and final account balances.

#### **2.2 Constraints**
- Implemented in C++ using STL threading library.
- Console-based interaction only.

---

### **3. Functional Requirements**

#### **3.1 BankAccount Class**
- **Attributes**:
  - `balance` (integer): Current balance of the account.
  - `accountNumber` (integer): Unique identifier for the account.
- **Methods**:
  - `deposit(int amount)`
  - `withdraw(int amount)`
  - `getBalance()`

#### **3.2 Bank Class**
- Manage multiple accounts using `std::map<int, BankAccount>`.
- Provide methods to add and retrieve accounts.

#### **3.3 Multithreaded Customer Simulation**
- Simulates at least 10 customers performing random operations.
- Ensures all operations are logged.

#### **3.4 Logging and Output**
- Logs each transaction with customer ID and account number.
- Displays final account balances after all operations.

---

### **4. Non-Functional Requirements**
- **Reliability**: No data corruption under concurrent operations.
- **Performance**: Handles at least 10 concurrent threads efficiently.
- **Usability**: Clear and formatted console outputs.
- **Maintainability**: Modular and well-documented code.

---

## Developer's To-Do List

### **1. BankAccount Class**
#### Task 1: Create the BankAccount Class
- [ ] Define attributes `balance` and `accountNumber`.
- [ ] Implement methods `deposit(int amount)`, `withdraw(int amount)`, and `getBalance()`.

### **2. Bank Class**
#### Task 1: Manage Multiple Accounts
- [ ] Use `std::map<int, BankAccount>` to store accounts.
- [ ] Implement methods to add and retrieve account details.

### **3. Customer Simulation**
#### Task 1: Create a Client Function
- [ ] Write a function to simulate random customer transactions.
- [ ] Use random number generation for account selection and transaction types.
- [ ] Log each transaction.

#### Task 2: Implement Multithreading
- [ ] Use `std::thread` to create at least 10 threads for customers.
- [ ] Ensure thread-safe operations.

### **4. Synchronization**
#### Task 1: Protect Shared Resources
- [ ] Use `std::mutex` for thread safety.
- [ ] Test for race conditions and ensure proper synchronization.

### **5. Logging and Output**
#### Task 1: Log Transactions
- [ ] Log transaction details with customer ID, account number, and action.
- [ ] Summarize final balances after all threads complete execution.

---

## Optional Tasks
- **Scalability**:
  - [ ] Extend the system to handle more accounts and customers.
  - [ ] Add more transaction types (e.g., fund transfer).
- **Database Integration**:
  - [ ] Store account data in a database for persistence.
- **Statistics**:
  - [ ] Collect and display statistics such as total deposits and withdrawals.

---

## Example Output
```
Customer 1: Deposited 100 to Account 123
Customer 2: Withdrew 50 from Account 456
Customer 3: Checked balance of Account 123: 250
...
Final Balance for Account 123: 500
Final Balance for Account 456: 100
```

---

## License
This project is for educational purposes and is open-sourced under the MIT License.

