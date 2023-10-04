//
//  main.cpp
//  ATM Programming Project
//
//  Created by Ellieanna Ross on 11/29/21.
//

#include <iostream>
#include <string>
using namespace std;



//Customer Struct
struct customer {
    string firstName;
    string loginID;
    string password;
    int numOfAccts;
    int accountNums[3];
    float acctBalance[3];
    bool acctStatus[3];
    bool logStatus;
};

//Function Prototypes
int displayMenu();
void enroll(customer[], int&);
int logIn(customer[], int);
void openAcct(customer[], int);
void checkBalance(customer[], int);
void deposit(customer[], int);
void withdraw(customer[], int);
void transfer(customer[], int);
void close(customer[], int);
void logOut(customer[],int&, int&);
void exit();
void notLoggedIn();

int main() {
    //Flag variable
    bool flag = false;
    //Bool if customer is logged in
    bool customerLoggedIn = false;
    //Index of customer currently logged in
    int customerIndex = -1;
    
    //Total customers in ATM
    int totalCustomers = 0;
    
    //Customers
    customer ATMCustomers[20];
    
    
    //Enroll and log in
    cout << "\n\nWelcome to the ATM!" << endl;
    enroll(ATMCustomers, totalCustomers);
    customerIndex = logIn(ATMCustomers, totalCustomers);
    customerLoggedIn = true;
    
    //While flag is false, show menu & execute choices
    while (!flag) {
        int choice = displayMenu();
        switch (choice) {
        case 1:
            openAcct(ATMCustomers, customerIndex);
            break;
        case 2:
            checkBalance(ATMCustomers, customerIndex);
            break;
        case 3:
            deposit(ATMCustomers, customerIndex);
            break;
        case 4:
            withdraw(ATMCustomers, customerIndex);
            break;
        case 5:
            transfer(ATMCustomers, customerIndex);
            break;
        case 6:
            close(ATMCustomers, customerIndex);
            break;
        case 7:
            logOut(ATMCustomers, customerIndex, totalCustomers);
            break;
        case 8:
            exit();
            flag = true;
            break;
        default:
            cout << "\nThat was an invalid choice. Please try again." << endl;
            break;
        }
    }
    
    
    return 0;
}


int displayMenu() {
    
    //Choice value
    int choice = 0;
    
    //Display Menu
    cout << "\n\n      Menu      " << endl;
    cout << "1: Open a bank account" << endl;
    cout << "2: Check an account balance" << endl;
    cout << "3: Deposit money" << endl;
    cout << "4: Withdraw money" << endl;
    cout << "5: Transfer money between accounts" << endl;
    cout << "6: Close an account" << endl;
    cout << "7: Log off the machine" << endl;
    cout << "8: Exit the machine" << endl;
    
    cout << "\n\nWhat is your selection?" << endl;
    
    //Receive Input
    cin >> choice;
    
    //Return choice back to main()
    return choice;
}


