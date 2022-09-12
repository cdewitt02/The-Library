#include <iostream>
#include <fstream>

using namespace std;

int intro();
void NewMember();
void CurrMember();
void Admin();
void displayFile(string const &username);
bool IsMember(string const &username);
void BookReturn(string const &username, string const &password);
void BookCheckOut(string const &username, string const &password);


int intro(){
    int option;
    cout<<"\n\t\t\t\tWelcome to The Library\n";
    cout<<"Please select an option by entering the corresponding number:\n\n";
    cout<<"1. New Member\n";
    cout<<"2. Current Member\n";
    cout<<"3. Administration\n\n";
    cout<<"INPUT: "; cin>>option;


    while(option < 1 || option > 3){
        cout<<"Invalid input try again\n";
        cout<<"INPUT: "; cin>>option;
    }

    return option;

}

void NewMember(){
    string username, password; char input;

    cout<<"\nEnter new username (no spaces): "; cin >> username;
    cout<<"Enter new password (no spaces): "; cin >> password;

    if(IsMember(username)){
        string user = username;
        while(user == username){
            cout<<"\nSorry that username is already taken\n";
            cout<<"Enter new username (no spaces): "; cin >> username;
            cout<<"Enter new password (no spaces): "; cin >> password;
            if(!IsMember(username)){
                user = "";
            }
        }
    }

    ofstream file;
    file.open(R"(c:\Users\charl\CLionProjects\TheLibrary\LibraryMembers\)" + username + ".txt"); //file location may have to change depending on device
    file<<username<<endl<<password;
    file.close();

    cout<<"\nNew Member "<< username<< " created\n";

    cout<<"Would you like to log in to new account? (Y/N)";cin>>input;

    if(input == 'y' || input == 'Y'){
        CurrMember();
    }
}

void CurrMember(){ //logging in to current account, account functions: checkout book, return book, logout
    string username, password, un, pw;
    int input; char flag = 'n';

    cout<<"\nEnter username: "; cin >> username;
    cout<<"Enter password: "; cin >> password;

    if(!IsMember(username)) {
        string user = username;
        while (user == username) {
            cout << "\nUser not found in system\n";
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            if (IsMember(username))
                user = "";
        }
    }

    ifstream read(R"(c:\Users\charl\CLionProjects\TheLibrary\LibraryMembers\)" + username + ".txt"); //file location may have to change depending on device
    getline(read, un);
    getline(read, pw);


    while(pw != password) {
        cout << "\nPassword incorrect\n";
        cout << "Enter password: ";cin >> password;
    }

    cout<<"\nLogged in as "<<username<<endl;

    while(flag == 'n' || flag == 'N') {
        cout << "\nWhat would you like to do? (enter corresponding number) " << endl;
        cout << "1. Check out book" << endl;
        cout << "2. Return book" << endl;
        cout << "3. Logout" << endl;
        cout << "\nINPUT: ";
        cin >> input;

        if (input == 3)
            return;
        else if (input == 2)
            BookReturn(username, password);
        else if(input == 1)
            BookCheckOut(username, password);

        cout<<"\nWould you like to log out? (Y/N)"<<endl;
        cout<<"INPUT: "; cin>>flag;
    }
}
void BookCheckOut(string const &username, string const &password){ //checks out 1 or 2 books depending on user input
    string book1, book2, un, pw, temp1, temp2; int num = 0; int flag = 0;
    cout<<"\nWould you like to check out 1 or 2 books?";
    cout<<"\nINPUT: ";cin>>num;

    if(!(num == 1 || num == 2))
        flag = 1;
    while (flag == 1){
        cout<<"\nInvalid input try again: ";cin>>num;
        if(num == 1 || num == 2)
            flag = 0;
    }

    ifstream read;
    read.open(R"(c:\Users\charl\CLionProjects\TheLibrary\LibraryMembers\)" + username + ".txt"); //file location may have to change depending on device
    getline(read, un); getline(read, pw); getline(read, temp1);getline(read, temp2);

    if(num == 1) {
        if(temp1 == "" && temp2 == ""){
            cout << "Enter Book Name (use _ for spaces): ";cin >> book1;
            ofstream file;
            file.open(R"(c:\Users\charl\CLionProjects\TheLibrary\LibraryMembers\)" + username + ".txt"); //file location may have to change depending on device
            file << username << endl << password << endl << book1;
            file.close();
        }
        else if(temp2 == ""){
            cout << "Enter Book Name (use _ for spaces): ";cin >> book1;
            ofstream file;
            file.open(R"(c:\Users\charl\CLionProjects\TheLibrary\LibraryMembers\)" + username + ".txt"); //file location may have to change depending on device
            file << username << endl << password << endl << temp1<< endl << book1;
            file.close();
        }
        else
            cout<<"Unable to check out more than two books, use return book function";
    }
    else{
        if(temp1 == ""){
            cout << "Enter 1st Book Name (use _ for spaces): ";cin >> book1;
            cout << "\nEnter 2nd Book Name (use _ for spaces): ";cin >> book2;

            ofstream file;
            file.open(R"(c:\Users\charl\CLionProjects\TheLibrary\LibraryMembers\)" + username + ".txt"); //file location may have to change depending on device
            file << username << endl << password << endl << book1 << endl << book2;
            file.close();
        }
        else{
            cout<<"Unable to check out more than two books, use return book function";
        }
    }
}

