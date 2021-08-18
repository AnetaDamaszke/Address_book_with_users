#include <iostream>
#include <fstream>
#include <cstdio>
#include <conio.h>
#include <windows.h>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

struct User
{
    int idNumberOfUser;
    string loginOfUser, passwordOfUser;
};

struct Person
{
    int personIdNumber = 0, userIdNumber = 0;
    string personName = "", personSurname = "", personPhoneNumber = "", personEmail = "", personAddress = "";
};

void loadDataFromFile(vector<User> &all_users);
void userMenu(vector<User> &all_users);
void registrationNewUser(vector<User> &all_users, int &numberOfUsers);
void addNewUserToFile(User user);
int userLogin(vector<User> &all_users);
int AdressBookMenu(vector<User> &all_users, int idNumberOfLoggedUser);
void loadDataFromFile(vector<Person> &all_persons);
void displayPersonDetails(Person person);
void findPersonByName(vector<Person> all_persons);
void findPersonBySurname(vector<Person> all_persons);
void showAllContacts(vector<Person> all_persons, Person person);
void addNewPerson(vector<Person> &all_persons, int &numberOfAllContacts);
void addToFile(Person person);
void removePerson(vector<Person> &all_persons, Person person);
void updateContactFromFile(Person person);
void editPerson(vector<Person> &all_persons, Person person);
string findFirstWord(string text);
void updateContactFromFileRemove(Person person);

int main()
{
    User user;
    vector<User> all_users;

    loadDataFromFile(all_users);

    while(1)
    {
        userMenu(all_users);
    }

    return 0;
}

void loadDataFromFile(vector<User> &all_users)
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

void userMenu(vector<User> &all_users)
{
    int numberOfUsers = all_users.size();
    char choiceSign;

    system("cls");
    cout << "KSIAZKA ADRESOWA" << endl;
    //cout << "Liczba uzytkownikow: " << numberOfUsers << endl;
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

void registrationNewUser(vector<User> &all_users, int &numberOfUsers)
{
    User user;
    string loginOfNewUser, passwordOfNewUser;
    int i = 1;

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

void addNewUserToFile(User user)
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

int userLogin(vector<User> &all_users)
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

int AdressBookMenu(vector<User> &all_users, int idNumberOfLoggedUser)
{
    Person person;
    vector<Person> all_persons;
    char choiceSign;

    loadDataFromFile(all_persons);

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
            addNewPerson(all_persons, idNumberOfLoggedUser);
            break;
        case '2':
            findPersonByName(all_persons);
            break;
        case '3':
            findPersonBySurname(all_persons);
            break;
        case '4':
            showAllContacts(all_persons, person);
            break;
        case '5':
            removePerson(all_persons, person);
            break;
        case '6':
            editPerson(all_persons, person);
            break;
        case '9':
            userMenu(all_users);
            break;
        default:
            cout << "Nie ma takiej cyfry w menu! Sprobuj jeszcze raz." << endl;
            Sleep(1500);
        }
    }
}

void loadDataFromFile(vector<Person> &all_persons)
{
    string lineOfTextFromFile = "";
    int elementOfLine = 1;
    Person person;

    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::in);

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
                person.personIdNumber = atoi(lineOfTextFromFile.c_str());
                break;
            case 2:
                person.userIdNumber = atoi(lineOfTextFromFile.c_str());
                break;
            case 3:
                person.personName = lineOfTextFromFile;
                break;
            case 4:
                person.personSurname = lineOfTextFromFile;
                break;
            case 5:
                person.personPhoneNumber = lineOfTextFromFile;
                break;
            case 6:
                person.personEmail = lineOfTextFromFile;
                break;
            case 7:
                person.personAddress = lineOfTextFromFile;
                break;
            }
            if ( elementOfLine == 7 )
            {
                elementOfLine = 0;
                all_persons.push_back(person);
            }

            elementOfLine++;
        }
        plik.close();
    }
}

