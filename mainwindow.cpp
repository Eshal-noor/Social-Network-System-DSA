#include "mainwindow.h"
#include <QString>


// ================= GLOBAL =================

DoublyList friendsLists[50];


// ================= CONSTRUCTOR =================

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("SocialNet");
    setFixedSize(430, 780);

    // Create shared widgets BEFORE any page builder
    txtOutput = new QTextEdit();
    txtOutput->setReadOnly(true);
    txtOutput->setFixedHeight(150);
    txtOutput->setStyleSheet(
        "QTextEdit {"
        "  background-color:#FAFAFA;"
        "  color:#262626;"
        "  border:none;"
        "  border-top:1px solid #DBDBDB;"
        "  padding:10px;"
        "  font-size:13px;"
        "}"
        );

    avatarLabel = new QLabel();
    avatarLabel->setFixedSize(90, 90);
    avatarLabel->setAlignment(Qt::AlignCenter);
    avatarLabel->setStyleSheet(
        "background-color:#DBDBDB;"
        "border-radius:45px;"
        "font-size:28px; font-weight:700; color:#262626;"
        );
    avatarLabel->setText("?");

    signupPicPath = "";

    QWidget     *root   = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(root);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    setCentralWidget(root);
    root->setStyleSheet("background-color:#FFFFFF;");

    mainStack = new QStackedWidget();
    mainStack->addWidget(buildLoginPage());   // 0
    mainStack->addWidget(buildSignupPage());  // 1
    mainStack->addWidget(buildAppWidget());   // 2
    layout->addWidget(mainStack);

    mainStack->setCurrentIndex(0);
    loadSampleData();
}

MainWindow::~MainWindow() {}


// ================= SAMPLE DATA =================

void MainWindow::loadSampleData()
{
    // Preload with embedded resource pictures
    pa.addProfile(1, "Waseem Rehman", "waseem_r",  20, ":/images/waseem.jpg");
    pa.addProfile(2, "Eshal Noor",    "eshal_n",   20, ":/images/eshal.jpg");
    pa.addProfile(3, "Mohsin Ihsan",  "mohsin_i",  21, ":/images/mohsin.jpg");
    pa.addProfile(4, "Tawheed Ullah", "tawheed_u", 22, ":/images/tawheed.jpg");

    gl.addUser(1,"Waseem Rehman");
    gl.addUser(2,"Eshal Noor");
    gl.addUser(3,"Mohsin Ihsan");
    gl.addUser(4,"Tawheed Ullah");

    friendsLists[0].addFriend(2,"Eshal Noor");
    friendsLists[0].addFriend(3,"Mohsin Ihsan");
    gl.connect(1,"Waseem Rehman",2,"Eshal Noor");
    gl.connect(1,"Waseem Rehman",3,"Mohsin Ihsan");

    friendsLists[1].addFriend(1,"Waseem Rehman");
    friendsLists[1].addFriend(4,"Tawheed Ullah");
    gl.connect(2,"Eshal Noor",4,"Tawheed Ullah");

    friendsLists[2].addFriend(1,"Waseem Rehman");
    friendsLists[3].addFriend(2,"Eshal Noor");

    cs.push(1,"Waseem Rehman","Guys did you see the new Spider-Man trailer?");
    cs.push(2,"Eshal Noor",   "Yes! It looks amazing!");
    cs.push(3,"Mohsin Ihsan", "Can't wait for it!");
    cs.push(4,"Tawheed Ullah","We should all go watch it together.");

    nq.enqueue(1,"Waseem Rehman","Just submitted my DSA project. Feeling great!");
    nq.enqueue(2,"Eshal Noor",   "Beautiful sunset at Lake View Park today.");
    nq.enqueue(3,"Mohsin Ihsan", "Finals are coming up. Time to grind!");
    nq.enqueue(4,"Tawheed Ullah","Islamabad weather is perfect right now.");

    bst.addPost(245,"5 study habits every student must know.", "Waseem Rehman");
    bst.addPost(512,"How to stay consistent in university.",   "Eshal Noor");
    bst.addPost(89, "Morning walks change everything.",        "Mohsin Ihsan");
    bst.addPost(380,"Top 10 places to visit in Islamabad.",   "Tawheed Ullah");
}


// ================= HELPERS =================

void MainWindow::showOutput(const QString &text)
{
    txtOutput->setPlainText(text);
}

QPixmap MainWindow::makeCircularPixmap(const QString &path, int size)
{
    QPixmap src(path);
    if(src.isNull()) return QPixmap();

    src = src.scaled(size, size, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QPixmap circle(size, size);
    circle.fill(Qt::transparent);
    QPainter painter(&circle);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(src));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(0, 0, size, size);
    painter.end();

    return circle;
}

