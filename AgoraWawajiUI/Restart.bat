@echo off 
@ping 127.0.0.1 -n 4 >nul 
taskkill /f /im AgoraWawajiUI.exe
start AgoraWawajiUI.exe