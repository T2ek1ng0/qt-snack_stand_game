#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "searchdialog.h"
#include"imagedialog.h"
#include<bits/stdc++.h>
#include<locale>
#ifdef _WIN32
#include<windows.h>
#endif
using namespace std;
#define ll long long
#define ld long double
static std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
QMap<QString,bool>achievements={{"「宇宙食商论」", false}, {"「薛定谔的商人」", false},
{"「。。。不知道说什么好，或许这是一种幸运者对不幸者的愧怍。」", false},{"「慈善家还是二道贩子？」",false},
{"「女巫来的」",false},{" 「爷们要战斗」",false},{"「命运掌握在骰子手中」",false},{"「自我催眠」",false},
{"「混乱中立的祭品」",false},{"「债的彼岸」",false},{"「小市民的生存之道」",false},{"「装逼犯」",false},
{"「好评如潮」",false},{"「群众的眼睛是……雇来的」",false},{"「传奇小吃，永不塌房」",false},
{"「“美名远扬，臭名更远”」",false},{"「“真正的口口相传”」",false}};
ll day=8,jgleaveday;
ld mypow(ld x,ll a)
{
    ll result=1;
    while(a>0)
    {
        if(a&1) result*=x;
        x=x*x;
        a>>=1;
    }
    return result;
}

class Food
{
    public:
    ll date,price,spoiltime;
    ld cost;
    bool amount;
    string name;
    friend bool cmp1(const Food &a,const Food &b);
    friend bool cmp2(const Food &a,const Food &b);
    Food(string s,ll p,ll cos):name(s),date(uniform_int_distribution<int>(4,7)(gen)),price(p),cost(cos),spoiltime(0),amount(1){}
    Food():name(),date(),price(),cost(),spoiltime(0),amount(1){}
    Food(string s,ll d,ll p,ll cos):name(s),date(d),price(p),cost(cos),spoiltime(0),amount(1){}
    Food(string s,ll p):name(s),date(uniform_int_distribution<int>(5,10)(gen)),price(p),cost((0.1*p*uniform_int_distribution<int>(1,2)(gen))),spoiltime(0),amount(1){}
    void setdate()
    {
        if(date>0) --date;
    }
    QString printfood()
    {
        QString result;
        result=QString::fromStdString(name)+u8" 成本"+QString::number(cost,'f',2)+u8"欢乐豆 价格"+QString::number(price)+u8"欢乐豆 还有"+QString::number(date)+u8"天过期\n";
        return result;
    }
    ll getprice()
    {
        return price;
    }
};
vector<Food>allfood={Food("cpp项目代写",15,2,0),Food("肉蛋堡",5),Food("章鱼烧",7),Food("炒粉",8),Food("烤冷面",8)};
vector<vector<Food>>inventory;
bool cmp1(const Food &a,const Food &b)
{
    return a.price<b.price;
}
bool cmp2(const Food &a,const Food &b)
{
    return a.date<b.date;
}
class character
{
    protected:
    int birthlast;
    public:
    character(int t):birthlast(t){}
    void setbirth()
    {
        --birthlast;
    }
    int getbirth()
    {
        return birthlast;
    }
};
class Guest:public character
{
    ll like;
    public:
    string name;
    vector<vector<string>>quotation;
    Guest(string s,ll a):name(s),quotation(),character(a),like(uniform_int_distribution<int>(2,5)(gen)){}
    Guest(string s,vector<vector<string>>str):name(s),quotation(str),character(uniform_int_distribution<int>(3,8)(gen)),like(uniform_int_distribution<int>(2,5)(gen)){}
    Guest(string s,ll a,vector<vector<string>>str):name(s),quotation(str),character(a),like(uniform_int_distribution<int>(2,5)(gen)){}
    ll getlike()
    {
        return like;
    }
    void setlike(const ll a)
    {
        if(like<10&&like>=0) like=like+a;
        if(like<0) like=0;
    }
    ll pay()
    {
        vector<ll>temp;
        for(ll i=0;i<inventory.size();++i)
        {
            if(inventory[i][0].amount) temp.push_back(i);      //统计有库存的菜品
        }
        ll t=uniform_int_distribution<ll>(0, temp.size()-1)(gen);
        ll k=t+like/3;            //好感度影响购买倾向：like越高，越倾向选择高价菜品
        if(k>inventory.size()-1) k=inventory.size()-1;
        while(!inventory[k][0].amount&&k>=0) --k;                      //防止越界
        return k;
    }
    QString printguest()
    {
        QString result=QString::fromStdString(name);
        if(birthlast>0) result+=u8" 还有"+QString::number(birthlast)+u8"天生日 好感度"+QString::number(like)+"/10\n";
        else if(birthlast==0) result+=u8" 生日就在今天！ 好感度"+QString::number(like)+"/10\n";
        else if(birthlast<0) result+=u8" 生日已过"+QString::number(abs(birthlast))+u8"天 好感度"+QString::number(like)+"/10\n";
        return result;
    }
};
class Gamer
{
    public:
    ld money,gifttime,beyondlaw,beatpolice,dicetime,dicefail,deadbeat,cowardly,zhuangb,rate;
    Gamer():money(0),gifttime(0),beyondlaw(0),beatpolice(0),dicetime(0),dicefail(0),deadbeat(0),cowardly(0),zhuangb(0),rate(0){}
};
class Police:public character
{
    public:
    ll degree;
    ld policepossible,fakuan;
    Police(ll t):character(uniform_int_distribution<int>(6,8)(gen)),degree(t),policepossible(0.18),fakuan(0.08){}
    Police():character(uniform_int_distribution<int>(6,8)(gen)),degree(),policepossible(0.18),fakuan(0.08){}
    void setdegree(ll t)
    {
        degree=t;
    }
    ll getdegree()
    {
        return degree;
    }
    void setbirth()
    {
        --birthlast;
    }
    ll getbirth()
    {
        return birthlast;
    }
    QString printpolice()
    {
        QString result=u8"城管大人还有"+QString::number(birthlast)+u8"天生日\n"+u8"被城管袭击的概率："+QString::number(policepossible*mypow((1+degree/40),day),'f',2)+'\n';
        return result;
    }
};
vector<Guest>allguests={Guest("lipu",{{u8"lipu\n\n我喜欢披萨放菠萝。",u8"那很美味了",u8"意大利人不会放过你的"},
{u8"lipu\n\n离考试还有一个多小时，现在开始抱佛脚",u8"佛给你一脚",u8"佛给你两脚"},{u8"lipu\n\n不想上学",u8"不想上学",u8"不想上学"},
{u8"lipu\n\n(凝视着锅里的沸腾气泡，若有所思。)\n它们在交流。","你能听懂它们的话？","你是不是该休息一下了？"},
{u8"lipu\n\n(摸了摸桌面，轻声问你。)\n你有没有听见……它在呼吸？",u8"谁在呼吸？！",u8"你等等，我试试能不能听见……"}})
,Guest("jiange",{{u8"jiange\n\n你看得见我吗？\n(低沉的声音从你的脚边传来，地上只是一片薄薄的黑影。)",u8"有鬼啊！",u8"废话"},
{u8"jiange\n\n(静静地伏在地上，声音轻得像是藏在黑暗中的回音。)\n你相信轮回吗？",u8"也许吧",u8"不信，这都是骗人的"},
{u8"jiange\n\n(缓缓地从地面升起一点，像一片微微浮动的墨迹。)\n你觉得世界上会有没有影子的人吗？",u8"也许吧",u8"那很灵异了"}}),
Guest("lihua",{{u8"lihua\n\n喵喵喵",u8"听不懂",u8"听不懂"},{u8"lihua\n\n我想吃肉蛋堡喵",u8"好的喵",u8"猫不能吃这个"},
{u8"lihua\n\n(把一片冷面放在桌上，双手合十，低声念念有词。)\n我要为它祈祷。",u8"你在做什么仪式？",u8"你是认真的吗？"},
{u8"lihua盯着你手里的筷子，眼神莫测。\nlihua：它们知道的比你想象的还要多。",u8"谁？筷子？",u8"你快住口，我害怕。"}}),
Guest("lao8",{{"lao8\n\n……",u8"你好",u8"有话快说"},{u8"lao8\n\n(用手指蘸了一点料汁，放在太阳光下观察。)\n这酱料……它在告诉我一个秘密。",u8"它说了什么？",u8"你喝高了吧？"},
{u8"lao8\n\n(盯着地上的影子，久久不动。)\n你有没有想过，我们的影子，可能才是本体？",u8"你是说我只是影子的幻觉？",u8"你影子刚才动了一下唷"}}),
Guest("ladygaba",{{u8"ladygaba\n\n(缓缓欠身)(你看着ladygaba)\n给我一份炙烧人马腿",u8"?这不好吧。",u8"人马腿最近不好进货，换成矮人肚好吗？"}})};
vector<string>rates={u8"脏乱差",u8"差",u8"一般",u8"还行",u8"很好"};
vector<string>dices={u8"财富之神光顾了你的摊位。今日收入翻倍",u8"幸运女神眷顾了你。今日内遇到城管的几率减小 ",
u8"一觉醒来物价又上涨了。今日的成本增加30%",u8"灰色Micky和广东棕黑色双马尾大精灵光临了你的小摊。\n今日小摊风评降低一档",
u8"城管做梦梦见被你挑衅了。今日内遇到城管的几率翻倍",u8"地球好像多转了一圈。全部预制菜的有效期额外减少1天"};
ld odds=0,earn=0,p0policepossible=0,jgt=0;
ll oddsadd=6,ratesnow=2,dice=0;
Police p;
Gamer g;
ll money0,updated=0;
string rate=rates[ratesnow];
bool downrate=false,lpletter=true,diceratedown=false;
ll policevisit=0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("欢迎来到~老高小吃摊");
    ui->nextpage0->hide();
    ui->nextpage1->hide();
    ui->nextpage2->hide();
    ui->nextpage3->hide();
    ui->nextpage4->hide();
    ui->easy->hide();
    ui->normal->hide();
    ui->hard->hide();
    ui->start->hide();
    ui->diceyes->hide();
    ui->diceno->hide();
    ui->startday->hide();
    ui->scrollArea->setFrameShape(QFrame::NoFrame);
    ui->scrollArea->setGeometry(ui->mainlabel->geometry());
    ui->mainlabel->setParent(ui->scrollArea->viewport());
    ui->scrollArea->setWidget(ui->mainlabel);
    ui->scrollArea->setWidgetResizable(true); // 允许内容自适应
    earn=0;
    loadAchievementsFromFile();
    saveAchievementsToFile();
    ui->mainlabel->setText("欢迎光临老高小吃摊。");
    connect(ui->infoaction,&QAction::triggered,this,&MainWindow::infoactionslot);
    connect(ui->lookachieveaction,&QAction::triggered,this,&MainWindow::openachievement);
    connect(ui->lookguestaction,&QAction::triggered,this,&MainWindow::lookguest);
    connect(ui->lookfoodaction,&QAction::triggered,this,&MainWindow::lookfood1);
    connect(ui->lookreviewaction,&QAction::triggered,this,&MainWindow::lookreview);
    connect(ui->lookpoliceaction,&QAction::triggered,this,&MainWindow::lookpolice);
    connect(ui->actionjiange,&QAction::triggered,this,&MainWindow::jiangestory);
    connect(ui->actionlipu,&QAction::triggered,this,&MainWindow::lipustory);
    connect(ui->actionlihua,&QAction::triggered,this,&MainWindow::lihuastory);
    connect(ui->actionlao8,&QAction::triggered,this,&MainWindow::lao8story);
    connect(ui->actionladygaba,&QAction::triggered,this,&MainWindow::ladygabastory);
    connect(ui->systempause,&QAction::triggered,this,&MainWindow::pauseaction);
}

