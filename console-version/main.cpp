#include<iostream>
#include<string>
using namespace std;

// ================================================
//   SOCIAL NETWORK PLATFORM
//   DSA Project - Semester 2
//
//   Data Structures Used:
//   1. Array          -> User Profiles
//   2. Doubly List    -> Friends List (per user)
//   3. Stack          -> Group Chat History
//   4. Queue          -> Shared News Feed
//   5. BST            -> Trending Posts
//   6. Graph          -> Social Connections
//      (auto-connects when you add a friend)
// ================================================




// ================= USER PROFILE (ARRAY) =================

class UserProfile
{
public:
    int    id;
    string name;
    string username;
    int    age;
    bool   active;

    UserProfile()
    {
        id     = 0;
        age    = 0;
        active = false;
    }
};

class ProfileArray
{
    UserProfile a[50];
    int         size;

public:

    ProfileArray()
    {
        size = 0;
    }

    int isEmpty()  { return size == 0; }
    int isFull()   { return size == 50; }
    int getSize()  { return size; }

    int findById(int id)
    {
        for(int i = 0; i < size; i++)
            if(a[i].id == id) return i;
        return -1;
    }

    UserProfile* getProfile(int id)
    {
        int i = findById(id);
        if(i == -1) return NULL;
        return &a[i];
    }

    UserProfile* getAt(int i) { return &a[i]; }

    string addProfile(int id, string name, string username, int age)
    {
        if(isFull())             return "Profile list is full.";
        if(findById(id) != -1)  return "ID " + to_string(id) + " already exists.";

        a[size].id       = id;
        a[size].name     = name;
        a[size].username = username;
        a[size].age      = age;
        a[size].active   = true;
        size++;

        return "Account created: " + name + " (@" + username + ")";
    }

    string deleteProfile(int id)
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

    string viewProfile(int id)
    {
        int i = findById(id);
        if(i == -1) return "Profile not found.";

        return  "\n===========================\n"
                "  ID:       " + to_string(a[i].id)   + "\n"
                "  Name:     " + a[i].name             + "\n"
                "  Username: @" + a[i].username        + "\n"
                "  Age:      " + to_string(a[i].age)   + "\n"
                "===========================";
    }

    string display()
    {
        if(isEmpty()) return "No users exist.";

        string result = "\n===== All Users =====\n";
        for(int i = 0; i < size; i++)
        {
            result += "  [" + to_string(a[i].id) + "] "
                    + a[i].name
                    + " (@" + a[i].username + ")"
                    + "  Age: " + to_string(a[i].age)
                    + "\n";
        }
        return result;
    }
};




// ================= FRIENDS LIST (DOUBLY LINKED LIST) =================

class DNode
{
public:
    int    friendId;
    string friendName;
    DNode *prev, *next;

    DNode(int id, string name)
    {
        friendId   = id;
        friendName = name;
        prev       = NULL;
        next       = NULL;
    }
};

class DoublyList
{
    DNode *head;

public:

    DoublyList()
    {
        head = NULL;
    }

    int isEmpty() { return head == NULL; }

    int alreadyFriend(int id)
    {
        DNode *temp = head;
        while(temp != NULL)
        {
            if(temp->friendId == id) return 1;
            temp = temp->next;
        }
        return 0;
    }

