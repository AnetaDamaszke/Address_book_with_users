#include <iostream>
#include <vector>
#include "users.h"
#include "Person.h"

using namespace std;

vector<User> all_users;
vector<Person> all_persons;

int AdressBookMenu(vector<User> &all_users, int idNumberOfLoggedUser);

int main()
{
    User user;


    user.loadDataFromFile(all_users);

    while(1)
    {
        user.userMenu(all_users);
    }

    return 0;
}

int AdressBookMenu(vector<User> &all_users, int idNumberOfLoggedUser)
{
    Person person;
    User user;

    char choiceSign;

    person.loadDataFromFile(all_persons);

    while(1)
    {
        system("cls");

        cout << "KSIAZKA ADRESOWA" << endl;
        //cout << "---------------------------------" <<endl;
        //cout << "Ilosc Twoich kontaktow: " << numberOfAllContacts << endl;
        //cout << "Nr ID zalogowanego uzytkownika: " << idNumberOfLoggedUser << endl;
        cout << "-------------------------" <<endl;
        cout << "1. Dodaj nowy kontakt" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Wyloguj sie" << endl;
        cout << "---------------------------------" <<endl;
        cout << "Twoj wybor: ";
        cin >> choiceSign;
        cout << endl;

        switch(choiceSign)
        {
        case '1':
            person.addNewPerson(all_persons, idNumberOfLoggedUser);
            break;
        case '2':
            person.findPersonByName(all_persons, idNumberOfLoggedUser);
            break;
        case '3':
            person.findPersonBySurname(all_persons, idNumberOfLoggedUser);
            break;
        case '4':
            person.showAllContacts(all_persons, idNumberOfLoggedUser);
            break;
        case '5':
            person.removePerson(all_persons, person);
            break;
        case '6':
            editPerson(all_persons, person);
            break;
        case '9':
            user.userMenu(all_users);
            break;
        default:
            cout << "Nie ma takiej cyfry w menu! Sprobuj jeszcze raz." << endl;
            Sleep(1500);
        }
    }
}
