#ifndef CONFIG_H
#define CONFIG_H

#include <string>

// ============================================
// ADMIN AUTHENTICATION CREDENTIALS
// ============================================
const std::string ADMIN_USERNAME = "admin";
const std::string ADMIN_PASSWORD = "admin123";

// ============================================
// CURRENCY CONVERSION RATES (to INR)
// ============================================
const double USD_TO_INR = 82.0;
const double EUR_TO_INR = 88.0;

// ============================================
// FILE PATHS
// ============================================
const std::string ACCOUNTS_FILE = "accounts.txt";
const std::string TRANSACTIONS_LOG_FILE = "transactions.log";

// ============================================
// VALIDATION CONSTRAINTS
// ============================================
const int MIN_WITHDRAWAL_AMOUNT = 1;
const int MAX_WITHDRAWAL_AMOUNT = 1000000;

// ============================================
// USD DENOMINATIONS (in USD)
// ============================================
const int USD_DENOMINATIONS[] = {100, 50, 20, 10, 5, 1};
const int USD_INITIAL_COUNTS[] = {5, 10, 15, 20, 20, 50};
const int USD_DENOMINATIONS_SIZE = 6;

// ============================================
// INR DENOMINATIONS (in INR)
// ============================================
const int INR_DENOMINATIONS[] = {2000, 500, 200, 100, 50, 20, 10, 5, 2, 1};
const int INR_INITIAL_COUNTS[] = {5, 10, 15, 20, 20, 50, 50, 100, 100, 100};
const int INR_DENOMINATIONS_SIZE = 10;

// ============================================
// EURO DENOMINATIONS (in EUR)
// ============================================
const int EUR_DENOMINATIONS[] = {500, 200, 100, 50, 20, 10, 5};
const int EUR_INITIAL_COUNTS[] = {2, 5, 10, 20, 30, 50, 100};
const int EUR_DENOMINATIONS_SIZE = 7;

// ============================================
// USER TYPES
// ============================================
const int USER_TYPE_ADMIN = 1;
const int USER_TYPE_ACCOUNT_HOLDER = 2;

// ============================================
// CURRENCY TYPES
// ============================================
const int CURRENCY_USD = 1;
const int CURRENCY_INR = 2;
const int CURRENCY_EUR = 3;

#endif // CONFIG_H