void MainWindow::updateAvatar()
{
    QString path = QString::fromStdString(session.picPath);

    if(path.isEmpty())
    {
        // Show initials
        string initials = "";
        bool nextCap = true;
        for(char c : session.userName)
        {
            if(c == ' ') { nextCap = true; }
            else if(nextCap) { initials += c; nextCap = false; }
        }
        avatarLabel->setText(QString::fromStdString(initials));
        avatarLabel->setPixmap(QPixmap());
        avatarLabel->setStyleSheet(
            "background-color:#DBDBDB;"
            "border-radius:45px;"
            "font-size:28px; font-weight:700; color:#262626;"
            );
    }
    else
    {
        QPixmap circle = makeCircularPixmap(path, 90);
        if(!circle.isNull())
        {
            avatarLabel->setPixmap(circle);
            avatarLabel->setText("");
            avatarLabel->setStyleSheet("border-radius:45px;");
        }
        else
        {
            avatarLabel->setText("?");
            avatarLabel->setStyleSheet(
                "background-color:#DBDBDB;"
                "border-radius:45px;"
                "font-size:28px; font-weight:700; color:#262626;"
                );
        }
    }
}

QPushButton* MainWindow::makeBtn(const QString &text, const QString &bg, const QString &fg)
{
    QPushButton *btn = new QPushButton(text);
    btn->setFixedHeight(44);
    btn->setCursor(Qt::PointingHandCursor);
    btn->setStyleSheet(QString(
                           "QPushButton {"
                           "  background-color:%1;"
                           "  color:%2;"
                           "  border:none;"
                           "  border-radius:8px;"
                           "  font-size:14px;"
                           "  font-weight:600;"
                           "}"
                           "QPushButton:pressed { opacity:0.7; }"
                           ).arg(bg, fg));
    return btn;
}

QPushButton* MainWindow::makeNavBtn(const QString &icon, const QString &label)
{
    QPushButton *btn = new QPushButton(icon + "\n" + label);
    btn->setFixedHeight(68);
    btn->setCursor(Qt::PointingHandCursor);
    btn->setStyleSheet(
        "QPushButton {"
        "  background-color:transparent;"
        "  color:#8E8E8E;"
        "  border:none;"
        "  font-size:11px;"
        "  font-weight:500;"
        "  padding:6px 0;"
        "}"
        "QPushButton:hover { color:#262626; }"
        "QPushButton:pressed { color:#0095F6; }"
        );
    return btn;
}

QLineEdit* MainWindow::makeInput(const QString &placeholder)
{
    QLineEdit *inp = new QLineEdit();
    inp->setPlaceholderText(placeholder);
    inp->setFixedHeight(44);
    inp->setStyleSheet(
        "QLineEdit {"
        "  background-color:#FAFAFA;"
        "  color:#262626;"
        "  border:1px solid #DBDBDB;"
        "  border-radius:6px;"
        "  padding:0 12px;"
        "  font-size:14px;"
        "}"
        "QLineEdit:focus {"
        "  border:1px solid #A8A8A8;"
        "  background-color:#FFFFFF;"
        "}"
        );
    return inp;
}

QLabel* MainWindow::makeSectionTitle(const QString &text)
{
    QLabel *lbl = new QLabel(text);
    lbl->setStyleSheet(
        "font-size:15px; font-weight:700;"
        "color:#262626; padding:4px 0 8px 0;"
        );
    return lbl;
}

QFrame* MainWindow::makeDivider()
{
    QFrame *f = new QFrame();
    f->setFrameShape(QFrame::HLine);
    f->setFixedHeight(1);
    f->setStyleSheet("background-color:#DBDBDB; border:none;");
    return f;
}

void MainWindow::updateNavHighlight(int index)
{
    QList<QPushButton*> btns = {
        navProfile,navFriends,navChat,
        navFeed,navTrending,navConnections
    };
    for(int i = 0; i < btns.size(); i++)
    {
        if(i == index)
            btns[i]->setStyleSheet(
                "QPushButton {"
                "  background-color:transparent;"
                "  color:#0095F6;"
                "  border:none;"
                "  font-size:11px;"
                "  font-weight:700;"
                "  padding:6px 0;"
                "}"
                );
        else
            btns[i]->setStyleSheet(
                "QPushButton {"
                "  background-color:transparent;"
                "  color:#8E8E8E;"
                "  border:none;"
                "  font-size:11px;"
                "  font-weight:500;"
                "  padding:6px 0;"
                "}"
                "QPushButton:hover { color:#262626; }"
                );
    }
}

void MainWindow::showPage(int index)
{
    pageStack->setCurrentIndex(index);
    currentPage = index;
    QStringList titles = {
        "Profile","Friends","Messages",
        "Feed","Trending","Network"
    };
    lblHeader->setText(titles[index]);
    updateNavHighlight(index);
}


// ================= LOGIN PAGE =================

