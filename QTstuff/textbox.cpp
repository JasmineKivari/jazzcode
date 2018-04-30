/*
 * Implementation of functions for textbox.h
 *
 * D. Shpak
 * June 19, 2017
 */

#include <QTextEdit>
#include "textbox.h"

TextBox::TextBox(QWidget *parent)
    : QTextEdit (parent) {
     this->setReadOnly(true);
}

void TextBox::slotTextIn (QString s) {
    this->append(s);
}
