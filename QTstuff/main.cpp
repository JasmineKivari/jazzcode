/*
 * main() for the peer-to-peer chat app
 *
 * D. Shpak
 * June 19, 2017
 */

#include <QApplication>
#include <QPushButton>
#include <QTextEdit>

#include "chatwindow.h"
#include "serversocketthread.h"

int main(int argc, char *argv[]) {
    // QApplication must be called first to set up the
    // Qt runtime support
    QApplication a(argc, argv);

    ChatWindow window;

    window.show();

    return a.exec();
}
