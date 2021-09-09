#ifndef USERS_H
#define USERS_H
#include <iostream>
#include <fstream>
#include <cstdio>
#include <conio.h>
#include <windows.h>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

class User
{
    int idNumberOfUser;
    string loginOfUser, passwordOfUser;
    vector<User> all_users;

    public:
        User(int number=0, string login="", string password="") {
            idNumberOfUser = number;
            login = loginOfUser = login;
            passwordOfUser = password;
        };

        void loadDataFromFile(vector<User> &all_users);
        void userMenu(vector<User> &all_users);
        void registrationNewUser(vector<User> &all_users);
        void addNewUserToFile(User user);
        int userLogin(vector<User> &all_users);
        friend int AdressBookMenu(vector<User> &all_users, int idNumberOfLoggedUser);
};

#endif // USERS_H