void BookReturn(string const &username, string const &password){ //returns 1 or both books depending on user input
    string book1, book2, un, pw, temp1, temp2; int num = 0; int flag = 0;

    cout<<"\nHow many books would you like to return (1 or 2)?"<< endl;
    cout<<"INPUT: "; cin>>num;

    if(!(num == 1 || num == 2))
        flag = 1;
    while (flag == 1){
        cout<<"\nInvalid input try again: ";cin>>num;
        if(num == 1 || num == 2)
            flag = 0;
    }

    ifstream read;
    read.open(R"(c:\Users\charl\CLionProjects\TheLibrary\LibraryMembers\)" + username + ".txt"); //file location may have to change depending on device
    getline(read, un); getline(read, pw); getline(read, temp1);getline(read, temp2);

    if(num == 1){
        cout<<"\nEnter name of book returning: ";cin>>book1;

        if(temp1 == book1){
            ofstream file;
            file.open(R"(c:\Users\charl\CLionProjects\TheLibrary\LibraryMembers\)" + username + ".txt"); //file location may have to change depending on device
            file << username << endl << password << endl << temp2 << "";
            file.close();
        }
        else if(temp2 == book1){
            ofstream file;
            file.open(R"(c:\Users\charl\CLionProjects\TheLibrary\LibraryMembers\)" + username + ".txt"); //file location may have to change depending on device
            file << username << endl << password << endl << temp1 << "";
            file.close();
        }
        else{
            cout<<"Book not checked out to user, try check out function";
        }
    }
    else if(num == 2){
        cout<<"\nEnter name of 1st book returning: ";cin>>book1;
        cout<<"Enter name of 2nd book returning: ";cin>>book2;

        if((temp1 == book1 && temp2 == book2) || (temp2 == book1 && temp1 == book2)){
            ofstream file;
            file.open(R"(c:\Users\charl\CLionProjects\TheLibrary\LibraryMembers\)" + username + ".txt"); //file location may have to change depending on device
            file << username << endl << password << endl << "" << "";
            file.close();
        }
        else
            cout<<"\nOne or both of the returning books are not checked out to the user, try check out function";

    }
}

void Admin(){//administration: display file
    string password = "admin123";
    string pw;
    string username;

    cout<<"\nEnter administration password: "; cin>>pw;
    while(pw != password){
        cout<<"Password incorrect\n";
        cout<<"Enter administration password: "; cin>>pw;
    }

    cout<<"Enter username of account that you want to view: "; cin>>username; cout<<endl;

    if(!IsMember(username)) {
        string user = username;
        while (user == username) {
            cout << "\nUser not found in system\n";
            cout << "Enter username: ";
            cin >> username;
            if (IsMember(username))
                user = "";
        }
    }
    displayFile(username);

}
void displayFile(string const &username){ //Admin file that displays the file corresponding to the username

    cout<<"File for "<< username << endl;

    string un, pw, b1, b2;

    ifstream read(R"(c:\Users\charl\CLionProjects\TheLibrary\LibraryMembers\)" + username + ".txt"); //file location may have to change depending on device
    getline(read, un);getline(read, pw);getline(read, b1);getline(read, b2);

    cout<<"\nUsername: " << un << endl;
    cout<<"Password: " << pw << endl;
    cout<<"Book 1: " << b1 << endl;
    cout<<"Book 2: " << b2 << endl;



}

bool IsMember(string const &username){ //helper function that returns true if username is already member

    if(ifstream(R"(c:\Users\charl\CLionProjects\TheLibrary\LibraryMembers\)" + username + ".txt")) //file location may have to change depending on device
        return true;
    else
        return false;
}

int main() {
    int option = intro();
    if(option == 1){
        NewMember();
        return 1;
    }
    else if(option == 2){
        CurrMember();
        return 1;
    }
    else if(option == 3){
        Admin();
    }
    return 0;
}
