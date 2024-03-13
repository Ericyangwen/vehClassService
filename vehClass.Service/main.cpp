#include <QCoreApplication>
#include "vehtypeservice.h"

int main(int argc, char *argv[])
{
    VehTypeService vehTypeService(argc, argv);

    return vehTypeService.exec();
}