//Choice 1
void enroll(customer customers[], int &totalCustomers) {
    string first;
    string login;
    string pass;
    string passVerify;
    bool flag = false;
    
    cout << "\n\nWhat is your first name?" << endl;
    
    cin >> first;
    
    for (int i = 0; i < 20; i ++) {
        if (customers[i].firstName == first) {
            flag = true;
            break;
        }
        
    }
    
    while (flag) {
        cout << "\nThat name has already been taken. Please try again." << endl;
        cout << "What is your first name?" << endl;
        cin >> first;
        flag = false;
        for (int i = 0; i < 20; i ++) {
            if (customers[i].firstName == first) {
                flag = true;
                break;
            }
        }
    }
    
    customers[totalCustomers].firstName = first;
    
    
    flag = false;
    cout << "\n\nPlease select a login ID" << endl;
    cin >> login;
    
    for (int i = 0; i < 20; i ++) {
        if (customers[i].loginID == login) {
            flag = true;
            break;
        }
    }
    
    while (flag) {
        cout << "\nThat login ID has already been taken. Please try again." << endl;
        cout << "Please select a login ID" << endl;
        cin >> login;
        flag = false;
        for (int i = 0; i < 20; i ++) {
            if (customers[i].loginID == login) {
                flag = true;
                break;
            }
        }
    }
    customers[totalCustomers].loginID = login;
    
    flag = false;
    cout << "\n\nPlease enter a password" << endl;
    cin >> pass;
    
    customers[totalCustomers].password = pass;
    
    cout << "\n\nYou have successfully enrolled in the ATM!" << endl;
    
    
    customers[totalCustomers].logStatus = false;
    customers[totalCustomers].numOfAccts = 0;
    
    
    for (int i = 0; i < 3; i ++) {
        customers[totalCustomers].accountNums[i] = 0;
        customers[totalCustomers].acctBalance[i] = 0;
        customers[totalCustomers].acctStatus[i] = false;
    }
    
    totalCustomers ++;
    
    cout << "\n\nWould you like to enroll another customer? \nEnter Y for yes, or any other character for no." << endl;
    char again;
    cin >> again;
    
    if (again == 'Y' || again == 'y') {
        enroll(customers, totalCustomers);
    } else {
        return;
    }
    
}


//Choice 2
int logIn(customer customers[], int totalCustomers) {
    if (totalCustomers == 0) {
        cout << "\n\nYou cannot log in. No customers are enrolled in this ATM." << endl;
        return -1;
    }
    
    string loginID;
    string password;
    int customerIndex = -1;
    
    while (customerIndex == -1) {
        cout << "\n\nWhat is your login ID?" << endl;
        cin >> loginID;
        
        for (int i = 0; i < 20; i ++) {
            if (customers[i].loginID == loginID) {
                customerIndex = i;
                break;
            }
        }
        
        if (customerIndex == -1) {
            cout << "\nThere is no account asscociated with that ID. Please try again." << endl;
        }
    }
    
    while (customers[customerIndex].password != password) {
        cout << "\n\nWhat is your password?" << endl;
        cin >> password;
        
        if (customers[customerIndex].password != password) {
            cout << "\nInvalid Password." << endl;
        }
    }
    
    cout << "\n\nWelcome, " << customers[customerIndex].firstName << "!" << endl;
    
    customers[customerIndex].logStatus = true;

    
    return customerIndex;
    
}

//Choice 3
void openAcct(customer customers[], int customerIndex) {
    if (customerIndex == -1) {
        notLoggedIn();
        return;
    }
    
    bool flag = true;
    int count = 0;
    int acctNumberCalculation = rand() % 10000 + 1;
    while (flag) {
        count = 0;
        for (int i = 0; i < 20; i ++) {
            for (int j = 0; j < 3; j++) {
                if (customers[i].accountNums[j] == acctNumberCalculation) {
                    acctNumberCalculation = rand() % 10000 + 1;
                    count ++;
                }
            }
            
        }
        if (count > 0) {
            flag = true;
        } else {
            flag = false;
        }
    }
    
    
    
    if (customers[customerIndex].numOfAccts == 3) {
        cout << "\n\nYou have reached the maximum number of accounts\nyou can open at one time." << endl;
        return;
    } else if (customers[customerIndex].numOfAccts == 2){
        cout << "\n\nYou have successfully opened a new account.\nYour new account number is " << acctNumberCalculation << endl;
        customers[customerIndex].accountNums[2] = acctNumberCalculation;
        
    } else if (customers[customerIndex].numOfAccts == 1){
        cout << "\n\nYou have successfully opened a new account.\nYour new account number is " << acctNumberCalculation << endl;
        customers[customerIndex].accountNums[1]  = acctNumberCalculation;
        
    } else if (customers[customerIndex].numOfAccts == 0){
        cout << "\n\nYou have successfully opened a new account.\nYour new account number is " << acctNumberCalculation << endl;
        customers[customerIndex].accountNums[0]  = acctNumberCalculation;
        
    }
    
    customers[customerIndex].numOfAccts ++;
    
}


