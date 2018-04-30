/*
 * Implementation of functions for serversocketthread.h
 *
 * D. Shpak
 * June 19, 2017
 */

#include "serversocketthread.h"
#include <QtNetwork/QTcpServer>
#include <QMessageBox>

ServerSocketThread::ServerSocketThread(QWidget *myParent, const quint16 serverPort) {
    this->myParent = myParent;
    this->serverPort = serverPort;

    quitFlag = false;
    if (!isRunning()) {
        // As in Java, we call start() rather than run() so that we get a new thread
        start();
    }
}

ServerSocketThread::~ServerSocketThread() {
    quitFlag = true;
    if (serverSocket->isListening()) {
        serverSocket->close();
    }
    delete serverSocket;
}

#include <iostream>

/*
 * Blocking thread that listens on a ServerSocket for incoming connection requests
 */
void ServerSocketThread::run() {
    std::cout << "ServerSocketThread" << this->currentThreadId() << std::endl;
    // serverSocket must be created here so that it belongs to the correct thread
    serverSocket = new QTcpServer();  // Cannot have parent object!

    // Using QHostAddress::Any will cause server to listen on all network interfaces
    if (!serverSocket->listen(QHostAddress::Any, serverPort)) {
      std::cerr << "Server Socket unable to listen on port " << serverPort << std::endl;
      /* This QMessageBox needs to be done in the GUI thread since that thread
	 own all GUI components.  We would need to send a signal to the GUI thread.
        // Display a blocking pop-up message
        QMessageBox::critical(myParent, tr("Server Mode"),
                              tr("Unable to start the server: %1.")
                              .arg(serverSocket->errorString()));
      */
        return;
    }

    std::cout << "Listening on " << serverSocket->serverAddress().toString().toStdString() << ":" << serverSocket->serverPort() << std::endl;
    while (!quitFlag) {
        std::cout << "Waiting for Connection" << std::endl;
        serverSocket->waitForNewConnection(SERVER_TIMEOUT_MS);
        if (!serverSocket->hasPendingConnections()) {
            std::cout << "Timeout" << std::endl;
            continue;
        }
        std::cout << "New Client connecting ... " ;
        QTcpSocket *clientSocket = serverSocket->nextPendingConnection();
        std::cout << "connected on " << clientSocket->localAddress().toString().toStdString() << ":" << clientSocket->localPort() << std::endl;
        emit newClient (clientSocket);
    }
    serverSocket->close();
}

/*
 * Set a flag so that the server thread will stop after the next Timeout
 * This is safe even though it is called from a different thread.
 */
void ServerSocketThread::stop(void) {
    std::cout << "ServerSocketThread stop() called" << std::endl;
    quitFlag = true;
}
