/*
 * Implementation of the functions for chatwindow.h
 *
 * D. Shpak
 * June 19, 2017
 */

#include "chatwindow.h"
#include "textbox.h"
#include <QApplication>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QtNetwork/QTcpSocket>

ChatWindow::ChatWindow(QWidget *parent) : QWidget(parent) {
    clientSocket = NULL;
    serverSocketThread = NULL;

    myPort = 6666;
    yourPort = 6666;
    yourHostName = "127.0.0.1";

    // Set size of the window
    setFixedSize(700, 500);

    // The tr() function is for Qt's multiple-language support
    QWidget::setWindowTitle(tr("ICS 214 Peer-to-Peer Chat"));

    myPortBox = new LabeledInputBox(tr("My Port: "), myPort, this);
    myPortBox->setGeometry(10, 10, 120, 45);
    // Connect the signal for this text box to the slot that reads and uses the text
    connect(myPortBox, SIGNAL(valueChanged()), this, SLOT(setMyPort()));

    listenButton = new QPushButton(tr("Listen"), this);
    listenButton->setGeometry(140, 10, 100, 30);
    connect (listenButton, SIGNAL(clicked(bool)), SLOT(listen()));
    // Connect this button to the function that creates and starts the TCP server thread
    //!!

    yourHostBox = new LabeledInputBox(tr("Your Host: "), yourHostName, this);
    yourHostBox->setGeometry(250, 10, 200, 45);
    // Connect the signal for this text box to the slot that sets the remote host name
    connect(yourHostBox, SIGNAL(valueChanged()), this, SLOT(setYourHostName()));

    yourPortBox = new LabeledInputBox(tr("Your Port: "), yourPort, this);
    yourPortBox->setGeometry(460, 10, 120, 45);
    connect(yourPortBox, SIGNAL(valueChanged()), this, SLOT(setYourPort()));
    // Connect the signal for this text box to the slot that sets the remote port number
    

    connectButton = new QPushButton(tr("Connect"), this);
    connectButton->setGeometry(590, 10, 100, 30);
    // Connect this button to the function that sets up the connection to a remote server
    connect(connectButton, SIGNAL(clicked(bool)), SLOT(connectToHost()));

    // A large text box to display the chat dialog
    rxDialogText = new TextBox(this);
    rxDialogText->setGeometry(10, 60, 680, 300);

    // A smaller text box for input dialog
    inputDialogBox = new QTextEdit(this);
    inputDialogBox->setGeometry(10, 370, 680, 60);

    // A button to post the input dialog
    postButton = new QPushButton(tr("Post"), this);
    postButton->setGeometry(330, 430, 70, 30);
    // Connect this button to the function that posts the local dialog
    connect(postButton, SIGNAL(clicked()), this, SLOT (postDialog()));

    // Create and position the Quit button
    quitButton = new QPushButton(tr("Quit"), this);
    quitButton->setGeometry(330, 460, 70, 30);
    // Connect the signal from the button to the stop() slot on this object
    connect(quitButton, SIGNAL(clicked(bool)), this, SLOT(stop()));
}

#include <iostream>

/*
 * Gracefully shut down the multi-threaded app
 */
void ChatWindow::stop() {
    rxDialogText->append(tr("Stopping ..."));
    // Tell the ServerSocketThread to stop().
    // It will then signal to stop() this thread when it has stopped.
    if (serverSocketThread && serverSocketThread->isRunning()) {
        serverSocketThread->stop();
        if (!serverSocketThread->isFinished()) {
            std::cout << "ServerSocketThread not finished yet" << std::endl;
            return;
        }
    }
    QApplication::quit();
}

/*
 *  Slot to handle dialog received from someone else
 * */
void ChatWindow::readYourDialog(void) {
    // inStream was already wrapped around a Socket by setClientSocket()
    inStream.startTransaction();
    QString dialog;
    inStream >> dialog;
    if (!inStream.commitTransaction()) {
        // Failed, so do nothing.
        return;
    }

    QString outDialog = tr("You: ");
    outDialog.append(dialog);
    rxDialogText->append(outDialog);
}

/*
 * Slot to post my own dialog into the Text box
 * and send it over the remote TCP connection
 */