QWidget* MainWindow::buildLoginPage()
{
    QWidget     *w  = new QWidget();
    QVBoxLayout *vl = new QVBoxLayout(w);
    vl->setContentsMargins(40,0,40,40);
    vl->setSpacing(10);
    w->setStyleSheet("background-color:#FFFFFF;");

    vl->addStretch(2);

    QLabel *logo = new QLabel("SocialNet");
    logo->setAlignment(Qt::AlignCenter);
    logo->setStyleSheet(
        "font-size:40px; font-weight:700; color:#262626;"
        "font-family:Georgia,serif; padding-bottom:24px;"
        );
    vl->addWidget(logo);

    txtLoginId = makeInput("Enter your ID (number)");
    vl->addWidget(txtLoginId);

    lblLoginError = new QLabel("");
    lblLoginError->setAlignment(Qt::AlignCenter);
    lblLoginError->setStyleSheet("color:#ED4956; font-size:12px;");
    lblLoginError->setWordWrap(true);
    vl->addWidget(lblLoginError);

    QPushButton *btnLogin = makeBtn("Log In", primaryBlue);
    vl->addWidget(btnLogin);

    vl->addStretch(3);
    vl->addWidget(makeDivider());
    vl->addSpacing(12);

    QHBoxLayout *row = new QHBoxLayout();
    QLabel *noAcc = new QLabel("Don't have an account?");
    noAcc->setStyleSheet("color:#8E8E8E; font-size:13px;");
    QPushButton *btnGoSignup = new QPushButton("Sign up.");
    btnGoSignup->setFlat(true);
    btnGoSignup->setCursor(Qt::PointingHandCursor);
    btnGoSignup->setStyleSheet(
        "color:#0095F6; font-size:13px; font-weight:600;"
        "border:none; background:transparent;"
        );
    row->addStretch();
    row->addWidget(noAcc);
    row->addWidget(btnGoSignup);
    row->addStretch();
    vl->addLayout(row);

    connect(btnLogin,    &QPushButton::clicked, this, &MainWindow::on_btnLogin_clicked);
    connect(btnGoSignup, &QPushButton::clicked, this, &MainWindow::on_btnGoToSignup_clicked);

    return w;
}


// ================= SIGNUP PAGE =================

QWidget* MainWindow::buildSignupPage()
{
    QScrollArea *scroll = new QScrollArea();
    QWidget     *w      = new QWidget();
    QVBoxLayout *vl     = new QVBoxLayout(w);
    scroll->setWidget(w);
    scroll->setWidgetResizable(true);
    scroll->setStyleSheet("border:none; background:#FFFFFF;");

    vl->setContentsMargins(40,20,40,40);
    vl->setSpacing(10);
    w->setStyleSheet("background-color:#FFFFFF;");

    QLabel *logo = new QLabel("SocialNet");
    logo->setAlignment(Qt::AlignCenter);
    logo->setStyleSheet(
        "font-size:36px; font-weight:700; color:#262626;"
        "font-family:Georgia,serif; padding-bottom:6px;"
        );
    vl->addWidget(logo);

    QLabel *sub = new QLabel("Sign up to connect with your friends.");
    sub->setAlignment(Qt::AlignCenter);
    sub->setStyleSheet("color:#8E8E8E; font-size:13px; padding-bottom:12px;");
    vl->addWidget(sub);

    // ---- Profile pic section ----
    lblSignupPicPreview = new QLabel();
    lblSignupPicPreview->setFixedSize(80,80);
    lblSignupPicPreview->setAlignment(Qt::AlignCenter);
    lblSignupPicPreview->setStyleSheet(
        "background-color:#DBDBDB;"
        "border-radius:40px;"
        "font-size:28px;"
        );
    lblSignupPicPreview->setText("👤");

    QPushButton *btnPickPic = new QPushButton("Add Profile Photo  (optional)");
    btnPickPic->setFlat(true);
    btnPickPic->setCursor(Qt::PointingHandCursor);
    btnPickPic->setStyleSheet(
        "color:#0095F6; font-size:13px; font-weight:600;"
        "border:none; background:transparent;"
        );

    QHBoxLayout *picRow = new QHBoxLayout();
    picRow->addStretch();
    picRow->addWidget(lblSignupPicPreview);
    picRow->addSpacing(12);
    picRow->addWidget(btnPickPic);
    picRow->addStretch();
    vl->addLayout(picRow);

    vl->addSpacing(8);

    // ---- Inputs ----
    txtSignupName     = makeInput("Full Name");
    txtSignupUsername = makeInput("Username");
    txtSignupId       = makeInput("ID (number)");
    txtSignupAge      = makeInput("Age");

    vl->addWidget(txtSignupName);
    vl->addWidget(txtSignupUsername);
    vl->addWidget(txtSignupId);
    vl->addWidget(txtSignupAge);

    lblSignupMsg = new QLabel("");
    lblSignupMsg->setAlignment(Qt::AlignCenter);
    lblSignupMsg->setStyleSheet("font-size:12px;");
    lblSignupMsg->setWordWrap(true);
    vl->addWidget(lblSignupMsg);

    QPushButton *btnCreate = makeBtn("Sign Up", primaryBlue);
    vl->addWidget(btnCreate);

    vl->addStretch();
    vl->addWidget(makeDivider());
    vl->addSpacing(12);

    QHBoxLayout *row = new QHBoxLayout();
    QLabel *haveAcc = new QLabel("Have an account?");
    haveAcc->setStyleSheet("color:#8E8E8E; font-size:13px;");
    QPushButton *btnBack = new QPushButton("Log in.");
    btnBack->setFlat(true);
    btnBack->setCursor(Qt::PointingHandCursor);
    btnBack->setStyleSheet(
        "color:#0095F6; font-size:13px; font-weight:600;"
        "border:none; background:transparent;"
        );
    row->addStretch();
    row->addWidget(haveAcc);
    row->addWidget(btnBack);
    row->addStretch();
    vl->addLayout(row);

    connect(btnPickPic, &QPushButton::clicked, this, &MainWindow::on_btnPickSignupPic_clicked);
    connect(btnCreate,  &QPushButton::clicked, this, &MainWindow::on_btnCreateAccount_clicked);
    connect(btnBack,    &QPushButton::clicked, this, &MainWindow::on_btnBackToLogin_clicked);

    return scroll;
}


