echo.uninstall service......  
echo off  
net stop JDLine32.Service.VehType
echo.delete service......  
sc delete JDLine32.Service.VehType
echo off  
echo.delete success!
pause