//Choice 4
void checkBalance(customer customers[], int customerIndex) {
    int acctNum = -1;
    bool flag = false;
    int index = 0;
    
    if (customers[customerIndex].numOfAccts == 0) {
        cout << "\n\nThere are no accounts associated with this login." << endl;
        return;
    }
    
    while (!flag) {
        cout << "\n\nEnter your bank account number: " << endl;
        cin >> acctNum;
        
        for (int i = 0; i < 3; i++) {
            if (customers[customerIndex].accountNums[i] == acctNum) {
                flag = true;
                index = i;
            }
        }
        
        if (flag == false) {
            cout << "\nThere is no account associated with that number. Try again." << endl;
        }
        
    }
    
    if (customers[customerIndex].acctStatus[index] == true) {
        cout << "\n\nThis account has been closed." << endl;
        return;
    }
    
    cout << "The balance of account #" << acctNum << " is $" << customers[customerIndex].acctBalance[index] << "." << endl;
}


//Make a deposit
void deposit(customer customers[], int customerIndex) {
    int acctNum = -1;
    bool flag = false;
    int index = 0;
    double deposit = 0;
    
    if (customers[customerIndex].numOfAccts == 0) {
        cout << "\n\nThere are no accounts associated with this login." << endl;
        return;
    }
    
    
    cout << "\n\nEnter your bank account number: " << endl;
    cin >> acctNum;
    
    for (int i = 0; i < 3; i++) {
        if (customers[customerIndex].accountNums[i] == acctNum) {
            flag = true;
            index = i;
        }
    }
    
    if (flag == false) {
        cout << "\nThere is no account associated with that number." << endl;
        return;
    }
        
    if (customers[customerIndex].acctStatus[index] == true) {
        cout << "\n\nThis account has been closed." << endl;
        return;
    }
    
    
    flag = false;
    
    while (!flag) {
        cout << "\n\nHow much money would you like to deposit?\n$";
        cin >> deposit;
        if (deposit >= 1 && deposit <= 1000) {
            customers[customerIndex].acctBalance[index] += deposit;
            flag = true;
        } else {
            cout << "\n\nYou may only deposit a value between $1 and $1000." << endl;
        }
    }
    
    cout << "\n\nThe new balance of your account is $" << customers[customerIndex].acctBalance[index] << ".";
    
}


//Withdraw money
void withdraw(customer customers[], int customerIndex) {
    int acctNum = -1;
    bool flag = false;
    int index = 0;
    double withdraw = 0;
    
    if (customers[customerIndex].numOfAccts == 0) {
        cout << "\n\nThere are no accounts associated with this login." << endl;
        return;
    }
    
    
    cout << "\n\nEnter your bank account number: " << endl;
    cin >> acctNum;
    
    for (int i = 0; i < 3; i++) {
        if (customers[customerIndex].accountNums[i] == acctNum) {
            flag = true;
            index = i;
        }
    }
    
    if (flag == false) {
        cout << "\n\nThere is no account associated with that number." << endl;
        return;
    }
    
    if (customers[customerIndex].acctStatus[index] == true) {
        cout << "This account has been closed." << endl;
        return;
    }
    
    
    flag = false;
    
    while (!flag) {
        cout << "\n\nHow much money would you like to withdraw?\n$";
        cin >> withdraw;
        if (withdraw >= 1 && withdraw <= customers[customerIndex].acctBalance[index] && customers[customerIndex].acctBalance[index] > 0) {
            flag = true;
        } else if (customers[customerIndex].acctBalance[index] == 0) {
            cout << "\n\nYou have no money in that account. You may not withdraw." << endl;
            return;
        } else {
            cout << "\n\nYou may only withdraw a value between $1 and $" << customers[customerIndex].acctBalance[index] << endl;
        }
    }
    
    customers[customerIndex].acctBalance[index] -= withdraw;
    
    cout << "\n\nYour new account balance is $" << customers[customerIndex].acctBalance[index] << "." << endl;
    
}


