#include<iostream>
#include<math.h>
#include<string>
#include<fstream>
#include<iomanip>
#include<sstream>

using namespace std;

class Finance {

private:

    string exp_name;
    string exp_date;
    
    int no_exp = 0;
    int category;

    float total_expenses = 0;
    float total_expense2 = 0;
    float amt;
    float food = 0;
    float bills = 0;
    float shopping = 0;
    float misc = 0;
    float fun = 0;
    float cash = 0;
    float budget = 0;

    fstream Expenses;
    fstream Budget;


public:

    // Function to create or reset the expense file
    void CreateExpenseFile(int choice) {
        if(!choice){
            cout<<"Reseting data..";
            Expenses.open("Expenses.txt", ios::out);
        }
        else{
            cout<<"Continuing with previous data...";
            Expenses.open("Expenses.txt");
        }
        if (Expenses.is_open()) {
            Expenses << setw(15) << left << "Expense Name"
                     << setw(25) << right << "Date" 
                     << setw(25) << right << "Category"
                     << setw(25) << right << "Amount (INR)"<< endl;
                         
            Expenses.close();
        }
    }

    // Function to add expenses to file
    void AddExpensesToFile() {
        Expenses.open("Expenses.txt", ios::app);
        if (Expenses.is_open()) {
            Expenses << setw(15) << left << exp_name
                     << setw(25) << right << exp_date
                     << setw(25) << right << getCategoryName(category) 
                     << setw(25) << right << amt<< endl;
                     
            Expenses.close();
        }
    }

    // Function to create or reset the budget file
    void CreateBudgetFile(int choice) {
        
        if(!choice){
            Budget.open("Budget.txt", ios::out);
        }
        else{
            Budget.open("Budget.txt");
            //budget= last element of budget
            ifstream file("Budget.txt");
            string line;
            while (getline(file,line)) {
                stringstream ss(line);
                float bud;
                ss >> bud;
                if (ss) {
                    budget = bud; // Update last budget only if conversion was successful
                }
            }
        }
        if (Budget.is_open()) {
            Budget << setw(15) << left << "Budget (INR)"
                   <<setw(15)<<right<<"Date"<< endl; 
            Budget.close();
        }
    }

    // Function to add expenses to file
    void AddBudgetToFile() {
        Budget.open("Budget.txt", ios::app);
        if (Budget.is_open()) {
            Budget << setw(15) << left << budget
                   <<setw(15)<<right<<exp_date<< endl;
            Budget.close();
        }
    }

    // Function to add money to the budget
    void AddMoney() {
        cout << "Enter Amount (INR): ";
        cin >> cash;
        Cash:
        if (cash <= 0) {
            cout << "Invalid Input!" << endl;
            goto Cash;
        }
        cout << "\nYou've added INR " << cash << " to your Budget" << endl;
        budget += cash;
    
        Date:
        exp_date="";
        cout << "Enter Deposit Date (DD-MM-YYYY FORMAT ONLY): ";
        // cin.ignore();
        // getline(cin, exp_date);
        cin>>exp_date;
        if (exp_date.length() != 10 || exp_date[2] != '-' || exp_date[5] != '-') {
            cout<<"\nWrong format"<<endl;
            goto Date;
        }

        AddBudgetToFile();
    }

