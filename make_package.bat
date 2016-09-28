mkdir package
cd package

copy %CD%\..\Release\MetCOM.exe MetCOM.exe

windeployqt MetCOM.exe
copy %CD%\..\*.qm translations\

cd ..

copy %CD%\package\MetCOM.exe E:\tmp\MetCOM.exe.txt

pause