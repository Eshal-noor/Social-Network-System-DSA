#ifndef CHATSTACK_H
#define CHATSTACK_H

#include <string>
using namespace std;


// ================= GROUP CHAT (STACK) =================

class Message
{
public:
    int    senderId;
    string senderName;
    string text;
    int    timestamp;
};

class ChatStack
{
    Message a[50];
    int     top;
    int     timer;

public:

    ChatStack();

    int isEmpty();
    int isFull();

    string push(int senderId, string senderName, string text);
    string pop();
    string peek();
    string display();
};

#endif // CHATSTACK_H
