#include <QtWidgets>

 #include <cmath>

 #include "button.h"
 #include "calculator.h"

 Calculator::Calculator(QWidget *parent)
     : QWidget(parent)
 {
     sumInMemory = 0;
     sumSoFar = 0;
     factorSoFar = 0;
     waitingForOperand = true;

     display = new QLineEdit("0");
     hexDisplay = createDisplay();
     decDisplay = createDisplay();
     octDisplay = createDisplay();
     binDisplay = createDisplay(200);
     connect(display, SIGNAL(textChanged(QString)), this, SLOT(bitButtonsChange()));
     connect(display, SIGNAL(textChanged(QString)), this, SLOT(displayNumeral()));
     connect(display, SIGNAL(clicked()), this, SLOT(selectAll()));
     display->setAlignment(Qt::AlignRight);
     display->setMaxLength(32);

     QFont font = display->font();
     font.setPointSize(font.pointSize() + 4);
     display->setFont(font);
     display->setFixedWidth(300);



     for (int i = 0; i < NumDigitButtons; ++i) {
         digitButtons[i] = createButton(QString::number(i,16).toUpper(), SLOT(digitClicked()));
     }
     for (int i = 0; i < NumBitButtons; ++i) {
         bitButtons[i] = createButton("0", SLOT(bitClicked()));
         bitButtons[i]->setExp(i);
         bitButtons[i]->setStyleSheet("background-color: white;");
         bitButtons[i]->setFixedSize(20,25);
     }
     for (int i = 0; i < NumBitButtons; ++i) {
         bitLabel[i] = createButton(QString::number(i), SLOT());
         bitLabel[i]->setExp(i);
         bitLabel[i]->setFixedSize(20,25);
         bitLabel[i]->setStyleSheet("border: 0px");
         bitLabel[i]->setEnabled(false);
     }
     //Button *hexLabel = createButton(tr("Hex"), SLOT());
     //hexLabel->setEnabled();
     QLabel *hexLabel = new QLabel("Hex");
     QLabel *decLabel = new QLabel("Dec");
     QLabel *octLabel = new QLabel("Oct");
     QLabel *binLabel = new QLabel("Bin");
     hexLabel->setAlignment(Qt::AlignCenter);
     decLabel->setAlignment(Qt::AlignCenter);
     octLabel->setAlignment(Qt::AlignCenter);
     binLabel->setAlignment(Qt::AlignCenter);

     Button *About = createButton(tr("About"), SLOT(about()));

     Button *rightShift = createButton(tr("Shift >>"), SLOT(rShiftClicked()));
     rightShift->setFixedWidth(80);
     Button *leftShift = createButton(tr("Shift <<"), SLOT(lShiftClicked()));
     leftShift->setFixedWidth(80);
     valueShift = new QLineEdit("1");
     valueShift->setFixedWidth(40);
     Button *pointButton = createButton(tr("."), SLOT(pointClicked()));
     pointButton->setEnabled(false);
     Button *changeSignButton = createButton(tr("\302\261"), SLOT(changeSignClicked()));

     radioButton *hexButton = createRadioButton(tr("Hex"), SLOT(numeralClicked()));
     radioButton *decButton = createRadioButton(tr("Dec"), SLOT(numeralClicked()));
     radioButton *octButton = createRadioButton(tr("Oct"), SLOT(numeralClicked()));
     radioButton *binButton = createRadioButton(tr("Bin"), SLOT(numeralClicked()));
     Button *backspaceButton = createButton(tr("Backspace"), SLOT(backspaceClicked()));
     backspaceButton->setFixedWidth(87);
     Button *clearButton = createButton(tr("Clear"), SLOT(clear()));
     clearButton->setFixedWidth(86);
     Button *clearAllButton = createButton(tr("Clear All"), SLOT(clearAll()));
     clearAllButton->setFixedWidth(85);

     Button *clearMemoryButton = createButton(tr("MC"), SLOT(clearMemory()));
     Button *readMemoryButton = createButton(tr("MR"), SLOT(readMemory()));
     Button *setMemoryButton = createButton(tr("MS"), SLOT(setMemory()));
     Button *addToMemoryButton = createButton(tr("M+"), SLOT(addToMemory()));

     Button *divisionButton = createButton(tr("\303\267"), SLOT(multiplicativeOperatorClicked()));
     Button *timesButton = createButton(tr("\303\227"), SLOT(multiplicativeOperatorClicked()));
     Button *minusButton = createButton(tr("-"), SLOT(additiveOperatorClicked()));
     Button *plusButton = createButton(tr("+"), SLOT(additiveOperatorClicked()));

     Button *squareRootButton = createButton(tr("Sqrt"), SLOT(unaryOperatorClicked()));
     Button *powerButton = createButton(tr("x\302\262"), SLOT(unaryOperatorClicked()));
     Button *reciprocalButton = createButton(tr("1/x"), SLOT(unaryOperatorClicked()));
     Button *equalButton = createButton(tr("="), SLOT(equalClicked()));


     QGridLayout *mainLayout = new QGridLayout;
     mainLayout->setSizeConstraint(QLayout::SetFixedSize);
     QHBoxLayout *bitDisplay = new QHBoxLayout();
     for (int k = 8; k >= 1; k--)
     {
         QHBoxLayout *bitLabelLayout = new QHBoxLayout();
         QHBoxLayout *bitLayout = new QHBoxLayout();
         for (int i = k*4; i > k*4-4; i--)
         {
             bitLabelLayout->addWidget(bitLabel[i-1]);
             bitLayout->addWidget(bitButtons[i-1]);
         }
         QVBoxLayout *chunk = new QVBoxLayout();
         chunk->addLayout(bitLabelLayout);
         chunk->addLayout((bitLayout));
         QFrame *line = new QFrame();
         line->setObjectName(QStringLiteral("line"));
         line->setFrameShape(QFrame::VLine);
         //line->setFrameShadow(QFrame::Sunken);
         if(k != 8)bitDisplay->addWidget(line);
         bitDisplay->addLayout(chunk);
     }



     //Check button for switch between numerals
     QHBoxLayout *hesodem = new QHBoxLayout();
     hesodem->addWidget(hexButton);
     hesodem->addWidget(decButton);
     hesodem->addWidget(octButton);
     hesodem->addWidget(binButton);
     QHBoxLayout *numeralHBox = new QHBoxLayout();
     QVBoxLayout *numeralVBox = new QVBoxLayout();
     numeralVBox->addLayout(hesodem);
     numeralHBox->addLayout(numeralVBox);

     //======Main display
     QHBoxLayout *disLayout = new QHBoxLayout();
     disLayout->addWidget(display);

     //====Second display for each numeral
     QVBoxLayout *hexVBox = new QVBoxLayout();
     hexVBox->addWidget(hexLabel);
     hexVBox->addWidget(hexDisplay);
     QVBoxLayout *decVBox = new QVBoxLayout();
     decVBox->addWidget(decLabel);
     decVBox->addWidget(decDisplay);
     QVBoxLayout *octVBox = new QVBoxLayout();
     octVBox->addWidget(octLabel);
     octVBox->addWidget(octDisplay);
     QVBoxLayout *binVBox = new QVBoxLayout();
     binVBox->addWidget(binLabel);
     binVBox->addWidget(binDisplay);
     QHBoxLayout *numLabel = new QHBoxLayout();
     numLabel->addLayout(hexVBox);
     numLabel->addLayout(decVBox);
     numLabel->addLayout(octVBox);
     numLabel->addLayout(binVBox);
     //QVBoxLayout *numDisplayVBox = new QVBoxLayout();
     //numDisplayVBox->addLayout(numLabel);
     //numDisplayVBox->addLayout(numDisplay);
     //QHBoxLayout *numDisplayHBox = new QHBoxLayout();
     //numDisplayHBox->addLayout(numDisplayVBox);

     QHBoxLayout *padMainLayout = new QHBoxLayout();
     QVBoxLayout *padCenterLayout = new QVBoxLayout();
     QHBoxLayout *row_0 = new QHBoxLayout();//Shift bit
       row_0->addWidget(leftShift);
       row_0->addWidget(valueShift);
       row_0->addWidget(rightShift);
     QHBoxLayout *row_1 = new QHBoxLayout();//backspace, clear, clear all
       row_1->addWidget(backspaceButton);
       row_1->addWidget(clearButton);
       row_1->addWidget(clearAllButton);
     QHBoxLayout *rowHexValue = new QHBoxLayout();
       for (int i = 10; i < 16; i++)
       {
           rowHexValue->addWidget(digitButtons[i]);
       }
     QHBoxLayout *row_2 = new QHBoxLayout();// MC, 7, 8, ,9, division, sqrt
       row_2->addWidget(clearMemoryButton);
       row_2->addWidget(digitButtons[7]);
       row_2->addWidget(digitButtons[8]);
       row_2->addWidget(digitButtons[9]);
       row_2->addWidget(divisionButton);
       row_2->addWidget(squareRootButton);
    QHBoxLayout *row_3 = new QHBoxLayout();
       row_3->addWidget(readMemoryButton);
       row_3->addWidget(digitButtons[4]);
       row_3->addWidget(digitButtons[5]);
       row_3->addWidget(digitButtons[6]);
       row_3->addWidget(timesButton);
       row_3->addWidget(powerButton);
    QHBoxLayout *row_4 = new QHBoxLayout();
       row_4->addWidget(setMemoryButton);
       row_4->addWidget(digitButtons[1]);
       row_4->addWidget(digitButtons[2]);
       row_4->addWidget(digitButtons[3]);
       row_4->addWidget(minusButton);
       row_4->addWidget(reciprocalButton);
    QHBoxLayout *row_5 = new QHBoxLayout();
       row_5->addWidget(addToMemoryButton);
       row_5->addWidget(digitButtons[0]);
       row_5->addWidget(pointButton);
       row_5->addWidget(changeSignButton);
       row_5->addWidget(plusButton);
       row_5->addWidget(equalButton);

     padCenterLayout->addLayout(row_0);
     padCenterLayout->addLayout(row_1);
     padCenterLayout->addLayout(rowHexValue);
     padCenterLayout->addLayout(row_2);
     padCenterLayout->addLayout(row_3);
     padCenterLayout->addLayout(row_4);
     padCenterLayout->addLayout(row_5);
     padMainLayout->addLayout(padCenterLayout);


     int mainRow = 0;
     mainLayout->addLayout(bitDisplay,mainRow++,0);
     mainLayout->addLayout(numeralHBox, mainRow++, 0);
     mainLayout->addLayout(disLayout, mainRow++, 0);
     mainLayout->addLayout(numLabel, mainRow++, 0);
     mainLayout->addLayout(padMainLayout, mainRow++, 0);
     mainLayout->addWidget(About, mainRow++,0);

     setLayout(mainLayout);
     setWindowTitle(tr("RegCalc v1.0"));
 }

 void Calculator::digitClicked()
 {
     Button *clickedButton = qobject_cast<Button *>(sender());
     unsigned __int32 digitValue = clickedButton->text().toLongLong(NULL, CNUM_TYPE);
     if (display->text() == "0" && digitValue == 0.0)
         return;

     if (waitingForOperand) {
         display->clear();
         waitingForOperand = false;
     }
     display->setText((display->text() + QString::number(digitValue, CNUM_TYPE)).toUpper());
 }
 void Calculator::bitClicked()
 {
     Button *clickedButton = qobject_cast<Button *>(sender());
     unsigned __int32 operand = display->text().toLongLong(NULL, CNUM_TYPE);
     unsigned __int32 temp = qPow(2, clickedButton->getExp());

     if(clickedButton->text().toInt()) // bitButton == 1
     {
         //Change value of bitButton to zero and decrease value of display 2^x
         clickedButton->setText("0");
         clickedButton->setStyleSheet("background-color: white;");
         operand -= temp;
     }
     else// bitButton == 0
     {
        //Change value of bitButton to 1 and increase value of display: 2^x
         clickedButton->setText("1");
         clickedButton->setStyleSheet("background: rgb(172, 172, 172);");
         operand += temp;
     }
     display->setText(QString::number(operand, CNUM_TYPE).toUpper());
 }
 void Calculator::bitButtonsChange()
 {
     unsigned __int32 operand = display->text().toLongLong(NULL, CNUM_TYPE);
     //int bit[32] {};
     for (int i = 0 ; i < 32 ; i++)
     {
         //bit[i] = operand & 1;
         if (operand&1)
         {
             bitButtons[i]->setText("1");
             bitButtons[i]->setStyleSheet("background: rgb(172, 172, 172);");
         }
         else
         {
            bitButtons[i]->setText("0");
            bitButtons[i]->setStyleSheet("background: rgb(255, 255, 255);");
         }
         operand >>= 1;
     }
 }
 void Calculator::displayNumeral()
 {
     unsigned __int32 operand = display->text().toLongLong(NULL, CNUM_TYPE);
     hexDisplay->setText(QString::number(operand, 16).toUpper());
     decDisplay->setText(QString::number(operand, 10).toUpper());
     octDisplay->setText(QString::number(operand, 8).toUpper());
     binDisplay->setText(QString::number(operand, 2).toUpper());
 }


 void Calculator::unaryOperatorClicked()
 {
     Button *clickedButton = qobject_cast<Button *>(sender());
     QString clickedOperator = clickedButton->text();
     unsigned __int32 operand = display->text().toDouble();
     unsigned __int32 result = 0;

     if (clickedOperator == tr("Sqrt")) {
         if (operand < 0.0) {
             abortOperation();
             return;
         }
         result = std::sqrt(operand);
     } else if (clickedOperator == tr("x\302\262")) {
         result = std::pow(operand, 2.0);
     } else if (clickedOperator == tr("1/x")) {
         if (operand == 0.0) {
             abortOperation();
             return;
         }
         result = 1.0 / operand;
     }
     display->setText(QString::number(result, CNUM_TYPE).toUpper());
     waitingForOperand = true;
 }

 void Calculator::additiveOperatorClicked()
 {
     Button *clickedButton = qobject_cast<Button *>(sender());
     QString clickedOperator = clickedButton->text();
     unsigned __int32  operand = display->text().toLongLong(NULL, CNUM_TYPE);

     if (!pendingMultiplicativeOperator.isEmpty()) {
         if (!calculate(operand, pendingMultiplicativeOperator)) {
             abortOperation();
             return;
         }
         display->setText(QString::number(factorSoFar, CNUM_TYPE).toUpper());
         operand = factorSoFar;
         factorSoFar = 0.0;
         pendingMultiplicativeOperator.clear();
     }

     if (!pendingAdditiveOperator.isEmpty()) {
         if (!calculate(operand, pendingAdditiveOperator)) {
             abortOperation();
             return;
         }
         display->setText(QString::number(sumSoFar, CNUM_TYPE).toUpper());
     } else {
         sumSoFar = operand;
     }

     pendingAdditiveOperator = clickedOperator;
     waitingForOperand = true;
 }

 void Calculator::multiplicativeOperatorClicked()
 {
     Button *clickedButton = qobject_cast<Button *>(sender());
     QString clickedOperator = clickedButton->text();
     unsigned __int32 operand = display->text().toLongLong(NULL, CNUM_TYPE);

     if (!pendingMultiplicativeOperator.isEmpty()) {
         if (!calculate(operand, pendingMultiplicativeOperator)) {
             abortOperation();
             return;
         }
         display->setText(QString::number(factorSoFar, CNUM_TYPE).toUpper());
     } else {
         factorSoFar = operand;
     }

     pendingMultiplicativeOperator = clickedOperator;
     waitingForOperand = true;
 }

 void Calculator::equalClicked()
 {
     unsigned __int32 operand = display->text().toLongLong(NULL, CNUM_TYPE);

     if (!pendingMultiplicativeOperator.isEmpty()) {
         if (!calculate(operand, pendingMultiplicativeOperator)) {
             abortOperation();
             return;
         }
         operand = factorSoFar;
         factorSoFar = 0;
         pendingMultiplicativeOperator.clear();
     }
     if (!pendingAdditiveOperator.isEmpty()) {
         if (!calculate(operand, pendingAdditiveOperator)) {
             abortOperation();
             return;
         }
         pendingAdditiveOperator.clear();
     } else {
         sumSoFar = operand;
     }

     display->setText(QString::number(sumSoFar, CNUM_TYPE).toUpper());
     sumSoFar = 0;
     waitingForOperand = true;
 }

 void Calculator::pointClicked()
 {
     if (waitingForOperand)
         display->setText("0");
     if (!display->text().contains('.'))
         display->setText(display->text() + tr("."));
     waitingForOperand = false;
 }

 void Calculator::changeSignClicked()
 {
     QString text = display->text();
     double value = text.toDouble();

     if (value > 0.0) {
         text.prepend(tr("-"));
     } else if (value < 0.0) {
         text.remove(0, 1);
     }
     display->setText(text);
 }
 void Calculator::numeralClicked()
 {
     radioButton *checkedButton = qobject_cast<radioButton *>(sender());
     QString text = display->text();
     unsigned __int32 value;
     bool *ok = NULL;
     value = text.toLongLong(ok, CNUM_TYPE);
     CNUM_TYPE = checkedButton->getNumeral();
     for (int i = 10; i < 16; i++)
         digitButtons[i]->setEnabled((CNUM_TYPE == 16));
     for (int i = 2; i < 10; i++)
        digitButtons[i]->setEnabled(!(CNUM_TYPE == 2));
     if (CNUM_TYPE == 8)
     {
         digitButtons[8]->setEnabled(false);
         digitButtons[9]->setEnabled(false);
     }

     display->setText(QString::number(value, CNUM_TYPE).toUpper());
 }
 void Calculator::rShiftClicked()
 {
     QString text = display->text();
     QString valueText = valueShift->text();
     unsigned __int32 value = text.toLongLong(NULL, CNUM_TYPE);
     value >>= valueText.toInt();
     display->setText(QString::number(value, CNUM_TYPE).toUpper());
 }
 void Calculator::lShiftClicked()
 {
     QString text = display->text();
     QString valueText = valueShift->text();
     unsigned __int32 value = text.toLongLong(NULL, CNUM_TYPE);
     value <<= valueText.toInt();
     display->setText(QString::number(value, CNUM_TYPE).toUpper());
 }


 void Calculator::backspaceClicked()
 {
     if (waitingForOperand)
         return;

     QString text = display->text();
     text.chop(1);
     if (text.isEmpty()) {
         text = "0";
         waitingForOperand = true;
     }
     display->setText(text);
 }

 void Calculator::clear()
 {
     if (waitingForOperand)
         return;

     display->setText("0");
     waitingForOperand = true;
 }

 void Calculator::clearAll()
 {
     sumSoFar = 0;
     factorSoFar = 0;
     pendingAdditiveOperator.clear();
     pendingMultiplicativeOperator.clear();
     display->setText("0");
     waitingForOperand = true;
 }

 void Calculator::clearMemory()
 {
     sumInMemory = 0;
 }

 void Calculator::readMemory()
 {
     display->setText(QString::number(sumInMemory, CNUM_TYPE).toUpper());
     waitingForOperand = true;
 }

 void Calculator::setMemory()
 {
     equalClicked();
     sumInMemory = display->text().toLongLong(NULL, CNUM_TYPE);
 }

 void Calculator::addToMemory()
 {
     equalClicked();
     sumInMemory += display->text().toDouble();
 }
 Button *Calculator::createButton(const QString &text, const char *member)
 {
     Button *button = new Button(text);
     connect(button, SIGNAL(clicked()), this, member);
     button->setFixedWidth(40);
     return button;
 }
 radioButton *Calculator::createRadioButton(const QString &text, const char *member)
 {
     radioButton *button = new radioButton(text);
     connect(button, SIGNAL(clicked()), this, member);
     button->setFixedWidth(40);
     if (text == "Hex") button->setChecked(true);
     return button;
 }
 QLineEdit *Calculator::createDisplay(int width)
 {
     QLineEdit *numdisplay = new QLineEdit("0");
     numdisplay->setFixedWidth(width);
     numdisplay->setAlignment(Qt::AlignRight);
     numdisplay->setReadOnly(true);
     return numdisplay;
 }

 void Calculator::abortOperation()
 {
     clearAll();
     display->setText(tr("####"));
 }

 bool Calculator::calculate(unsigned __int32 rightOperand, const QString &pendingOperator)
 {
     if (pendingOperator == tr("+")) {
         sumSoFar += rightOperand;
     } else if (pendingOperator == tr("-")) {
         sumSoFar -= rightOperand;
     } else if (pendingOperator == tr("\303\227")) {
         factorSoFar *= rightOperand;
     } else if (pendingOperator == tr("\303\267")) {
         if (rightOperand == 0.0)
             return false;
         factorSoFar /= rightOperand;
     }
     return true;
 }
void Calculator::about()
{
    QMessageBox::about(this, tr("About RegCalc v1.0"),
                       tr("<h2>Register Calculator 1.0 </h2>"
                          "<p>Copyright &copy; 2017 MrPear Inc."
                          "<p>Register Calculator is a small application that helps you "
                          " calculates and analyze register quickly."
                          "<p>If you have any problems with using RegCalc please contact us in the flowing:"
                          "<p>Author: Le Ngoc Thuong"
                          "<p>Email: lengocthuong15@gmail.com"
                          "<p>Website: <a href='http://mrpear.com'>mrpear.com/register-calculator</href>"
                          ));
}
