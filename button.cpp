#include <QtGui>

#include "button.h"

Button::Button(const QString &text, QWidget *parent)
    : QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setText(text);
}

QSize Button::sizeHint() const
{
    QSize size = QToolButton::sizeHint();
    size.rheight() += 20;
    size.rwidth() = qMax(size.width(), size.height());
    return size;
}
void Button::setExp(int v)
{
    Exp = v;
}
int Button::getExp()
{
    return Exp;
}


radioButton::radioButton(const QString &text, QWidget *parent)
    : QRadioButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setText(text);
    if (text == "Hex") NUM_TYPE = 16;
    if (text == "Dec") NUM_TYPE = 10;
    if (text == "Oct") NUM_TYPE = 8;
    if (text == "Bin") NUM_TYPE = 2;
}

QSize radioButton::sizeHint() const
{
    QSize size = QRadioButton::sizeHint();
    size.rheight() += 20;
    size.rwidth() = qMax(size.width(), size.height());
    return size;
}
int radioButton::getNumeral()
{
    return NUM_TYPE;
}
