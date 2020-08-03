@echo off
cd /d %~dp0
start call windows_build_release 2017
start call windows_build_release 2018
start call windows_build_release 2019
start call windows_build_release 2020