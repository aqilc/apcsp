@echo off
rmdir /S /Q package
mkdir package
copy main.exe "./package/" /y
copy graphics.glsl "./package/" /y

xcopy "./dawnlike" "./package/DawnLike" /s /i /q
xcopy "./maps" "./package/maps" /s /i /q