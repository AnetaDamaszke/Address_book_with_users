#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <vector>

using namespace std;

struct User
{
    int idNumberOfUser;
    string loginOfUser, passwordOfUser;
};

void loadDataFromFile(vector<User> &all_users);
void registrationNewUser(vector<User> &all_users, int &numberOfUsers);
void addNewUserToFile(vector<User> &all_users, User user);

int main()
{
    User user;
    vector<User> all_users;

    int idNumberOfLoggedUser = 0;
    char choiceSign;

    loadDataFromFile(all_users);

    int numberOfUsers = all_users.size();

    while(1)
    {
        system("cls");

        cout << "KSIAZKA ADRESOWA" << endl;
        cout << "---------------------------------" <<endl;
        cout << "1. LOGOWANIE" << endl;
        cout << "2. REJESTRACJA" << endl;
        cout << "9. ZAMKNIJ PROGRAM" << endl;
        cout << "---------------------------------" <<endl;
        cout << "Twoj wybor: ";
        cin >> choiceSign;
        cout << endl;

        switch(choiceSign)
        {
        case '1':
            cout << "logowanie" << endl;
            Sleep(1500);
            break;
        case '2':
            registrationNewUser(all_users, numberOfUsers);
            break;
        case '9':
            exit(0);
            break;
        default:
            cout << "Nie ma takiej cyfry w menu! Wybierz jeszcze raz." << endl;
            Sleep(1500);
        }
    }

    return 0;
}

void loadDataFromFile(vector<User> &all_users)
{
    string lineOfTextFromFile = "";
    int elementOfLine = 1;
    User user;

    fstream plik;
    plik.open("uzytkownicy.txt", ios::in);

    if(plik.good() == false)
    {
        cout << "Nie mozna odznalezc pliku!" << endl;
    }
    else
    {
        while(getline(plik, lineOfTextFromFile, '|'))
        {
            switch(elementOfLine)
            {
            case 1:
                user.idNumberOfUser = atoi(lineOfTextFromFile.c_str());
                break;
            case 2:
                user.loginOfUser = lineOfTextFromFile;
                break;
            case 3:
                user.passwordOfUser = lineOfTextFromFile;
                break;
            }
            if(elementOfLine == 3)
            {
                all_users.push_back(user);
                elementOfLine = 0;
            }

            elementOfLine++;
        }
        plik.close();
    }
}

void registrationNewUser(vector<User> &all_users, int &numberOfUsers)
{
    User user;
    string loginOfNewUser, passwordOfNewUser;
    int i = 0;

    system("cls");
    cout << "Podaj login: " ;
    cin >> loginOfNewUser;

    while(i < numberOfUsers)
    {
        if( loginOfNewUser == all_users[i].loginOfUser )
        {
           cout << "Taki uzytkownik juz istnieje. Wpisz inny login: ";
           cin >>  loginOfNewUser;
           i = 0;
        }
        else
        {
            i++;
        }
    }

    cout << "Podaj haslo: " ;
    cin >> passwordOfNewUser;
    cout << endl;

    user.loginOfUser = loginOfNewUser;
    user.passwordOfUser = passwordOfNewUser;
    user.idNumberOfUser = numberOfUsers + 1;

    addNewUserToFile(all_users, user);
    all_users.push_back(user);
    numberOfUsers++;
}

void addNewUserToFile(vector<User> &all_users, User user)
{

    fstream plik;
    plik.open("uzytkownicy.txt", ios::out | ios::app);

    if(plik.good())
    {
        plik << user.idNumberOfUser << "|";
        plik << user.loginOfUser << "|";
        plik << user.passwordOfUser;
        plik << endl;

        plik.close();

        cout << endl;
        cout << "Uzytkownik dodany pomyslnie!" << endl;
        Sleep(1500);
    }
    else
        cout << "Nie mozna odznalezc pliku!" << endl;
}

