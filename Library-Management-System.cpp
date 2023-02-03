#include <iostream>
#include <iomanip>
#include <string>
#include <process.h>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <conio.h>

using namespace std;

HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);   //USED IN set_console_settings FUNCTION

void set_console_settings();
void menu(string users[10][7], string books[50][5]);
void loadfile(string users[10][7],string books[50][5]);
void savefile(string users[10][7], string books[50][5]);

void adduser(string users[10][7], string books[50][5]);
void deleteuser(string users[10][7], string books[50][5]);
void searchuser(string users[10][7], string books[50][5]);
void loanbook(string users[10][7], string books[50][5]);
void returnbook(string users[10][7], string books[50][5]);
void displayusers(string users[10][7], string books[50][5]);
void displaybooks(string users[10][7], string books[50][5]);
void exitprogram(string users[10][7], string books[50][5]);
void bubblesort(string users[10][7]);


int main()
{
    string users[10][7];
    string books[50][5];
    cout << "Welcome to Library Management System!" << endl;
    set_console_settings();
    loadfile(users, books);
    menu(users, books);
    return 0;
}

void set_console_settings() 
{
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_SHOWMAXIMIZED);         //MAKING CONSOLE FULLSCREEN

    PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();    //INCREASING FONT SIZE
    lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
    lpConsoleCurrentFontEx->dwFontSize.X = 35;
    lpConsoleCurrentFontEx->dwFontSize.Y = 35;
    SetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
}

void menu(string users[10][7], string books[50][5])
{
    int Set[] = { 12,7,7,7,7,7,7,7 }; // DEFAULT COLORS
    int counter = 1;
    char key;

    while (true)
    {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << "Please choose from the following options:" << endl << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[0]);
        cout << "1) Add new user" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[1]);
        cout << "2) Delete an existing user" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[2]);
        cout << "3) Search user and their outstanding books" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[3]);
        cout << "4) Loan book to user" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[4]);
        cout << "5) Return book from user" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[5]);
        cout << "6) Display list of users" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[6]);
        cout << "7) Display list of books and their status" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[7]);
        cout << "8) Exit program" << endl << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << "(USE ARROW KEYS TO NAVIGATE AND ENTER KEY TO SELECT)";

        key = _getch();

        if (key == 72 && (counter >= 2 && counter <= 8))
            counter--;
        if (key == 80 && (counter >= 1 && counter <= 7))
            counter++;
        if (key == '\r')		//ENTER KEY
        {
            switch (counter)
            {
            case 1:
                adduser(users, books);
                break;
            case 2:
                deleteuser(users, books);
                break;
            case 3:
                searchuser(users, books);
                break;
            case 4:
                loanbook(users, books);
                break;
            case 5:
                returnbook(users, books);
                break;
            case 6:
                displayusers(users, books);
                break;
            case 7:
                displaybooks(users, books);
                break;
            case 8:
                exitprogram(users, books);
                break;
            }
        }

        Set[0] = 7;
        Set[1] = 7;
        Set[2] = 7;
        Set[3] = 7;
        Set[4] = 7;
        Set[5] = 7;
        Set[6] = 7;
        Set[7] = 7;

        Set[counter - 1] = 12;
    }
}

void loadfile(string users[10][7], string books[50][5])
{
    ifstream readfile;
    readfile.open("datafile.txt");
    if (!readfile) 
    {
        cout << "Error loading file";
        return;
    }
    int numusers, numbooks;
    
    readfile >> numusers;
    readfile >> numbooks;

    for (int user=0; user < numusers; user++)
    {
        for (int userdata = 0; userdata < 7; userdata++) 
        {
            readfile >> users[user][userdata];
            if (userdata == 1)
                replace(users[user][userdata].begin(), users[user][userdata].end(), '_', ' ');
        }   
    }

    for (int book = 0; book < numbooks; book++)
    {
        for (int bookdata = 0; bookdata < 5; bookdata++)
        {
            readfile >> books[book][bookdata];
            if (bookdata == 1 || bookdata == 3)
                replace(books[book][bookdata].begin(), books[book][bookdata].end(), '_', ' ');
        }
    }
    cout << "Previous records retreived successfully" << endl << endl;
    readfile.close();
}

