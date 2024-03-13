#ifndef VEHTYPEMODELAPP_H
#define VEHTYPEMODELAPP_H

#include <QObject>
#include <QThread>
#include "vehtypemodelworker.h"
#include "ctcpserver.h"

class VehTypeModelApp : public QObject
{
    Q_OBJECT
public:
    explicit VehTypeModelApp(QObject *parent = nullptr);
    ~VehTypeModelApp();

    int init();

private:
    VehTypeModelWorker _vehTypeModelWorker;
    QThread _vehTypeModelThread;//模型推理线程
    CTcpServer _tcpServer;
    bool _modelInitRes;

    void initVehTypeModel();

signals:

public slots:
    void slot_modelInitRes(bool);
    void slot_vehTypeResult(int id, int resType);
    void slot_tcpRecvData(const QString&);
    void slot_newConnection(QTcpSocket*);
};

#endif // VEHTYPEMODELAPP_H
