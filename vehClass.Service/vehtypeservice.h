#pragma once
#include "qtservice.h"

class VehTypeService : public QtService<QCoreApplication>
{
public:
    VehTypeService(int argc, char** argv);

protected:
    QCoreApplication* _app;

    /* 开启服务 */
    virtual void start() override;

    /* 停止服务 */
    virtual void stop() override;

    /* 暂停服务 */
    virtual void pause() override;

    /* 重启服务 */
    virtual void resume() override;

};
