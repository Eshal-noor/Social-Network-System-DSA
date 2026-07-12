#ifndef PROFILEARRAY_H
#define PROFILEARRAY_H

#include <string>
using namespace std;


// ================= USER PROFILE (ARRAY) =================

class UserProfile
{
public:
    int    id;
    string name;
    string username;
    int    age;
    bool   active;
    string picPath;   // stores resource path or file path

    UserProfile();
};

class ProfileArray
{
    UserProfile a[50];
    int         size;

public:

    ProfileArray();

    int isEmpty();
    int isFull();
    int getSize();
    int findById(int id);

    UserProfile* getProfile(int id);
    UserProfile* getAt(int i);

    string addProfile(int id, string name, string username, int age, string picPath = "");
    string deleteProfile(int id);
    string viewProfile(int id);
    string display();
};

#endif // PROFILEARRAY_H