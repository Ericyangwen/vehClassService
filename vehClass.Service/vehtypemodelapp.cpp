#include "vehtypemodelapp.h"
#include "Utils.h"

ModelParam g_ModelParam;

VehTypeModelApp::VehTypeModelApp(QObject *parent) : QObject(parent)
{
    _modelInitRes = false;
}

VehTypeModelApp::~VehTypeModelApp()
{

}

int VehTypeModelApp::init()
{
    //读取参数
    if(!readParam())
        return -1;

    //开启server
    connect(&_tcpServer, &CTcpServer::signal_newConnection, this, &VehTypeModelApp::slot_newConnection);
    connect(&_tcpServer, &CTcpServer::signal_recvData, this, &VehTypeModelApp::slot_tcpRecvData);
    if(!_tcpServer.init(QHostAddress(g_ModelParam.lidarParam.localIP), 11009))
    {
        qDebug() << "[error]tcpserver init.";
        return -2;
    }

    //初始化点云分类模型
    initVehTypeModel();
    return 0;
}

void VehTypeModelApp::initVehTypeModel()
{
    //启动推理线程
    _vehTypeModelWorker.setVehTypeModelParam(g_ModelParam.vehTypeModelParam);
    _vehTypeModelWorker.moveToThread(&_vehTypeModelThread);
    connect(&_vehTypeModelThread, &QThread::started, &_vehTypeModelWorker, &VehTypeModelWorker::doWork);
    connect(&_vehTypeModelWorker, &VehTypeModelWorker::signal_initRes, this, &VehTypeModelApp::slot_modelInitRes);
    connect(&_vehTypeModelWorker, &VehTypeModelWorker::signal_vehTypeProcDone, this, &VehTypeModelApp::slot_vehTypeResult);
    _vehTypeModelThread.start();
}

void VehTypeModelApp::slot_modelInitRes(bool res)
{
    if (!res)
    {
        _modelInitRes = false;
        qDebug() << "[error]model init.";
    }
    else
    {
        _modelInitRes = true;
        qDebug() << "[ok]model init.";
    }
}

void VehTypeModelApp::slot_tcpRecvData(const QString& str)
{
    //json解析
    QJsonParseError parseErr;
    QJsonDocument document = QJsonDocument::fromJson(str.toUtf8(), &parseErr);
    if (parseErr.error != QJsonParseError::NoError)
    {
        qDebug() << "[error]parse recv data: " << str;
        return;
    }
    auto jsonObject = document.object();
    int code = jsonObject["code"].toInt();//指令码 0-模型状态  1-推理结果
    if (code == 1)
    {
        if (jsonObject.value("data").isObject())
        {
            RegPointCloudObj info;
            auto dataObj = jsonObject.value("data").toObject();
            info.id = dataObj["id"].toInt();
            info.modelId = dataObj["modelId"].toInt();
            info.pcdDirName = dataObj["pcdDirName"].toString();
            _vehTypeModelWorker.AddToProc(info);
        }
    }
}

void VehTypeModelApp::slot_newConnection(QTcpSocket* socket)
{
    try 
    {
        //发送模型状态
        QJsonObject jsonObj;
        QJsonObject dataObj;
        dataObj.insert("modelState", _modelInitRes);

        jsonObj.insert("code", 0);
        jsonObj.insert("data", dataObj);
        QString str = QString(QJsonDocument(jsonObj).toJson());
        _tcpServer.sendBroadCast(str.toUtf8());
        qDebug() << "sendBroadCast, json:" << str;
    }
    catch (...)
    {

    }
}

void VehTypeModelApp::slot_vehTypeResult(int id,int resType)
{
    QJsonObject jsonObj;
    QJsonObject dataObj;
    dataObj.insert("id", id);
    dataObj.insert("resType", resType);

    jsonObj.insert("code", 1);
    jsonObj.insert("data", dataObj);
    QString str = QString(QJsonDocument(jsonObj).toJson());
    _tcpServer.sendBroadCast(str.toUtf8());
    qDebug() << "sendBroadCast, json:" << str;
}
