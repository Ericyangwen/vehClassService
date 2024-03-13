//#include "precompiled.h"
#include "vehtypemodelworker.h"
#include <QCoreApplication>
#include <QThread>
#include <QDebug>

VehTypeModelWorker::VehTypeModelWorker(QObject *parent)
	: QObject(parent)
{
}

VehTypeModelWorker::~VehTypeModelWorker()
{
}

bool VehTypeModelWorker::initModel()
{
    if (!_vParam.useModel_xkxh)
    {
        return _vehTypeModelAll.init(VehTypeModel_ALL, QCoreApplication::applicationDirPath() + "/Dll32LidarModel.dll", QCoreApplication::applicationDirPath() + "/" + _vParam.modelPath_all);
    }

    return _vehTypeModelAll.init(VehTypeModel_ALL, QCoreApplication::applicationDirPath() + "/Dll32LidarModel.dll", QCoreApplication::applicationDirPath() + "/" + _vParam.modelPath_all)
        && _vehTypeModelXKXH.init(VehTypeModel_XKXH, QCoreApplication::applicationDirPath() + "/Dll32LidarModel_1.dll", QCoreApplication::applicationDirPath() + "/" + _vParam.modelPath_xkxh);
}

void VehTypeModelWorker::AddToProc(RegPointCloudObj info)
{
    _queue.push(info);
}

void VehTypeModelWorker::doWork()
{
    int res = 0;
    clock_t t0, t1;
    QString log = "";

    if (!initModel())
    {
        //init err
        emit signal_initRes(false);
        return;
    }
    emit signal_initRes(true);

    _run = true;
    while (_run)
    {
        res = 0;
        RegPointCloudObj veh;
        if (!_queue.wait_and_pop_fortime(veh, 100))
        {
            //超时
            continue;
        }

        //得到模型推理结果
        QString filename = QString("%1\\%2.pcd").arg(veh.pcdDirName).arg(veh.id);
        t0 = clock();
        if (veh.modelId == VehTypeModel_ALL)
            res = _vehTypeModelAll.getClsResult(filename);
        else if (veh.modelId == VehTypeModel_XKXH)
            res = _vehTypeModelXKXH.getClsResult(filename);
        t1 = clock();
        log = QString("id: %1, model_res: %2, model_id: %3, wastetime: %4")
            .arg(veh.id).arg(res).arg(veh.modelId).arg(t1 - t0);
        qDebug() << log;

        emit signal_vehTypeProcDone(veh.id, res);

        QThread::msleep(50);
    }

    emit signal_workDone();
}
