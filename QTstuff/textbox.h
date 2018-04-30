/*
 * A Qt widget that facilitates using a signal for the updating of text
 * in a QTextEdit
 *
 * I named it TextBox (as in Java)
 *
 * D. Shpak
 * June 19, 2017
 */
#ifndef TEXTAREA_H
#define TEXTAREA_H

#include <QWidget>
#include <QTextEdit>
#include <QString>

class TextBox : public QTextEdit {
    Q_OBJECT
public:
    explicit TextBox(QWidget *parent = 0);
private slots:
    void slotTextIn (QString s);
};

#endif // TEXTAREA_H
