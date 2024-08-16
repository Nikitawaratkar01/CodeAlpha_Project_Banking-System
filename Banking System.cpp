#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Forward declaration
class Account;

// Class representing a Customer
class Customer {
private:
    string name;
    string customerID;
    vector<Account> accounts;  // Each customer can have multiple accounts

public:
    Customer(string n, string id) : name(n), customerID(id) {}

    string getName() { return name; }
    string getCustomerID() { return customerID; }
    void addAccount(Account acc);
    void displayAccounts();
};

// Class representing an Account
class Account {
private:
    string accountNumber;
    double balance;
    vector<string> transactions;

public:
    Account(string accNum, double initialBalance = 0.0) 
        : accountNumber(accNum), balance(initialBalance) {}

    string getAccountNumber() { return accountNumber; }
    double getBalance() { return balance; }
    
    void deposit(double amount) {
        balance += amount;
        transactions.push_back("Deposit: " + to_string(amount));
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!" << endl;
            return false;
        }
        balance -= amount;
        transactions.push_back("Withdrawal: " + to_string(amount));
        return true;
    }

    void transfer(Account &toAccount, double amount) {
        if (withdraw(amount)) {
            toAccount.deposit(amount);
            transactions.push_back("Transfer to " + toAccount.getAccountNumber() + ": " + to_string(amount));
            toAccount.transactions.push_back("Transfer from " + accountNumber + ": " + to_string(amount));
        }
    }

    void displayTransactions() {
        cout << "Transactions for account " << accountNumber << ":" << endl;
        for (string &transaction : transactions) {
            cout << transaction << endl;
        }
    }
};

// Add Account to Customer
void Customer::addAccount(Account acc) {
    accounts.push_back(acc);
}

// Display Customer's Accounts
void Customer::displayAccounts() {
    cout << "Accounts for customer " << name << ":" << endl;
    for (Account &acc : accounts) {
        cout << "Account Number: " << acc.getAccountNumber() << ", Balance: " << acc.getBalance() << endl;
    }
}

// Main Banking Service
class BankingService {
private:
    vector<Customer> customers;

public:
    void addCustomer(Customer cust) {
        customers.push_back(cust);
    }

    void displayAllCustomers() {
        for (Customer &cust : customers) {
            cout << "Customer ID: " << cust.getCustomerID() << ", Name: " << cust.getName() << endl;
            cust.displayAccounts();
        }
    }
};

int main() {
    // Create some customers
    Customer customer1("Alice", "C001");
    Customer customer2("Bob", "C002");

    // Create some accounts for the customers
    Account account1("A001", 1000.0);
    Account account2("A002", 2000.0);
    Account account3("A003", 1500.0);

    // Add accounts to customers
    customer1.addAccount(account1);
    customer1.addAccount(account2);
    customer2.addAccount(account3);

    // Create banking service
    BankingService bankService;
    bankService.addCustomer(customer1);
    bankService.addCustomer(customer2);

    // Perform some transactions
    account1.deposit(500);
    account1.withdraw(200);
    account1.transfer(account2, 300);
    account3.deposit(1000);

    // Display all customers and their accounts
    bankService.displayAllCustomers();

    // Display individual transactions
    account1.displayTransactions();
    account2.displayTransactions();
    account3.displayTransactions();

    return 0;
}
