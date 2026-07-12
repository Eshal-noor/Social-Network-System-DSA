#include "graphlist.h"


// ================= SOCIAL CONNECTIONS (GRAPH) =================

GNode::GNode(int id, string name)
{
    userId   = id;
    userName = name;
    next     = NULL;
}

GraphList::GraphList()
{
    userCount = 0;
    for(int i = 0; i < 50; i++)
        adj[i] = NULL;
}

int GraphList::findUser(int id)
{
    for(int i = 0; i < userCount; i++)
        if(ids[i] == id) return i;
    return -1;
}

void GraphList::addUser(int id, string name)
{
    if(userCount == 50)    return;
    if(findUser(id) != -1) return;

    ids[userCount]   = id;
    names[userCount] = name;
    adj[userCount]   = NULL;
    userCount++;
}

string GraphList::connect(int idA, string nameA, int idB, string nameB)
{
    addUser(idA, nameA);
    addUser(idB, nameB);

    int ai = findUser(idA);
    int bi = findUser(idB);

    GNode *temp = adj[ai];
    while(temp != NULL)
    {
        if(temp->userId == idB)
            return nameA + " and " + nameB + " are already connected.";
        temp = temp->next;
    }

    GNode *n1 = new GNode(idB, nameB);
    n1->next  = adj[ai];
    adj[ai]   = n1;

    GNode *n2 = new GNode(idA, nameA);
    n2->next  = adj[bi];
    adj[bi]   = n2;

    return nameA + " and " + nameB + " are now connected!";
}

string GraphList::removeConnection(int idA, int idB)
{
    int ai = findUser(idA);
    int bi = findUser(idB);

    if(ai == -1 || bi == -1)
        return "One or both users not found.";

    GNode *temp = adj[ai], *prev = NULL;
    while(temp != NULL)
    {
        if(temp->userId == idB)
        {
            if(prev == NULL) adj[ai] = temp->next;
            else             prev->next = temp->next;
            delete temp;
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    temp = adj[bi];
    prev = NULL;
    while(temp != NULL)
    {
        if(temp->userId == idA)
        {
            if(prev == NULL) adj[bi] = temp->next;
            else             prev->next = temp->next;
            delete temp;
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    return "Connection removed between " + names[ai] + " and " + names[bi] + ".";
}

string GraphList::display()
{
    if(userCount == 0) return "Network is empty.";

    string result = "===== Social Connections =====\n";
    for(int i = 0; i < userCount; i++)
    {
        result += "[" + to_string(ids[i]) + "] " + names[i] + " -> ";

        GNode *temp = adj[i];
        if(temp == NULL) result += "No connections";

        while(temp != NULL)
        {
            result += temp->userName;
            if(temp->next != NULL) result += ", ";
            temp = temp->next;
        }
        result += "\n";
    }
    return result;
}
