#include "ctcpserver.h"
#include <QHostAddress>

CTcpServer::CTcpServer(QObject *parent) : QObject(parent)
{
    _port = 0;
    _server = new QTcpServer(this);
}

CTcpServer::~CTcpServer()
{

}

bool CTcpServer::init(const QHostAddress& address, int v)
{
    if(_port == 0)
    {
        _port = v;
    }

//    if(_server->isListening())
    {
        close();
    }

    connect(_server, &QTcpServer::newConnection, this, &CTcpServer::slot_newConnection);
    connect(_server, &QTcpServer::acceptError,[this](QAbstractSocket::SocketError){
        qDebug() << "Server Error:" << _server->errorString();
    });

    return _server->listen(address, _port);
}

void CTcpServer::close()
{
    _server->close();
    for(QTcpSocket* socket : _clientList)
    {
        //disconnect clients
        socket->disconnectFromHost();
        if(socket->state()!=QAbstractSocket::UnconnectedState)
        {
            socket->abort();
        }
    }
}

bool CTcpServer::sendBroadCast(QString data)
{
    if(!_server->isListening())
        return false;
    const QByteArray sendData = data.toUtf8();
    if(sendData.isEmpty())
        return false;
    for(QTcpSocket *socket : _clientList)
    {
        socket->write(sendData);
    }
}

//新的客户端连接请求
void CTcpServer::slot_newConnection()
{
    //如果有新的连接就取出
    while(_server->hasPendingConnections())
    {
        //nextPendingConnection返回下一个挂起的连接作为已连接的QTcpSocket对象
                    //套接字是作为服务器的子级创建的，这意味着销毁QTcpServer对象时会自动删除该套接字。
                    //最好在完成处理后显式删除该对象，以避免浪费内存。
                    //返回的QTcpSocket对象不能从另一个线程使用，如有需要可重写incomingConnection().
        QTcpSocket *socket=_server->nextPendingConnection();
        qDebug() << "new client connected: " << socket->peerAddress().toString() << ":" << socket->peerPort();
        _clientList.append(socket);
        emit signal_newConnection(socket);

        //收到数据
        connect(socket,&QTcpSocket::readyRead,[this,socket]{
            if(socket->bytesAvailable()<=0)
                return;
            //注意收发两端文本要使用对应的编解码
            QString recv_text=QString::fromUtf8(socket->readAll());
            qDebug() << "recv data from [" << socket->peerAddress().toString() << ":" << socket->peerPort() << "]:" << recv_text;
            emit signal_recvData(recv_text);
        });

        //error信号在5.15换了名字
#if QT_VERSION < QT_VERSION_CHECK(5, 15, 0)
        //错误信息
        connect(socket, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
                [this,socket](QAbstractSocket::SocketError){
        });
#else
        //错误信息
        connect(socket,&QAbstractSocket::errorOccurred,[this,socket](QAbstractSocket::SocketError){
        });
#endif

        //连接断开，销毁socket对象，这是为了开关server时socket正确释放
        connect(socket,&QTcpSocket::disconnected,[this,socket]{
            socket->deleteLater();
            _clientList.removeOne(socket);
            qDebug() << "disconnected:[" << socket->peerAddress().toString() << ":" << socket->peerPort() << "]";
        });


    }
}