void MainWindow::pauseaction()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("暂停");
    msgBox.setText("现在游戏暂停惹");
    msgBox.exec();
}

void MainWindow::loadAchievementsFromFile()
{
    QFile file(QCoreApplication::applicationDirPath()+"\\achievements.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"无成就文件，将创建新文件。";
        return;
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    while (!in.atEnd()) {
        QString line=in.readLine();
        // 解析每一行并更新成就状态（根据实际格式调整）
        if (line.contains("已解锁")) {
            QString achievementName=line.split(":")[0].trimmed();
            achievements[achievementName]=true;
        }
    }
    file.close();
}

void MainWindow::saveAchievementsToFile() {
    QFile file(QCoreApplication::applicationDirPath()+"\\achievements.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件！";
        return;
    }
    QByteArray ba;
    QString str=u8"====== 游戏成就 ======\n";
    ll cnttotal=0,cntno=0;
    for (auto it=achievements.begin();it!=achievements.end();++it)
    {
        ++cnttotal;
        QString status=it.value()?u8"已解锁" : u8"未解锁";
        if(!it.value())
        {
            str+=u8"？？？:未解锁\n";
            ++cntno;
        }
        else
        {
            str+=it.key()+": "+status+"\n";
            if(it.key()=="「宇宙食商论」")
            {
                str+="老高小吃摊从此走出小谷围岛，走出平流层，\n走出地球，走出太阳系，走出银河系,走出总星系，走向宇宙。\n";
                str+="因为有你，也许某天外星人也能吃上老高小吃摊的烤冷面。\n但愿你没做昧良心的事情。\n";
            }
            if(it.key()=="「薛定谔的商人」") str+="至少你回本了，至少你回本了，至少你回本了。\n";
            if(it.key()=="「慈善家还是二道贩子？」") str+="你的礼物到底是送出去的，还是借机清库存？\n";
            if(it.key()=="「女巫来的」") str+="卖素肉丸的夜晚，注定不会有好梦。\n";
            if(it.key()=="「爷们要战斗」") str+="你和城管较量了不止三次，具体输赢不重要，重要的是你还在摆摊。\n";
            if(it.key()=="「命运掌握在骰子手中」") str+="你已经不记得上次用理性做决策是什么时候了。\n";
            if(it.key()=="「自我催眠」") str+="“输得够多了，下次一定赢。”——你昨天也这么说\n";
            if(it.key()=="「混乱中立的祭品」") str+="你掷出的骰子究竟是命运的安排，还是单纯的数学错误？\n";
            if(it.key()=="「债的彼岸」") str+="你曾许愿想成为一个自由人，现在你确实身无分文。\n";
            if(it.key()=="「小市民的生存之道」") str+="你给城管送了礼物，不知道你是为了和谐相处，还是单纯懦弱。\n";
            if(it.key()=="「装逼犯」") str+="不管怎样，你是ladygaba亲自认定的装逼犯。\n";
            if(it.key()=="「好评如潮」") str+="摊子名声大噪，人人都说好吃，但奇怪的是，每条评价的语气都出奇地相似。\n";
            if(it.key()=="「群众的眼睛是……雇来的」")
            {
                str+="你的摊位评分稳居榜首，顾客们纷纷留言称赞，甚至有人说，\n吃了你的东西后改写了人生轨迹。\n";
                str+="你开始怀疑，这些评价你是不是在哪见过。\n";
            }
            if(it.key()=="「传奇小吃，永不塌房」") str+="你的摊子已经成为本地美食界的神话，\n所有评价都高度一致，甚至连错别字都一模一样。\n或许，这就是美食的力量？\n";
            if(it.key()=="「“美名远扬，臭名更远”」") str+="你的摊子无人不知无人不晓——主要是因为食安问题上了新闻。\n";
            if(it.key()=="「“真正的口口相传”」") str+="你的摊子声名远播，全是靠顾客们的真实评价。\n没有水军，没有套路，\n只有实打实的好味道——这在如今，简直比美食本身更难得。\n";
        }
    }
    str+="你的成就解锁进度："+QString::number((cnttotal-cntno)*100/cnttotal,'f',1)+"%\n";
    ba.append(str);
    file.write(ba);
    file.close();
}

void MainWindow::openachievement()
{
    QFile file(QCoreApplication::applicationDirPath()+"\\achievements.txt");
    QMessageBox msgBox;
    msgBox.setWindowTitle("成就");
    file.open(QIODevice::ReadOnly);
    QByteArray ba=file.readAll();
    msgBox.setText(QString(ba));
    msgBox.exec();
    file.close();
}

void MainWindow::infoactionslot()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("关于老高小吃摊");
    QString str="代码编写：稿子建\n交互设计及代码实现：稿子建、deepseek\n人物设定：稿子建、找炆芋\n特别鸣谢：\nDeepseek-R1、Chatgpt-4o、Gemini2.5pro(排名分先后)\n";
    msgBox.setText(str);
    msgBox.exec();
}

void MainWindow::lookguest()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("查看顾客");
    QString allOutput="";
    for(int i=0;i<allguests.size();++i) allOutput+=allguests[i].printguest();
    msgBox.setText(allOutput);
    msgBox.exec();
}

void MainWindow::lookpolice()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("查看城管");
    QString allOutput=p.printpolice();
    msgBox.setText(allOutput);
    msgBox.exec();
}

void MainWindow::lookfood1()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("查看菜品");
    QString allOutput="";
    for(int i=0;i<allfood.size();++i) allOutput+=QString::number(i+1)+"."+allfood[i].printfood();
    msgBox.setText(allOutput);
    msgBox.exec();
}

