#ifndef MSGBOX_H
#define MSGBOX_H

#include <list>
#include <QDialog>
#include "ui_msgbox.h"

using namespace std;

class MsgBox : public QDialog
{
    Q_OBJECT

public:
    enum msgType
    {
        info,
        alert
    };
    static void throwBox1(const QString &msg, msgType type = info);
    static void throwBox2(const QString &msg, msgType type = info);
    static bool catchBox();
private:
    explicit MsgBox(int btn, QWidget *parent = nullptr);
    ~MsgBox();
    Ui::MsgBox ui;
    void setMsg(const QString &msg, msgType type);
    bool access;

    static list<MsgBox *> ls;
    static MsgBox *act();
};

#endif // MSGBOX_H
