# ATM Cash Withdrawal System

## Project Overview

A multi-currency ATM simulation system in C++ that optimizes cash dispensing by calculating the minimum number of banknotes required for any withdrawal request. The system supports multiple currencies (USD, INR, Euro), account management, and inventory tracking.


---

## Project Structure

```
ATM_project/
├── main.cpp              # Entry point, UI, transaction logic
├── ATM.cpp               # ATM class implementation
├── atm.h                 # ATM class header with methods & struct
├── config.h              # Centralized configuration & constants
├── accounts.txt          # Account data (account_number name balance)
├── README.md             # This file
└── ATM.exe               # Compiled executable
```

---

## How to Compile & Run

### **Windows (PowerShell/CMD)**

```bash
# Compile all files
g++ -Wall -o ATM ATM.cpp main.cpp

# Run the program
.\ATM.exe
```

Linux/Mac

```bash
# Compile
g++ -Wall -o ATM ATM.cpp main.cpp

# Run
./ATM
```


## Usage Guide

### **Admin Mode**
1. Select `1` for Bank Admin
2. Enter credentials: `admin` / `admin123`
3. Select currency (USD/INR/EUR)
4. Add notes to inventory (denomination & quantity)
5. View updated inventory

Account Holder Mode
1. Select `2` for Account Holder
2. Enter valid account number (1001, 1002, etc. - see accounts.txt)
3. View current balance and account details
4. Select currency and withdrawal amount
5. Review calculated minimum bills to be dispensed
6. Confirm or abort transaction
7. View updated balance and inventory

Example Withdrawal Flow
```
Select user type:
1. Bank admin
2. Account holder
Choose an option: 2

Enter account number: 1001
Welcome, Anuja
Available account balance: 49966

Select currency:
1. US Dollar
2. Indian Rupee
3. Euro
Choose an option: 1

Selected currency: US Dollar
Enter the amount: 100

Do you want to see INR equivalent? (y/n): y
Equivalent in Indian Rupees: 8200 INR

Notes to dispense for 100 US Dollar:
100 x 1

Confirm transaction? (y/n): y
Transaction successful. Cash dispensed.
Remaining account balance: 49866 INR
```