void MainWindow::lookfood2()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("请选择");
    msgBox.setText("选什么好呢……");
    QPushButton *yesButton=msgBox.addButton("按售价排序", QMessageBox::YesRole);
    QPushButton *noButton=msgBox.addButton("按保质期排序", QMessageBox::NoRole);
    msgBox.exec();
    if(msgBox.clickedButton()==yesButton)
    {
        sort(allfood.begin(),allfood.end(),cmp1);
        sort(inventory.begin(), inventory.end(),
            [](const vector<Food>& a, const vector<Food>& b){
                return cmp1(a.front(), b.front());
            });
    }
    else if(msgBox.clickedButton()==noButton)
    {
        for(ll i=0;i<allfood.size();++i) allfood[i].date=inventory[i][0].date;
        sort(allfood.begin(),allfood.end(),cmp2);
        sort(inventory.begin(), inventory.end(),
            [](const vector<Food>& a, const vector<Food>& b){
                return cmp2(a.front(), b.front());
            });
    }
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("查询菜品");
    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);
    dialog->resize(800, 500);
    // 创建表格控件
    QTableWidget *table = new QTableWidget();
    table->setColumnCount(6);
    table->setHorizontalHeaderLabels({"名称", "当前售价", "平均成本","保质期", "库存数量", "操作"});
    table->verticalHeader()->setVisible(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 填充数据
    for (size_t i = 0; i < inventory.size(); ++i)
    {
        int row = table->rowCount();
        table->insertRow(row);

        // 名称
        QTableWidgetItem *nameItem = new QTableWidgetItem(
            QString::fromStdString(inventory[i][0].name));
        table->setItem(row, 0, nameItem);

        // 售价
        QTableWidgetItem *priceItem = new QTableWidgetItem(
            QString::number(inventory[i][0].price));
        table->setItem(row, 1, priceItem);

        // 平均成本
        double avgCost = 0;
        if(inventory[i][0].amount)
        {
            for (const auto& food : inventory[i]) avgCost += food.cost;
            avgCost /= inventory[i].size();
            table->setItem(row, 2, new QTableWidgetItem(QString::number(avgCost, 'f', 2)));
        }
        else table->setItem(row, 2, new QTableWidgetItem("NULL"));

        // 保质期
        QLabel *dateLabel;
        if(!inventory[i][0].amount) dateLabel = new QLabel("NULL");
        else
        {
            QString dateStr;
            vector<ll>temp={inventory[i][0].date};
            for(ll j=1;j<inventory[i].size();++j)
            {
                bool flag=1;
               for(ll k=0;k<temp.size();++k)
               {
                   if(inventory[i][j].date==temp[k]) flag=0;
               }
               if(flag) temp.push_back(inventory[i][j].date);
            }
            dateStr+=QString::number(inventory[i][0].date);
            for(ll k=1;k<temp.size();++k) dateStr+=","+QString::number(temp[k]);
            dateLabel = new QLabel(dateStr);
        }
        dateLabel->setAlignment(Qt::AlignCenter);
        table->setCellWidget(row, 3, dateLabel);

        // 库存数量
        QLabel *countLabel;
        if(inventory[i][0].amount) countLabel=new QLabel(QString::number(inventory[i].size()));
        else countLabel=new QLabel(QString::number(0));
        countLabel->setAlignment(Qt::AlignCenter);
        table->setCellWidget(row, 4, countLabel);

        // 操作列
        QWidget *btnWidget = new QWidget();
        QHBoxLayout *btnLayout = new QHBoxLayout(btnWidget);

        // 进货按钮
        QPushButton *addBtn = new QPushButton("进货");
        addBtn->setStyleSheet("QPushButton { padding: 5px; }");
        connect(addBtn, &QPushButton::clicked, [this, i, table](){
            handleRestock(i, table); // 传递table用于刷新
        });

        // 过期处理按钮
        QPushButton *expireBtn = new QPushButton("处理过期");
        connect(expireBtn, &QPushButton::clicked, [this, i, table](){
            handleExpired(i, table);
        });

        btnLayout->addWidget(addBtn);
        btnLayout->addWidget(expireBtn);
        btnLayout->setContentsMargins(0, 0, 0, 0);
        table->setCellWidget(row, 5, btnWidget);
    }
    mainLayout->addWidget(table);
    dialog->exec();
    QMessageBox msgBox1;
    msgBox1.setWindowTitle("增删菜品");
    QString allOutput="是否需要增加(200欢乐豆/次)或删除菜品(10欢乐豆/次)？\n";
    msgBox1.setText(allOutput);
    QPushButton *addButton = msgBox1.addButton("增加", QMessageBox::YesRole);
    QPushButton *delButton = msgBox1.addButton("删除", QMessageBox::NoRole);
    QPushButton *notingButton = msgBox1.addButton("什么都不做", QMessageBox::RejectRole);
    msgBox1.exec();
    if(msgBox1.clickedButton() == addButton&&g.money<200)
    {
        QMessageBox msgBox2;
        msgBox2.setWindowTitle("warning");
        QString allOutput="欢乐豆不足。\n";
        ++g.deadbeat;
        msgBox2.setText(allOutput);
        msgBox2.exec();
    }
    else if(msgBox1.clickedButton() == addButton) {
        // 新增菜品逻辑
        QString newfoodname = QInputDialog::getText(
            this, "新增菜品", "请输入菜品名称：", QLineEdit::Normal, "");

        QString newfoodprice = QInputDialog::getText(
            this, "设置价格", "请输入售价（欢乐豆）：", QLineEdit::Normal, "");
        bool changeok=true;
        if(!newfoodname.isEmpty()&&!newfoodprice.isEmpty()&&newfoodprice.toLongLong(&changeok)<1000) {
            // 创建新菜品对象
            Food newFood(
                newfoodname.toStdString(),
                newfoodprice.toLongLong()
            );

            // 同步添加到allfood和inventory
            allfood.push_back(newFood);

            // 为新菜品生成初始库存（3-5个）
            vector<Food> newStock;
            int stockCount = uniform_int_distribution<int>(3,5)(gen);
            for(int i=0; i<stockCount; ++i)
            {
                Food stockItem = newFood;
                newStock.push_back(stockItem);
            }
            inventory.push_back(newStock);
            g.money -= 200;
            earn-=200;
            QMessageBox msgBox2;
            msgBox2.setWindowTitle("添加成功");
            QString allOutput="花费200欢乐豆。\n你添加的菜品：\n"+inventory[inventory.size()-1][0].printfood()+"库存："+QString::number(newStock.size())+'\n';
            msgBox2.setText(allOutput);
            msgBox2.exec();
        }
        else
        {
            QMessageBox msgBox2;
            msgBox2.setWindowTitle("添加失败");
            QString allOutput="新菜品的最高售价为999欢乐豆喵。\n";
            msgBox2.setText(allOutput);
            msgBox2.exec();
        }
    }
    else if(msgBox1.clickedButton() == delButton&&g.money<10)
    {
        QMessageBox msgBox1;
        QString allOutput="欢乐豆不足。\n";
        ++g.deadbeat;
        msgBox1.setText(allOutput);
        msgBox1.exec();
    }
    else if(msgBox1.clickedButton() == delButton) {
        // 删除菜品逻辑
        QStringList foodNames;
        for(const auto& food : allfood) {
            foodNames << QString::fromStdString(food.name);
        }

        SearchDialog dlg(foodNames, this);
        if(dlg.exec() == QDialog::Accepted) {
            QString selected = dlg.selectedItem();
            if(selected==QString::fromStdString(allfood[0].name))
            {
                QMessageBox msgBox1;
                msgBox1.setWindowTitle("warning");
                QString allOutput="删除失败。\n不准忘本！\n";
                msgBox1.setText(allOutput);
                msgBox1.exec();
            }
            else
            {
                for(int i=0; i<allfood.size(); ++i){
                    if(QString::fromStdString(allfood[i].name) == selected) {
                        // 同步删除
                        allfood.erase(allfood.begin() + i);
                        inventory.erase(inventory.begin() + i);
                        g.money -= 10;
                        earn-=10;
                        QMessageBox::information(this, "删除成功",
                            QString("已删除%1及其所有库存").arg(selected));
                        break;
                    }
                }
            }
        }
    }

    // 保持排序一致性
    sort(allfood.begin(), allfood.end(), cmp1);
    // inventory需要同步排序
    sort(inventory.begin(), inventory.end(),
        [](const vector<Food>& a, const vector<Food>& b){
            return cmp1(a.front(), b.front());
        });
    QString condition=u8"第"+QString::number(9-day)+u8"天，"+QString::number(g.money,'f',2)+u8"欢乐豆";
    ui->statelabel->setText(condition);
}