    string addFriend(int id, string name)
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
            n->prev = temp;
        }

        return name + " added to your friends list.";
    }

    string removeFriend(int id)
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

    string display()
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
};




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

    ChatStack()
    {
        top   = -1;
        timer = 0;
    }

    int isEmpty() { return top == -1; }
    int isFull()  { return top == 49; }

    string push(int senderId, string senderName, string text)
    {
        if(isFull()) return "Chat is full.";

        timer++;
        a[++top].senderId  = senderId;
        a[top].senderName  = senderName;
        a[top].text        = text;
        a[top].timestamp   = timer;

        return "Message sent.";
    }

    string pop()
    {
        if(isEmpty()) return "No messages to delete.";

        string msg = "Deleted: [" + a[top].senderName + "]: " + a[top].text;
        top--;
        return msg;
    }

    string peek()
    {
        if(isEmpty()) return "No messages yet.";
        return "Latest -> [" + a[top].senderName + "]: " + a[top].text;
    }

    string display()
    {
        if(isEmpty()) return "Group chat is empty.";

        string result = "\n===== Group Chat (newest first) =====\n";
        for(int i = top; i >= 0; i--)
        {
            result += "  t=" + to_string(a[i].timestamp)
                   + " [" + a[i].senderName + "]: "
                   + a[i].text + "\n";
        }
        return result;
    }
};




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

    NewsFeedQueue()
    {
        front = -1;
        rear  = -1;
    }

    int isEmpty() { return front == -1; }
    int isFull()  { return rear == 49; }

    string enqueue(int authorId, string authorName, string content)
    {
        if(isFull()) return "News feed is full.";

        if(front == -1) front = 0;

        rear++;
        a[rear].authorId   = authorId;
        a[rear].authorName = authorName;
        a[rear].content    = content;

        return "Post shared to news feed!";
    }

    string dequeue()
    {
        if(isEmpty()) return "News feed is empty.";

        string msg = "Removed post by: " + a[front].authorName;

        if(front == rear)
            front = rear = -1;
        else
            front++;

        return msg;
    }

    string peek()
    {
        if(isEmpty()) return "News feed is empty.";
        return "Next -> [" + a[front].authorName + "]: " + a[front].content;
    }

    string display()
    {
        if(isEmpty()) return "News feed is empty.";

        string result = "\n===== News Feed =====\n";
        for(int i = front; i <= rear; i++)
        {
            result += "  [" + a[i].authorName + "]: "
                    + a[i].content + "\n";
        }
        return result;
    }
};




// ================= TRENDING POSTS (BST) =================

class TNode
{
public:
    int    likes;
    string postContent;
    string authorName;
    TNode *left, *right;

    TNode(int l, string content, string author)
    {
        likes       = l;
        postContent = content;
        authorName  = author;
        left        = NULL;
        right       = NULL;
    }
};

class BST
{
    TNode *root;

    TNode* insert(TNode *node, int likes, string content, string author)
    {
        if(node == NULL)
            return new TNode(likes, content, author);

        if(likes < node->likes)
            node->left  = insert(node->left,  likes, content, author);
        else
            node->right = insert(node->right, likes, content, author);

        return node;
    }

    void inorder(TNode *node, string &result)
    {
        if(node == NULL) return;
        inorder(node->left, result);
        result += "  Likes: " + to_string(node->likes)
               + " | By: "   + node->authorName
               + " | "       + node->postContent + "\n";
        inorder(node->right, result);
    }

    void search(TNode *node, int likes, string &result)
    {
        if(node == NULL) { result = "Post not found."; return; }

        if(likes == node->likes)
        {
            result = "Found -> Likes: " + to_string(node->likes)
                   + " | By: " + node->authorName
                   + " | "     + node->postContent;
            return;
        }

        if(likes < node->likes)
            search(node->left,  likes, result);
        else
            search(node->right, likes, result);
    }

public:

    BST() { root = NULL; }

    string addPost(int likes, string content, string author)
    {
        root = insert(root, likes, content, author);
        return "Post added to trending!";
    }

    string showTrending()
    {
        if(root == NULL) return "No trending posts.";

        string result = "\n===== Trending Posts (sorted by likes) =====\n";
        inorder(root, result);
        return result;
    }

    string searchPost(int likes)
    {
        string result;
        search(root, likes, result);
        return result;
    }
};




// ================= SOCIAL CONNECTIONS (GRAPH) =================

class GNode
{
public:
    int    userId;
    string userName;
    GNode *next;

    GNode(int id, string name)
    {
        userId   = id;
        userName = name;
        next     = NULL;
    }
};

class GraphList
{
    GNode  *adj[50];
    int     ids[50];
    string  names[50];
    int     userCount;

    int findUser(int id)
    {
        for(int i = 0; i < userCount; i++)
            if(ids[i] == id) return i;
        return -1;
    }

public:

    GraphList()
    {
        userCount = 0;
        for(int i = 0; i < 50; i++)
            adj[i] = NULL;
    }

    void addUser(int id, string name)
    {
        if(userCount == 50)    return;
        if(findUser(id) != -1) return;

        ids[userCount]   = id;
        names[userCount] = name;
        adj[userCount]   = NULL;
        userCount++;
    }

    string connect(int idA, string nameA, int idB, string nameB)
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

    string removeConnection(int idA, int idB)
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

