#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class BankAccount
{
public:
    int accNo;
    string name;
    float balance;

    void createAccount()
    {
        ofstream file("bank.txt", ios::app);

        cout << "\nEnter Account Number: ";
        cin >> accNo;

        cin.ignore();
        cout << "Enter Customer Name: ";
        getline(cin, name);

        cout << "Enter Initial Deposit: ";
        cin >> balance;

        file << accNo << "|" << name << "|" << balance << endl;
        file.close();

        cout << "\nAccount Created Successfully!\n";
    }

    void displayAccounts()
    {
        ifstream file("bank.txt");
        string line;

        cout << "\n===== ACCOUNT DETAILS =====\n";

        while (getline(file, line))
        {
            cout << line << endl;
        }

        file.close();
    }

    void searchAccount()
    {
        int searchAcc;
        bool found = false;

        cout << "\nEnter Account Number: ";
        cin >> searchAcc;

        ifstream file("bank.txt");
        string line;

        while (getline(file, line))
        {
            int pos1 = line.find('|');
            int pos2 = line.rfind('|');

            int acc = stoi(line.substr(0, pos1));
            string cname = line.substr(pos1 + 1, pos2 - pos1 - 1);
            float bal = stof(line.substr(pos2 + 1));

            if (acc == searchAcc)
            {
                cout << "\nAccount Found\n";
                cout << "Account No : " << acc << endl;
                cout << "Name       : " << cname << endl;
                cout << "Balance    : " << bal << endl;

                found = true;
                break;
            }
        }

        if (!found)
            cout << "\nAccount Not Found!\n";

        file.close();
    }

    void deposit()
    {
        int searchAcc;
        float amount;
        bool found = false;

        cout << "\nEnter Account Number: ";
        cin >> searchAcc;

        cout << "Enter Deposit Amount: ";
        cin >> amount;

        ifstream file("bank.txt");
        ofstream temp("temp.txt");

        string line;

        while (getline(file, line))
        {
            int pos1 = line.find('|');
            int pos2 = line.rfind('|');

            int acc = stoi(line.substr(0, pos1));
            string cname = line.substr(pos1 + 1, pos2 - pos1 - 1);
            float bal = stof(line.substr(pos2 + 1));

            if (acc == searchAcc)
            {
                bal += amount;
                found = true;
            }

            temp << acc << "|" << cname << "|" << bal << endl;
        }

        file.close();
        temp.close();

        remove("bank.txt");
        rename("temp.txt", "bank.txt");

        if (found)
            cout << "\nAmount Deposited Successfully!\n";
        else
            cout << "\nAccount Not Found!\n";
    }

    void withdraw()
    {
        int searchAcc;
        float amount;
        bool found = false;

        cout << "\nEnter Account Number: ";
        cin >> searchAcc;

        cout << "Enter Withdrawal Amount: ";
        cin >> amount;

        ifstream file("bank.txt");
        ofstream temp("temp.txt");

        string line;

        while (getline(file, line))
        {
            int pos1 = line.find('|');
            int pos2 = line.rfind('|');

            int acc = stoi(line.substr(0, pos1));
            string cname = line.substr(pos1 + 1, pos2 - pos1 - 1);
            float bal = stof(line.substr(pos2 + 1));

            if (acc == searchAcc)
            {
                found = true;

                if (amount <= bal)
                {
                    bal -= amount;
                    cout << "\nWithdrawal Successful!\n";
                }
                else
                {
                    cout << "\nInsufficient Balance!\n";
                }
            }

            temp << acc << "|" << cname << "|" << bal << endl;
        }

        file.close();
        temp.close();

        remove("bank.txt");
        rename("temp.txt", "bank.txt");

        if (!found)
            cout << "\nAccount Not Found!\n";
    }

    void checkBalance()
    {
        int searchAcc;
        bool found = false;

        cout << "\nEnter Account Number: ";
        cin >> searchAcc;

        ifstream file("bank.txt");
        string line;

        while (getline(file, line))
        {
            int pos1 = line.find('|');
            int pos2 = line.rfind('|');

            int acc = stoi(line.substr(0, pos1));
            string cname = line.substr(pos1 + 1, pos2 - pos1 - 1);
            float bal = stof(line.substr(pos2 + 1));

            if (acc == searchAcc)
            {
                cout << "\nCurrent Balance: " << bal << endl;
                found = true;
                break;
            }
        }

        if (!found)
            cout << "\nAccount Not Found!\n";

        file.close();
    }
};

int main()
{
    BankAccount b;
    int choice;

    do
    {
        cout << "\n==============================";
        cout << "\n BANK MANAGEMENT APPLICATION";
        cout << "\n==============================";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit Money";
        cout << "\n3. Withdraw Money";
        cout << "\n4. Check Balance";
        cout << "\n5. Search Account";
        cout << "\n6. Display All Accounts";
        cout << "\n7. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                b.createAccount();
                break;

            case 2:
                b.deposit();
                break;

            case 3:
                b.withdraw();
                break;

            case 4:
                b.checkBalance();
                break;

            case 5:
                b.searchAccount();
                break;

            case 6:
                b.displayAccounts();
                break;

            case 7:
                cout << "\nThank You!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while(choice != 7);

    return 0;
}
