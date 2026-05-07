#include <iostream>
#include <string>
#include "atm.h"

bool authenticateAdmin() {
    const std::string ADMIN_USER = "admin";
    const std::string ADMIN_PASS = "admin123";
    std::string enteredUser;
    std::string enteredPass;

    std::cout << "\n========== ADMIN LOGIN ==========" << std::endl;
    std::cout << "Username: ";
    std::cin >> enteredUser;
    std::cout << "Password: ";
    std::cin >> enteredPass;

    if (enteredUser == ADMIN_USER && enteredPass == ADMIN_PASS) {
        std::cout << "Login successful." << std::endl;
        return true;
    }

    std::cout << "Invalid username or password." << std::endl;
    return false;
}

void displayAdminMenu() {
    std::cout << "\n========== ADMIN MENU ==========" << std::endl;
    std::cout << "1. Add cash to USD ATM" << std::endl;
    std::cout << "2. Add cash to INR ATM" << std::endl;
    std::cout << "3. Add cash to EUR ATM" << std::endl;
    std::cout << "4. View USD ATM Inventory" << std::endl;
    std::cout << "5. View INR ATM Inventory" << std::endl;
    std::cout << "6. View EUR ATM Inventory" << std::endl;
    std::cout << "7. Exit" << std::endl;
    std::cout << "Choose an option: ";
}

void adminAddCash(ATM& atm, const std::string& currencyName) {
    int denomination, quantity;
    std::cout << "\nEnter denomination and quantity to add to " << currencyName << " ATM:" << std::endl;
    std::cout << "Denomination: ";
    std::cin >> denomination;
    std::cout << "Quantity: ";
    std::cin >> quantity;

    atm.addCash(denomination, quantity);
    std::cout << "Successfully added " << quantity << " notes of denomination " << denomination << std::endl;
}

void handleAdminOperations(ATM& usdAtm, ATM& inrAtm, ATM& eurAtm) {
    int choice;
    bool adminRunning = true;

    while (adminRunning) {
        displayAdminMenu();
        std::cin >> choice;

        switch(choice) {
            case 1:
                adminAddCash(usdAtm, "US Dollar");
                break;
            case 2:
                adminAddCash(inrAtm, "Indian Rupee");
                break;
            case 3:
                adminAddCash(eurAtm, "Euro");
                break;
            case 4:
                std::cout << "\n==== USD ATM Inventory ====" << std::endl;
                usdAtm.displayInventory();
                break;
            case 5:
                std::cout << "\n==== INR ATM Inventory ====" << std::endl;
                inrAtm.displayInventory();
                break;
            case 6:
                std::cout << "\n==== EUR ATM Inventory ====" << std::endl;
                eurAtm.displayInventory();
                break;
            case 7:
                std::cout << "Exiting admin panel." << std::endl;
                adminRunning = false;
                break;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
        }
    }
}

int selectUserType() {
    std::cout << "\n========== ATM WELCOME ==========" << std::endl;
    std::cout << "Select user type:" << std::endl;
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
    const double USD_TO_INR = 82.0;
    const double EUR_TO_INR = 88.0;

    if (currencyType == 1) {
        return amount * USD_TO_INR;
    }

    if (currencyType == 3) {
        return amount * EUR_TO_INR;
    }

    return static_cast<double>(amount);
}

void initializeInventories(ATM& usdAtm, ATM& inrAtm, ATM& eurAtm) {
    usdAtm.addCash(100, 5);
    usdAtm.addCash(50, 10);
    usdAtm.addCash(20, 15);
    usdAtm.addCash(10, 20);
    usdAtm.addCash(5, 20);
    usdAtm.addCash(1, 50);

    inrAtm.addCash(2000, 5);
    inrAtm.addCash(500, 10);
    inrAtm.addCash(200, 15);
    inrAtm.addCash(100, 20);
    inrAtm.addCash(50, 20);
    inrAtm.addCash(20, 50);
    inrAtm.addCash(10, 50);
    inrAtm.addCash(5, 100);
    inrAtm.addCash(2, 100);
    inrAtm.addCash(1, 100);

    eurAtm.addCash(500, 2);
    eurAtm.addCash(200, 5);
    eurAtm.addCash(100, 10);
    eurAtm.addCash(50, 20);
    eurAtm.addCash(20, 30);
    eurAtm.addCash(10, 50);
    eurAtm.addCash(5, 100);
}

void printBills(const std::map<int, int>& bills) {
    for (const auto& bill : bills) {
        std::cout << bill.first << " x " << bill.second << std::endl;
    }
}

int main() {
    ATM usdAtm;
    ATM inrAtm;
    ATM eurAtm;
    initializeInventories(usdAtm, inrAtm, eurAtm);

    int userType = selectUserType();
    if (userType == 1) {
        // Admin login
        if (!authenticateAdmin()) {
            return 0;
        }
        // Admin gets access to admin menu
        handleAdminOperations(usdAtm, inrAtm, eurAtm);
        return 0;
    } else if (userType != 2) {
        std::cout << "Invalid user type." << std::endl;
        return 0;
    }

    // Account holder flow
    int currencyType = selectCurrencyType();
    ATM* selectedAtm = nullptr;
    std::string currencyName;

    if (currencyType == 1) {
        selectedAtm = &usdAtm;
        currencyName = "US Dollar";
    } else if (currencyType == 2) {
        selectedAtm = &inrAtm;
        currencyName = "Indian Rupee";
    } else if (currencyType == 3) {
        selectedAtm = &eurAtm;
        currencyName = "Euro";
    } else {
        std::cout << "Invalid currency selection." << std::endl;
        return 0;
    }

    std::cout << "\nSelected currency: " << currencyName << std::endl;
    int withdrawalAmount;
    std::cout << "Enter the amount: ";
    std::cin >> withdrawalAmount;

    if (!selectedAtm->validateWithdrawalAmount(withdrawalAmount)) {
        return 0;
    }

    if (currencyType == 1 || currencyType == 3) {
        double inrValue = convertToINR(currencyType, withdrawalAmount);
        std::cout << "Equivalent in Indian Rupees: " << inrValue << " INR" << std::endl;
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
        std::cout << "Transaction successful. Cash dispensed." << std::endl;
    } else {
        std::cout << "Transaction aborted. Inventory not changed." << std::endl;
    }

    std::cout << "\nRemaining inventory for " << currencyName << ":" << std::endl;
    selectedAtm->displayInventory();

    return 0;
}