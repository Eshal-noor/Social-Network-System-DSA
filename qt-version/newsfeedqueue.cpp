#include "newsfeedqueue.h"


// ================= NEWS FEED (QUEUE) =================

NewsFeedQueue::NewsFeedQueue()
{
    front = -1;
    rear  = -1;
}

int NewsFeedQueue::isEmpty() { return front == -1; }
int NewsFeedQueue::isFull()  { return rear == 49; }

string NewsFeedQueue::enqueue(int authorId, string authorName, string content)
{
    if(isFull()) return "News feed is full.";

    if(front == -1) front = 0;

    rear++;
    a[rear].authorId   = authorId;
    a[rear].authorName = authorName;
    a[rear].content    = content;

    return "Post shared to news feed!";
}

string NewsFeedQueue::dequeue()
{
    if(isEmpty()) return "News feed is empty.";

    string msg = "Removed post by: " + a[front].authorName;

    if(front == rear)
        front = rear = -1;
    else
        front++;

    return msg;
}

string NewsFeedQueue::peek()
{
    if(isEmpty()) return "News feed is empty.";
    return "Next -> [" + a[front].authorName + "]: " + a[front].content;
}

string NewsFeedQueue::display()
{
    if(isEmpty()) return "News feed is empty.";

    string result = "===== News Feed =====\n";
    for(int i = front; i <= rear; i++)
    {
        result += "[" + a[i].authorName + "]: "
                  + a[i].content + "\n";
    }
    return result;
}