void displayPersonDetails(Person person)
{
    cout << person.personIdNumber << endl;
    cout << person.personName << endl;
    cout << person.personSurname << endl;
    cout << person.personPhoneNumber << endl;
    cout << person.personEmail << endl;
    cout << person.personAddress << endl;
}

void findPersonByName(vector<Person> all_persons)
{
    Person person;
    string personName;
    int searchedName = 0;
    int singleOfContact = 0;
    char choiceSign;

    cout << "Wpisz imie: ";
    cin >> personName;
    cout << endl;

    for(singleOfContact; singleOfContact < all_persons.size(); singleOfContact++)
    {
        if(personName == all_persons[singleOfContact].personName)
        {
            displayPersonDetails(all_persons[singleOfContact]);
            searchedName++;
            cout << endl;
        }
    }

    if( searchedName == 0)
    {
        cout << "Nie ma osoby o takim imieniu w Twoich kontaktach." << endl;
        cout << endl;
    }

    cout << "Aby zakonczyc wcisnij dowolny klawisz";
    choiceSign = getch();
}

void findPersonBySurname(vector<Person> all_persons)
{
    Person person;
    string personSurname;
    int singleOfContact = 0;
    int searchedSurname = 0;
    char choiceSign;

    cout << "Wpisz nazwisko: ";
    cin >> personSurname;
    cout << endl;

    for(singleOfContact; singleOfContact < all_persons.size(); singleOfContact++)
    {
        if(personSurname == all_persons[singleOfContact].personSurname)
        {
            displayPersonDetails(all_persons[singleOfContact]);
            searchedSurname++;
            cout << endl;
        }
    }
    if( searchedSurname == 0)
    {
        cout << "Nie ma osoby o takim nazwisku w Twoich kontaktach." << endl;
        cout << endl;
    }

    cout << "Aby zakonczyc wcisnij dowolny klawisz";
    choiceSign = getch();
}

void showAllContacts(vector<Person> all_persons, Person person)
{
    char choiceSign;
    int singleOfContact = 0;

    system("cls");
    cout << "WSZYSTKIE KONTAKTY" << endl;
    cout << endl;

    for(singleOfContact; singleOfContact < all_persons.size(); singleOfContact++)
    {
        displayPersonDetails(all_persons[singleOfContact]);
        cout << endl;
    }

    cout << "Aby zakonczyc wcisnij dowolny klawisz";
    choiceSign = getch();
}

void addNewPerson(vector<Person> &all_persons, int &idNumberOfLoggedUser)
{
    Person person;
    int singleOfContact = 0;
    char choiceSign;

    person.personIdNumber = all_persons.size() + 1;
    person.userIdNumber = idNumberOfLoggedUser;

    for(singleOfContact; singleOfContact < all_persons.size(); singleOfContact++)
    {
        int maxIdNumber = 0;

        if ( person.personIdNumber > 0)
        {
            for( int i = 0; i < person.personIdNumber; i++ )
            {
                if( all_persons[singleOfContact].personIdNumber > maxIdNumber )
                    maxIdNumber = all_persons[singleOfContact].personIdNumber;
            }
        }
        person.personIdNumber = maxIdNumber + 1;
    }

    system("cls");
    cout << "Imie: ";
    cin >> person.personName;
    cout << "Nazwisko: ";
    cin >> person.personSurname;

    for(singleOfContact; singleOfContact < all_persons.size(); singleOfContact++)
    {
        if((person.personName == all_persons[singleOfContact].personName) && (person.personSurname == all_persons[singleOfContact].personSurname))
        {
            cout << endl;
            cout << "Taka osoba juz istnieje w kontaktach!" << endl;
            cout << endl;
            cout << "Aby zakonczyc wcisnij dowolny klawisz";
            choiceSign = getch();
        }
    }

    cout << "Numer telefonu: ";
    cin >> person.personPhoneNumber;
    cout << "Adres e-mail: ";
    cin >> person.personEmail;
    cout << "Adres zamieszkania: ";
    cin.sync();
    getline(cin, person.personAddress);

    all_persons.push_back(person);
    addToFile(person);
}

