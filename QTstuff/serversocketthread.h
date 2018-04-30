/*
 * A Qt QThread that runs a blocking TCP server socket.
 * It signals when a new client connects.
 *
 * D. Shpak
 * June 19, 2017
 */

#ifndef SERVERSOCKETTHREAD_H
#define SERVERSOCKETTHREAD_H

#include <QObject>
#include <QThread>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>

class ServerSocketThread : public QThread {
    Q_OBJECT
public:
    ServerSocketThread(QWidget *myParent, const quint16 serverPort);
    ~ServerSocketThread();
    void run() override;

signals:
    void newClient (QTcpSocket *clientSocket);

public slots:
    void stop();

private:
    const int SERVER_TIMEOUT_MS = 2 * 1000; // ms

    QWidget *myParent;
    QTcpServer *serverSocket;
    quint16 serverPort;
    bool quitFlag;
};

#endif // SERVERSOCKETTHREAD_H