    // Function to add an expense
    void AddExpense() {
        AddExpense:
        cout << "\nEnter Expense Name: ";
        cin.ignore();
        getline(cin, exp_name);

        Amt:
        cout << "Enter Expense Amount (INR): ";
        cin >> amt;
        if (amt <= 0) {
            cout << "Invalid Input!" << endl;
            goto Amt;
        }

        Date:
        exp_date="";
        cout << "Enter Expense Date (DD-MM-YYYY FORMAT ONLY): ";
        cin>>exp_date;
        if (exp_date.length() != 10 || exp_date[2] != '-' || exp_date[5] != '-') {
            cout<<"\nWrong format"<<endl;
            goto Date;
        }


        cout << "\nSelect a Category" << endl;
        cout << "1. Food" << endl;
        cout << "2. Shopping" << endl;
        cout << "3. Bills & Utilities" << endl;
        cout << "4. Fun" << endl;
        cout << "5. Miscellaneous" << endl; 

        Category:
        cout << "\nEnter Your Category Number [1-5]: ";
        cin >> category;
        if (category < 1 || category > 5) {
            cout << "Invalid Input!" << endl;
            goto Category;
        }

        // Update total expenses and category expenses
        total_expenses += amt;
        // total_expense2 += amt; //for budget
        no_exp++;
        switch(category) {
            case 1:
                food += amt;
                break;
            case 2:
                shopping += amt;
                break;
            case 3:
                bills += amt;
                break;
            case 4:
                fun += amt;
                break;
            case 5:
                misc += amt;
                break;
        }
        
        budget -= amt;
        // Add expenses to file
        AddExpensesToFile();
        AddBudgetToFile();

        cout << "\nYou've added " << exp_name << " (INR " << amt << ") to your Expenses on "<<exp_date<<" "<< endl;
        cout << "You have " << no_exp << " expenses totalling: INR " << total_expenses << endl;


        // Ask user if they want to add more expenses
        int addmore;
        cout << "\nDo you want to add more Expenses?" << endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;

        Addmore:
        cout << "\nEnter Your Choice [1-2]: ";
        cin >> addmore;
        if (addmore != 1 && addmore != 2) {   
            cout << "Invalid Input!" << endl;
            goto Addmore;
        }
        if (addmore == 1)
            goto AddExpense;
    }


    // Function to display the remaining budget
    void DisplayBudget() {
       // budget -= total_expense2;
        if (budget < 0) {
            cout << "\n!!!Budget Overdrawn!!!" << endl;
        }
        // total_expense2 = 0;
        cout << "\nBudget" << endl;
        cout << "You have INR " << budget << endl;
    }

    // Function to display expenses by category
    void DisplayExpense() {
        cout << "\nExpenses by Category" << endl;
        cout << "Food: INR " << food << endl;
        cout << "Shopping: INR " << shopping << endl;
        cout << "Bills & Utilities: INR " << bills << endl;
        cout << "Fun: INR " << fun << endl;
        cout << "Miscellaneous: INR " << misc << endl;
        cout << "\nTotal Expenses: INR " << total_expenses << endl;
        // Display all expenses from file
        cout << "\n---------------------------------------------------------------------------------------------------" << endl;
        DisplayAllExpenses();
    }

    

    // Function to get category name from category number
    string getCategoryName(int category) {
        switch(category) {
            case 1:
                return "Food";
            case 2:
                return "Shopping";
            case 3:
                return "Bills_&_Utilities";
            case 4:
                return "Fun";
            case 5:
                return "Miscellaneous";
            default:
                return "Unknown";
        }
    }

    // Function to display all expenses from file with category
    void DisplayAllExpenses() {
        Expenses.open("Expenses.txt", ios::in);
        if (Expenses.is_open()) {
            string line;
            while (getline(Expenses, line)) {
                cout << line << endl;
            }
            Expenses.close();
        }
    }


    // Function to plot expenses using matplotlib in Python
    void PlotExpenses() {
        system("python3 plot_expenses.py");
    }
};

// Main function
int main() {
    Finance f;
    int choice,ch;
    cout<<"Do you want to reset data or continue with previous data.\n1.Enter 1 to continue\n2.Enter 0 to reset\nEnter choice : ";
    cin>>ch;
    f.CreateExpenseFile(ch);
    f.CreateBudgetFile(ch);
    if(!ch)
        f.AddBudgetToFile();


    
while (true){

    cout << "\nWelcome to Expense Tracker!" << endl;
    cout << "---------------------------------------------------------------------------------------------------" << endl;
    cout << "1. Show Budget" << endl;
    cout << "2. Show Expenses" << endl;
    cout << "3. Add Money" << endl;
    cout << "4. Add Expenses" << endl;
    cout << "5. Plot Expenses" << endl; 
    cout << "6. Exit" << endl;
    cout << "---------------------------------------------------------------------------------------------------" << endl;

    cout << "\nEnter Your Choice [1-5]: ";
    cin >> choice;
    if (choice < 1 || choice > 6) {
        cout << "Invalid Input!" << endl;
        continue;
    }

    switch(choice) {
        case 1:
            f.DisplayBudget();
            break;
        case 2:
            f.DisplayExpense();
            break;
        case 3:
            f.AddMoney();
            break;
        case 4:
            f.AddExpense();
            break;
        case 5:
            f.PlotExpenses(); 
            break;
        case 6:
            return 0;
    }
}
return 0;
}

