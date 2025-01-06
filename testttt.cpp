#include <iostream>
#include <conio.h>
#include <windows.h>
#include <limits>
#include <fstream>

using namespace std;





void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


void resetColor() {
    const int WHITE = 15;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}


struct Cars {
    string mark[10] = {"Hyundai", "BMW", "Mercedes", "Audi", "Tesla", "Skoda", "Volkswagen", "Toyota", "Ford"};
    string model[10] = {"2016MD", "2018AS", "2018DS", "2017LA", "2018OW", "2005Ps", "2008PW", "2010QW", "2016SA"};
    string color[10] = {"Red", "Black", "Yellow", "Blue", "Red", "Brown", "Silver", "Black", "Grey"};
    string max_speed[10] = {"100 Km/h", "150 Km/h", "150 Km/h", "170 Km/h", "130 Km/h", "140 Km/h", "130 Km/h", "120 Km/h", "150 Km/h"};
    int price[10] = {2999, 1499, 2999, 4999, 1999, 3599, 3999, 5999, 9999};
    int date[10] = {2010, 2012, 2013, 2017, 2018, 2005, 2008, 2010, 2014};
};


struct Lessee {
    string fname[10];
    string lname[10];
    string nid[10];
    int pno[20];
    int payment_acc[10];
    int days[10];
};


Cars car;
Lessee lessee;

void Menu() {
    int num = 1;
    for (int i = 0; i < 9; ++i) {
        cout << "\t\t\t";
        cout << "Enter " << num << "\t- To Select " << car.mark[i] << endl;
        num++;
    }
}
bool user_input(int theChoice) {
    system("CLS");
    const int GREEN = 10;
    int j = theChoice - 1;

    cout << "\t\t\t----------------------------------------\n";
    setColor(GREEN);
    cout << "\t\t\tPlease Provide Your Personal Details  : \n";
    resetColor();
    cout << "\t\t\t----------------------------------------\n\n";
    cout << "\033[31m\n\tNOTE:\033[0m\n\tDO NOT ENTER SPACE WHILE PROVIDING NAME,\n\tPAYMENT WON'T PROCEED IF THE GIVEN AMOUNT IS LESS THAN THE RENT AMOUNT OF ONE DAY\n" << endl;
    cout << "\n\tYou have to pay the rent amount of selected car of one day minimum RS:"<<car.price[j]<<" in advance!\n\n\n\n" << endl;

    cout << "\tEnter Your First Name: ";
    cin >> lessee.fname[j];
    if (lessee.fname[j] == "back") return false;
    cout << "\tEnter Your Last Name: ";
    cin >> lessee.lname[j];
    cout << "\tEnter Your National ID number: ";
    cin >> lessee.nid[j];
    //cout << "\tEnter Your Phone number: ";
    //cin>>lessee.pno[j];
    cout << "\tNumber of days you wish to rent the car: ";
    //cin>>lessee.days[j];
    while (!(cin >> lessee.days[j]) || lessee.days[j] <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\tInvalid input. Please enter a positive number: ";
    }
    cout << "\tAdvance Payment Amount: ";
    cin >> lessee.payment_acc[j];

    const int RED = 12;
    if (lessee.payment_acc[j] >= car.price[j]&& lessee.payment_acc[j]<car.price[j]*car.price[j]) {
        setColor(GREEN);
          system("CLS");
        cout << "\n\n\n\tProcess has been done successfully!! " << endl;
          resetColor();
    } else {
        setColor(RED);
        cout << "PROCESS PENDING! minimum payable Advance Amount: Rs." << car.price[j] << " and maximum Advance Amounte: Rs"<<lessee.days[j]*car.price[j]<<endl; cout<<" paid first to complete your order!" << endl;
       resetColor();
        system("PAUSE");
       // return false;
       return user_input(theChoice); // Loop until correct payment is made or back is selected
    }
    
    return true;
}

// Function to print the invoice
void printInvoice(int theChoice) {
  
    
    int j = theChoice - 1;

    cout << "\n\n                      GOCARO Car Rental - Customer Invoice                  " << endl;
    cout << "    ///////////////////////////////////////////////////////////" << endl;
    cout<<  "    | Car Selected:-------------------|" <<car.mark[j]<<endl;
    cout<<  "    | Car color:----------------------|"<<car.color[j]<<endl;
    cout << "    | Customer Name: " << "-----------------|" << lessee.fname[j] + " " + lessee.lname[j] << endl;
    //cout<<  "    | phone number:-------------------|" <<lessee.pno <<endl;
    cout << "    | National ID number:" << "-------------|" << lessee.nid[j] << endl;
    cout << "    | Number of days: " << "----------------|" << lessee.days[j] << " days" << endl;
    cout << "    | Advance payment Amount is: " << "-----|Rs." << lessee.payment_acc[j] << endl;
    cout << "\n";
    cout << "    ________________________________________________________" << endl;
    cout << "    | Total Rental Amount is: " << "--------|Rs." << lessee.days[j] * car.price[j] << endl;
    cout << "    | Less: Advance Payment Amount: " << "--|Rs." << lessee.payment_acc[j] << endl;
    cout << "    | Dues Amount: " << "-------------------|Rs." << lessee.days[j] * car.price[j] - lessee.payment_acc[j] << endl;
    cout << "    ________________________________________________________" << endl;

    // Save invoice to file
    ofstream outFile("invoice.txt"); // Open file in append mode
    if (outFile.is_open()) {
        outFile << "\n\n                      GOCARO Car Rental - Customer Invoice                  " << endl;
        outFile << "    ///////////////////////////////////////////////////////////" << endl;
        outFile<<  "    | Car Name:----------------------------|"<<car.mark[j]<<endl;
        outFile << "    | Customer Name: " << "----------------|" << lessee.fname[j] + " " + lessee.lname[j] << endl;

        //outFile << "    | National Phone number:" << "------------|" << lessee.pno[j] << endl;
        outFile << "    | National ID number:" << "------------|" << lessee.nid[j] << endl;
        outFile << "    | Number of days: " << "---------------|" << lessee.days[j] << " days" << endl;
        outFile << "    | Advance payment Amount is: " << "----|Rs." << lessee.payment_acc[j] << endl;
        outFile << "\n";
        outFile << "    ________________________________________________________" << endl;
        outFile << "    | Total Rental Amount is: " << "-------|Rs." << lessee.days[j] * car.price[j] << endl;
        outFile << "    | Less: Advance Payment Amount: " << "--|Rs." << lessee.payment_acc[j] << endl;
        outFile << "    | Dues Amount: " << "-------------------|Rs." << lessee.days[j] * car.price[j] - lessee.payment_acc[j] << endl;
        outFile << "    ________________________________________________________" << endl;
        outFile.close();
        cout << "\nInvoice saved to file successfully.\n";
    } else {
        cout << "\nError opening file to save invoice.\n";
    }
}