void savefile(string users[10][7], string books[50][5])
{
    ofstream savefile;
    savefile.open("datafile.txt");
    if (!savefile)
    {
        cout << "Error loading file for saving";
        return;
    }
    int numusers, numbooks;

    for (numusers = 0; numusers < 10; numusers++)
    {
        if (users[numusers][0] == "")
            break;
    }

    for (numbooks = 0; numbooks < 50; numbooks++)
    {
        if (books[numbooks][0] == "")
            break;
    }

    savefile << numusers << endl << numbooks << endl << endl;    

    for (int user = 0; user <= numusers; user++)
    {
        for (int userdata = 0; userdata < 7; userdata++)
        {
            if (userdata == 1)
                replace(users[user][userdata].begin(), users[user][userdata].end(), ' ', '_');
            savefile << users[user][userdata] << "\t";
        }
        savefile << endl;
    }

    for (int book = 0; book <= numbooks; book++)
    {
        for (int bookdata = 0; bookdata < 5; bookdata++)
        {
            if (bookdata == 1 || bookdata == 3)
                replace(books[book][bookdata].begin(), books[book][bookdata].end(), ' ', '_');
            savefile << books[book][bookdata] << "\t";
        }
        savefile << endl;
    }
    cout << "Changes saved successfully" << endl << endl;
    savefile.close();
}

void adduser(string users[10][7], string books[50][5])
{
    system("cls");
    if (users[9][0] != "") {                                            //CHECKS LAST ENTRY IN USERS ARRAYS...IF IT IS OCCUPIED THEN THERE ARE ALREADY 10 USERS REGISTERED
        cout << "Maximum users have already been registered!" << endl
            << "Delete user and try again" << endl << endl
            << "Returning to menu..." << endl;
        system("pause");
        menu(users, books);
    }
    
    for (int counter = 0; counter < 10; counter++)
    {
        if (users[counter][0] == "") 
        {    
            cout << "Adding new user" << endl
                << "Enter Reg-number:\t";
            string temp;
            cin >> temp;
            {   //CHECKING IF USER WITH SAME REG NUMBER ALREADY EXISTS
                for (int repetitive_check = 0; repetitive_check < counter; repetitive_check++)
                    if (users[repetitive_check][0] == temp)
                    {
                        cout << endl << "User with this Reg-number already exists!" << endl
                            << "Please try again with a different user!" << endl;
                        system("pause");
                        menu(users, books);
                    }
            }
            users[counter][0] = temp;
            cout << "Enter full name:\t";
            cin.ignore();
            getline(cin, users[counter][1]);
            cout << "Enter age:\t\t";
            cin >> temp;
            {   //CONFIRMING AGE BETWEEN SET VALUES
                bool isadigit = true;
                for (int i = 0; i < temp.length(); i++)
                    if (isdigit(temp[i]) == false)
                        isadigit = false;

                while (!isadigit || stoi(temp) < 5 || stoi(temp) > 101)
                {
                    isadigit = true;
                    cout << "Age must be a number between 4 and 100!" << endl
                        << "Please enter again:\t";
                    cin >> temp;
                    for (int i = 0; i < temp.length(); i++)
                        if (isdigit(temp[i]) == false)
                            isadigit = false;
                }
            }
            users[counter][2] = temp;
            cout << "Enter contact-number:\t";
            cin >> users[counter][3];
            users[counter][4] = "none";
            users[counter][5] = "none";
            users[counter][6] = "none";
            cout << endl << "User successfully registered!" << endl;
            break;
        }     
    }
    system("pause");
    menu(users, books);
}

