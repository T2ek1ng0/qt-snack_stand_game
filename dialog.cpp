#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<bits/stdc++.h>
#include<locale>
#ifdef _WIN32
#include<windows.h>
#endif
using namespace std;
ll t=0;
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
bool cmp1(const Food &a,const Food &b)
{
    return a.price<b.price;
}
bool cmp2(const Food &a,const Food &b)
{
    return a.date<b.date;
}
ll choice=0;
Dialog::Dialog(ll dice,vector<Food>allfood,vector<Guest>allguests,Guest &g1,ld &earn,ll &jgt,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->say1->hide();
    ui->say2->hide();
    timer=new QTimer;
    timer2=new QTimer;
    connect(timer,&QTimer::timeout,this,&Dialog::timeoutslot1);
    connect(timer2,&QTimer::timeout,this,&Dialog::timeoutslot2);
    whenopen();
}

void Dialog::timeoutslot1()
{
    QString path("D:\\Code\\qt\\shaokaotan-zhuanshengversion\\");
    path+=g1.name;
    path+=".jpg";
    QImage img;
    img.load(path);
    sort(allfood.begin(),allfood.end(),cmp1);
    ui->piclabel->setPixmap(QPixmap::fromImage(img));
    QString saystr=QString::fromStdString(g1.name)+"\n\n";
    if(choice==1) g1.setlike(1);
    if(!(g1.name=="lipu"&&t==1))
    {
        ll buychoice=g1.pay();
        saystr+=u8"购入"+QString::number(allfood[buychoice].price)+u8"欢乐豆"+QString::fromStdString(allfood[buychoice].name)+'\n';
        ui->saylabel->setText(saystr);
        if(dice==3) earn-=allfood[buychoice].cost*1.3;
        else earn-=allfood[buychoice].cost;
        if(dice==1) earn+=allfood[buychoice].price*2;
        else earn+=allfood[buychoice].price;
    }
    if(g1.name=="lipu"&&t==1)
    {
        saystr+=u8"购入"+QString::number(allfood[0].price)+u8"欢乐豆"+QString::fromStdString(allfood[0].name)+'\n';
        if(dice==3) earn-=allfood[0].cost*1.3;
        if(dice==1) earn+=allfood[0].price*2;
        ui->saylabel->setText(saystr);
    }
    timer2->start(500);
}

void Dialog::timeoutslot2()
{
    QString saystr=QString::fromStdString(g1.name)+"\n\n";
    if(g1.name=="jiange")
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
            else if(choice==2) cout<<u8"(低低地笑了一声，但笑意里透着一丝悲哀。)\n也许他们就在你身边，只是你从未注意过。\n";
        }
        ui->saylabel->setText(saystr);
        g1.setlike(1);
        if(t==2) g1.quotation.clear();
    }
    else if(g1.name=="lihua")
    {
        if(t==0)
        {
            path="D:\\Code\\qt\\shaokaotan-zhuanshengversion\\u.jpg";
            img.load(path);
            ui->picture->setPixmap(QPixmap::fromImage(img));
            saystr=u8"你\n\n送走了奇怪的客人。\n";
            g1.setlike(1);
        }
        else if(t==1&&choice==2) saystr=u8"狸hua\n\n要你管喵。\n";
        else if(t==2&&choice==1)
        {
            saystr+=u8"(低声)如果它愿意自己翻面，那它就是被选中的烤冷面。\n";
            g1.setlike(1);
        }
        else if(t==3&&choice==1)
        {
            saystr+=u8"(点头)它们见证了太多秘密。\n";
            g1.setlike(1);
        }
        ui->sayword->setText(saystr);
    }
    else if(g1.name=="lao8")
    {
        if(t==1&&choice==1)
        {
            saystr+=u8"(严肃)它说，时间不是线性的。\n";
            g1.setlike(1);
        }
        else if(t==2&&choice==2) saystr+=u8"(迅速跳开)……它已经觉醒了。\n";
        ui->saylabel->setText(saystr);
    }
    else if(g1.name=="lipu")
    {
        if(t==3&&choice==1)
        {
            saystr+=u8"(低声)它们在讲一个关于消失的城市的故事。\n";
            g1.setlike(1);
        }
        else if(t==4&&choice==2) saystr+=u8"(靠近你耳边轻声)太迟了，它已经听见你了。\n";
        ui->saylabel->setText(saystr);
        Sleep(500);
    }
    else if(g1.name=="ladygaba")
    {
        if(choice==1) saystr+=u8"……看来我来早了，不用在意。\n";
        else if(choice==2)
        {
            saystr+=u8"装逼犯。\n";
            ++g.zhuangb;
        }
        ui->saylabel->setText(saystr);
        Sleep(500);
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
}


void Dialog::whenopen()
{
    QString path("D:\\Code\\qt\\shaokaotan-zhuanshengversion\\");
    QImage img;
    t=0;
    if(g1.name!="jiange"&&!g1.quotation.empty())
    {
        uniform_int_distribution<size_t>dist(0, allguests[i].quotation.size()-1);
        t=dist(gen);
    }
    else
    {
        t=jgt;
        ++jgt;
    }
    path+=QString::fromStdString(g1.name);
    path+=".jpg";
    img.load(path);
    ui->piclabel->setPixmap(QPixmap::fromImage(img));
    QString saystr=QString::fromStdString(g1.quotation[t][0])+'\n';
    ui->saylabel->setText(saystr);
    QString usay1=QString::fromStdString(g1.quotation[t][1]);
    QString usay2=QString::fromStdString(g1.quotation[t][2]);
    ui->say1->setText(usay1);
    ui->say2->setText(usay2);
    ui->say1->show();
    ui->say2->show();
}

Dialog::~Dialog()
{
    delete ui;
    delete Dialog::timer;
    delete Dialog::timer2;
}

void Dialog::on_say1_clicked()
{
    choice=1;
    ui->say1->hide();
    ui->say2->hide();
    path="D:\\Code\\qt\\shaokaotan-zhuanshengversion\\u.jpg";
    img.load(path);
    ui->piclabel->setPixmap(QPixmap::fromImage(img));
    QString saystr=u8"你\n\n"+QString::fromStdString(g1.quotation[t][choice]);
    ui->saylabel->setText(saystr);
    timer->start(500);
}

void Dialog::on_say2_clicked()
{
    choice=2;
    ui->say1->hide();
    ui->say2->hide();
    path="D:\\Code\\qt\\shaokaotan-zhuanshengversion\\u.jpg";
    img.load(path);
    ui->piclabel->setPixmap(QPixmap::fromImage(img));
    QString saystr=u8"你\n\n"+QString::fromStdString(allguests[i].quotation[t][choice]);
    ui->saylabel->setText(saystr);
    timer->start(500);
}
