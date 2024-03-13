#ifndef COMMON_H
#define COMMON_H

#include <QString>

/// <summary>
/// 分类模型类型
/// </summary>
enum VehTypeModel
{
    VehTypeModel_ALL, //全车型
    VehTypeModel_XKXH //小客小货
};

//配准点云及车型结果信息
struct RegPointCloudObj {
    int id;
//    PointCloud<PointXYZ> cloud;
    int modelId;//使用模型id
    int resType;//车型结果
    QString pcdDirName;

    RegPointCloudObj()
    {
        id = 0;
        resType = 0;
        modelId = 0;
        pcdDirName = "";
    }

    RegPointCloudObj(int i, /*PointCloud<PointXYZ> c,*/ int m, int r)
    {
        id = i;
//        cloud = c;
        modelId = m;
        resType = r;
    }
};

//激光器参数
struct LidarParam
{
    QString lidarIP;
    int lidarPort;
    QString localIP;
    int localUdpPort;

    float verAzimuth[32];//垂直方位角
    float horAzimuth[32];//水平方位角
};

//点云分类车型模型
struct VehTypeModelParam
{
    QString modelPath_all;//模型本地路径-全车型c7
    bool useModel_xkxh;//是否使用小客小货模型
    bool pointCloudSave_hc;//货车点云另存
    QString modelPath_xkxh;//模型路径-小客小货c2
    float xkxh_height;//使用xkxh模型阈值
    float xkxh_length;
};

//模型参数
struct ModelParam
{
    LidarParam lidarParam;
    VehTypeModelParam vehTypeModelParam;
};

extern ModelParam g_ModelParam;

#endif // COMMON_H