// ================= APP WIDGET =================

QWidget* MainWindow::buildAppWidget()
{
    QWidget     *w  = new QWidget();
    QVBoxLayout *vl = new QVBoxLayout(w);
    vl->setContentsMargins(0,0,0,0);
    vl->setSpacing(0);
    w->setStyleSheet("background-color:#FFFFFF;");

    // ---- Header ----
    QWidget     *header = new QWidget();
    QHBoxLayout *hl     = new QHBoxLayout(header);
    header->setFixedHeight(52);
    header->setStyleSheet(
        "background-color:#FFFFFF;"
        "border-bottom:1px solid #DBDBDB;"
        );
    hl->setContentsMargins(16,0,16,0);

    lblHeader = new QLabel("Profile");
    lblHeader->setStyleSheet(
        "font-size:18px; font-weight:700; color:#262626;"
        "font-family:Georgia,serif;"
        );

    lblHeaderUser = new QLabel("");
    lblHeaderUser->setStyleSheet("font-size:12px; color:#8E8E8E;");

    QPushButton *btnLogout = new QPushButton("Log out");
    btnLogout->setFlat(true);
    btnLogout->setCursor(Qt::PointingHandCursor);
    btnLogout->setStyleSheet(
        "color:#ED4956; font-size:13px; font-weight:600;"
        "border:none; background:transparent;"
        );

    hl->addWidget(lblHeader);
    hl->addStretch();
    hl->addWidget(lblHeaderUser);
    hl->addSpacing(8);
    hl->addWidget(btnLogout);
    vl->addWidget(header);

    // ---- Page Stack ----
    pageStack = new QStackedWidget();
    pageStack->addWidget(buildProfilePage());      // 0
    pageStack->addWidget(buildFriendsPage());      // 1
    pageStack->addWidget(buildChatPage());         // 2
    pageStack->addWidget(buildFeedPage());         // 3
    pageStack->addWidget(buildTrendingPage());     // 4
    pageStack->addWidget(buildConnectionsPage());  // 5
    vl->addWidget(pageStack, 1);

    // ---- Shared Output ----
    vl->addWidget(txtOutput);

    // ---- Bottom Nav ----
    QWidget     *navBar = new QWidget();
    QHBoxLayout *nl     = new QHBoxLayout(navBar);
    navBar->setFixedHeight(68);
    navBar->setStyleSheet(
        "background-color:#FFFFFF;"
        "border-top:1px solid #DBDBDB;"
        );
    nl->setContentsMargins(0,0,0,0);
    nl->setSpacing(0);

    navProfile     = makeNavBtn("🏠","Profile");
    navFriends     = makeNavBtn("👥","Friends");
    navChat        = makeNavBtn("💬","Messages");
    navFeed        = makeNavBtn("📰","Feed");
    navTrending    = makeNavBtn("🔥","Trending");
    navConnections = makeNavBtn("🌐","Network");

    nl->addWidget(navProfile);
    nl->addWidget(navFriends);
    nl->addWidget(navChat);
    nl->addWidget(navFeed);
    nl->addWidget(navTrending);
    nl->addWidget(navConnections);
    vl->addWidget(navBar);

    connect(navProfile,     &QPushButton::clicked, this, [=](){ showPage(0); });
    connect(navFriends,     &QPushButton::clicked, this, [=](){ showPage(1); });
    connect(navChat,        &QPushButton::clicked, this, [=](){ showPage(2); });
    connect(navFeed,        &QPushButton::clicked, this, [=](){ showPage(3); });
    connect(navTrending,    &QPushButton::clicked, this, [=](){ showPage(4); });
    connect(navConnections, &QPushButton::clicked, this, [=](){ showPage(5); });
    connect(btnLogout,      &QPushButton::clicked, this, &MainWindow::on_btnLogout_clicked);

    return w;
}


// ================= PAGE BUILDERS =================

