#include "chatstack.h"


// ================= GROUP CHAT (STACK) =================

ChatStack::ChatStack()
{
    top   = -1;
    timer = 0;
}

int ChatStack::isEmpty() { return top == -1; }
int ChatStack::isFull()  { return top == 49; }

string ChatStack::push(int senderId, string senderName, string text)
{
    if(isFull()) return "Chat is full.";

    timer++;
    a[++top].senderId  = senderId;
    a[top].senderName  = senderName;
    a[top].text        = text;
    a[top].timestamp   = timer;

    return "Message sent.";
}

string ChatStack::pop()
{
    if(isEmpty()) return "No messages to delete.";

    string msg = "Deleted: [" + a[top].senderName + "]: " + a[top].text;
    top--;
    return msg;
}

string ChatStack::peek()
{
    if(isEmpty()) return "No messages yet.";
    return "Latest -> [" + a[top].senderName + "]: " + a[top].text;
}

string ChatStack::display()
{
    if(isEmpty()) return "Group chat is empty.";

    string result = "===== Group Chat (newest first) =====\n";
    for(int i = top; i >= 0; i--)
    {
        result += "t=" + to_string(a[i].timestamp)
        + " [" + a[i].senderName + "]: "
            + a[i].text + "\n";
    }
    return result;
}