void deleteuser(string users[10][7], string books[50][5])
{
    system("cls");
    cout << "Enter the Reg-number of user to delete: ";
    string delete_id;
    cin >> delete_id;
    cout << endl;
    for (int u = 0; u < 10; u++)
    {
        if (u == 9 && users[u][0] != delete_id)
        {
            char choice;
            cout << "User with this ID does not exist!" << endl 
                << "Enter 'T' to try with another User ID or 'M' to return to the main menu: ";
            cin >> choice;
            if (choice == 'T' || choice == 't')
                deleteuser(users, books);
            else
                menu(users, books);

        }
        if (users[u][0] == delete_id)
        {
            
            int outstandingbooks = 0;
            if (users[u][4] != "none")
                outstandingbooks++;
            if (users[u][5] != "none")
                outstandingbooks++;
            if (users[u][6] != "none")
                outstandingbooks++;
            
            if (outstandingbooks != 0) 
            {
                cout << "User currently has " << outstandingbooks << " books issued!" << endl
                    << "Kindly return books from return book menu and try again to delete!" << endl << endl;
                system("pause");
                menu(users, books);
            }
            
            if (u == 9) 
                for (int z = 0; z < 7; z++)
                    users[9][z] = "";
            else 
                for (int y = u; y < 9; y++)
                    for (int z = 0; z < 7; z++)
                        users[y][z] = users[y + 1][z];

            
            cout << "User with id: " << delete_id << " successfully deleted" << endl << endl;
            system("pause");
            menu(users, books);
        }
    }
}

void searchuser(string users[10][7], string books[50][5])
{
    system("cls");
    cout << "Enter user id to search: ";
    string userid;
    cin >> userid;
        
    for (int u = 0; u < 10; u++)
    {
        if ((u == 9) && (users[u][0] != userid))
        {
            char choice;
            cout << "User not found!" << endl << "Enter 'T' to try with another User ID or 'M' to return to the main menu: ";
            cin >> choice;
            if (choice == 'T' || choice == 't')
                searchuser(users, books);
            else
                menu(users, books);
        }
        if (users[u][0] == userid) 
        {
            int outstandingbooks = 0;
            if (users[u][4] != "none")
                outstandingbooks++;
            if (users[u][5] != "none")
                outstandingbooks++;
            if (users[u][6] != "none")
                outstandingbooks++;

            cout << endl << "User ID:\t\t" << userid << endl
                << "User name:\t\t" << users[u][1] << endl
                << "User Age:\t\t" << users[u][2] << endl
                << "User Contact:\t\t" << users[u][3] << endl
                << "Outstanding books:\t" << outstandingbooks << " / 3" << endl << endl
                << "Outstanding books details:" << endl << endl
                << left << setw(10) << "|S. no." 
                << left << setw(10) << "|Book ID" 
                << left << setw(25) << "|Book Title" 
                << left << setw(15) << "|ISBN" 
                << left << setw(25) << "|Author" << endl;
            
            for (int outbooks = 1; outbooks <= outstandingbooks; outbooks++)
                for (int book = 0; book < 50; book++)
                    if (books[book][0] == users[u][outbooks + 3])
                        cout << left << setw(10) << ("|" + to_string(outstandingbooks))
                        << left << setw(10) << ("|" + books[book][0])
                        << left << setw(25) << ("|" + books[book][1])
                        << left << setw(15) << ("|" + books[book][2])
                        << left << setw(25) << ("|" + books[book][3]) << endl;

            cout << endl << endl;
            system("pause");
            menu(users, books);
        }
    }      
}

