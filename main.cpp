
#include <iostream>
#include <iomanip>
#include <limits>
#include <cassert>
#include <cmath>  

using namespace std;

void showMenu() {
    cout << "\n======== BANKING SYSTEM ========\n"
         << "1. Deposit Money\n"
         << "2. Withdraw Money\n"
         << "3. Check Balance\n"
         << "4. Exit\n"
         << "================================\n"
         << "Choose an option: ";
}

bool readAmount(const string& prompt, double& amount) {
    cout << prompt;
    if (!(cin >> amount)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

int main() {
    double balance = 0.0;
    cout << fixed << showpoint << setprecision(2);

    while (true) {
        showMenu();

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid option! Please choose a valid menu option.\n";
            continue;
        }

        switch (choice) {
            case 1: { // Deposit
                double amount;
                if (!readAmount("Enter amount to deposit: ", amount)) {
                    cout << "Invalid amount. Deposit must be positive.\n";
                    break;
                }
                if (amount > 0.0 && isfinite(amount)) { // selection + logical operators
                    double oldBalance = balance;
                    balance += amount;
                    assert(balance >= 0.0 && "Balance became negative after deposit!");
                    assert(fabs((oldBalance + amount) - balance) < 1e-9 && "Incorrect balance calculation on deposit!");
                    cout << "Deposit successful! New balance: $" << balance << "\n";
                } else {
                    cout << "Invalid amount. Deposit must be positive.\n";
                }
                break;
            }

            case 2: { // Withdraw
                double amount;
                if (!readAmount("Enter amount to withdraw: ", amount)) {
                    cout << "Invalid amount. Withdrawal must be positive and within balance.\n";
                    break;
                }
                if (amount <= 0.0 || !isfinite(amount)) {
                    cout << "Invalid amount. Withdrawal must be positive.\n";
                } else if (amount > balance) { // selection + logical operators
                    cout << "Insufficient funds! Withdrawal failed.\n";
                } else {
                    double oldBalance = balance;
                    balance -= amount;
                    assert(balance >= 0.0 && "Balance became negative after withdrawal!");
                    assert(fabs((oldBalance - amount) - balance) < 1e-9 && "Incorrect balance calculation on withdrawal!");
                    cout << "Withdrawal successful! New balance: $" << balance << "\n";
                }
                break;
            }

            case 3: { // Check Balance
                cout << "Your current balance is: $" << balance << "\n";
                break;
            }

            case 4: { // Exit
                cout << "Exiting the banking system. Thank you for using our service!\n";
                return 0;
            }

            default:
                cout << "Invalid option! Please choose a valid menu option.\n";
                break;
        }
    }
}