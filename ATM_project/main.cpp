#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "atm.h"
#include "config.h"


bool authenticateAdmin() {
    std::string enteredUser;
    std::string enteredPass;

    std::cout << "Bank admin login required." << std::endl;
    std::cout << "Username: ";
    std::cin >> enteredUser;
    std::cout << "Password: ";
    std::cin >> enteredPass;

    if (enteredUser == ADMIN_USERNAME && enteredPass == ADMIN_PASSWORD) {
        std::cout << "Login successful." << std::endl;
        return true;
    }

    std::cout << "Invalid username or password." << std::endl;
    return false;
}

int selectUserType() {
    std::cout << "\nSelect user type:" << std::endl;
    std::cout << "1. Bank admin" << std::endl;
    std::cout << "2. Account holder" << std::endl;
    std::cout << "Choose an option: ";

    int option;
    std::cin >> option;
    return option;
}

int selectCurrencyType() {
    std::cout << "\nSelect currency:" << std::endl;
    std::cout << "1. US Dollar" << std::endl;
    std::cout << "2. Indian Rupee" << std::endl;
    std::cout << "3. Euro" << std::endl;
    std::cout << "Choose an option: ";

    int option;
    std::cin >> option;
    return option;
}

double convertToINR(int currencyType, int amount) {
    if (currencyType == CURRENCY_USD) {
        return amount * USD_TO_INR;
    }

    if (currencyType == CURRENCY_EUR) {
        return amount * EUR_TO_INR;
    }

    return static_cast<double>(amount);
}

void initializeInventories(ATM& usdAtm, ATM& inrAtm, ATM& eurAtm) {
    // Initialize USD ATM from config
    for (int i = 0; i < USD_DENOMINATIONS_SIZE; i++) {
        usdAtm.addCash(USD_DENOMINATIONS[i], USD_INITIAL_COUNTS[i]);
    }

    // Initialize INR ATM from config
    for (int i = 0; i < INR_DENOMINATIONS_SIZE; i++) {
        inrAtm.addCash(INR_DENOMINATIONS[i], INR_INITIAL_COUNTS[i]);
    }

    // Initialize EUR ATM from config
    for (int i = 0; i < EUR_DENOMINATIONS_SIZE; i++) {
        eurAtm.addCash(EUR_DENOMINATIONS[i], EUR_INITIAL_COUNTS[i]);
    }
}

void printBills(const std::map<int, int>& bills) {
    for (const auto& bill : bills) {
        std::cout << bill.first << " x " << bill.second << std::endl;
    }
}


void adminAddNotes(ATM& atm, const std::string& currencyName) {
    std::cout << "\nCurrent inventory for " << currencyName << ":" << std::endl;
    atm.displayInventory();

    char addMore = 'y';

    while (addMore == 'y' || addMore == 'Y') {
        int denomination;
        int quantity;

        std::cout << "\nEnter note denomination to add: ";
        std::cin >> denomination;

        std::cout << "Enter quantity of notes: ";
        std::cin >> quantity;

        if (denomination <= 0 || quantity <= 0) {
            std::cout << "Invalid denomination or quantity." << std::endl;
        } else {
            atm.addCash(denomination, quantity);
            std::cout << "Notes added successfully." << std::endl;
        }

        std::cout << "Add more notes? (y/n): ";
        std::cin >> addMore;
    }

    std::cout << "\nUpdated inventory for " << currencyName << ":" << std::endl;
    atm.displayInventory();
}


std::map<int, Account> loadAccounts() {
    std::map<int, Account> accounts;
    std::ifstream file(ACCOUNTS_FILE);

    if (!file) {
        std::cout << ACCOUNTS_FILE << " file not found." << std::endl;
        return accounts;
    }

    int accountNumber;
    std::string name;
    double balance;

    while (file >> accountNumber >> name >> balance) {
        accounts[accountNumber] = {name, balance};
    }

    file.close();
    return accounts;
}

void saveAccounts(const std::map<int, Account>& accounts) {
    std::ofstream file(ACCOUNTS_FILE);

    for (const auto& account : accounts) {
        file << account.first << " "
             << account.second.name << " "
             << account.second.balance << std::endl;
    }

    file.close();
}

