#ifndef BST_H
#define BST_H

#include <string>
using namespace std;


// ================= TRENDING POSTS (BST) =================

class TNode
{
public:
    int    likes;
    string postContent;
    string authorName;
    TNode *left, *right;

    TNode(int l, string content, string author);
};

class BST
{
    TNode *root;

    TNode* insert(TNode *node, int likes, string content, string author);
    void   inorder(TNode *node, string &result);
    void   search(TNode *node, int likes, string &result);

public:

    BST();

    string addPost(int likes, string content, string author);
    string showTrending();
    string searchPost(int likes);
};

#endif // BST_H