QWidget* MainWindow::buildProfilePage()
{
    QScrollArea *scroll = new QScrollArea();
    QWidget     *page   = new QWidget();
    QVBoxLayout *vl     = new QVBoxLayout(page);
    vl->setContentsMargins(20,20,20,20);
    vl->setSpacing(12);
    scroll->setWidget(page);
    scroll->setWidgetResizable(true);
    scroll->setStyleSheet("border:none; background:white;");

    QHBoxLayout *avatarRow = new QHBoxLayout();
    avatarRow->addStretch();
    avatarRow->addWidget(avatarLabel);
    avatarRow->addStretch();
    vl->addLayout(avatarRow);

    QPushButton *btnChangePic = new QPushButton("Change Photo");
    btnChangePic->setFlat(true);
    btnChangePic->setCursor(Qt::PointingHandCursor);
    btnChangePic->setStyleSheet(
        "color:#0095F6; font-size:13px; font-weight:600;"
        "border:none; background:transparent;"
        );
    QHBoxLayout *picRow = new QHBoxLayout();
    picRow->addStretch();
    picRow->addWidget(btnChangePic);
    picRow->addStretch();
    vl->addLayout(picRow);

    vl->addWidget(makeDivider());
    vl->addWidget(makeSectionTitle("My Account"));

    QPushButton *btnViewMine = makeBtn("View My Profile", primaryBlue);
    QPushButton *btnViewAll  = makeBtn("View All Users",  bgGray, textPrimary);
    btnViewAll->setStyleSheet(btnViewAll->styleSheet() +
                              "QPushButton { border:1px solid #DBDBDB; }");

    vl->addWidget(btnViewMine);
    vl->addWidget(btnViewAll);
    vl->addStretch();

    connect(btnViewMine,  &QPushButton::clicked, this, &MainWindow::on_btnViewMyProfile_clicked);
    connect(btnViewAll,   &QPushButton::clicked, this, &MainWindow::on_btnViewAllProfiles_clicked);
    connect(btnChangePic, &QPushButton::clicked, this, &MainWindow::on_btnChangePic_clicked);

    return scroll;
}

QWidget* MainWindow::buildFriendsPage()
{
    QScrollArea *scroll = new QScrollArea();
    QWidget     *page   = new QWidget();
    QVBoxLayout *vl     = new QVBoxLayout(page);
    vl->setContentsMargins(20,20,20,20);
    vl->setSpacing(12);
    scroll->setWidget(page);
    scroll->setWidgetResizable(true);
    scroll->setStyleSheet("border:none; background:white;");

    vl->addWidget(makeSectionTitle("Friends  —  Doubly Linked List"));
    txtFriendId = makeInput("Enter friend's ID (number)");
    vl->addWidget(txtFriendId);

    QPushButton *btnAdd    = makeBtn("Add Friend",      primaryBlue);
    QPushButton *btnRemove = makeBtn("Remove Friend",   redColor);
    QPushButton *btnView   = makeBtn("My Friends List", bgGray, textPrimary);
    btnView->setStyleSheet(btnView->styleSheet() + "QPushButton { border:1px solid #DBDBDB; }");

    vl->addWidget(btnAdd);
    vl->addWidget(btnRemove);
    vl->addWidget(makeDivider());
    vl->addWidget(btnView);
    vl->addStretch();

    connect(btnAdd,    &QPushButton::clicked, this, &MainWindow::on_btnAddFriend_clicked);
    connect(btnRemove, &QPushButton::clicked, this, &MainWindow::on_btnRemoveFriend_clicked);
    connect(btnView,   &QPushButton::clicked, this, &MainWindow::on_btnViewFriends_clicked);

    return scroll;
}

QWidget* MainWindow::buildChatPage()
{
    QScrollArea *scroll = new QScrollArea();
    QWidget     *page   = new QWidget();
    QVBoxLayout *vl     = new QVBoxLayout(page);
    vl->setContentsMargins(20,20,20,20);
    vl->setSpacing(12);
    scroll->setWidget(page);
    scroll->setWidgetResizable(true);
    scroll->setStyleSheet("border:none; background:white;");

    vl->addWidget(makeSectionTitle("Group Chat  —  Stack"));
    txtChatMessage = makeInput("Write a message...");
    vl->addWidget(txtChatMessage);

    QPushButton *btnSend   = makeBtn("Send Message",       primaryBlue);
    QPushButton *btnDelete = makeBtn("Delete Last (Pop)",  redColor);
    QPushButton *btnPeek   = makeBtn("View Latest (Peek)", bgGray, textPrimary);
    QPushButton *btnView   = makeBtn("View All Messages",  bgGray, textPrimary);
    btnPeek->setStyleSheet(btnPeek->styleSheet() + "QPushButton { border:1px solid #DBDBDB; }");
    btnView->setStyleSheet(btnView->styleSheet() + "QPushButton { border:1px solid #DBDBDB; }");

    vl->addWidget(btnSend);
    vl->addWidget(btnDelete);
    vl->addWidget(makeDivider());
    vl->addWidget(btnPeek);
    vl->addWidget(btnView);
    vl->addStretch();

    connect(btnSend,   &QPushButton::clicked, this, &MainWindow::on_btnSendMessage_clicked);
    connect(btnDelete, &QPushButton::clicked, this, &MainWindow::on_btnDeleteMessage_clicked);
    connect(btnPeek,   &QPushButton::clicked, this, &MainWindow::on_btnPeekMessage_clicked);
    connect(btnView,   &QPushButton::clicked, this, &MainWindow::on_btnViewChat_clicked);

    return scroll;
}

