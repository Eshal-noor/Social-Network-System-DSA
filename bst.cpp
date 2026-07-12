#include "bst.h"


// ================= TRENDING POSTS (BST) =================

TNode::TNode(int l, string content, string author)
{
    likes       = l;
    postContent = content;
    authorName  = author;
    left        = NULL;
    right       = NULL;
}

BST::BST() { root = NULL; }

TNode* BST::insert(TNode *node, int likes, string content, string author)
{
    if(node == NULL)
        return new TNode(likes, content, author);

    if(likes < node->likes)
        node->left  = insert(node->left,  likes, content, author);
    else
        node->right = insert(node->right, likes, content, author);

    return node;
}

void BST::inorder(TNode *node, string &result)
{
    if(node == NULL) return;
    inorder(node->left, result);
    result += "Likes: " + to_string(node->likes)
              + " | By: "  + node->authorName
              + " | "      + node->postContent + "\n";
    inorder(node->right, result);
}

void BST::search(TNode *node, int likes, string &result)
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

string BST::addPost(int likes, string content, string author)
{
    root = insert(root, likes, content, author);
    return "Post added to trending!";
}

string BST::showTrending()
{
    if(root == NULL) return "No trending posts.";

    string result = "===== Trending (sorted by likes) =====\n";
    inorder(root, result);
    return result;
}

string BST::searchPost(int likes)
{
    string result;
    search(root, likes, result);
    return result;
}