void MainWindow::handleRestock(int foodIndex, QTableWidget* table) {
    bool ok;
    // 获取进货数量
    int quantity = QInputDialog::getInt(this, "进货管理",
        QString("请输入%1的进货数量：").arg(QString::fromStdString(inventory[foodIndex][0].name)),
        1, 1, 100, 1, &ok);

    if (ok) {
        // 生成新库存项
        for (int i = 0; i < quantity; ++i) {
            Food newItem = allfood[foodIndex];
            if(p.degree==1) newItem.date = uniform_int_distribution<int>(4,6)(gen);
            else if(p.degree==2) newItem.date = uniform_int_distribution<int>(2,4)(gen);
            else if(p.degree==3) newItem.date = uniform_int_distribution<int>(1,3)(gen);
            if(i==0&&inventory[foodIndex].size()==1&&!inventory[foodIndex][0].amount) inventory[foodIndex][0]=newItem;
            else inventory[foodIndex].push_back(newItem);
        }
        inventory[foodIndex][0].amount=1;
        sort(allfood.begin(),allfood.end(),cmp1);
        sort(inventory.begin(), inventory.end(),
            [](const vector<Food>& a, const vector<Food>& b){
                return cmp1(a.front(), b.front());
            });

            vector<Food>& stock = inventory[foodIndex]; // 当前菜品库存的引用

            // 更新库存数量
            QLabel *countLabel = qobject_cast<QLabel*>(table->cellWidget(foodIndex, 4 /*库存数量列*/));
            if (countLabel) {
                if(stock[0].amount) countLabel->setText(QString::number(stock.size()));
                else countLabel->setText("NULL");
            }

            // 更新平均成本
            double avgCost = 0;
            QTableWidgetItem *costItem = table->item(foodIndex, 2 /*平均成本列*/);
            if (!costItem) {
                costItem = new QTableWidgetItem();
                table->setItem(foodIndex, 2, costItem);
            }
            if(!stock.empty()&&stock[0].amount) {
                for (const auto& foodItem : stock) {
                    avgCost += foodItem.cost;
                }
                avgCost /= stock.size();
                costItem->setText(QString::number(avgCost, 'f', 2));
            } else {
                // 刚进货，一般不会为空，除非进货数量为0 (但已限制数量>=1)
                costItem->setText("NULL");
            }

            // 更新保质期 (唯一日期列表)
            QLabel *dateLabel = qobject_cast<QLabel*>(table->cellWidget(foodIndex, 3 /*保质期列*/));
            if (dateLabel) {
                if (!stock.empty()) {
                    QString dateStr;
                    vector<ll> unique_dates;
                    for(const auto& foodItem : stock) {
                        bool found = false;
                        for(ll ud : unique_dates) {
                            if (ud == foodItem.date) {
                                found = true;
                                break;
                            }
                        }
                        if (!found) {
                            unique_dates.push_back(foodItem.date);
                        }
                    }
                    // sort(unique_dates.begin(), unique_dates.end()); // 可选：排序日期
                    for(size_t k=0; k < unique_dates.size(); ++k) {
                        dateStr += QString::number(unique_dates[k]);
                        if (k < unique_dates.size() - 1) dateStr += ",";
                    }
                    dateLabel->setText(dateStr);
                } else {
                     dateLabel->setText("NULL");
                }
            }
        // 资金扣除
        double cost = allfood[foodIndex].cost * quantity;
        g.money -= cost;
        earn-=cost;

        QMessageBox::information(this, "操作成功",
            QString("成功进货%1件，花费%2欢乐豆")
            .arg(quantity).arg(cost, 0, 'f', 2));
        QString condition=u8"第"+QString::number(9-day)+u8"天，"+QString::number(g.money,'f',2)+u8"欢乐豆";
        ui->statelabel->setText(condition);
    }
}

void MainWindow::handleExpired(int foodIndex, QTableWidget* table) {
    int expiredCount = 0;
    // 遍历检查过期
    for(ll i=inventory[foodIndex].size()-1;i>=0;--i)
    {
        if(inventory[foodIndex][i].date<=0)
        {
            if(inventory[foodIndex].size()<=1)
            {
                inventory[foodIndex][0].amount=0;
                expiredCount++;
            }
            else
            {
                inventory[foodIndex].erase(inventory[foodIndex].begin()+i);
                expiredCount++;
            }
        }
    }
    --allfood[foodIndex].spoiltime;

    // 更新库存数量
    vector<Food>& stock = inventory[foodIndex];
    QLabel *countLabel = qobject_cast<QLabel*>(table->cellWidget(foodIndex, 4 /*库存数量列*/));
    if (countLabel&&stock[0].amount) {
        countLabel->setText(QString::number(stock.size())); // 直接使用剩余库存大小
    }
    else countLabel->setText("NULL");

    // 更新平均成本
    double avgCost = 0;
    QTableWidgetItem *costItem = table->item(foodIndex, 2 /*平均成本列*/);
    if (!costItem) { // 如果单元格不存在，则创建一个新的
        costItem = new QTableWidgetItem();
        table->setItem(foodIndex, 2, costItem);
    }
    if (stock[0].amount) {
        for (const auto& foodItem : stock) {
            avgCost += foodItem.cost;
        }
        avgCost /= stock.size();
        costItem->setText(QString::number(avgCost, 'f', 2));
    } else {
        costItem->setText("NULL"); // 库存为空则显示NULL
    }

    // 更新保质期 (唯一日期列表)
    QLabel *dateLabel = qobject_cast<QLabel*>(table->cellWidget(foodIndex, 3 /*保质期列*/));
    if (dateLabel) {
        if (!stock.empty()) {
            QString dateStr;
            vector<ll> unique_dates; // 用于存储不重复的保质期天数
            for(const auto& foodItem : stock) {
                bool found = false;
                for(ll ud : unique_dates) {
                    if (ud == foodItem.date) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    unique_dates.push_back(foodItem.date);
                }
            }
            // 可以选择对 unique_dates 排序以获得一致的显示顺序
            // sort(unique_dates.begin(), unique_dates.end());
            for(size_t k=0; k < unique_dates.size(); ++k) {
                dateStr += QString::number(unique_dates[k]);
                if (k < unique_dates.size() - 1) dateStr += ","; // 用逗号分隔
            }
            dateLabel->setText(dateStr);
        } else {
            dateLabel->setText("NULL"); // 库存为空则显示NULL
        }
    }
    if(expiredCount)
    {
        QMessageBox::information(this, "处理完成",QString("已扔掉%1件过期库存").arg(expiredCount));
        --allfood[foodIndex].spoiltime;
    }
    else QMessageBox::information(this, "提示", "当前没有过期库存");
}

