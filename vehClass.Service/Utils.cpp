#include "Utils.h"

/// <summary>
/// 读取本地配置
/// </summary>
bool readParam()
{
    QString filePath = QCoreApplication::applicationDirPath() + "/config.json";
    QFile file(filePath);
    if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }

    QString str = file.readAll();
    file.close();

    QJsonParseError parseErr;
    QJsonDocument document = QJsonDocument::fromJson(str.toUtf8(), &parseErr);
    if (parseErr.error != QJsonParseError::NoError)
    {
        return false;
    }

    QJsonObject jsonObj = document.object();

    try
    {
        if (jsonObj.contains("lidarParam"))
        {
            if (jsonObj.value("lidarParam").isObject())
            {
                auto lidarParam = jsonObj.value("lidarParam").toObject();
//                g_ModelParam.lidarParam.lidarIP = lidarParam["lidarIP"].toString();
//                g_ModelParam.lidarParam.lidarPort = lidarParam["lidarPort"].toInt();
                g_ModelParam.lidarParam.localIP = lidarParam["localIP"].toString();
//                g_ModelParam.lidarParam.localUdpPort = lidarParam["localUdpPort"].toInt();
//                QJsonArray val = lidarParam["verAzimuth"].toArray();
//                if (val.count() == 32)
//                {
//                    for (int i = 0;i < 32;i++)
//                    {
//                        g_ModelParam.lidarParam.verAzimuth[i] = val.at(i).toDouble();
//                    }
//                }
//                val = lidarParam["horAzimuth"].toArray();
//                if (val.count() == 32)
//                {
//                    for (int i = 0;i < 32;i++)
//                    {
//                        g_ModelParam.lidarParam.horAzimuth[i] = val.at(i).toDouble();
//                    }
//                }
            }
        }
        if (jsonObj.contains("vehTypeModelParam"))
        {
            if (jsonObj.value("vehTypeModelParam").isObject())
            {
                auto vehTypeModelParam = jsonObj.value("vehTypeModelParam").toObject();
                g_ModelParam.vehTypeModelParam.modelPath_all = vehTypeModelParam["modelPath_all"].toString();
                g_ModelParam.vehTypeModelParam.useModel_xkxh = vehTypeModelParam["useModel_xkxh"].toBool();
                g_ModelParam.vehTypeModelParam.pointCloudSave_hc = vehTypeModelParam["pointCloudSave_hc"].toBool();
                g_ModelParam.vehTypeModelParam.modelPath_xkxh = vehTypeModelParam["modelPath_xkxh"].toString();
                g_ModelParam.vehTypeModelParam.xkxh_height = vehTypeModelParam["xkxh_height"].toDouble();
                g_ModelParam.vehTypeModelParam.xkxh_length = vehTypeModelParam["xkxh_length"].toDouble();
            }
        }
    }
    catch (...)
    {
        return false;
    }

    return true;
}

/// <summary>
/// 加载默认参数
/// </summary>
void loadDefaultParam()
{
    //本地IP
    g_ModelParam.lidarParam.localIP = "192.168.3.121";
    //veh type model参数
    g_ModelParam.vehTypeModelParam.modelPath_all = QCoreApplication::applicationDirPath() + "/32lidar_c7_in4096_nofilter_ep6216_whole_cpu.model";
    g_ModelParam.vehTypeModelParam.useModel_xkxh = false;
    g_ModelParam.vehTypeModelParam.pointCloudSave_hc = false;
    g_ModelParam.vehTypeModelParam.modelPath_xkxh = QCoreApplication::applicationDirPath() + "/32lidar_c2_xkxh_planBgyh_1003+0326_ep6186_whole_cpu.model";
    g_ModelParam.vehTypeModelParam.xkxh_length = 7.0f;
    g_ModelParam.vehTypeModelParam.xkxh_height = 2.4f;
}
