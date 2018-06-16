#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFrame>
#include <iostream>

class QLineEdit;

class Button;
class radioButton;

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = 0);
    int CNUM_TYPE = 16;
private:
    Button *createButton(const QString &text, const char *member);
    radioButton *createRadioButton(const QString &text, const char *member);
    QLineEdit *createDisplay(int widht = 150);
    void abortOperation();
    bool calculate(unsigned __int32 rightOperand, const QString &pendingOperator);

    unsigned __int32 sumInMemory;
    unsigned __int32 sumSoFar;
    unsigned __int32 factorSoFar;
    QString pendingAdditiveOperator;
    QString pendingMultiplicativeOperator;
    bool waitingForOperand;

    QLineEdit *display;
    QLineEdit *hexDisplay;
    QLineEdit *decDisplay;
    QLineEdit *octDisplay;
    QLineEdit *binDisplay;
    QLineEdit *valueShift;

    enum { NumDigitButtons = 16 };
    Button *digitButtons[NumDigitButtons];
    enum { NumBitButtons = 32 };
    Button *bitButtons[NumBitButtons];
    Button *bitLabel[NumBitButtons];




private slots:
    void digitClicked();
    void bitClicked();
    void unaryOperatorClicked();
    void additiveOperatorClicked();
    void multiplicativeOperatorClicked();
    void equalClicked();
    void pointClicked();
    void changeSignClicked();
    void backspaceClicked();
    void clear();
    void clearAll();
    void clearMemory();
    void readMemory();
    void setMemory();
    void addToMemory();

    void bitButtonsChange();
    void numeralClicked();
    void rShiftClicked();
    void lShiftClicked();

    void displayNumeral();

    void about();



};


#endif
