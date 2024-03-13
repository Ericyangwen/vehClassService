#pragma once
#include <QObject>
#include "common.h"
#include "GQueue.h"
#include "model/dll32lidarmodel.h"

///// <summary>
///// 分类模型类型
///// </summary>
//enum VehTypeModel
//{
//	VehTypeModel_ALL, //全车型
//	VehTypeModel_XKXH //小客小货
//};

class VehTypeModelWorker : public QObject
{
	Q_OBJECT

public:
	VehTypeModelWorker(QObject *parent = nullptr);
	~VehTypeModelWorker();

	Dll32LidarModel _vehTypeModelAll;//点云分类模型-全车型
	Dll32LidarModel _vehTypeModelXKXH;//点云分类模型-小客小货

	void setRunFlag(bool flag) { _run = flag; }
	bool getRunFlag() { return _run; }
	void setVehTypeModelParam(VehTypeModelParam vParam) { _vParam = vParam; }
	void AddToProc(RegPointCloudObj outveh);

private:
	VehTypeModelParam _vParam;
	bool _run;
	GQueue<RegPointCloudObj> _queue;

	bool initModel();

signals:
	void signal_initRes(bool);
	void signal_workDone();
	void signal_vehTypeProcDone(int, int);

public slots:
	void doWork();
};