void addToFile(Person person)
{

    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::out | ios::app);

    if( plik.good() == true )
    {
        plik << person.personIdNumber << "|";
        plik << person.userIdNumber << "|";
        plik << person.personName << "|";
        plik << person.personSurname << "|";
        plik << person.personPhoneNumber << "|";
        plik << person.personEmail << "|";
        plik << person.personAddress << "|";
        plik << endl;

        plik.close();

        cout << endl;
        cout << "Kontakt dodany pomyslnie!" << endl;
        Sleep(1500);
    }
    else
    {
        cout << endl;
        cout << "Nie mozna odznalezc pliku!" << endl;
        Sleep(1500);
    }
}

void removePerson(vector<Person> &all_persons, Person person)
{
    int personIdNumberToRemove;
    int singleOfContact = 0;
    char choiceSign;

    cout << "Podaj numer ID kontaktu,ktory chcesz usunac:" << endl;
    cin >> personIdNumberToRemove;
    cout << endl;

    for(singleOfContact; singleOfContact < all_persons.size(); singleOfContact++)
    {
        if(all_persons[singleOfContact].personIdNumber == personIdNumberToRemove)
        {
            displayPersonDetails(all_persons[singleOfContact]);
            cout << endl;
            cout << "Czy na pewno chcesz usunac ten kontakt? t/n" << endl;
            cin >> choiceSign;

            if( choiceSign == 't')
            {
                updateContactFromFileRemove(all_persons[singleOfContact]);
                all_persons.erase(all_persons.begin()+ singleOfContact);
                cout << "Kontakt usuniety!" << endl;
                Sleep(1500);
            }
            else if( choiceSign == 'n')
            {
                cout << "Aby zakonczyc wcisnij dowolny klawisz";
                choiceSign = getch();
            }
        }
    }
}

string findFirstWord(string text)
{
    string word;

    char wantedSign = '|';

    int foundPosition = text.find(wantedSign);

    int lenghtOfText = text.size();

    word = text.erase(foundPosition, lenghtOfText - foundPosition);

    return word;
}

void updateContactFromFile(Person person)
{
    string lineOfTextFromFile = "", partOfLine = "";
    int elementOfLine = 1;

    fstream plik1, plik2;
    plik1.open("ksiazka_adresowa.txt", ios::in);

    if( plik1.good() )
    {
        plik2.open("ksiazka_adresowa_tymczasowa.txt", ios::out | ios::app);

        while(getline(plik1, lineOfTextFromFile))
        {
            partOfLine = findFirstWord(lineOfTextFromFile);

            if( atoi(partOfLine.c_str()) != person.personIdNumber )
            {
                plik2 << lineOfTextFromFile << endl;
            }
            else
            {
                plik2 << person.personIdNumber << "|";
                plik2 << person.userIdNumber << "|";
                plik2 << person.personName << "|";
                plik2 << person.personSurname << "|";
                plik2 << person.personPhoneNumber << "|";
                plik2 << person.personEmail << "|";
                plik2 << person.personAddress << "|";
                plik2 << endl;
            }
        }
    }
    else
        cout << "Nie znaleziono pliku!" << endl;

    plik2.close();
    plik1.close();

    if(( remove("ksiazka_adresowa.txt") == 0) && ( rename("ksiazka_adresowa_tymczasowa.txt", "ksiazka_adresowa.txt") == 0 ) )
    {
        cout << "Aktualizacja danych zakonczona powodzeniem!" << endl;
        Sleep(1500);
    }
    else
    {
        cout << "BLAD ZAPISU!" << endl;
        Sleep(1500);
    }
}

