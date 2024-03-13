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
    //// �������ӿͻ��ˣ����������Ҫע�⣬��QT 5����İ汾������������Ҫ��Ϊ **qintptr** ���������������ˣ�����û��ִ�к��������
    //virtual void incomingConnection(qintptr socketDescriptor);

signals:
    void signal_recvData(const QString&);
    void signal_newConnection(QTcpSocket*);

public slots:
    void slot_newConnection();
};

#endif // CTCPSERVER_H
