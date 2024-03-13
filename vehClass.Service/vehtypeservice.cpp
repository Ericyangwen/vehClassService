#include "vehtypeservice.h"
#include "vehtypemodelapp.h"

VehTypeService::VehTypeService(int argc, char** argv) : QtService<QCoreApplication>(argc, argv, "JDLine32.Service.VehType")
{
    setServiceDescription("JDLine32 VehType Service");
    setServiceFlags(QtServiceBase::CanBeSuspended);

    _app = application();
}

void VehTypeService::start()
{
    VehTypeModelApp* vehTypeModelApp = new VehTypeModelApp(_app);
    int res = vehTypeModelApp->init();
    if (res != 0)
    {
        logMessage(QString("[error]start err: %1").arg(res), QtServiceBase::Error);
        _app->quit();
    }
}

void VehTypeService::stop()
{
    _app->quit();
}

void VehTypeService::pause()
{
}

void VehTypeService::resume()
{

}