void MainWindow::lookreview()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("查看摊子风评");
    QString allOutput="摊子现在的风评是："+QString::fromStdString(rates[ratesnow])+"\n要花250欢乐豆买水军提高摊子的风评吗？\n";
    QPushButton *yesButton=msgBox.addButton("花", QMessageBox::YesRole);
    QPushButton *noButton=msgBox.addButton("不花", QMessageBox::NoRole);
    msgBox.setText(allOutput);
    msgBox.exec();
    if(msgBox.clickedButton()==yesButton&&g.money>=250&&ratesnow<4)
    {
        ++ratesnow;
        rate=rates[ratesnow];
        oddsadd+=2;
        g.money-=250;
        earn-=250;
        ++g.rate;
        QMessageBox msgBox1;
        msgBox1.setText("你摊子的风评提升为"+QString::fromStdString(rate)+"。\n");
        msgBox1.exec();
    }
    else if(msgBox.clickedButton()==yesButton&&g.money<250)
    {
        QMessageBox msgBox1;
        msgBox1.setText("欢乐豆不足。\n");
        ++g.deadbeat;
        msgBox1.exec();
    }
    else if(msgBox.clickedButton()==yesButton&&ratesnow==4)
    {
        QMessageBox msgBox1;
        msgBox1.setText("你的摊子风评已经非常好了。\n请不要再买水军污染互联网啦！\n");
        msgBox1.exec();
        ++g.rate;
    }
    QString condition=u8"第"+QString::number(9-day)+u8"天，"+QString::number(g.money,'f',2)+u8"欢乐豆";
    ui->statelabel->setText(condition);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_infobutton_clicked()
{
    ui->mainlabel->clear();
    QFile file(":/new/totaltxt/0.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray ba=file.readAll();
    ui->mainlabel->setText(QString(ba));
    ui->nextpage0->show();
    ui->infobutton->hide();
}

void MainWindow::on_nextpage0_clicked()
{
    ui->mainlabel->clear();
    QString allOutput="操作说明\n操作-暂停可以暂停游戏\n传记可以查看各个顾客的传记\n";
    allOutput+="查询-顾客可以查看各个顾客的具体情况\n查询-菜品可以查看、管理和增删小摊的菜品\n增设菜品时请设置合理的售价\n";
    allOutput+="查询-风评可以查看和管理小摊的风评\n查询-成就可以查看已经解锁的成就，通常成就在游戏结束时才会更新";
    ui->mainlabel->setText(allOutput);
    ui->nextpage0->hide();
    ui->nextpage1->show();
}

void MainWindow::on_nextpage1_clicked()
{
    ui->mainlabel->clear();
    QString allOutput="关于预制菜：是你赖以谋生的伙伴。\n你可以靠售卖这些菜品来赚取欢乐豆。\n";
    for(int i=0;i<allfood.size();++i) allOutput+=QString::number(i+1)+"."+allfood[i].printfood();
    allOutput+="在游戏的进程中，\n你可以花费一些欢乐豆来增加自定义的菜品或删除原有的菜品。\n";
    ui->mainlabel->setText(allOutput);
    ui->nextpage1->hide();
    ui->nextpage2->show();
}

void MainWindow::on_nextpage2_clicked()
{
    ui->mainlabel->clear();
    QString allOutput="关于顾客：花钱的'人'。\n顾客就是上帝。\n";
    for(int i=0;i<allguests.size();++i) allOutput+=allguests[i].printguest();
    ui->mainlabel->setText(allOutput);
    ui->nextpage2->hide();
    ui->nextpage3->show();
}


void MainWindow::on_nextpage3_clicked()
{
    ui->mainlabel->clear();
    QString allOutput="关于城管：负责罚款的'人'。\n请小心地与其周旋。\n";
    allOutput+=p.printpolice();
    ui->mainlabel->setText(allOutput);
    ui->nextpage3->hide();
    ui->nextpage4->show();
}

void MainWindow::on_nextpage4_clicked()
{
    ui->mainlabel->clear();
    ui->nextpage4->hide();
    QString allOutput="关于风评：会影响到摊消费顾客的数量。\n";
    allOutput+=u8"目前摊子的风评为："+QString::fromStdString(rate)+u8"\n\n现在开始游戏吧！\n";
    ui->mainlabel->setText(allOutput);
}

void MainWindow::on_enter1_clicked()
{
    ui->infobutton->hide();
    ui->nextpage0->hide();
    ui->nextpage1->hide();
    ui->nextpage2->hide();
    ui->nextpage3->hide();
    ui->nextpage4->hide();
    ui->enter1->hide();
    ui->mainlabel->clear();
    ui->mainlabel->setText("请选择游戏难度\n");
    ui->easy->show();
    ui->normal->show();
    ui->hard->show();
    disconnect(ui->lookfoodaction,&QAction::triggered,this,&MainWindow::lookfood1);
    connect(ui->lookfoodaction,&QAction::triggered,this,&MainWindow::lookfood2);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        emit rightClick(); // 发射右键信号
        event->accept();  // 标记事件已处理
    } else {
        QMainWindow::mousePressEvent(event); // 其他鼠标事件交给默认处理
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if(event->key()==Qt::Key_Escape) close();
    QMainWindow::keyPressEvent(event);
}

void MainWindow::jiangestory()
{
    ImageDialog dialog(this);
    QFile file(":/new/totaltxt/jiange.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray ba=file.readAll();
    dialog.setContent(":/new/picture/picture/jiange2.jpg",QString(ba));
    dialog.exec(); // 模态显示对话框
}

void MainWindow::lipustory()
{
    ImageDialog dialog(this);
    QFile file(":/new/totaltxt/lipu.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray ba=file.readAll();
    dialog.setContent(":/new/picture/picture/lipu2.jpg",QString(ba));
    dialog.exec(); // 模态显示对话框
}

void MainWindow::lihuastory()
{
    ImageDialog dialog(this);
    QFile file(":/new/totaltxt/lihua.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray ba=file.readAll();
    dialog.setContent(":/new/picture/picture/lihua2.jpg",QString(ba));
    dialog.exec(); // 模态显示对话框
}

void MainWindow::lao8story()
{
    ImageDialog dialog(this);
    QFile file(":/new/totaltxt/lao8.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray ba=file.readAll();
    dialog.setContent(":/new/picture/picture/lao82.jpg",QString(ba));
    dialog.exec(); // 模态显示对话框
}

void MainWindow::ladygabastory()
{
    ImageDialog dialog(this);
    QFile file(":/new/totaltxt/ladygaba.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray ba=file.readAll();
    dialog.setContent(":/new/picture/picture/ladygaba2.jpg",QString(ba));
    dialog.exec(); // 模态显示对话框
}

void MainWindow::on_easy_clicked()
{
    ui->easy->hide();
    ui->normal->hide();
    ui->hard->hide();
    p.setdegree(1);
    int base=400;
    uniform_int_distribution<int>money_dist(base, base+400);
    g.money=money_dist(gen);
    money0=g.money;
    QString currentText = ui->mainlabel->text();
    currentText+="你选择了：简单\n系统今日送您"+QString::number(g.money,'f',2)+u8"欢乐豆！\n";
    ui->mainlabel->setText(currentText);
    for(long long i=0;i<allfood.size();++i)
    {
        vector<Food>temp;
        Food f=allfood[i];
        f.date=uniform_int_distribution<int>(4,7)(gen);
        if(i==0) for(long long j=0;j<60;++j) temp.push_back(allfood[i]);
        else for(long long j=0;j<5;++j) temp.push_back(f);
        inventory.push_back(temp);
    }
    ui->start->show();
}

void MainWindow::on_normal_clicked()
{
    ui->easy->hide();
    ui->normal->hide();
    ui->hard->hide();
    p.setdegree(2);
    int base=200;
    uniform_int_distribution<int>money_dist(base, base+400);
    g.money=money_dist(gen);
    money0=g.money;
    QString currentText = ui->mainlabel->text();
    currentText+="你选择了：一般\n系统今日送您"+QString::number(g.money,'f',2)+u8"欢乐豆！\n";
    ui->mainlabel->setText(currentText);
    for(long long i=0;i<allfood.size();++i)
    {
        vector<Food>temp;
        Food f=allfood[i];
        f.date=uniform_int_distribution<int>(3,5)(gen);
        if(i==0) for(long long j=0;j<60;++j) temp.push_back(allfood[i]);
        else for(long long j=0;j<5;++j) temp.push_back(f);
        inventory.push_back(temp);
    }
    ui->start->show();
}

void MainWindow::on_hard_clicked()
{
    ui->easy->hide();
    ui->normal->hide();
    ui->hard->hide();
    p.setdegree(3);
    int base=100;
    uniform_int_distribution<int>money_dist(base, base+400);
    g.money=money_dist(gen);
    money0=g.money;
    QString currentText = ui->mainlabel->text();
    currentText+="你选择了：困难\n系统今日送您"+QString::number(g.money,'f',2)+u8"欢乐豆！\n";
    ui->mainlabel->setText(currentText);
    for(long long i=0;i<allfood.size();++i)
    {
        vector<Food>temp;
        Food f=allfood[i];
        f.date=uniform_int_distribution<int>(2,4)(gen);
        if(i==0) for(long long j=0;j<60;++j) temp.push_back(allfood[i]);
        else for(long long j=0;j<5;++j) temp.push_back(f);
        inventory.push_back(temp);
    }
    ui->start->show();
}

void MainWindow::on_start_clicked()
{
    ui->mainlabel->clear();
    ui->start->hide();
    QString condition=u8"第"+QString::number(9-day)+u8"天，"+QString::number(g.money,'f',2)+u8"欢乐豆";
    ui->statelabel->setText(condition);
    ui->mainlabel->setText(u8"你有一次掷骰子的机会。\n");
    ui->diceyes->show();
    ui->diceno->show();
}

void MainWindow::on_diceyes_clicked()
{
    ui->diceyes->hide();
    ui->diceno->hide();
    ++g.dicetime;
    ll dice0=dice;
    while(dice==dice0)
    {
        dice=uniform_int_distribution<int>(1,6)(gen);
    }
    dice0=dice;
    QString str=ui->mainlabel->text()+u8"你掷到了"+QString::number(dice)+u8"点。\n";
    if(dice>2) ++g.dicefail;
    str+=QString::fromStdString(dices[dice-1])+'\n';
    ui->mainlabel->setText(str);
    if(dice==2) p.policepossible=0.08;
    if(dice==4)
    {
        if(ratesnow==0) ui->mainlabel->setText(u8"意外之喜！摊位风评差到降无可降！\n");
        else
        {
            diceratedown=true;
            --ratesnow;
            rate=rates[ratesnow];
            oddsadd-=2;
        }
    }
    if(dice==5) p.policepossible=0.3;
    if(dice==6)
    {
        for(ll i=0;i<allfood.size();++i) allfood[i].setdate();
    }
    QString fornext=u8"进入第"+QString::number(9-day)+u8"天";
    ui->dicelabel->setText(QString::fromStdString(dices[dice-1]));
    ui->startday->setText(fornext);
    ui->startday->show();
}

void MainWindow::on_diceno_clicked()
{
    ui->diceyes->hide();
    ui->diceno->hide();
    QString str=ui->mainlabel->text()+"你选择不掷。\n";
    ui->mainlabel->setText(str);
    ui->dicelabel->clear();
    QString fornext=u8"进入第"+QString::number(11-day)+u8"天";
    ui->startday->setText(fornext);
    ui->startday->show();
}

void MainWindow::on_startday_clicked()
{
    ui->mainlabel->clear();
    ui->startday->hide();
    earn=0;
    policevisit=0;
    if(p.getbirth()==0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("城管生日");
        msgBox.setText("城管生日就在今天！要花250欢乐豆送礼吗？");
        QPushButton *yesButton=msgBox.addButton("花", QMessageBox::YesRole);
        QPushButton *noButton=msgBox.addButton("不花", QMessageBox::NoRole);
        msgBox.exec();
        if(msgBox.clickedButton()==yesButton&&g.money>=250)
        {
            earn-=250;
            g.money-=250;
            p.policepossible=0.08;
            ui->mainlabel->setText("你被城管袭击的概率小幅降低了。\n");
            ++g.cowardly;
        }
        else if(msgBox.clickedButton()==yesButton&&g.money<250)
        {
            QMessageBox msgBox1;
            msgBox1.setWindowTitle("warning");
            msgBox1.setText("欢乐豆不足。\n");
            ++g.deadbeat;
        }
        QString condition=u8"第"+QString::number(9-day)+u8"天，"+QString::number(g.money,'f',2)+u8"欢乐豆";
        ui->statelabel->setText(condition);
    }
    if(jgleaveday==1)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("这是俺拾的嘞");
        msgBox.setText("似乎在摊子捡到了遗失物。\n原来是lao8遗落的假刘海。");
        QPushButton *yesButton=msgBox.addButton("戴上", QMessageBox::YesRole);
        QPushButton *noButton=msgBox.addButton("不戴", QMessageBox::NoRole);
        msgBox.exec();
        if(msgBox.clickedButton()==yesButton)
        {
            ui->mainlabel->setText(ui->mainlabel->text()+"城管被你魅惑了。\n从此城管罚款的几率降低了。\n");
            p.fakuan/=3;
        }
        else if(msgBox.clickedButton()==noButton)
        {
            QMessageBox msgBox1;
            msgBox1.setWindowTitle("正直的人");
            msgBox1.setText("希望你不会后悔。\n要还给lao8吗？");
            QPushButton *yesButton1=msgBox1.addButton("还", QMessageBox::YesRole);
            QPushButton *noButton1=msgBox1.addButton("不还", QMessageBox::NoRole);
            msgBox1.exec();
            if(msgBox1.clickedButton()==yesButton1)
            {
                ui->mainlabel->setText(ui->mainlabel->text()+"lao8对你的好感度提升了。\n");
                ll i=0;
                for(;i<allguests.size();++i) if(allguests[i].name=="lao8") break;
                allguests[i].setlike(1);
            }
        }
    }
    if(jgleaveday==3)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("神秘信件");
        msgBox.setText(u8"收到了jiange寄来的食谱。\n你解锁了新菜式：");
        allfood.push_back(Food(u8"吃了就咽痛的曲奇",30,5));
        vector<Food>newStock;
        int stockCount = uniform_int_distribution<int>(3,5)(gen);
        for(int i=0; i<stockCount; ++i)
        {
            Food stockItem=allfood[allfood.size()-1];
            newStock.push_back(stockItem);
        }
        inventory.push_back(newStock);
        QString str=msgBox.text()+allfood[allfood.size()-1].printfood();
        msgBox.setText(str);
        msgBox.exec();
        sort(allfood.begin(),allfood.end(),cmp1);
        sort(inventory.begin(), inventory.end(),
                [](const vector<Food>& a, const vector<Food>& b){
                    return cmp1(a.front(), b.front());
                });
    }
    if(jgleaveday==2)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("神秘信件");
        msgBox.setText(u8"收到了ladygaba寄来的食谱。是否学习呢？\n");
        QPushButton *yesButton=msgBox.addButton("学", QMessageBox::YesRole);
        QPushButton *noButton=msgBox.addButton("不学", QMessageBox::NoRole);
        msgBox.exec();
        if(msgBox.clickedButton()==yesButton)
        {
            ++g.beyondlaw;
            QString str=ui->mainlabel->text()+u8"命运馈赠的礼物，往往在暗中标注了价格。\n";
            ui->mainlabel->setText(str);
            allfood.push_back(Food(u8"素肉丸(配果味含GABA(4-氨基丁酸)的褪黑素酱)",20,5));
            str+="你解锁了新菜式：\n"+allfood[allfood.size()-1].printfood();
            ui->mainlabel->setText(str);
            vector<Food>newStock;
            int stockCount = uniform_int_distribution<int>(3,5)(gen);
            for(int i=0; i<stockCount; ++i)
            {
                Food stockItem=allfood[allfood.size()-1];
                newStock.push_back(stockItem);
            }
            inventory.push_back(newStock);
            sort(allfood.begin(),allfood.end(),cmp1);
            sort(inventory.begin(), inventory.end(),
                    [](const vector<Food>& a, const vector<Food>& b){
                        return cmp1(a.front(), b.front());
                    });
        }
    }
    if(allguests[0].getlike()==10&&lpletter)
    {
        allfood.push_back(Food(u8"奶油蘑菇汤",30,3));
        QMessageBox msgBox;
        msgBox.setWindowTitle("感谢lipu");
        msgBox.setText(u8"lipu今天教会了你新的菜式：");
        allfood[allfood.size()-1].printfood();
        QString str=msgBox.text()+allfood[allfood.size()-1].printfood();
        msgBox.setText(str);
        sort(allfood.begin(),allfood.end(),cmp1);
        lpletter=false;
        msgBox.exec();
    }
    for(ll i=0;i<inventory.size();++i)
    {
        bool flag1=0;
        for(ll j=0;j<inventory[i].size();++j)
        {
            if(inventory[i][j].date<=0&&inventory[i][0].amount) flag1=1;
        }
        if(flag1) ++allfood[i].spoiltime;
        if(inventory[i][0].amount&&flag1)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("我过期了");
            QString str=QString::fromStdString(inventory[i][0].name)+u8"过期了。\n请到查询-菜品中及时处理唷。\n";
            msgBox.setText(str);
            msgBox.exec();
        }
        bool flag=0;
        for(ll k=0;k<allfood.size();++k) if(allfood[k].spoiltime>1) flag=1;
        if(flag1&&flag&&inventory[i][0].amount)
        {
            QString str=ui->mainlabel->text()+u8"奸商。你会遭报应的。\n";
            ui->mainlabel->setText(str);
            ll k=0,temp=0;
            for(ll i=0;i<allguests.size();++i)
            {
                allguests[i].setlike(-0.2);
                temp=uniform_int_distribution<int>(1,5)(gen);
                k=max(k,temp);
            }
        }
    }
    QString str=ui->mainlabel->text();
    for(ll i=0;i<allguests.size();++i)
    {
        if(allguests[i].getbirth()==0)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("顾客生日");
            QString birtstr=QString::fromStdString(allguests[i].name)+u8"生日就在今天！要花25欢乐豆送礼物吗？";
            msgBox.setText(birtstr);
            QPushButton *yesButton=msgBox.addButton("花", QMessageBox::YesRole);
            QPushButton *noButton=msgBox.addButton("不花", QMessageBox::NoRole);
            msgBox.exec();
            if(msgBox.clickedButton()==yesButton&&g.money>=25)
            {
                g.money-=25;
                earn-=25;
                allguests[i].setlike(1);
                ++g.gifttime;
                str+=QString::fromStdString(allguests[i].name)+u8"对你的好感度小幅提升了。\n";
                ui->mainlabel->setText(str);
                QString condition=u8"第"+QString::number(9-day)+u8"天，"+QString::number(g.money,'f',2)+u8"欢乐豆";
                ui->statelabel->setText(condition);
            }
            else if(msgBox.clickedButton()==yesButton&&g.money<25)
            {
                QMessageBox msgBox1;
                msgBox1.setWindowTitle("warning");
                msgBox1.setText("欢乐豆不足。\n");
            }
        }
    }
    str=ui->mainlabel->text();
    for(ll i=0;i<allguests.size();++i)
    {
        odds=uniform_int_distribution<int>(0,90)(gen)/100.0;
        if(odds<=p.policepossible&&policevisit<2)
        {
            ++policevisit;
            QMessageBox msgBox;
            msgBox.setWindowTitle("城管袭来！");
            msgBox.setText("城管袭来了。你选择：");
            QPushButton *yesButton=msgBox.addButton("逃跑", QMessageBox::YesRole);
            QPushButton *noButton=msgBox.addButton("硬刚", QMessageBox::NoRole);
            msgBox.exec();
            if(msgBox.clickedButton()==yesButton)
            {
                ll temp=uniform_int_distribution<int>(18,60)(gen);
                earn-=temp;
                str+="跑得太快，掉了"+QString::number(temp)+u8"欢乐豆\n";
                ui->mainlabel->setText(str);
                g.money-=temp;
                QString condition=u8"第"+QString::number(9-day)+u8"天，"+QString::number(g.money,'f',2)+u8"欢乐豆";
                ui->statelabel->setText(condition);
                break;
            }
            else if(msgBox.clickedButton()==noButton)
            {
                odds=uniform_int_distribution<int>(10,99)(gen)/100.0;
                if(odds<=1-p.policepossible)
                {
                    str+=u8"你把城管骂走了。你下次遇到城管的几率增加了。\n";
                    p.policepossible*=1.1;
                    ++g.beatpolice;
                    ui->mainlabel->setText(str);
                }
                else if(odds>(1-p.policepossible)*(1+p.fakuan))
                {
                    str+=u8"城管劈头盖脸地骂了你一顿，并处罚款250欢乐豆。\n";
                    earn-=250;
                    ui->mainlabel->setText(str);
                    g.money-=250;
                    QString condition=u8"第"+QString::number(9-day)+u8"天，"+QString::number(g.money,'f',2)+u8"欢乐豆";
                    ui->statelabel->setText(condition);
                }
            }
            for(ll i=allfood.size()-1;i>-1;--i)
            {
                if(allfood[i].name=="素肉丸(配果味含GABA(4-氨基丁酸)的褪黑素酱)")
                {
                    str+=u8"无论如何，因为你售卖食品经营许可证之外的食物(素肉丸)，被城管开出150欢乐豆的罚款。\n";
                    earn-=150;
                    g.money-=150;
                    QString condition=u8"第"+QString::number(9-day)+u8"天，"+QString::number(g.money,'f',2)+u8"欢乐豆";
                    ui->statelabel->setText(condition);
                    break;
                }
            }
            ui->mainlabel->setText(str);
        }
        odds=uniform_int_distribution<int>(0,5)(gen)+oddsadd;
        QString path(":/new/picture/picture/");
        QImage img;
        if(odds>5)
        {
            ll t=0;
            if(allguests[i].name!="jiange"&&!allguests[i].quotation.empty())
            {
                uniform_int_distribution<size_t>dist(0, allguests[i].quotation.size()-1);
                t=dist(gen);
            }
            else
            {
                t=jgt;
                ++jgt;
            }
            path+=QString::fromStdString(allguests[i].name);
            path+=".jpg";
            img.load(path);
            ui->picture->setPixmap(QPixmap::fromImage(img));
            QString saystr=QString::fromStdString(allguests[i].quotation[t][0])+'\n';
            ui->sayword->setText(saystr);
            QString usay1=QString::fromStdString(allguests[i].quotation[t][1]);
            QString usay2=QString::fromStdString(allguests[i].quotation[t][2]);
            QMessageBox msgBox;
            msgBox.setWindowTitle("怎么说");
            msgBox.setText("你怎么说？");
            QPushButton *yesButton=msgBox.addButton(usay1, QMessageBox::YesRole);
            QPushButton *noButton=msgBox.addButton(usay2, QMessageBox::NoRole);
            msgBox.exec();
            ll choice=0;
            if(msgBox.clickedButton()==yesButton) choice=1;
            else if(msgBox.clickedButton()==noButton) choice=2;
            path=":/new/picture/picture/u.jpg";
            img.load(path);
            ui->picture->setPixmap(QPixmap::fromImage(img));
            saystr=u8"你\n\n"+QString::fromStdString(allguests[i].quotation[t][choice]);
            ui->sayword->setText(saystr);
            sort(allfood.begin(),allfood.end(),cmp1);
            ui->statusBar->showMessage("右键点击继续...");
            QEventLoop loop;
            connect(this, &MainWindow::rightClick, &loop, &QEventLoop::quit);
            this->setFocus(); // 确保窗口获得焦点
            loop.exec();
            ui->statusBar->clearMessage();// 清除提示
            saystr=QString::fromStdString(allguests[i].name)+"\n\n";
            path=":/new/picture/picture/";
            if(choice==1) allguests[i].setlike(1);
            ll buychoice=allguests[i].pay();
            if(allguests[i].name=="lipu"&&t==1) buychoice=0;
            str=ui->mainlabel->text()+QString::fromStdString(allguests[i].name)+u8"购入"
            +QString::number(inventory[buychoice][0].price)+u8"欢乐豆"+QString::fromStdString(inventory[buychoice][0].name)+'\n';
            ui->mainlabel->setText(str);
            if(dice==3)
            {
                earn+=inventory[buychoice][0].cost*0.7;
                g.money+=inventory[buychoice][0].cost*0.7;
            }
            else if(dice==1)
            {
                earn+=inventory[buychoice][0].price*2;
                g.money+=inventory[buychoice][0].price*2;
            }
            else
            {
                earn+=inventory[buychoice][0].price;
                g.money+=inventory[buychoice][0].price;
            }
            QString condition=u8"第"+QString::number(9-day)+u8"天，"+QString::number(g.money,'f',2)+u8"欢乐豆";
            ui->statelabel->setText(condition);
            if(inventory[buychoice].size()>1) inventory[buychoice].erase(inventory[buychoice].begin());
            else inventory[buychoice][0].amount=0;
            path+=QString::fromStdString(allguests[i].name);
            path+=".jpg";
            img.load(path);
            bool check=false;
            saystr=QString::fromStdString(allguests[i].name)+"\n\n";
            if(allguests[i].name=="jiange")
            {
                if(t==0)
                {
                    if(choice==1) saystr+=u8"(轻轻笑了一声，听上去像风穿过枯井。)\n如果我是鬼，那你脚下这片影子是谁的？\n";
                    else if(choice==2) saystr+=u8"(祂的影子微微晃动了一下，像是在轻叹。)\n也许你是第一个能看见我的人……\n也许你也是影子。\n";
                }
                else if(t==1)
                {
                    if(choice==1) saystr+=u8"(祂的影子像水波一样轻轻颤抖了一下。)\n那也许，我们曾经见过。也许，我曾经是你的影子。\n";
                    else if(choice==2) saystr+=u8"(停顿了一会儿，才幽幽开口。)\n那么，如果下一世的我站在你面前，你会认出我吗？\n";
                }
                else if(t==2)
                {
                    if(choice==1) saystr+=u8"(静静地凝视着你，像是在审视你的灵魂。)\n如果你有一天发现自己失去了影子……请记得来找我。\n";
                    else if(choice==2) saystr+=u8"(低低地笑了一声，但笑意里透着一丝悲哀。)\n也许他们就在你身边，只是你从未注意过。\n";
                }
                ui->picture->setPixmap(QPixmap::fromImage(img));
                ui->sayword->setText(saystr);
                ui->statusBar->showMessage("右键点击继续...");
                QEventLoop loop;
                connect(this, &MainWindow::rightClick, &loop, &QEventLoop::quit);
                this->setFocus(); // 确保窗口获得焦点
                loop.exec();
                ui->statusBar->clearMessage();// 清除提示
                allguests[i].setlike(1);
                if(t==2) allguests[i].quotation.clear();
            }
            else if(allguests[i].name=="lihua")
            {
                if(t==0)
                {
                    check=true;
                    path=":/new/picture/picture/u.jpg";
                    img.load(path);
                    saystr=u8"你\n\n送走了奇怪的客人。\n";
                    allguests[i].setlike(1);
                }
                else if(t==1&&choice==2)
                {
                    check=true;
                    saystr=u8"狸hua\n\n要你管喵。\n";
                }
                else if(t==2&&choice==1)
                {
                    check=true;
                    saystr+=u8"(低声)如果它愿意自己翻面，那它就是被选中的烤冷面。\n";
                    allguests[i].setlike(1);
                }
                else if(t==3&&choice==1)
                {
                    check=true;
                    saystr+=u8"(点头)它们见证了太多秘密。\n";
                    allguests[i].setlike(1);
                }
                if(check)
                {
                    ui->sayword->setText(saystr);
                    ui->picture->setPixmap(QPixmap::fromImage(img));
                    ui->statusBar->showMessage("右键点击继续...");
                    QEventLoop loop;
                    connect(this, &MainWindow::rightClick, &loop, &QEventLoop::quit);
                    this->setFocus(); // 确保窗口获得焦点
                    loop.exec();
                    ui->statusBar->clearMessage();// 清除提示
                    check=false;
                }
            }
            else if(allguests[i].name=="lao8")
            {
                if(t==1&&choice==1)
                {
                    check=true;
                    saystr+=u8"(严肃)它说，时间不是线性的。\n";
                    allguests[i].setlike(1);
                }
                else if(t==2&&choice==2)
                {
                    check=true;
                    saystr+=u8"(迅速跳开)……它已经觉醒了。\n";
                }
                if(check)
                {
                    ui->sayword->setText(saystr);
                    ui->picture->setPixmap(QPixmap::fromImage(img));
                    ui->statusBar->showMessage("按下空格键继续...");//启动事件循环等待空格键
                    ui->statusBar->showMessage("右键点击继续...");
                    QEventLoop loop;
                    connect(this, &MainWindow::rightClick, &loop, &QEventLoop::quit);
                    this->setFocus(); // 确保窗口获得焦点
                    loop.exec();
                    ui->statusBar->clearMessage();// 清除提示
                    check=false;
                }
            }
            else if(allguests[i].name=="lipu")
            {
                if(t==3&&choice==1)
                {
                    check=true;
                    saystr+=u8"(低声)它们在讲一个关于消失的城市的故事。\n";
                    allguests[i].setlike(1);
                }
                else if(t==4&&choice==2)
                {
                    check=true;
                    saystr+=u8"(靠近你耳边轻声)太迟了，它已经听见你了。\n";
                }
                if(check)
                {
                    ui->sayword->setText(saystr);
                    ui->picture->setPixmap(QPixmap::fromImage(img));
                    ui->statusBar->showMessage("右键点击继续...");
                    QEventLoop loop;
                    connect(this, &MainWindow::rightClick, &loop, &QEventLoop::quit);
                    this->setFocus(); // 确保窗口获得焦点
                    loop.exec();
                    ui->statusBar->clearMessage();// 清除提示
                    check=false;
                }
            }
            else if(allguests[i].name=="ladygaba")
            {
                if(choice==1) saystr+=u8"……看来我来早了，不用在意。\n";
                else if(choice==2)
                {
                    saystr+=u8"装逼犯。\n";
                    ++g.zhuangb;
                }
                ui->sayword->setText(saystr);
                ui->picture->setPixmap(QPixmap::fromImage(img));
                ui->statusBar->showMessage("右键点击继续...");
                QEventLoop loop;
                connect(this, &MainWindow::rightClick, &loop, &QEventLoop::quit);
                this->setFocus(); // 确保窗口获得焦点
                loop.exec();
                ui->statusBar->clearMessage();// 清除提示
                ll i=0;
                for(;i<allguests.size();++i)
                {
                    if(allguests[i].name=="ladygaba")
                    {
                        allguests.erase(allguests.begin()+i);
                        break;
                    }
                }
            }
            ui->sayword->clear();
            ui->picture->clear();
            ui->mainlabel->setText(str);
            path=":/new/picture/picture/";
        }
        for(ll i=0;i<inventory.size();++i)
        {
            if(inventory[i][0].amount==0)
            {
                QMessageBox msgBox;
                msgBox.setWindowTitle("我没货了");
                QString str=QString::fromStdString(inventory[i][0].name)+u8"没库存了。\n请到查询-菜品中及时处理唷。\n";
                msgBox.setText(str);
                msgBox.exec();
            }
        }
    }
    for(ll i=0;i<allfood.size();++i)
    {
        if(allfood[i].price>=500)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("warning");
            QString str=QString::fromStdString(inventory[i][0].name)+u8"的售价是不是过于离谱了？\n扣你250欢乐豆。\n";
            earn-=250;
            g.money-=250;
            QString condition=u8"第"+QString::number(9-day)+u8"天，"+QString::number(g.money,'f',2)+u8"欢乐豆";
            ui->statelabel->setText(condition);
            msgBox.setText(str);
            msgBox.exec();
        }
    }
    ui->sayword->clear();
    ui->picture->clear();
    str+=u8"第"+QString::number(9-day)+u8"天";
    if(earn>0) str+=u8"挣了"+QString::number(earn,'f',2)+u8"欢乐豆\n爽。\n";
    else if(earn<0) str+=u8"亏了"+QString::number(fabs(earn),'f',2)+u8"欢乐豆\n伤心捏。\n";
    else if(earn==0) str+=u8"没挣欢乐豆也没亏欢乐豆\nJust soso.不好也不坏的一天。\n";
    ui->mainlabel->setText(str);
    for(ll i=0;i<inventory.size();++i)
    {
        bool flag1=0;
        for(ll j=0;j<inventory[i].size();++j)
        {
            if(inventory[i][j].date<=0&&inventory[i][0].amount) flag1=1;
        }
        bool flag=0;
        for(ll k=0;k<allfood.size();++k) if(allfood[k].spoiltime>1) flag=1;
        if(flag1&&flag&&inventory[i][0].amount)
        {
            ll k=0,temp=0;
            for(ll i=0;i<allguests.size();++i)
            {
                allguests[i].setlike(-0.2);
                temp=uniform_int_distribution<int>(1,5)(gen);
                k=max(k,temp);
            }
            if(k>3)	downrate=true;
        }
    }
    if(downrate)
    {
        if(ratesnow>=1)
        {
            --ratesnow;
            rate=rates[ratesnow];
        }
        QMessageBox msgBox;
        msgBox.setWindowTitle("小红书-你的生活指南");
        msgBox.setText("睡前你打开小红书，刷到了一篇帖子\n小红书632819284163发帖：避雷这个老高小吃摊，连屎都是不新鲜的！\n");
        msgBox.exec();
        str=ui->mainlabel->text();
        if(ratesnow>0) str+=u8"你摊子的风评有所降低了。\n";
        else str+=u8"你摊子的风评已经降无可降了。\n";
        oddsadd-=2;
        downrate=false;
        ui->mainlabel->setText(str);
    }
    bool update=true;
    for(ll i=0;i<allguests.size();++i)
    {
        if(allguests[i].getlike()<5*(updated+1))
        {
            update=false;
            break;
        }
    }
    if(update&&updated<2&&ratesnow<4)
    {
        ++updated;
        str+=u8"大家很喜欢你的摊子！你的摊子风评提升了。\n";
        ++ratesnow;
        oddsadd+=2;
        rate=rates[ratesnow];
    }
    ui->mainlabel->setText(str);
    for(ll i=0;i<allguests.size();++i)
    {
        if(allguests[i].name=="jiange")
        {
            if(allguests[i].quotation.empty())
            {
                allguests.erase(allguests.begin()+i);
                jgleaveday=8-day;
                break;
            }
            break;
        }
    }
    if(dice==2||dice==5) p.policepossible=p0policepossible;
    if(dice==4&&diceratedown)
    {
        diceratedown=false;
        ++ratesnow;
        rate=rates[ratesnow];
        oddsadd+=2;
    }
    p.policepossible*=(1+p.getdegree()/40);
    p.setbirth();
    for(ll i=0;i<inventory.size();++i)
    {
        for(ll j=0;j<inventory[i].size();++j) inventory[i][j].setdate();
    }
    for(ll i=0;i<allguests.size();++i) allguests[i].setbirth();
    sort(allfood.begin(),allfood.end(),cmp1);
    earn=0;
    if(day>1&&g.money>=0)
    {
        QString fornext=u8"结束第"+QString::number(9-day)+"天";
        ++jgleaveday;
        --day;
        ui->start->setText(fornext);
        ui->start->show();
    }
    else if(day<=1)
    {
        ui->mainlabel->clear();
        ui->statelabel->clear();
        ui->dicelabel->clear();
        setWindowTitle("感谢游玩~");
        if(g.money>=0)
        {
            if(g.money-money0>200) achievements["「宇宙食商论」"]=true;
            else achievements["「薛定谔的商人」"]=true;
        }
        else achievements["「。。。不知道说什么好，或许这是一种幸运者对不幸者的愧怍。」"]=true;
        if(g.gifttime>2) achievements["「慈善家还是二道贩子？」"]=true;
        if(g.beyondlaw>0) achievements["「女巫来的」"]=true;
        if(g.beatpolice>3) achievements["「爷们要战斗」"]=true;
        if(g.dicetime==10) achievements["「命运掌握在骰子手中」"]=true;
        if(g.dicefail>6) achievements["「自我催眠」"]=true;
        if(g.dicetime-g.dicefail>8) achievements["「混乱中立的祭品」"]=true;
        if(g.deadbeat>2) achievements["「债的彼岸」"]=true;
        if(g.cowardly>0) achievements["「小市民的生存之道」"]=true;
        if(g.zhuangb>0) achievements["「装逼犯」"]=true;
        if(g.rate==1&&ratesnow>=3) achievements["「好评如潮」"]=true;
        if(g.rate==2&&ratesnow>=3) achievements["「群众的眼睛是……雇来的」"]=true;
        if(g.rate>2&&ratesnow==4) achievements["「传奇小吃，永不塌房」"]=true;
        if(g.rate>0&&ratesnow<3) achievements["「“美名远扬，臭名更远”」"]=true;
        if(g.rate==0&&ratesnow==4) achievements["「“真正的口口相传”」"]=true;
        saveAchievementsToFile();
        ui->mainlabel->setText("感谢游玩！\n你现在可以查看已经更新过的成就了。\n");
    }
    else
    {
        ui->mainlabel->clear();
        ui->statelabel->clear();
        ui->dicelabel->clear();
        if(g.money>=0)
        {
            if(g.money-money0>200) achievements["「宇宙食商论」"]=true;
            else achievements["「薛定谔的商人」"]=true;
        }
        else achievements["「。。。不知道说什么好，或许这是一种幸运者对不幸者的愧怍。」"]=true;
        if(g.gifttime>2) achievements["「慈善家还是二道贩子？」"]=true;
        if(g.beyondlaw>0) achievements["「女巫来的」"]=true;
        if(g.beatpolice>3) achievements["「爷们要战斗」"]=true;
        if(g.dicetime==10) achievements["「命运掌握在骰子手中」"]=true;
        if(g.dicefail>6) achievements["「自我催眠」"]=true;
        if(g.dicetime-g.dicefail>8) achievements["「混乱中立的祭品」"]=true;
        if(g.deadbeat>2) achievements["「债的彼岸」"]=true;
        if(g.cowardly>0) achievements["「小市民的生存之道」"]=true;
        if(g.zhuangb>0) achievements["「装逼犯」"]=true;
        if(g.rate==1&&ratesnow>=3) achievements["「好评如潮」"]=true;
        if(g.rate==2&&ratesnow>=3) achievements["「群众的眼睛是……雇来的」"]=true;
        if(g.rate>2&&ratesnow==4) achievements["「传奇小吃，永不塌房」"]=true;
        if(g.rate>0&&ratesnow<3) achievements["「“美名远扬，臭名更远”」"]=true;
        if(g.rate==0&&ratesnow==4) achievements["「“真正的口口相传”」"]=true;
        saveAchievementsToFile();
        ui->mainlabel->setText("小吃摊倒闭了。\n感谢游玩。\n你现在可以查看已经更新过的成就了。\n");
    }
}