void loanbook(string users[10][7], string books[50][5])
{    
    system("cls");
    cout << "Enter user id: ";
    string userid;
    cin >> userid;

    for (int u = 0; u < 10; u++)
    {
        if ((u == 9) && (users[u][0] != userid))                //CHECK USER EXISTS 
        {
            char choice;
            cout << "User not found!" << endl << "Enter 'T' to try with another User ID or 'M' to return to the main menu: ";
            cin >> choice;
            if (choice == 'T' || choice == 't')
                loanbook(users, books);
            else
                menu(users, books);
        }       
        if (users[u][0] == userid)
        {
            int outstandingbooks = 0;
            if (users[u][4] != "none")
                outstandingbooks++;
            if (users[u][5] != "none")
                outstandingbooks++;
            if (users[u][6] != "none")
                outstandingbooks++;

            if (outstandingbooks == 3)         //CHECK IF ALREADY 3 BOOKS
            {
                char choice;
                cout << "The user already has maximum number of issued books!" << endl << "Enter 'T' to try with another User ID or 'M' to return to the main menu: ";
                cin >> choice;
                if (choice == 'T' || choice == 't')
                    loanbook(users, books);
                else
                    menu(users, books);
            }    

            cout << "Enter book id: ";
            string bookid;
            cin >> bookid;

            for (int b = 0; b < 50; b++) 
            {
                if ((b == 49) && (books[b][0] != bookid))   //CHECK IF BOOK EXISTS
                {
                    char choice;
                    cout << "Book not found!" << endl << "Enter 'T' to try again or 'M' to return to the main menu: ";
                    cin >> choice;
                    if (choice == 'T' || choice == 't')
                        loanbook(users, books);
                    else
                        menu(users, books);
                }

                if (books[b][0] == bookid)
                {
                    if (books[b][4] != "Available")     //CHECK IF BOOK AVAILABLE
                    {
                        char choice;
                        cout << "Book is currently issued to another user!" << endl 
                            << "Enter 'T' to try with another Book ID or 'M' to return to the main menu: ";
                        cin >> choice;
                        if (choice == 'T' || choice == 't')
                            loanbook(users, books);
                        else
                            menu(users, books);
                    }

                    books[b][4] = users[u][0];

                    if (users[u][4] == "none")
                        users[u][4] = books[b][0];
                    else if (users[u][5] == "none")
                        users[u][5] = books[b][0];
                    else if (users[u][6] == "none")
                        users[u][6] = books[b][0];

                    cout << endl << "Book with ID " << books[b][0] << " successfuly isssued to User with ID " << users[u][0] << endl << endl;
                    system("pause");
                    menu(users, books);
                }
            }
        }
    }
}

void returnbook(string users[10][7], string books[50][5])
{
    system("cls");
    cout << "Enter user id : ";
    string userid;
    cin >> userid;

    for (int u = 0; u < 10; u++)
    {
        if ((u == 9) && (users[u][0] != userid))
        {
            char choice;
            cout << "User not found!" << endl << "Enter 'T' to try with another User ID or 'M' to return to the main menu: ";
            cin >> choice;
            if (choice == 'T' || choice == 't')
                returnbook(users, books);
            else
                menu(users, books);
        }
        
        if (users[u][0] == userid)
        {
            int outstandingbooks = 0;
            if (users[u][4] != "none")
                outstandingbooks++;
            if (users[u][5] != "none")
                outstandingbooks++;
            if (users[u][6] != "none")
                outstandingbooks++;

            if (outstandingbooks == 0)         //CHECK IF NO BOOKS TO RETURN
            {
                char choice;
                cout << "The user already has no borrowed books!" << endl << "Enter 'T' to try with another User ID or 'M' to return to the main menu: ";
                cin >> choice;
                if (choice == 'T' || choice == 't')
                    returnbook(users, books);
                else
                    menu(users, books);
            }

            cout << "Current outstanding books:" << endl << endl
                << left << setw(10) << "|Book ID" 
                << left << setw(25) << "|Book Title" 
                << left << setw(15) << "|ISBN" 
                << "|Author" << endl;
            
            for (int book = 0; book < 50; book++)
            {
                if (books[book][0] == "")
                    break;
                if (books[book][4] == userid)
                    cout << left << setw(10) << ("|" + books[book][0]) 
                    << left << setw(25) << ("|" + books[book][1]) 
                    << left << setw(15) << ("|" + books[book][2]) 
                    << "|" << books[book][3] << endl;
            }

            cout << endl << endl << "Enter Book ID for book to return: ";
            string bookid;
            cin >> bookid;
            for (int book = 0; book < 50; book++)
            {
                if (book == 49 && books[book][book] != bookid)
                {
                    char choice;
                    cout << "Book does not exist" << endl 
                        << "Enter 'T' to try with another Book or 'M' to return to the main menu: ";
                    cin >> choice;
                    if (choice == 'T' || choice == 't')
                        returnbook(users, books);
                    else
                        menu(users, books);
                }

                if (books[book][0] == bookid) 
                {
                    if (books[book][4] != userid)
                    {
                        char choice;
                        cout << "This book was not borrowed by this user!" << endl << "Enter 'T' to try with another Book or 'M' to return to the main menu: ";
                        cin >> choice;
                        if (choice == 'T' || choice == 't')
                            returnbook(users, books);
                        else
                            menu(users, books);
                    }

                    if (books[book][4] == userid)
                    {
                        if (users[u][4] == bookid)
                            users[u][4] = "none";
                        else if (users[u][5] == bookid)
                            users[u][5] = "none";
                        else if (users[u][6] == bookid)
                            users[u][6] = "none";

                        books[book][4] = "Available";

                        cout << endl << "User with id " << userid << " has successfully returned book with id " << bookid << endl << endl;
                        system("pause");
                        menu(users, books);
                    }
                }
            }
        }
    }
}

