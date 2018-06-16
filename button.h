#ifndef BUTTON_H
#define BUTTON_H

#include <QToolButton>
#include <QRadioButton>
#include <QtWidgets/QToolButton>

class Button : public QToolButton
{
    Q_OBJECT

public:
    Button(const QString &text, QWidget *parent = 0);

    QSize sizeHint() const;
    void setExp(int v);
    int getExp();

private:
    int Exp = 0;
};//Endclass: Button

class radioButton : public QRadioButton
{
    Q_OBJECT
private:
    int NUM_TYPE;
public:
    radioButton(const QString &text, QWidget *parent = 0);

    QSize sizeHint() const;
    int getNumeral();
};

#endif
