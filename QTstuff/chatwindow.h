/*
 * A Qt widget for use as a peer-to-peer TCP chat window
 *
 * D. Shpak
 * June 17, 2017
 */

#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include "textbox.h"
#include "labeledinputbox.h"
#include "serversocketthread.h"

class QPushButton;
class QTextEdit;
class QLabel;
class QTcpSocket;

class ChatWindow : public QWidget {
    Q_OBJECT
public:
    explicit ChatWindow(QWidget *parent = 0);
signals:

public slots:
    void setClientSocket (QTcpSocket *clientSocket);
    void readYourDialog ();
    void stop();

private slots:
    void setMyPort();
    void setYourHostName();
    void setYourPort();
    void connectToHost();
    void listen();
    void postDialog ();

private:
    const int CONNECTION_TIMEOUT = 5 * 1000;  // ms

    QPushButton *quitButton, *connectButton, *listenButton, *postButton;
    QTextEdit *inputDialogBox;
    LabeledInputBox *yourHostBox, *yourPortBox, *myPortBox;
    TextBox *rxDialogText;

    QTcpSocket *clientSocket;
    ServerSocketThread *serverSocketThread;

    QDataStream inStream, outStream;

    quint16 myPort;
    QString yourHostName;
    quint16 yourPort;

    QString getTextLine (QString inText);
};

#endif // CHATWINDOW_H
