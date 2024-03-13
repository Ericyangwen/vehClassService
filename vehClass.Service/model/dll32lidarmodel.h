#ifndef DLL32LIDARMODEL_H
#define DLL32LIDARMODEL_H

#include <QObject>
#include <QLibrary>
#include "common.h"
#include "GQueue.h"
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>

typedef int (CDECL *pFunc_SetClsModel)(char* path);
typedef int (CDECL *pFunc_GetClsResult)(char* pcdPath);
#endif

typedef int (*pFunc_SetClsModel)(char* path);
typedef int (*pFunc_GetClsResult)(char* pcdPath);

class Dll32LidarModel : public QObject
{
    Q_OBJECT
public:
    explicit Dll32LidarModel(QObject *parent = nullptr);
    ~Dll32LidarModel();

    bool init(int id, QString dllPath, QString modelPath);
    int getId() { return _id; }
    int getClsResult(QString cldPath);
//    int getClsResultByPtr(pcl::PointCloud<pcl::PointXYZ>::Ptr ptr);

private:
    int _id;
    QLibrary _qlib;
    pFunc_SetClsModel _setClsModel;
    pFunc_GetClsResult _getClsResult;
//    pFunc_GetClsResult2 _getClsResult2;

    bool load(QString modelPath);
    bool setClsModel(QString modelPath);
};

#endif // DLL32LIDARMODEL_H