void ChatWindow::postDialog(void) {
    if (clientSocket == NULL || !clientSocket->isOpen()) {
        rxDialogText->append(tr("No Connection"));
        return;
    }
    QString dialog = inputDialogBox->toPlainText();
    if (dialog.length() == 0) {
        return;
    }

    outStream.setDevice(clientSocket);
    outStream.setVersion(QDataStream::Qt_4_0);
    outStream << dialog;

    dialog = tr(" Me: ");
    // Append the text from the inputDialogBox to the QString on the previous line
    dialog.append(inputDialogBox->toPlainText());
    // Append "dialog" to the text box that displays the dialog
    rxDialogText->append(dialog);

    
    inputDialogBox->clear();
}

/*
 * Start the TCP server socket thread (which is done from this thread)
 */
void ChatWindow::listen(void) {

    // If the thread exists and is already running, stop it before restarting.
    if (serverSocketThread != NULL) {
        if (serverSocketThread->isRunning()) {
            serverSocketThread->stop();
        }
        delete serverSocketThread;
    }
    serverSocketThread = new ServerSocketThread(this, myPort);
    QString msg(tr("Server Listening on port "));
    msg.append(QString::number(myPort));
    rxDialogText->append(msg);

    // Have the ServerSocketThread's newClient() signal send a signal to this thread when a new client connects
    connect(serverSocketThread, SIGNAL(newClient(QTcpSocket*)), this, SLOT(setClientSocket(QTcpSocket*)));

    // Connect the quitButton the to serverSocketThread's stop()
    connect(quitButton, SIGNAL (clicked()), serverSocketThread, SLOT (stop()));
    // Connect the serverSocketThread finished() signal to this object's stop()
    connect(serverSocketThread, SIGNAL(finished()), this, SLOT(stop()));
}

/*
 * Slot to connect to someone else's server
 */
void ChatWindow::connectToHost(void) {
    clientSocket = new QTcpSocket(this);

    std::cout << "Connecting to server " << yourHostName.toStdString() << ":" << yourPort << std::endl;

    clientSocket->connectToHost(yourHostName, yourPort);
    if (!clientSocket->waitForConnected(CONNECTION_TIMEOUT)) {
        rxDialogText->append(tr("Unable to connect to server"));
        std::cerr << clientSocket->error() << " " << clientSocket->errorString().toStdString() << std::endl;
        return;
    }

    // Have the clientSocket signal when there is data to read
    connect (clientSocket, SIGNAL(readyRead()), this, SLOT(readYourDialog()));
    // Wrap a QDataStream around the socket for IO buffering and data packet alignment
    inStream.setDevice(clientSocket);
    inStream.setVersion(QDataStream::Qt_4_0);

    QString msg = tr("Connected to Server ");
    msg.append(clientSocket->peerAddress().toString());
    msg.append(":");
    msg.append(QString::number(clientSocket->peerPort()));
    rxDialogText->append(msg);
}

/*
 * Slot to handle an incoming connection to our ServerSocket
 */
void ChatWindow::setClientSocket (QTcpSocket *newClientSocket) {
    std::cout << "setClientSocket: " << std::endl;
    this->clientSocket = new QTcpSocket();
    // In Qt, it is necessary to clone the socket because it was created
    // in the ServerSocketThread and we want to use it in this thread.
    // Normally (outside of Qt), sockets are thread-safe
    this->clientSocket->setSocketDescriptor(newClientSocket->socketDescriptor());

    connect (clientSocket, SIGNAL(readyRead()), this, SLOT(readYourDialog()));
    inStream.setDevice(clientSocket);
    inStream.setVersion(QDataStream::Qt_4_0);

    QString msg = tr("Client connected from ");
    msg.append(clientSocket->peerAddress().toString());
    msg.append(":");
    msg.append(QString::number(clientSocket->peerPort()));
    rxDialogText->append(msg);
}

void ChatWindow::setMyPort(void) {
    myPortBox->updateNumber(myPort);
}

void ChatWindow::setYourPort(void) {
    yourPortBox->updateNumber(yourPort);
}

void ChatWindow::setYourHostName(void) {
    yourHostBox->updateString(yourHostName);
}
