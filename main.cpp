#include <iostream>
#include <map>
#include <vector>
#include <climits>
#include <utility>

using namespace std;

class ATM {
private:
    map<int, int, greater<int>> cashInventory;

public:
    void addCash(int denomination, int quantity) {
        cashInventory[denomination] += quantity;
    }

    void displayInventory() {
        cout << "\nATM Inventory:\n";
        for (auto cash : cashInventory) {
            cout << cash.first << " x " << cash.second << endl;
        }
    }

    int getTotalCash() {
        int totalCash = 0;

        for (auto cash : cashInventory) {
            totalCash += cash.first * cash.second;
        }

        return totalCash;
    }

    bool validateWithdrawalAmount(int withdrawalAmount) {
        if (withdrawalAmount == 0) {
            cout << "Amount cannot be zero." << endl;
            return false;
        }

        if (withdrawalAmount < 0) {
            cout << "Negative amount is invalid." << endl;
            return false;
        }

        if (withdrawalAmount > getTotalCash()) {
            cout << "Requested amount exceeds ATM cash." << endl;
            return false;
        }

        return true;
    }

    map<int, int> calculateMinimumBills(int withdrawalAmount) {
        const int IMPOSSIBLE = INT_MAX - 1;

        vector<int> minimumNotes(withdrawalAmount + 1, IMPOSSIBLE);
        vector<map<int, int>> selectedBills(withdrawalAmount + 1);

        minimumNotes[0] = 0;

        for (auto cash : cashInventory) {
            int denomination = cash.first;
            int availableCount = cash.second;

            for (int copy = 0; copy < availableCount; copy++) {
                for (int currentAmount = withdrawalAmount;
                     currentAmount >= denomination;
                     currentAmount--) {

                    if (minimumNotes[currentAmount - denomination] != IMPOSSIBLE &&
                        minimumNotes[currentAmount - denomination] + 1 < minimumNotes[currentAmount]) {

                        minimumNotes[currentAmount] =
                            minimumNotes[currentAmount - denomination] + 1;

                        selectedBills[currentAmount] =
                            selectedBills[currentAmount - denomination];

                        selectedBills[currentAmount][denomination]++;
                    }
                }
            }
        }

        if (minimumNotes[withdrawalAmount] == IMPOSSIBLE) {
            return {};
        }

        return selectedBills[withdrawalAmount];
    }

    pair<int, int> findNearestPossibleAmounts(int requestedAmount) {
        int maximumCash = getTotalCash();

        int lowerSuggestion = -1;
        int higherSuggestion = -1;

        for (int difference = 1; difference <= maximumCash; difference++) {
            int lowerAmount = requestedAmount - difference;
            int higherAmount = requestedAmount + difference;

            if (lowerSuggestion == -1 && lowerAmount > 0) {
                auto lowerResult = calculateMinimumBills(lowerAmount);

                if (!lowerResult.empty()) {
                    lowerSuggestion = lowerAmount;
                }
            }

            if (higherSuggestion == -1 && higherAmount <= maximumCash) {
                auto higherResult = calculateMinimumBills(higherAmount);

                if (!higherResult.empty()) {
                    higherSuggestion = higherAmount;
                }
            }

            if (lowerSuggestion != -1 && higherSuggestion != -1) {
                break;
            }
        }

        return {lowerSuggestion, higherSuggestion};
    }

    void updateInventory(map<int, int> withdrawalBills) {
        for (auto bill : withdrawalBills) {
            cashInventory[bill.first] -= bill.second;
        }
    }
};

int main() {
    ATM atmMachine;

    int numberOfDenominations;

    cout << "Enter number of bill types: ";
    cin >> numberOfDenominations;

    for (int index = 0; index < numberOfDenominations; index++) {
        int denomination;
        int quantity;

        cout << "Enter denomination and quantity: ";
        cin >> denomination >> quantity;

        atmMachine.addCash(denomination, quantity);
    }

    atmMachine.displayInventory();

    int withdrawalAmount;

    cout << "\nEnter withdrawal amount: ";
    cin >> withdrawalAmount;

    if (!atmMachine.validateWithdrawalAmount(withdrawalAmount)) {
        return 0;
    }

    map<int, int> withdrawalBills =
        atmMachine.calculateMinimumBills(withdrawalAmount);

    if (withdrawalBills.empty()) {
        cout << "\nExact amount not possible." << endl;

        auto suggestions =
            atmMachine.findNearestPossibleAmounts(withdrawalAmount);

        int lowerAmount = suggestions.first;
        int higherAmount = suggestions.second;

        if (lowerAmount == -1 && higherAmount == -1) {
            cout << "No possible amount available." << endl;
            return 0;
        }

        cout << "\nSuggested amounts:\n";

        if (lowerAmount != -1) {
            cout << "1. Lower amount: " << lowerAmount << endl;
        }

        if (higherAmount != -1) {
            cout << "2. Higher amount: " << higherAmount << endl;
        }

        int choice;
        cout << "Choose option 1 or 2: ";
        cin >> choice;

        int selectedAmount;

        if (choice == 1 && lowerAmount != -1) {
            selectedAmount = lowerAmount;
        } else if (choice == 2 && higherAmount != -1) {
            selectedAmount = higherAmount;
        } else {
            cout << "Invalid choice." << endl;
            return 0;
        }

        withdrawalAmount = selectedAmount;
        withdrawalBills =
            atmMachine.calculateMinimumBills(withdrawalAmount);

        cout << "\nYou selected amount: "
             << withdrawalAmount
             << endl;
    }

    cout << "\nBills to dispense for "
         << withdrawalAmount
         << ":\n";

    for (auto bill : withdrawalBills) {
        cout << bill.first
             << " x "
             << bill.second
             << endl;
    }

    char confirmation;

    cout << "\nConfirm transaction? (y/n): ";
    cin >> confirmation;

    if (confirmation == 'y' || confirmation == 'Y') {
        atmMachine.updateInventory(withdrawalBills);
        cout << "Transaction successful. Cash dispensed." << endl;
    } else {
        cout << "Transaction aborted. Inventory not changed." << endl;
    }

    atmMachine.displayInventory();

    return 0;
}