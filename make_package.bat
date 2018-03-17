mkdir package
cd package

copy %CD%\..\Release\TGlobal.exe TGlobal.exe

windeployqt TGlobal.exe
copy %CD%\..\*.qm translations\

cd ..

copy %CD%\package\TGlobal.exe E:\tmp\TGlobal.exe.txt

pause