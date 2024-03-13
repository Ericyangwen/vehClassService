#pragma once
#include "qtservice.h"

class VehTypeService : public QtService<QCoreApplication>
{
public:
    VehTypeService(int argc, char** argv);

protected:
    QCoreApplication* _app;

    /* �������� */
    virtual void start() override;

    /* ֹͣ���� */
    virtual void stop() override;

    /* ��ͣ���� */
    virtual void pause() override;

    /* �������� */
    virtual void resume() override;

};