QWidget* MainWindow::buildFeedPage()
{
    QScrollArea *scroll = new QScrollArea();
    QWidget     *page   = new QWidget();
    QVBoxLayout *vl     = new QVBoxLayout(page);
    vl->setContentsMargins(20,20,20,20);
    vl->setSpacing(12);
    scroll->setWidget(page);
    scroll->setWidgetResizable(true);
    scroll->setStyleSheet("border:none; background:white;");

    vl->addWidget(makeSectionTitle("News Feed  —  Queue"));
    txtFeedPost = makeInput("What's on your mind?");
    vl->addWidget(txtFeedPost);

    QPushButton *btnPost   = makeBtn("Post",               primaryBlue);
    QPushButton *btnView   = makeBtn("View All Feed",      bgGray, textPrimary);
    QPushButton *btnPeek   = makeBtn("View Next Post",     bgGray, textPrimary);
    QPushButton *btnRemove = makeBtn("Remove Oldest Post", redColor);
    btnView->setStyleSheet(btnView->styleSheet() + "QPushButton { border:1px solid #DBDBDB; }");
    btnPeek->setStyleSheet(btnPeek->styleSheet() + "QPushButton { border:1px solid #DBDBDB; }");

    vl->addWidget(btnPost);
    vl->addWidget(makeDivider());
    vl->addWidget(btnView);
    vl->addWidget(btnPeek);
    vl->addWidget(btnRemove);
    vl->addStretch();

    connect(btnPost,   &QPushButton::clicked, this, &MainWindow::on_btnPost_clicked);
    connect(btnView,   &QPushButton::clicked, this, &MainWindow::on_btnViewFeed_clicked);
    connect(btnPeek,   &QPushButton::clicked, this, &MainWindow::on_btnPeekFeed_clicked);
    connect(btnRemove, &QPushButton::clicked, this, &MainWindow::on_btnRemoveFeedPost_clicked);

    return scroll;
}

QWidget* MainWindow::buildTrendingPage()
{
    QScrollArea *scroll = new QScrollArea();
    QWidget     *page   = new QWidget();
    QVBoxLayout *vl     = new QVBoxLayout(page);
    vl->setContentsMargins(20,20,20,20);
    vl->setSpacing(12);
    scroll->setWidget(page);
    scroll->setWidgetResizable(true);
    scroll->setStyleSheet("border:none; background:white;");

    vl->addWidget(makeSectionTitle("Trending Posts  —  BST"));

    QHBoxLayout *likesRow = new QHBoxLayout();
    QLabel *lbl = new QLabel("Likes:");
    lbl->setStyleSheet("color:#262626; font-size:13px;");
    spinTrendingLikes = new QSpinBox();
    spinTrendingLikes->setRange(0,999999);
    spinTrendingLikes->setFixedHeight(44);
    spinTrendingLikes->setStyleSheet(
        "QSpinBox { background-color:#FAFAFA; color:#262626;"
        "border:1px solid #DBDBDB; border-radius:6px;"
        "padding:0 8px; font-size:14px; }"
        );
    likesRow->addWidget(lbl);
    likesRow->addWidget(spinTrendingLikes);
    vl->addLayout(likesRow);

    txtTrendingPost = makeInput("Post content");
    vl->addWidget(txtTrendingPost);

    QPushButton *btnAdd    = makeBtn("Add to Trending",        primaryBlue);
    QPushButton *btnView   = makeBtn("View Trending (sorted)", bgGray, textPrimary);
    QPushButton *btnSearch = makeBtn("Search by Likes",        bgGray, textPrimary);
    btnView->setStyleSheet(btnView->styleSheet()     + "QPushButton { border:1px solid #DBDBDB; }");
    btnSearch->setStyleSheet(btnSearch->styleSheet() + "QPushButton { border:1px solid #DBDBDB; }");

    vl->addWidget(btnAdd);
    vl->addWidget(makeDivider());
    vl->addWidget(btnView);
    vl->addWidget(btnSearch);
    vl->addStretch();

    connect(btnAdd,    &QPushButton::clicked, this, &MainWindow::on_btnAddTrending_clicked);
    connect(btnView,   &QPushButton::clicked, this, &MainWindow::on_btnViewTrending_clicked);
    connect(btnSearch, &QPushButton::clicked, this, &MainWindow::on_btnSearchTrending_clicked);

    return scroll;
}

