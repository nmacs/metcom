mkdir package
cd package

copy %CD%\..\build\release\MetCOM.exe MetCOM.exe

windeployqt MetCOM.exe
copy %CD%\..\*.qm translations\

cd ..