// Function to display car details
bool Details(int theChoice) {
    const int GREEN = 10;
    string decide = "yes";
    system("CLS");
    cout << "\n\n\n\t\t\t -----------------------------\n";
    setColor(GREEN);
    cout << "\t\t\t You Have Selected - " << car.mark[theChoice - 1] << endl;
    resetColor();
    cout << "\t\t\t -----------------------------\n\n\n";
    cout << "\t\t\t |Model : " << car.model[theChoice - 1] << endl;
    cout << "\t\t\t |Color : " << car.color[theChoice - 1] << endl;
    cout << "\t\t\t |Maximum Speed : " << car.max_speed[theChoice - 1] << endl;
    cout << "\t\t\t |Rent Amount : Rs." << car.price[theChoice - 1] << " per day" << endl;
    cout << "\n\n\n\t\t\tAre You Sure, you want to rent this Car? (yes /back /exit) : ";
    cin >> decide;

    if (decide == "yes") {
        return user_input(theChoice);
    } else if (decide == "no" || decide == "back") {
        return false;
    } else if (decide == "exit") {
        system("CLS");
        cout << "\n\n\n\t\t\tThank you! Our car rental service is available 24/7.";
        exit(0);
    } else {
        system("CLS");
        cout << "\n\n\t\t\tInvalid input. Please choose 'yes', 'no', 'back', or 'exit'.";
        return Details(theChoice);
    }
    return true;
}

int login() {
    string pass = ""; // String to handle the 10-digit phone number
    int ch;
    const int GREEN = 10;
    const int YELLOW = 14;
    const int WHITE = 15;
    const int RED = 12;

    setColor(GREEN);
    cout << "\n\n\t\t\t\t\tGOCARO CAR RENTAL SYSTEM";
    resetColor();
    cout << "\n\n\t\t\t\t\t------------------";
    setColor(WHITE);
    cout << "\n\t\t\t\t\tLOGIN";
    resetColor();
    cout << "\n\t\t\t\t\t------------------";
    setColor(YELLOW);
    cout << "\n\n\t\t\t\t\tEnter your phone number: ";
    resetColor();

    while (true) {
        ch = _getch();
        if (ch == 13 && pass.length() == 10) { 
            break;
        } else if (ch == 8 && !pass.empty()) { 
            pass.pop_back();
            cout << "\b \b"; 
        } else if (isdigit(ch) && pass.length() < 10) { 
            pass.push_back(ch);
            cout << char(ch);
        }
    }

    if (pass.length() == 10) { 
        setColor(GREEN);
        cout << "\n\n\n\t\t\t\tAccess Granted! Welcome To Our System \n\n";
        resetColor();
        system("PAUSE");
        system("CLS");
    } else {
        setColor(RED);
        cout << "\n\n\n\n\t\t\t\t\tAccess Aborted...Please Try Again!!\n";
        resetColor();
        system("PAUSE");
        system("CLS");
        return login(); 
    }
    

    return 0;
}

int main() {
    login();

    cout << "\t\t\t-------------------------------------------\n" << endl;
    const string GREEN = "\033[32m";
    const string RESET = "\033[0m";
    string decide = "yes";

    cout << GREEN << "\t\t\tWelcome to GOCARO CAR RENTAL SYSTEM \n" << RESET << endl;
    cout << "\t\t\t-------------------------------------------\n" << endl;
    cout << "\t\t\tSelect your desired car from the menu: " << endl;
    cout << "\t\t\t-------------------------------------------\n";

    while (decide != "exit") {
        Menu();
        cout << "\n\n\n\t\t\tYour Choice (or type 'exit' to quit): ";
        string input;
        cin >> input;
        if (input == "exit") {
            break;
        }
        int theChoice;
        try {
            theChoice = stoi(input);
        } catch (invalid_argument&) {
            cout << "\t\t\tInvalid choice. Please enter a number between 1 and 9: ";
            continue;
        }

        if (theChoice < 1 || theChoice > 9) {
            cout << "\t\t\tInvalid choice. Please enter a number between 1 and 9: ";
            continue;
        }

        bool proceed = Details(theChoice);
        if (!proceed) {
            continue;
        }
        

        printInvoice(theChoice);

        cout << "\n\n\n\t\t\tDo you want to select another car? (yes / exit): ";
        cin >> decide;
        if (decide == "exit") {
            system("CLS");
            cout << "\n\n\n\t\t\tThank you! Our car rental service is available 24/7.";
        }
    }

    return 0;
}
