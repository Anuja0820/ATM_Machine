#include "ATM.h"
#include <climits>
#include <iostream>
#include <map>
#include <vector>

void ATM::addCash(int denomination, int quantity) {
    cashInventory[denomination] += quantity;
}

void ATM::displayInventory() const {
    std::cout << "\nATM Inventory:\n";
    for (const auto& cash : cashInventory) {
        std::cout << cash.first << " x " << cash.second << "\n";
    }
}

int ATM::getTotalCash() const {
    int totalCash = 0;
    for (const auto& cash : cashInventory) {
        totalCash += cash.first * cash.second;
    }
    return totalCash;
}

bool ATM::validateWithdrawalAmount(int withdrawalAmount) const {
    if (withdrawalAmount == 0) {
        std::cout << "Amount cannot be zero." << std::endl;
        return false;
    }

    if (withdrawalAmount < 0) {
        std::cout << "Negative amount is invalid." << std::endl;
        return false;
    }

    if (withdrawalAmount > getTotalCash()) {
        std::cout << "Requested amount exceeds ATM cash." << std::endl;
        return false;
    }

    return true;
}

std::map<int, int> ATM::calculateMinimumBills(int withdrawalAmount) const {
    const int IMPOSSIBLE = INT_MAX - 1;
    std::vector<int> minimumNotes(withdrawalAmount + 1, IMPOSSIBLE);
    std::vector<std::map<int, int>> selectedBills(withdrawalAmount + 1);

    minimumNotes[0] = 0;

    for (const auto& cash : cashInventory) {
        int denomination = cash.first;
        int availableCount = cash.second;

        for (int copy = 0; copy < availableCount; copy++) {
            for (int currentAmount = withdrawalAmount;currentAmount >= denomination;
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

ATM::Suggestion ATM::findNearestPossibleAmounts(int requestedAmount) const {
    int maximumCash = getTotalCash();
    Suggestion suggestions{-1, -1};

    for (int difference = 1; difference <= maximumCash; difference++) {
        int lowerAmount = requestedAmount - difference;
        int higherAmount = requestedAmount + difference;

        if (suggestions.lower == -1 && lowerAmount > 0) {
            auto lowerResult = calculateMinimumBills(lowerAmount);
            if (!lowerResult.empty()) {
                suggestions.lower = lowerAmount;
            }
        }

        if (suggestions.higher == -1 && higherAmount <= maximumCash) {
            auto higherResult = calculateMinimumBills(higherAmount);
            if (!higherResult.empty()) {
                suggestions.higher = higherAmount;
            }
        }

        if (suggestions.lower != -1 && suggestions.higher != -1) {
            break;
        }
    }

    return suggestions;
}

void ATM::updateInventory(const std::map<int, int>& withdrawalBills) {
    for (const auto& bill : withdrawalBills) {
        cashInventory[bill.first] -= bill.second;
    }
}