QWidget* MainWindow::buildConnectionsPage()
{
    QScrollArea *scroll = new QScrollArea();
    QWidget     *page   = new QWidget();
    QVBoxLayout *vl     = new QVBoxLayout(page);
    vl->setContentsMargins(20,20,20,20);
    vl->setSpacing(12);
    scroll->setWidget(page);
    scroll->setWidgetResizable(true);
    scroll->setStyleSheet("border:none; background:white;");

    vl->addWidget(makeSectionTitle("Social Connections  —  Graph"));

    QLabel *info = new QLabel(
        "Connections update automatically\nwhen you add or remove friends."
        );
    info->setStyleSheet("color:#8E8E8E; font-size:13px;");
    info->setWordWrap(true);
    vl->addWidget(info);

    QPushButton *btnView = makeBtn("View All Connections", primaryBlue);
    vl->addWidget(btnView);
    vl->addStretch();

    connect(btnView, &QPushButton::clicked, this, &MainWindow::on_btnViewConnections_clicked);

    return scroll;
}


// ================= AUTH SLOTS =================

void MainWindow::on_btnLogin_clicked()
{
    QString input = txtLoginId->text().trimmed();
    lblLoginError->setText("");

    if(input.isEmpty())
    {
        lblLoginError->setText("Please enter your ID.");
        return;
    }

    bool ok;
    int id = input.toInt(&ok);
    if(!ok)
    {
        lblLoginError->setText("ID must be a number.");
        return;
    }

    UserProfile *p = pa.getProfile(id);
    if(p == NULL)
    {
        lblLoginError->setText("ID not found. Please enter a correct ID or sign up.");
        return;
    }

    session.login(id, p->name, p->picPath);
    lblHeaderUser->setText(QString::fromStdString("@" + p->username));
    updateAvatar();
    txtLoginId->clear();
    mainStack->setCurrentIndex(2);
    showPage(0);
    showOutput(QString("Welcome back, %1!")
                   .arg(QString::fromStdString(p->name)));
}

void MainWindow::on_btnGoToSignup_clicked()
{
    signupPicPath = "";
    lblSignupPicPreview->setText("👤");
    lblSignupPicPreview->setPixmap(QPixmap());
    lblSignupPicPreview->setStyleSheet(
        "background-color:#DBDBDB; border-radius:40px; font-size:28px;"
        );
    mainStack->setCurrentIndex(1);
}

void MainWindow::on_btnPickSignupPic_clicked()
{
    QString path = QFileDialog::getOpenFileName(
        this, "Select Profile Photo", "",
        "Images (*.png *.jpg *.jpeg *.bmp)"
        );
    if(!path.isEmpty())
    {
        signupPicPath = path;
        QPixmap circle = makeCircularPixmap(path, 80);
        if(!circle.isNull())
        {
            lblSignupPicPreview->setPixmap(circle);
            lblSignupPicPreview->setText("");
            lblSignupPicPreview->setStyleSheet("border-radius:40px;");
        }
    }
}

void MainWindow::on_btnCreateAccount_clicked()
{
    QString idStr    = txtSignupId->text().trimmed();
    QString ageStr   = txtSignupAge->text().trimmed();
    string  name     = txtSignupName->text().trimmed().toStdString();
    string  username = txtSignupUsername->text().trimmed().toStdString();

    if(idStr.isEmpty() || ageStr.isEmpty() || name.empty() || username.empty())
    {
        lblSignupMsg->setStyleSheet("color:#ED4956; font-size:12px;");
        lblSignupMsg->setText("Please fill in all fields.");
        return;
    }

    bool ok1, ok2;
    int id  = idStr.toInt(&ok1);
    int age = ageStr.toInt(&ok2);

    if(!ok1 || !ok2)
    {
        lblSignupMsg->setStyleSheet("color:#ED4956; font-size:12px;");
        lblSignupMsg->setText("ID and Age must be numbers.");
        return;
    }

    // picPath is optional — empty string if not picked
    string picPath = signupPicPath.toStdString();

    string result = pa.addProfile(id, name, username, age, picPath);
    gl.addUser(id, name);

    if(result.find("already") != string::npos || result.find("full") != string::npos)
    {
        lblSignupMsg->setStyleSheet("color:#ED4956; font-size:12px;");
        lblSignupMsg->setText(QString::fromStdString(result));
        return;
    }

    lblSignupMsg->setStyleSheet("color:#2ECC71; font-size:12px;");
    lblSignupMsg->setText("Account created! You can now log in.");
    txtSignupId->clear();
    txtSignupName->clear();
    txtSignupUsername->clear();
    txtSignupAge->clear();
    signupPicPath = "";
}

void MainWindow::on_btnBackToLogin_clicked()
{
    lblSignupMsg->setText("");
    mainStack->setCurrentIndex(0);
}

void MainWindow::on_btnLogout_clicked()
{
    session.logout();
    txtLoginId->clear();
    lblLoginError->setText("");
    mainStack->setCurrentIndex(0);
}


