#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QStackedWidget>
#include <QScrollArea>
#include <QFrame>
#include <QPixmap>
#include <QPainter>
#include <QFileDialog>

#include "profilearray.h"
#include "doublylist.h"
#include "chatstack.h"
#include "newsfeedqueue.h"
#include "bst.h"
#include "graphlist.h"


// ================= SESSION =================

class Session
{
public:
    int    userId;
    string userName;
    string picPath;
    bool   loggedIn;

    Session()
    {
        userId   = -1;
        userName = "";
        picPath  = "";
        loggedIn = false;
    }

    void login(int id, string name, string pic)
    {
        userId   = id;
        userName = name;
        picPath  = pic;
        loggedIn = true;
    }

    void logout()
    {
        userId   = -1;
        userName = "";
        picPath  = "";
        loggedIn = false;
    }
};


// ================= FRIENDS LIST ARRAY =================

extern DoublyList friendsLists[50];


// ================= MAIN WINDOW =================

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    // Auth
    void on_btnLogin_clicked();
    void on_btnGoToSignup_clicked();
    void on_btnCreateAccount_clicked();
    void on_btnBackToLogin_clicked();
    void on_btnLogout_clicked();

    // Signup pic
    void on_btnPickSignupPic_clicked();

    // Profile
    void on_btnViewMyProfile_clicked();
    void on_btnViewAllProfiles_clicked();
    void on_btnChangePic_clicked();

    // Friends
    void on_btnAddFriend_clicked();
    void on_btnRemoveFriend_clicked();
    void on_btnViewFriends_clicked();

    // Chat
    void on_btnSendMessage_clicked();
    void on_btnDeleteMessage_clicked();
    void on_btnPeekMessage_clicked();
    void on_btnViewChat_clicked();

    // Feed
    void on_btnPost_clicked();
    void on_btnViewFeed_clicked();
    void on_btnPeekFeed_clicked();
    void on_btnRemoveFeedPost_clicked();

    // Trending
    void on_btnAddTrending_clicked();
    void on_btnViewTrending_clicked();
    void on_btnSearchTrending_clicked();

    // Connections
    void on_btnViewConnections_clicked();

    // Nav
    void showPage(int index);

private:

    // ---- DS ----
    ProfileArray  pa;
    GraphList     gl;
    ChatStack     cs;
    NewsFeedQueue nq;
    BST           bst;
    Session       session;

    // ---- Stacks ----
    QStackedWidget *mainStack;
    QStackedWidget *pageStack;

    // ---- Shared output ----
    QTextEdit  *txtOutput;

    // ---- Header ----
    QLabel *lblHeader;
    QLabel *lblHeaderUser;

    // ---- Avatar (lives in profile page) ----
    QLabel *avatarLabel;

    // ---- Nav Buttons ----
    QPushButton *navProfile;
    QPushButton *navFriends;
    QPushButton *navChat;
    QPushButton *navFeed;
    QPushButton *navTrending;
    QPushButton *navConnections;

    // ---- Login ----
    QLineEdit *txtLoginId;
    QLabel    *lblLoginError;

    // ---- Signup ----
    QLineEdit   *txtSignupId;
    QLineEdit   *txtSignupName;
    QLineEdit   *txtSignupUsername;
    QLineEdit   *txtSignupAge;
    QLabel      *lblSignupMsg;
    QLabel      *lblSignupPicPreview;
    QString      signupPicPath;

    // ---- Friends ----
    QLineEdit *txtFriendId;

    // ---- Chat ----
    QLineEdit *txtChatMessage;

    // ---- Feed ----
    QLineEdit *txtFeedPost;

    // ---- Trending ----
    QLineEdit *txtTrendingPost;
    QSpinBox  *spinTrendingLikes;

    // ---- Builders ----
    QWidget* buildLoginPage();
    QWidget* buildSignupPage();
    QWidget* buildAppWidget();
    QWidget* buildProfilePage();
    QWidget* buildFriendsPage();
    QWidget* buildChatPage();
    QWidget* buildFeedPage();
    QWidget* buildTrendingPage();
    QWidget* buildConnectionsPage();

    // ---- Helpers ----
    QPushButton* makeBtn(const QString &text, const QString &bg, const QString &fg = "#ffffff");
    QPushButton* makeNavBtn(const QString &icon, const QString &label);
    QLineEdit*   makeInput(const QString &placeholder);
    QLabel*      makeSectionTitle(const QString &text);
    QFrame*      makeDivider();
    QPixmap      makeCircularPixmap(const QString &path, int size);
    void         showOutput(const QString &text);
    void         updateAvatar();
    void         updateNavHighlight(int index);
    void         loadSampleData();

    int currentPage = 0;

    // ---- Colors ----
    QString bgColor       = "#FFFFFF";
    QString bgGray        = "#FAFAFA";
    QString borderColor   = "#DBDBDB";
    QString primaryBlue   = "#0095F6";
    QString textPrimary   = "#262626";
    QString textSecondary = "#8E8E8E";
    QString redColor      = "#ED4956";
    QString greenColor    = "#2ECC71";
};

#endif // MAINWINDOW_H