void displayusers(string users[10][7], string books[50][5])
{
    system("cls");
    bubblesort(users);
    cout << "Sorted (by name) list of all registered users:" << endl << endl
        << left << setw(10) << "|User ID" << left << setw(35) << "|Name" << left << setw(7) << "|Age" << left << setw(20) << "|Contact number" << "|Issued books" << endl;
    for (int user = 0; user < 10; user++)
    {
        if (users[user][0] == "")
            break;
        int issuedbooks = 0;
        if (users[user][4] != "none")
            issuedbooks++;
        if (users[user][5] != "none")
            issuedbooks++;
        if (users[user][6] != "none")
            issuedbooks++;

        cout << left << setw(10) << ("|" + users[user][0]) << left << setw(35) << ("|" + users[user][1]) << left << setw(7) << ("|" + users[user][2]) << left << setw(20) << ("|" + users[user][3]) << "|" << issuedbooks << " / 3" << endl;
    }
    cout << endl;
    system("pause");
    menu(users, books);
}

void displaybooks(string users[10][7], string books[50][5])
{
    system("cls");
    cout << "List of all books:" << endl << endl
        << left << setw(10) << "|Book ID" << left << setw(20) << "|Book Title" << left << setw(15) << "|ISBN" << left << setw(25) << "|Author" << "|Status" << endl;
    for (int book = 0; book < 50; book++)
    {
        if (books[book][0] == "")
            break;

        cout << left << setw(10) << ("|" + books[book][0]) << left << setw(20) << ("|" + books[book][1]) << left << setw(15) << ("|" + books[book][2]) << left << setw(25) << ("|" + books[book][3]);
        cout << "|" << (books[book][4] == "Available" ? "Available" : ("Issued to user with id: " + books[book][4])) << endl;

    }
    cout << endl;
    system("pause");
    menu(users, books);
}

void exitprogram(string users[10][7], string books[50][5])
{
    system("cls");
    char s;
    cout << "Save changes to external file? (Y/N) : ";
    cin >> s;
    cout << endl;
    if (s == 'N' || s == 'n')
        cout << "Discarding changes..." << endl;
    else if (s == 'Y' || s == 'y')
    {
        cout << "Saving changes to file..." << endl;
        savefile(users, books);
    }
    else
    {
        cout << "Invalid entry! Please enter correct choice" << endl;
        exitprogram(users, books);
    }
    
    cout << "Exiting program" << endl;
    system("pause");
    exit(0);
}

void bubblesort(string users[10][7]) 
{
    for (int j = 10; j > 0; j--)
    {
        for (int i = 0; i < (j - 1); i++)
        {
            if (users[i+1][0] == "")
                break;
            if (users[i][1] > users[i + 1][1])
            {
                for (int u = 0; u < 7; u++)
                {
                    swap(users[i][u], users[i + 1][u]);
                }

            }
        }
    }
}
