#include "profilearray.h"


// ================= USER PROFILE (ARRAY) =================

UserProfile::UserProfile()
{
    id     = 0;
    age    = 0;
    active = false;
    picPath= "";
}

ProfileArray::ProfileArray()
{
    size = 0;
}

int ProfileArray::isEmpty()  { return size == 0; }
int ProfileArray::isFull()   { return size == 50; }
int ProfileArray::getSize()  { return size; }

int ProfileArray::findById(int id)
{
    for(int i = 0; i < size; i++)
        if(a[i].id == id) return i;
    return -1;
}

UserProfile* ProfileArray::getProfile(int id)
{
    int i = findById(id);
    if(i == -1) return NULL;
    return &a[i];
}

UserProfile* ProfileArray::getAt(int i) { return &a[i]; }

string ProfileArray::addProfile(int id, string name, string username, int age, string picPath)
{
    if(isFull())            return "Profile list is full.";
    if(findById(id) != -1)  return "ID " + to_string(id) + " already exists.";

    a[size].id       = id;
    a[size].name     = name;
    a[size].username = username;
    a[size].age      = age;
    a[size].active   = true;
    a[size].picPath  = picPath;
    size++;

    return "Account created: " + name + " (@" + username + ")";
}

string ProfileArray::deleteProfile(int id)
{
    if(isEmpty()) return "No profiles exist.";

    int i = findById(id);
    if(i == -1)   return "Profile not found.";

    string name = a[i].name;
    for(int j = i; j < size - 1; j++)
        a[j] = a[j+1];
    size--;

    return "Profile deleted: " + name;
}

string ProfileArray::viewProfile(int id)
{
    int i = findById(id);
    if(i == -1) return "Profile not found.";

    return  "===========================\n"
           "ID:       " + to_string(a[i].id)   + "\n"
                                  "Name:     " + a[i].name             + "\n"
                         "Username: @" + a[i].username        + "\n"
                             "Age:      " + to_string(a[i].age)   + "\n"
                                   "===========================";
}

string ProfileArray::display()
{
    if(isEmpty()) return "No users exist.";

    string result = "===== All Users =====\n";
    for(int i = 0; i < size; i++)
    {
        result += "[" + to_string(a[i].id) + "] "
                  + a[i].name
                  + " (@" + a[i].username + ")"
                  + "  Age: " + to_string(a[i].age)
                  + "\n";
    }
    return result;
}