@echo off

pushd ..\..
tools\Premake\Windows\premake5.exe --verbose vs2010
popd
pause