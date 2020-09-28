#include <list>
#include <QPushButton>
#include "msgbox.h"
#include "ui_msgbox.h"

using namespace std;

list<MsgBox *> MsgBox::ls;

MsgBox::MsgBox(int btn, QWidget *parent) :
    QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);  //禁用对话框边框及控件
    setAttribute(Qt::WA_TranslucentBackground);  //背景透明
    ui.setupUi(this);
    ls.push_back(this);

    if(btn==1)
    {
        ui.pushButton->close();
        ui.pushButton_2->move(160, ui.pushButton_2->y());
        connect(ui.pushButton_2, &QPushButton::clicked, this, &MsgBox::close);
    }
    if(btn==2)
    {
        connect(ui.pushButton_2, &QPushButton::clicked, [&]{access=true; close();});
        connect(ui.pushButton, &QPushButton::clicked, [&]{access=false; close();});
    }
}

MsgBox::~MsgBox()
{
    ls.pop_back();
}

void MsgBox::setMsg(const QString &msg, msgType type)
{
    if(type==alert)
        ui.label_2->setText("！警告");
    if(type==info)
        ui.label_2->setText("？提示");
    ui.label->setText(msg);
}

MsgBox *MsgBox::act()
{
    if(ls.empty())
        return nullptr;
    return ls.back();
}

void MsgBox::throwBox1(const QString &msg, msgType type)
{
    MsgBox *box=new MsgBox(1, QApplication::activeWindow());
    box->setMsg(msg, type);
    box->show();
}

void MsgBox::throwBox2(const QString &msg, msgType type)
{
    MsgBox *box=new MsgBox(2, QApplication::activeWindow());
    box->setMsg(msg, type);
    box->show();
}

bool MsgBox::catchBox()
{
    if(MsgBox::act()==nullptr)
        return false;
    MsgBox::act()->exec();
    bool ret=MsgBox::act()->access;
    delete MsgBox::act();
    return ret;
}
