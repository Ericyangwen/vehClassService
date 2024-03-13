#include "./dll32lidarmodel.h"
#include "common.h"
#include <QFile>
#include <QDebug>

Dll32LidarModel::Dll32LidarModel(QObject *parent) : QObject(parent)
{
    _id = 0;
    _setClsModel = nullptr;
    _getClsResult = nullptr;
//    _getClsResult2 = nullptr;
}

Dll32LidarModel::~Dll32LidarModel()
{
    //if(_qlib.isLoaded())
    //    _qlib.unload();
}

bool Dll32LidarModel::init(int id, QString dllPath, QString modelPath)
{
    _id = id;

    if(_qlib.isLoaded())
        _qlib.unload();

    if(!load(dllPath))
    {
        return false;
    }

    return setClsModel(modelPath);
}

bool Dll32LidarModel::load(QString dllPath)
{
    if(!QFile::exists(dllPath))
    {
        qWarning() << "Dll32LidarModel dll file is not exist.";
        return false;
    }

    _qlib.setFileName(dllPath);
    if(_qlib.load())
    {
        _setClsModel = (pFunc_SetClsModel)_qlib.resolve("setClsModel");
        _getClsResult = (pFunc_GetClsResult)_qlib.resolve("getClsResult");
//        _getClsResult2 = (pFunc_GetClsResult2)_qlib.resolve("getClsResult2");
        return true;
    }
    else
    {
        qWarning() << "Dll32LidarModel dll load fail.";
        return false;
    }
}

//bool Dll32LidarModel::load_win(const char* libpath)
//{
//    try
//    {
//        WCHAR wszClassName[256];
//        memset(wszClassName, 0, sizeof(wszClassName));
//        MultiByteToWideChar(CP_ACP, 0, libpath, strlen(libpath) + 1, wszClassName,
//            sizeof(wszClassName) / sizeof(wszClassName[0]));
//        HINSTANCE hDllhinst = LoadLibrary(wszClassName);
//        if (hDllhinst)
//        {
//            //获取动态连接库里的函数地址。
//            _init = (pfunc_cluster_init)GetProcAddress(hDllhinst, "init");
//            _setClsModel = (pfunc_cluster_setClsModel)GetProcAddress(hDllhinst, "setClsModel");
//            _getClsResultXyzPcl = (pfunc_cluster_getClsResultXyzPcl)GetProcAddress(hDllhinst, "getClsResultXyzPcl");
//            _getClsResultXyz = (pfunc_cluster_getClsResultXyz)GetProcAddress(hDllhinst, "getClsResultXyz");
//
//            return true;
//        }
//        else
//        {
//            cout << "ClusterModel dll load fail:-1" << endl;
//            return false;
//        }
//    }
//    catch (...)
//    {
//        cout << "ClusterModel dll load fail:-2" << endl;
//        return false;
//    }
//}

bool Dll32LidarModel::setClsModel(QString modelPath)
{
    if(_setClsModel == nullptr)
        return false;

    return _setClsModel((char*)modelPath.toStdString().c_str()) != -1;
}

int Dll32LidarModel::getClsResult(QString cldPath)
{
    if(_getClsResult == nullptr)
        return -2;

    return _getClsResult((char*)cldPath.toStdString().c_str());
}

//int Dll32LidarModel::getClsResultByPtr(pcl::PointCloud<pcl::PointXYZ>::Ptr ptr)
//{
//    if(_getClsResult2 == nullptr)
//        return -2;

//    return _getClsResult2(ptr);
//}
