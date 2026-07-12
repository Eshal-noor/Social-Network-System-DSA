#include "doublylist.h"


// ================= FRIENDS LIST (DOUBLY LINKED LIST) =================

DNode::DNode(int id, string name)
{
    friendId   = id;
    friendName = name;
    prev       = NULL;
    next       = NULL;
}

DoublyList::DoublyList()
{
    head = NULL;
}

int DoublyList::isEmpty()
{
    return head == NULL;
}

int DoublyList::alreadyFriend(int id)
{
    DNode *temp = head;
    while(temp != NULL)
    {
        if(temp->friendId == id) return 1;
        temp = temp->next;
    }
    return 0;
}

string DoublyList::addFriend(int id, string name)
{
    if(alreadyFriend(id))
        return name + " is already your friend.";

    DNode *n = new DNode(id, name);

    if(head == NULL)
    {
        head = n;
    }
    else
    {
        DNode *temp = head;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = n;
        n->prev    = temp;
    }

    return name + " added to your friends list.";
}

string DoublyList::removeFriend(int id)
{
    DNode *temp = head;

    while(temp != NULL)
    {
        if(temp->friendId == id)
        {
            string name = temp->friendName;

            if(temp->prev == NULL)
                head = temp->next;
            else
                temp->prev->next = temp->next;

            if(temp->next != NULL)
                temp->next->prev = temp->prev;

            delete temp;
            return name + " removed from your friends list.";
        }
        temp = temp->next;
    }

    return "Friend not found.";
}

string DoublyList::display()
{
    if(isEmpty()) return "Your friends list is empty.";

    string result = "Friends: ";
    DNode *temp   = head;

    while(temp != NULL)
    {
        result += temp->friendName;
        if(temp->next != NULL) result += " <-> ";
        temp = temp->next;
    }
    return result;
}