void updateContactFromFileRemove(Person person)
{
    string lineOfTextFromFile = "", partOfLine = "";

    fstream plik1, plik2;
    plik1.open("ksiazka_adresowa.txt", ios::in);

    if( plik1.good() )
    {
        plik2.open("ksiazka_adresowa_tymczasowa.txt", ios::out | ios::app);

        while(getline(plik1, lineOfTextFromFile))
        {
            partOfLine = findFirstWord(lineOfTextFromFile);

            if( atoi(partOfLine.c_str()) != person.personIdNumber )
            {
                plik2 << lineOfTextFromFile << endl;
            }
            else
            {
                cout << endl;
            }
        }
    }
    else
        cout << "Nie znaleziono pliku!" << endl;

    plik2.close();
    plik1.close();

    if(( remove("ksiazka_adresowa.txt") == 0) && ( rename("ksiazka_adresowa_tymczasowa.txt", "ksiazka_adresowa.txt") == 0 ) )
    {
        cout << "Aktualizacja danych zakonczona powodzeniem!" << endl;
        Sleep(1500);
    }
    else
    {
        cout << "BLAD ZAPISU!" << endl;
        Sleep(1500);
    }
}

void editPerson(vector<Person> &all_persons, Person person)
{
    int personIdNumberToEdit;
    int singleOfContact = 0;
    string newPersonData = "";
    char choiceSign;

    cout << "Wpisz numer ID kontaktu, ktory chcesz edytowac:" << endl;
    cin >> personIdNumberToEdit;
    cout << endl;

    for(singleOfContact; singleOfContact < all_persons.size(); singleOfContact++)
    {
        if(all_persons[singleOfContact].personIdNumber == personIdNumberToEdit)
        {
            displayPersonDetails(all_persons[singleOfContact]);
            cout << endl;
            cout << "Czy na pewno chcesz edytowac ten kontakt? t/n" << endl;
            cin >> choiceSign;

            if( choiceSign == 't')
            {
                system("cls");
                cout << "Co chcesz edytowac?" << endl;
                cout << "-----------------------------" << endl;
                cout << "1. Imie" << endl;
                cout << "2. Nazwisko" << endl;
                cout << "3. Numer telefonu" << endl;
                cout << "4. E-mail" << endl;
                cout << "5. Adres" << endl;
                cout << "6. Wroc do menu" << endl;
                cout << "-----------------------------" << endl;
                cout << "Twoj wybor: ";
                cin >> choiceSign;
                cout << endl;

                switch(choiceSign)
                {
                case '1':
                    cout << "Wpisz nowe imie: " << endl;
                    cin >> newPersonData;
                    all_persons[singleOfContact].personName = newPersonData;
                    break;
                case '2':
                    cout << "Wpisz nowe nazwisko: " << endl;
                    cin >> newPersonData;
                    all_persons[singleOfContact].personSurname = newPersonData;
                    break;
                case '3':
                    cout << "Wpisz nowy numer telefonu: " << endl;
                    cin >> newPersonData;
                    all_persons[singleOfContact].personPhoneNumber = newPersonData;
                    break;
                case '4':
                    cout << "Wpisz nowy e-mail: " << endl;
                    cin >> newPersonData;
                    all_persons[singleOfContact].personEmail = newPersonData;
                    break;
                case '5':
                    cout << "Wpisz nowy adres: " << endl;
                    cin.sync();
                    getline(cin, newPersonData);
                    all_persons[singleOfContact].personAddress = newPersonData;
                    break;
                case '6':
                    cout << "Aby zakonczyc wcisnij dowolny klawisz";
                    choiceSign = getch();
                    break;
                default:
                    cout << "Nie ma takiej cyfry w menu! Sprobuj jeszcze raz." << endl;
                    Sleep(1500);
                }

                updateContactFromFile(all_persons[singleOfContact]);

            }
            else if( choiceSign == 'n')
            {
                cout << "Aby zakonczyc wcisnij dowolny klawisz";
                choiceSign = getch();
            }
        }
    }

}
