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
![image](https://github.com/user-attachments/assets/7ec36ab6-46df-4748-8c6f-1c506ea611c1)