//Transfer money from one account to another
void transfer(customer customers[], int customerIndex) {
    //Variables
    int sourceAcct;
    int sourceIndex = -1;
    int receiveingAcct;
    int receivingIndex = -1;
    double amount = 0.0;
    bool flag = false;
    
    if (customers[customerIndex].numOfAccts < 2) {
        cout << "\n\nYou must open at least 2 accounts before withdrawing money." << endl;
        return;
    }
    
    cout << "\n\nWhat is the source account number?" << endl;
    cin >> sourceAcct;
    cout << "\n\nWhat is the receiveing account number?" << endl;
    cin >> receiveingAcct;
    
    
    
    //Check if account numbers are correct
    
    for (int i = 0; i < 3; i++) {
        if (customers[customerIndex].accountNums[i] == sourceAcct) {
            flag = true;
            sourceIndex = i;
        }
    }
    
    if (flag == false) {
        cout << "\n\nThere is no account associated one or more of those numbers." << endl;
        return;
    } else if (customers[customerIndex].acctStatus[sourceIndex] == true) {
        cout << "\n\nThe source account has been closed." << endl;
        return;
    }
    
    
    flag = false;
    for (int i = 0; i < 3; i++) {
        if (customers[customerIndex].accountNums[i] == receiveingAcct) {
            flag = true;
            receivingIndex = i;
        }
    }
    
    if (flag == false) {
        cout << "\n\nThere is no account associated one or more of those numbers." << endl;
        return;
    }  else if (customers[customerIndex].acctStatus[receiveingAcct] == true) {
        cout << "\n\nThe receiving account has been closed." << endl;
        return;
    }
    
    
    cout << "\n\nHow much would you like to transfer?\n$";
    cin >> amount;
    
    if (amount <= 0) {
        cout << "\n\nYou must transfer at least $1." << endl;
        return;
    } else if (amount > customers[customerIndex].acctBalance[sourceIndex]) {
        cout << "\n\nYou may not overdraw the source account. It only contains $" << customers[customerIndex].acctBalance[sourceIndex] << "." << endl;
        return;
    }
    
    customers[customerIndex].acctBalance[sourceIndex] -= amount;
    customers[customerIndex].acctBalance[receivingIndex] += amount;
    
    cout << "\n\nMoney transfered successfully." << endl;
    
}


//Close an account
void close(customer customers[], int customerIndex) {
    int closeAcct;
    bool flag = false;
    int closeAcctIndex = -1;
    
    cout << "\n\nWhich account number would you like to close?" << endl;
    cin >> closeAcct;
    
    for (int i = 0; i < 3; i ++) {
        if (customers[customerIndex].accountNums[i] == closeAcct) {
            flag = true;
            closeAcctIndex = i;
        }
    }
    
    if (!flag) {
        cout << "\n\nThat number is not associated with an account." << endl;
        return;
    }
    
    if (customers[customerIndex].acctStatus[closeAcctIndex] == true) {
        cout << "\n\nThis account has already been closed. No futher action required." << endl;
    } else {
        customers[customerIndex].acctStatus[closeAcctIndex] = true;
        cout << "\n\nAccount #" << closeAcct << " has been closed. You may no longer access it." << endl;
    }
}


//Log out
void logOut(customer customers[], int &customerIndex, int &totalCustomers) {
    cout << "\n\nYou have successfully logged out." << endl;
    customers[customerIndex].logStatus = false;
    customerIndex = logIn(customers, totalCustomers);
}


//Exit
void exit() {
    cout << "\n\nThank you for running the ATM" << endl;
    return;
}




//Not logged in message
void notLoggedIn() {
    cout << "\n\nPlease log in before using this function." << endl;
}
