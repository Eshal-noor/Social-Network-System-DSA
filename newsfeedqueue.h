#ifndef NEWSFEEDQUEUE_H
#define NEWSFEEDQUEUE_H

#include <string>
using namespace std;


// ================= NEWS FEED (QUEUE) =================

class Post
{
public:
    int    authorId;
    string authorName;
    string content;
};

class NewsFeedQueue
{
    Post a[50];
    int  front, rear;

public:

    NewsFeedQueue();

    int isEmpty();
    int isFull();

    string enqueue(int authorId, string authorName, string content);
    string dequeue();
    string peek();
    string display();
};

#endif // NEWSFEEDQUEUE_H
