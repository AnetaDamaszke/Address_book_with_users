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

int registrationNewUser(vector<User> all_users, int numberOfUsers);

int main()
{
    User users;
    vector<User> all_users;

    int idNumberOfLoggedUser = 0;
    int numberOfUsers = 0;
    char choiceSign;

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
            numberOfUsers = registrationNewUser(all_users, numberOfUsers);
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


int registrationNewUser(vector<User> all_users, int numberOfUsers)
{
    User users;
    string loginOfNewUser, passwordOfNewUser;

    system("cls");
    cout << "Podaj login: " ;
    cin >> loginOfNewUser;

    for(int i = 0; i < numberOfUsers; i++)
    {
        if( users.loginOfUser == loginOfNewUser)
        {
           cout << "Taki uzytkownik juz istnieje. Wpisz inny login: ";
           cin >>  loginOfNewUser;
           i = 0;
        }
    }

    cout << "Podaj haslo: " ;
    cin >> passwordOfNewUser;
    cout << endl;

    users.loginOfUser = loginOfNewUser;
    users.passwordOfUser = passwordOfNewUser;
    users.idNumberOfUser = numberOfUsers + 1;

    cout << "Uzytkownik zarejestrowany!" << endl;
    Sleep(1500);

    return numberOfUsers + 1;
}