    string display()
    {
        if(userCount == 0) return "Network is empty.";

        string result = "\n===== Social Connections =====\n";
        for(int i = 0; i < userCount; i++)
        {
            result += "  [" + to_string(ids[i]) + "] " + names[i] + " -> ";

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
};




// ================= SESSION =================

class Session
{
public:
    int    userId;
    string userName;
    bool   loggedIn;

    Session()
    {
        userId   = -1;
        userName = "";
        loggedIn = false;
    }

    void login(int id, string name)
    {
        userId   = id;
        userName = name;
        loggedIn = true;
    }

    void logout()
    {
        userId   = -1;
        userName = "";
        loggedIn = false;
    }
};




// ================= FRIENDS LIST ARRAY (one per profile slot) =================

DoublyList friendsLists[50];




// ================= MENUS =================

void profileMenu(ProfileArray &pa, Session &session)
{
    int choice;
    do
    {
        cout << endl;
        cout << "===== MY PROFILE =====" << endl;
        cout << "1. View My Profile"     << endl;
        cout << "2. View All Users"      << endl;
        cout << "0. Back"               << endl;
        cout << "Choice: ";
        cin  >> choice;
        cin.ignore();

        if(choice == 1)
            cout << pa.viewProfile(session.userId) << endl;
        else if(choice == 2)
            cout << pa.display() << endl;
        else if(choice != 0)
            cout << "Invalid choice. Please try again." << endl;

    } while(choice != 0);
}

void friendsMenu(ProfileArray &pa, GraphList &gl, Session &session)
{
    int idx = pa.findById(session.userId);
    if(idx == -1) { cout << "Session error." << endl; return; }

    DoublyList &myList = friendsLists[idx];

    int choice;
    do
    {
        cout << endl;
        cout << "===== FRIENDS ==========="  << endl;
        cout << "1. Add Friend (by ID)"      << endl;
        cout << "2. Remove Friend (by ID)"   << endl;
        cout << "3. View My Friends"         << endl;
        cout << "0. Back"                    << endl;
        cout << "Choice: ";
        cin  >> choice;
        cin.ignore();

        if(choice == 1)
        {
            int fid;
            cout << "Enter friend's ID: ";
            cin  >> fid; cin.ignore();

            if(fid == session.userId)
            {
                cout << "You cannot add yourself." << endl;
            }
            else
            {
                UserProfile *fp = pa.getProfile(fid);
                if(fp == NULL)
                    cout << "User ID not found." << endl;
                else
                {
                    cout << myList.addFriend(fid, fp->name) << endl;
                    cout << gl.connect(session.userId, session.userName,
                                       fid, fp->name) << endl;
                }
            }
        }
        else if(choice == 2)
        {
            int fid;
            cout << "Enter friend's ID to remove: ";
            cin  >> fid; cin.ignore();

            UserProfile *fp = pa.getProfile(fid);
            if(fp == NULL)
                cout << "User ID not found." << endl;
            else
            {
                cout << myList.removeFriend(fid) << endl;
                cout << gl.removeConnection(session.userId, fid) << endl;
            }
        }
        else if(choice == 3)
            cout << myList.display() << endl;
        else if(choice != 0)
            cout << "Invalid choice. Please try again." << endl;

    } while(choice != 0);
}

void chatMenu(ChatStack &cs, Session &session)
{
    int choice;
    do
    {
        cout << endl;
        cout << "===== GROUP CHAT ==========="  << endl;
        cout << "1. Send Message"               << endl;
        cout << "2. Delete Last Message (Pop)"  << endl;
        cout << "3. View Latest (Peek)"         << endl;
        cout << "4. View All Messages"          << endl;
        cout << "0. Back"                       << endl;
        cout << "Choice: ";
        cin  >> choice;
        cin.ignore();

        if(choice == 1)
        {
            string text;
            cout << "Message: ";
            getline(cin, text);
            cout << cs.push(session.userId, session.userName, text) << endl;
        }
        else if(choice == 2)
            cout << cs.pop() << endl;
        else if(choice == 3)
            cout << cs.peek() << endl;
        else if(choice == 4)
            cout << cs.display() << endl;
        else if(choice != 0)
            cout << "Invalid choice. Please try again." << endl;

    } while(choice != 0);
}

void feedMenu(NewsFeedQueue &nq, Session &session)
{
    int choice;
    do
    {
        cout << endl;
        cout << "===== NEWS FEED ========"    << endl;
        cout << "1. Post Something"           << endl;
        cout << "2. View All Feed"            << endl;
        cout << "3. View Next Post (Peek)"    << endl;
        cout << "4. Remove Oldest Post"       << endl;
        cout << "0. Back"                     << endl;
        cout << "Choice: ";
        cin  >> choice;
        cin.ignore();

        if(choice == 1)
        {
            string content;
            cout << "What's on your mind? ";
            getline(cin, content);
            cout << nq.enqueue(session.userId, session.userName, content) << endl;
        }
        else if(choice == 2)
            cout << nq.display() << endl;
        else if(choice == 3)
            cout << nq.peek() << endl;
        else if(choice == 4)
            cout << nq.dequeue() << endl;
        else if(choice != 0)
            cout << "Invalid choice. Please try again." << endl;

    } while(choice != 0);
}

void trendingMenu(BST &bst, Session &session)
{
    int choice;
    do
    {
        cout << endl;
        cout << "===== TRENDING POSTS ======="  << endl;
        cout << "1. Add Post to Trending"       << endl;
        cout << "2. View Trending (sorted)"     << endl;
        cout << "3. Search by Likes"            << endl;
        cout << "0. Back"                       << endl;
        cout << "Choice: ";
        cin  >> choice;
        cin.ignore();

        if(choice == 1)
        {
            int    likes;
            string content;
            cout << "Likes count: ";
            cin  >> likes; cin.ignore();
            cout << "Post content: ";
            getline(cin, content);
            cout << bst.addPost(likes, content, session.userName) << endl;
        }
        else if(choice == 2)
            cout << bst.showTrending() << endl;
        else if(choice == 3)
        {
            int likes;
            cout << "Enter likes to search: ";
            cin  >> likes; cin.ignore();
            cout << bst.searchPost(likes) << endl;
        }
        else if(choice != 0)
            cout << "Invalid choice. Please try again." << endl;

    } while(choice != 0);
}

void connectionsMenu(GraphList &gl)
{
    int choice;
    do
    {
        cout << endl;
        cout << "===== SOCIAL CONNECTIONS =====" << endl;
        cout << "1. View All Connections"        << endl;
        cout << "0. Back"                        << endl;
        cout << "Choice: ";
        cin  >> choice;
        cin.ignore();

        if(choice == 1)
            cout << gl.display() << endl;
        else if(choice != 0)
            cout << "Invalid choice. Please try again." << endl;

    } while(choice != 0);
}

void mainMenu(ProfileArray &pa, GraphList &gl,
              ChatStack &cs, NewsFeedQueue &nq,
              BST &bst, Session &session)
{
    int choice;
    do
    {
        cout << endl;
        cout << "==============================="    << endl;
        cout << "  Hi, " << session.userName << "!" << endl;
        cout << "==============================="    << endl;
        cout << "1. My Profile"                     << endl;
        cout << "2. Friends"                        << endl;
        cout << "3. Group Chat"                     << endl;
        cout << "4. News Feed"                      << endl;
        cout << "5. Trending Posts"                 << endl;
        cout << "6. Social Connections"             << endl;
        cout << "0. Logout"                         << endl;
        cout << "==============================="    << endl;
        cout << "Choice: ";
        cin  >> choice;
        cin.ignore();

        if     (choice == 1) profileMenu(pa, session);
        else if(choice == 2) friendsMenu(pa, gl, session);
        else if(choice == 3) chatMenu(cs, session);
        else if(choice == 4) feedMenu(nq, session);
        else if(choice == 5) trendingMenu(bst, session);
        else if(choice == 6) connectionsMenu(gl);
        else if(choice != 0)
            cout << "Invalid choice. Please try again." << endl;

    } while(choice != 0);

    session.logout();
    cout << "Logged out successfully." << endl;
}




// ================= MAIN =================

int main()
{
    ProfileArray  pa;
    GraphList     gl;
    ChatStack     cs;
    NewsFeedQueue nq;
    BST           bst;
    Session       session;

    // -------- Pre-loaded Sample Data --------

    pa.addProfile(1, "Waseem Rehman", "waseem_r", 20);
    pa.addProfile(2, "Eshal Noor",    "eshal_n",  20);
    pa.addProfile(3, "Mohsin Ihsan",  "mohsin_i", 21);
    pa.addProfile(4, "Tawheed Ullah", "tawheed_u", 22);

    gl.addUser(1, "Waseem Rehman");
    gl.addUser(2, "Eshal Noor");
    gl.addUser(3, "Mohsin Ihsan");
    gl.addUser(4, "Tawheed Ullah");

    // Waseem's friends (index 0)
    friendsLists[0].addFriend(2, "Eshal Noor");
    friendsLists[0].addFriend(3, "Mohsin Ihsan");
    gl.connect(1, "Waseem Rehman", 2, "Eshal Noor");
    gl.connect(1, "Waseem Rehman", 3, "Mohsin Ihsan");

    // Eshal's friends (index 1)
    friendsLists[1].addFriend(1, "Waseem Rehman");
    friendsLists[1].addFriend(4, "Tawheed Ullah");
    gl.connect(2, "Eshal Noor", 4, "Tawheed Ullah");

    // Mohsin's friends (index 2)
    friendsLists[2].addFriend(1, "Waseem Rehman");

    // Tawheed's friends (index 3)
    friendsLists[3].addFriend(2, "Eshal Noor");

    // Group chat
    cs.push(1, "Waseem Rehman", "Guys did you see the new Spider-Man trailer?");
    cs.push(2, "Eshal Noor",    "Yes! It looks amazing!");
    cs.push(3, "Mohsin Ihsan",  "Can't wait for it!");
    cs.push(4, "Tawheed Ullah", "We should all go watch it together.");

    // News feed
    nq.enqueue(1, "Waseem Rehman", "Just submitted my DSA project. Feeling great!");
    nq.enqueue(2, "Eshal Noor",    "Beautiful sunset at Lake View Park today.");
    nq.enqueue(3, "Mohsin Ihsan",  "Finals are coming up. Time to grind!");
    nq.enqueue(4, "Tawheed Ullah", "Islamabad weather is perfect right now.");

    // Trending
    bst.addPost(245, "5 study habits every student must know.",  "Waseem Rehman");
    bst.addPost(512, "How to stay consistent in university.",    "Eshal Noor");
    bst.addPost(89,  "Morning walks change everything.",         "Mohsin Ihsan");
    bst.addPost(380, "Top 10 places to visit in Islamabad.",    "Tawheed Ullah");

    cout << "======================================" << endl;
    cout << "   SOCIAL NETWORK PLATFORM"             << endl;
    cout << "   DSA Project - Data loaded!"          << endl;
    cout << "======================================" << endl;

    // ----------------------------------------

    int choice;
    do
    {
        cout << endl;
        cout << "===============================" << endl;
        cout << "   SOCIAL NETWORK PLATFORM"      << endl;
        cout << "===============================" << endl;
        cout << "1. Login"                        << endl;
        cout << "2. Create Account"               << endl;
        cout << "3. View All Users"               << endl;
        cout << "0. Exit"                         << endl;
        cout << "===============================" << endl;
        cout << "Choice: ";

        // safe integer input
        string input;
        getline(cin, input);

        // check if input is a valid number
        int valid = 1;
        for(int i = 0; i < (int)input.size(); i++)
        {
            if(input[i] < '0' || input[i] > '9')
            {
                valid = 0;
                break;
            }
        }

        if(!valid || input.empty())
        {
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        choice = stoi(input);

        if(choice == 1)
        {
            cout << "Enter your ID: ";
            string idInput;
            getline(cin, idInput);

            int validId = 1;
            for(int i = 0; i < (int)idInput.size(); i++)
            {
                if(idInput[i] < '0' || idInput[i] > '9')
                {
                    validId = 0;
                    break;
                }
            }

            if(!validId || idInput.empty())
            {
                cout << "Invalid ID. Please enter a correct numeric ID." << endl;
                continue;
            }

            int id = stoi(idInput);
            UserProfile *p = pa.getProfile(id);

            if(p == NULL)
                cout << "ID not found. Please enter a correct ID." << endl;
            else
            {
                session.login(id, p->name);
                cout << "Welcome back, " << p->name << "!" << endl;
                mainMenu(pa, gl, cs, nq, bst, session);
            }
        }
        else if(choice == 2)
        {
            int    id, age;
            string name, username;

            cout << "Enter ID: ";       cin >> id;       cin.ignore();
            cout << "Enter Name: ";     getline(cin, name);
            cout << "Enter Username: "; getline(cin, username);
            cout << "Enter Age: ";      cin >> age;      cin.ignore();

            cout << pa.addProfile(id, name, username, age) << endl;
            gl.addUser(id, name);
        }
        else if(choice == 3)
            cout << pa.display() << endl;
        else if(choice != 0)
            cout << "Invalid choice. Please enter 0-3." << endl;

    } while(choice != 0);

    cout << "Goodbye!" << endl;
    return 0;
}