int main() {
    ATM usdAtm;
    ATM inrAtm;
    ATM eurAtm;
    initializeInventories(usdAtm, inrAtm, eurAtm);
    std::map<int, Account> accounts = loadAccounts();

    int userType = selectUserType();
    if (userType == USER_TYPE_ADMIN) {
        if (!authenticateAdmin()) {
            return 0;
        }
    } else if (userType != USER_TYPE_ACCOUNT_HOLDER) {
        std::cout << "Invalid user type." << std::endl;
        return 0;
    }

    int accountNumber = 0;

    if (userType == USER_TYPE_ACCOUNT_HOLDER) {
        std::cout << "Enter account number: ";
        std::cin >> accountNumber;

        if (accounts.find(accountNumber) == accounts.end()) {
            std::cout << "Account not found." << std::endl;
            return 0;
        }

        std::cout << "Welcome, " << accounts[accountNumber].name << std::endl;
        std::cout << "Available account balance: "
                << accounts[accountNumber].balance << std::endl;
    }
    int currencyType = selectCurrencyType();
    ATM* selectedAtm = nullptr;
    std::string currencyName;

    if (currencyType == CURRENCY_USD) {
        selectedAtm = &usdAtm;
        currencyName = "US Dollar";
    } else if (currencyType == CURRENCY_INR) {
        selectedAtm = &inrAtm;
        currencyName = "Indian Rupee";
    } else if (currencyType == CURRENCY_EUR) {
        selectedAtm = &eurAtm;
        currencyName = "Euro";
    } else {
        std::cout << "Invalid currency selection." << std::endl;
        return 0;
    }

    std::cout << "\nSelected currency: " << currencyName << std::endl;

    if (userType == USER_TYPE_ADMIN) {
        adminAddNotes(*selectedAtm, currencyName);
        return 0;
    }
    int withdrawalAmount;
    std::cout << "Enter the amount: ";
    std::cin >> withdrawalAmount;

    if (!selectedAtm->validateWithdrawalAmount(withdrawalAmount)) {
        return 0;
    }

    if (withdrawalAmount > accounts[accountNumber].balance) {
    std::cout << "Insufficient account balance." << std::endl;
    return 0;
}


    char showConversion;

    if (currencyType == CURRENCY_USD || currencyType == CURRENCY_EUR) {
        std::cout << "Do you want to see INR equivalent? (y/n): ";
        std::cin >> showConversion;

        if (showConversion == 'y' || showConversion == 'Y') {
            double inrValue = convertToINR(currencyType, withdrawalAmount);
            std::cout << "Equivalent in Indian Rupees: " << inrValue << " INR" << std::endl;
        }
    }

    auto withdrawalBills = selectedAtm->calculateMinimumBills(withdrawalAmount);
    if (withdrawalBills.empty()) {
        std::cout << "Exact amount not possible for " << currencyName << "." << std::endl;
        ATM::Suggestion suggestions = selectedAtm->findNearestPossibleAmounts(withdrawalAmount);

        if (suggestions.lower == -1 && suggestions.higher == -1) {
            std::cout << "No possible amount available." << std::endl;
            return 0;
        }

        std::cout << "Suggested amounts:" << std::endl;
        if (suggestions.lower != -1) {
            std::cout << "Lower amount: " << suggestions.lower << std::endl;
        }
        if (suggestions.higher != -1) {
            std::cout << "Higher amount: " << suggestions.higher << std::endl;
        }

        return 0;
    }

    std::cout << "\nNotes to dispense for " << withdrawalAmount << " " << currencyName << ":" << std::endl;
    printBills(withdrawalBills);

    char confirmation;
    std::cout << "\nConfirm transaction? (y/n): ";
    std::cin >> confirmation;

    if (confirmation == 'y' || confirmation == 'Y') {
        selectedAtm->updateInventory(withdrawalBills);

        double amountToDeduct = convertToINR(currencyType, withdrawalAmount);
        accounts[accountNumber].balance -= amountToDeduct;
        saveAccounts(accounts);

        std::cout << "Transaction successful. Cash dispensed." << std::endl;
        std::cout << "Remaining account balance: "
                << accounts[accountNumber].balance
                << " INR" << std::endl;
    } else {
        std::cout << "Transaction aborted. Inventory not changed." << std::endl;
    }

    std::cout << "\nRemaining inventory for " << currencyName << ":" << std::endl;
    selectedAtm->displayInventory();

    return 0;
}
