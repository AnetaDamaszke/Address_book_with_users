#include <iostream>
#include <fstream>
#include <cstdio>
#include <conio.h>
#include <windows.h>
#include <string>
#include <vector>
#include <stdio.h>
#include "users.h"

using namespace std;

void User::loadDataFromFile(vector<User> &all_users)
{
    string lineOfTextFromFile = "";
    int elementOfLine = 1;
    User user;

    fstream plik;
    plik.open("uzytkownicy.txt", ios::in );

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

void User::userMenu(vector<User> &all_users)
{
    int numberOfUsers = all_users.size();
    char choiceSign;

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
        userLogin(all_users);
        break;
    case '2':
        registrationNewUser(all_users);
        break;
    case '9':
        exit(0);
        break;
    default:
        cout << "Nie ma takiej cyfry w menu! Wybierz jeszcze raz." << endl;
        Sleep(1500);
    }
}

void User::registrationNewUser(vector<User> &all_users)
{
    User user;
    string loginOfNewUser, passwordOfNewUser;
    int i = 1;
    int numberOfUsers = all_users.size();

    system("cls");
    cout << "Podaj login: " ;
    cin >> loginOfNewUser;

    while(i < numberOfUsers )
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

    addNewUserToFile(user);
    all_users.push_back(user);
    numberOfUsers++;
}

void User::addNewUserToFile(User user)
{
    fstream plik;
    plik.open("uzytkownicy.txt", ios::out | ios::app);

    if( plik.good() )
    {
        plik << user.idNumberOfUser << "|";
        plik << user.loginOfUser << "|";
        plik << user.passwordOfUser << "|";
        plik << endl;
        cout << "Uzytkownik dodany pomyslnie!" << endl;
        Sleep(1500);

        plik.close();
    }
    else
    {
        cout << endl;
        cout << "Nie mozna odznalezc pliku!" << endl;
        Sleep(1500);
    }
}

int User::userLogin(vector<User> &all_users)
{
    User user;
    string loginOfUser, passwordOfUser;
    int idNumberOfLoggedUser = 0;

    system("cls");

    cout << "Podaj login: " ;
    cin >> loginOfUser;
    int i = 0;

    while( i < all_users.size() )
    {
        if( loginOfUser == all_users[i].loginOfUser )
        {
            for(int test = 0; test < 3; test++)
            {
                cout << "Podaj haslo. Pozostalo prob: " << 3 - test << endl;
                cin >>  passwordOfUser;

                if( all_users[i].passwordOfUser == passwordOfUser )
                {
                    cout << "Uzytkownik zalogowany!" << endl;
                    Sleep(1000);
                    idNumberOfLoggedUser = all_users[i].idNumberOfUser;
                    AdressBookMenu(all_users, idNumberOfLoggedUser);
                }
            }
            cout << "Podales 3 razy bledne haslo. Odczekaj 5 sekund." << endl;
            Sleep(5000);

        }
        i++;
    }
    cout << "Nie ma takiego uzytkownika!" << endl;
    Sleep(1500);
    return 0;
}