// ================= PROFILE SLOTS =================

void MainWindow::on_btnViewMyProfile_clicked()
{
    showOutput(QString::fromStdString(pa.viewProfile(session.userId)));
}

void MainWindow::on_btnViewAllProfiles_clicked()
{
    showOutput(QString::fromStdString(pa.display()));
}

void MainWindow::on_btnChangePic_clicked()
{
    QString path = QFileDialog::getOpenFileName(
        this, "Select Profile Picture", "",
        "Images (*.png *.jpg *.jpeg *.bmp)"
        );
    if(!path.isEmpty())
    {
        session.picPath = path.toStdString();

        // also update in profile array
        UserProfile *p = pa.getProfile(session.userId);
        if(p != NULL) p->picPath = path.toStdString();

        updateAvatar();
        showOutput("Profile picture updated!");
    }
}


// ================= FRIENDS SLOTS =================

void MainWindow::on_btnAddFriend_clicked()
{
    QString input = txtFriendId->text().trimmed();
    if(input.isEmpty()) { showOutput("Please enter a friend's ID."); return; }

    bool ok;
    int fid = input.toInt(&ok);
    if(!ok) { showOutput("Friend ID must be a number."); return; }
    if(fid == session.userId) { showOutput("You cannot add yourself."); return; }

    UserProfile *fp = pa.getProfile(fid);
    if(fp == NULL) { showOutput("User ID not found."); return; }

    int idx = pa.findById(session.userId);
    string r1 = friendsLists[idx].addFriend(fid, fp->name);
    string r2 = gl.connect(session.userId, session.userName, fid, fp->name);
    showOutput(QString::fromStdString(r1 + "\n" + r2));
    txtFriendId->clear();
}

void MainWindow::on_btnRemoveFriend_clicked()
{
    QString input = txtFriendId->text().trimmed();
    if(input.isEmpty()) { showOutput("Please enter a friend's ID."); return; }

    bool ok;
    int fid = input.toInt(&ok);
    if(!ok) { showOutput("Friend ID must be a number."); return; }

    UserProfile *fp = pa.getProfile(fid);
    if(fp == NULL) { showOutput("User ID not found."); return; }

    int idx = pa.findById(session.userId);
    string r1 = friendsLists[idx].removeFriend(fid);
    string r2 = gl.removeConnection(session.userId, fid);
    showOutput(QString::fromStdString(r1 + "\n" + r2));
    txtFriendId->clear();
}

void MainWindow::on_btnViewFriends_clicked()
{
    int idx = pa.findById(session.userId);
    showOutput(QString::fromStdString(friendsLists[idx].display()));
}


// ================= CHAT SLOTS =================

void MainWindow::on_btnSendMessage_clicked()
{
    string text = txtChatMessage->text().trimmed().toStdString();
    if(text.empty()) { showOutput("Please write a message."); return; }
    showOutput(QString::fromStdString(
        cs.push(session.userId, session.userName, text)
        ));
    txtChatMessage->clear();
}

void MainWindow::on_btnDeleteMessage_clicked()
{
    showOutput(QString::fromStdString(cs.pop()));
}

void MainWindow::on_btnPeekMessage_clicked()
{
    showOutput(QString::fromStdString(cs.peek()));
}

void MainWindow::on_btnViewChat_clicked()
{
    showOutput(QString::fromStdString(cs.display()));
}


// ================= FEED SLOTS =================

void MainWindow::on_btnPost_clicked()
{
    string content = txtFeedPost->text().trimmed().toStdString();
    if(content.empty()) { showOutput("Please write something to post."); return; }
    showOutput(QString::fromStdString(
        nq.enqueue(session.userId, session.userName, content)
        ));
    txtFeedPost->clear();
}

void MainWindow::on_btnViewFeed_clicked()
{
    showOutput(QString::fromStdString(nq.display()));
}

void MainWindow::on_btnPeekFeed_clicked()
{
    showOutput(QString::fromStdString(nq.peek()));
}

void MainWindow::on_btnRemoveFeedPost_clicked()
{
    showOutput(QString::fromStdString(nq.dequeue()));
}


// ================= TRENDING SLOTS =================

void MainWindow::on_btnAddTrending_clicked()
{
    string content = txtTrendingPost->text().trimmed().toStdString();
    if(content.empty()) { showOutput("Please enter post content."); return; }
    showOutput(QString::fromStdString(
        bst.addPost(spinTrendingLikes->value(), content, session.userName)
        ));
    txtTrendingPost->clear();
}

void MainWindow::on_btnViewTrending_clicked()
{
    showOutput(QString::fromStdString(bst.showTrending()));
}

void MainWindow::on_btnSearchTrending_clicked()
{
    showOutput(QString::fromStdString(
        bst.searchPost(spinTrendingLikes->value())
        ));
}


// ================= CONNECTIONS SLOT =================

void MainWindow::on_btnViewConnections_clicked()
{
    showOutput(QString::fromStdString(gl.display()));
}
