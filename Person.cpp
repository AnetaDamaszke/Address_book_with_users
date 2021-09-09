#include <iostream>
#include <fstream>
#include <cstdio>
#include <conio.h>
#include <windows.h>
#include <string>
#include <vector>
#include <stdio.h>
#include "Person.h"

void Person::loadDataFromFile(vector<Person> &all_persons)
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

void Person::displayPersonDetails(Person person)
{
    cout << person.personIdNumber << endl;
    cout << person.personName << endl;
    cout << person.personSurname << endl;
    cout << person.personPhoneNumber << endl;
    cout << person.personEmail << endl;
    cout << person.personAddress << endl;
}

void Person::findPersonByName(vector<Person> &all_persons, int &idNumberOfLoggedUser)
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
        if( idNumberOfLoggedUser == all_persons[singleOfContact].userIdNumber)
        {
            if(personName == all_persons[singleOfContact].personName)
            {
                displayPersonDetails(all_persons[singleOfContact]);
                searchedName++;
                cout << endl;
            }
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

void Person::findPersonBySurname(vector<Person> &all_persons, int &idNumberOfLoggedUser)
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
        if( idNumberOfLoggedUser == all_persons[singleOfContact].userIdNumber)
        {
            if(personSurname == all_persons[singleOfContact].personSurname)
            {
                displayPersonDetails(all_persons[singleOfContact]);
                searchedSurname++;
                cout << endl;
            }
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

void Person::showAllContacts(vector<Person> &all_persons, int &idNumberOfLoggedUser)
{
    char choiceSign;
    int singleOfContact = 0;

    system("cls");
    cout << "WSZYSTKIE KONTAKTY" << endl;
    cout << endl;

    for(singleOfContact; singleOfContact < all_persons.size(); singleOfContact++)
    {
        if( idNumberOfLoggedUser == all_persons[singleOfContact].userIdNumber)
        {
        displayPersonDetails(all_persons[singleOfContact]);
        cout << endl;
        }
    }

    cout << "Aby zakonczyc wcisnij dowolny klawisz";
    choiceSign = getch();
}

void Person::addNewPerson(vector<Person> &all_persons, int &idNumberOfLoggedUser)
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

void Person::addToFile(Person person)
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

void Person::removePerson(vector<Person> &all_persons, Person person)
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

void Person::updateContactFromFile(Person person)
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
            partOfLine = person.findFirstWord(lineOfTextFromFile);

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
            person.displayPersonDetails(all_persons[singleOfContact]);
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

                person.updateContactFromFile(all_persons[singleOfContact]);

            }
            else if( choiceSign == 'n')
            {
                cout << "Aby zakonczyc wcisnij dowolny klawisz";
                choiceSign = getch();
            }
        }
    }

}

string Person::findFirstWord(string text)
{
    string word;

    char wantedSign = '|';

    int foundPosition = text.find(wantedSign);

    int lenghtOfText = text.size();

    word = text.erase(foundPosition, lenghtOfText - foundPosition);

    return word;
}
