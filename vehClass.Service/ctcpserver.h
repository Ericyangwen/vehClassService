#ifndef CTCPSERVER_H
#define CTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class CTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit CTcpServer(QObject *parent = nullptr);
    ~CTcpServer();

    void setPort(int v){_port = v;}
    bool init(const QHostAddress &address = QHostAddress::Any, int v=11009);
    void close();
    bool sendBroadCast(QString data);

private:
    QTcpServer *_server;
    int _port;
    QVector<QTcpSocket*> _clientList;

protected:
    //// 用来连接客户端，这个函数需要注意，在QT 5后面的版本参数部分类型要改为 **qintptr** 否则会出现连接上了，但是没有执行函数的情况
    //virtual void incomingConnection(qintptr socketDescriptor);

signals:
    void signal_recvData(const QString&);
    void signal_newConnection(QTcpSocket*);

public slots:
    void slot_newConnection();
};

#endif // CTCPSERVER_H
