echo.install......  
echo off  
cd %~dp0
sc create JDLine32.Service.VehType binPath= "%~dp0\JDLine32.Service.exe"   
sc config JDLine32.Service.VehType start= AUTO
net start JDLine32.Service.VehType
echo off  
echo.install successed!  
pause