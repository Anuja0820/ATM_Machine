#ifndef ATM_H
#define ATM_H

#include <map>
#include <utility>
#include <string>

// ============================================
// ACCOUNT STRUCTURE (Global, not nested)
// ============================================
struct Account {
    std::string name;
    double balance;
};

// ============================================
// ATM CLASS
// ============================================
class ATM {
private:
    std::map<int, int, std::greater<int>> cashInventory;

public:
    struct Suggestion {
        int lower;
        int higher;
    };

    void addCash(int denomination, int quantity);
    void displayInventory() const;
    int getTotalCash() const;
    bool validateWithdrawalAmount(int withdrawalAmount) const;
    std::map<int, int> calculateMinimumBills(int withdrawalAmount) const;
    Suggestion findNearestPossibleAmounts(int requestedAmount) const;
    void updateInventory(const std::map<int, int>& withdrawalBills);
};

#endif // ATM_H
