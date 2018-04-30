/*
 * Implementation of the functions for labeledinputbox.h
 *
 * D. Shpak
 * June 19, 2017
 */

#include "labeledinputbox.h"

#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>

/*
 * Private constructor is used to handle common tasks during instantiation
 */
LabeledInputBox::LabeledInputBox(QString who, QWidget *parent) :
            QWidget(parent){
    textBox.setAcceptRichText(false);
    textBox.setFixedHeight(22);
    //label.setFixedHeight(25);
    QVBoxLayout *vBox = new QVBoxLayout(this);
    vBox->setMargin(2);
    vBox->addWidget(&textBox);
    vBox->addWidget(&label);
    this->who = who;
    connect(&textBox, SIGNAL(textChanged()), this, SLOT(changed()));

    /* This was used to set the background colour for debugging the layout
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::red);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    */
}

/*
 * Instantiate for quint16 (unsigned 16-bit integer) input
 */
LabeledInputBox::LabeledInputBox (QString who, quint16 value, QWidget *parent) :
        LabeledInputBox(who, parent) {
    isNumeric = true;
    label.setText(who.append(QString::number(value)));
}

/*
 * Instantiate for String input
 */
LabeledInputBox::LabeledInputBox (QString who, QString value, QWidget *parent) :
        LabeledInputBox(who, parent) {
    isNumeric = false;
    label.setText(who.append(value));
}

/*
 * Signal for when the LabeledInputBox value has changed.
 */
void LabeledInputBox::changed(void) {
    emit valueChanged();
}

/*
 * Private helper method that only returns the value if the ENTER key was pressed
 */
QString LabeledInputBox::getTextLine (QString inText) {
    QString result;
    if (inText.indexOf('\n') <= 0) {
        result = "";
        return result;
    }

    result = inText.trimmed();

    return result;
}

/*
 * Called by the user of the LabeledInputBox to get a numeric value
 */
void LabeledInputBox::updateNumber(quint16 &number) {
    QString boxText = textBox.toPlainText();
    boxText = getTextLine(boxText);
    if (boxText.length() > 0) {
        QString labelText(who);
        bool ok;
        quint16 newNum = boxText.toInt(&ok);
        textBox.clear();
        if (!ok) {
            newNum = number;
            textBox.setText(tr("Not Changed"));
        }
        labelText.append(QString::number(newNum));
        label.setText(labelText);
	number = newNum;
    }
}

/*
 * Called by the user of the LabeledInputBox to get a QString value
 */
void LabeledInputBox::updateString(QString &string) {
    QString boxText = textBox.toPlainText();
    boxText = getTextLine(boxText);
    if (boxText.length() > 0) {
        string = boxText;
        textBox.clear();
        QString labelText(who);
        labelText.append(boxText);
        label.setText(labelText);
    }
}
