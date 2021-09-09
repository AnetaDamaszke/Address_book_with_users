#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <fstream>
#include <cstdio>
#include <conio.h>
#include <windows.h>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

class Person
{
    int personIdNumber, userIdNumber;
    string personName, personSurname, personPhoneNumber, personEmail, personAddress;

    public:
        Person(int idNumber=0, int userId=0, string name="", string surname="", string phone="", string email="", string address="") {
            personIdNumber = idNumber;
            userIdNumber = userId;
            personName = name;
            personSurname = surname;
            personPhoneNumber = phone;
            personEmail = email;
            personAddress = address;
        };

        void loadDataFromFile(vector<Person> &all_persons);
        void displayPersonDetails(Person person);
        void findPersonByName(vector<Person> &all_persons, int &numberOfAllContacts);
        void findPersonBySurname(vector<Person> &all_persons, int &numberOfAllContacts);
        void showAllContacts(vector<Person> &all_persons, int &numberOfAllContacts);
        void addNewPerson(vector<Person> &all_persons, int &numberOfAllContacts);
        void addToFile(Person person);
        void removePerson(vector<Person> &all_persons, Person person);
        void updateContactFromFile(Person person);
        friend void editPerson(vector<Person> &all_persons, Person person);
        friend void updateContactFromFileRemove(Person person);
        string findFirstWord(string text);
};

#endif // PERSON_H
