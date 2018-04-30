/*
 * A Qt widget having an input text box with a label field below it.
 * Can be constructed to input Strings or quint16's
 *
 * D. Shpak
 * June 19, 2017
 */

#ifndef LABELEDINPUTBOX_H
#define LABELEDINPUTBOX_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>

class LabeledInputBox : public QWidget {
    Q_OBJECT
public:
    explicit LabeledInputBox(QString who, quint16 value, QWidget *parent=0);
    explicit LabeledInputBox(QString who, QString value, QWidget *parent=0);


// signals must be declared but not implemented
signals:
    void valueChanged();

// slots must be declared and implemented
public slots:
    void updateNumber (quint16 &number);
    void updateString (QString &string);

private slots:
    void changed();

private:
    QString who;
    QTextEdit textBox;
    QLabel label;
    bool isNumeric;

    LabeledInputBox(QString who, QWidget *parent);
    QString getTextLine (QString inText);
};

#endif // LABELEDINPUTBOX_H
