#ifndef GRAPHLIST_H
#define GRAPHLIST_H

#include <string>
using namespace std;


// ================= SOCIAL CONNECTIONS (GRAPH) =================

class GNode
{
public:
    int    userId;
    string userName;
    GNode *next;

    GNode(int id, string name);
};

class GraphList
{
    GNode  *adj[50];
    int     ids[50];
    string  names[50];
    int     userCount;

    int findUser(int id);

public:

    GraphList();

    void   addUser(int id, string name);
    string connect(int idA, string nameA, int idB, string nameB);
    string removeConnection(int idA, int idB);
    string display();
};

#endif // GRAPHLIST_H
