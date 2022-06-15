@ECHO OFF
    IF EXIST build RMDIR /S /Q build
    MKDIR build
    CD build
    
    PUSHD %~dp0\build
    CALL cmake ..
    POPD
PAUSE