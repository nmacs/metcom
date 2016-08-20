mkdir package
cd package

copy %CD%\..\..\build-untitled-Desktop_Qt_5_6_1_MSVC2015_32bit-Release\release\MetCOM.exe MetCOM.exe

windeployqt MetCOM.exe
copy %CD%\..\*.qm translations\

cd ..