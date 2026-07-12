#ifndef DOUBLYLIST_H
#define DOUBLYLIST_H

#include <string>
using namespace std;


// ================= FRIENDS LIST (DOUBLY LINKED LIST) =================

class DNode
{
public:
    int    friendId;
    string friendName;
    DNode *prev, *next;

    DNode(int id, string name);
};

class DoublyList
{
    DNode *head;

public:

    DoublyList();

    int isEmpty();
    int alreadyFriend(int id);

    string addFriend(int id, string name);
    string removeFriend(int id);
    string display();
};

#endif // DOUBLYLIST_H
