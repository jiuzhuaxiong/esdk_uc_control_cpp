@echo off

echo.
echo －－－－－ 编译 UC Control 2008－－－－－－－－－
rd /Q /S ..\Release
@"%VS90COMNTOOLS%\..\IDE\devenv.com" ..\eSDKClient2008.sln /Rebuild "Release"
echo.
echo －－－－－ 编译 UC Control 2008成功 －－－－－－－－

echo. 
echo －－－－－ 拷贝文件 －－－－－－－－－－
	::获得当前时间，作为生成版本的目录名
	for /F "tokens=1-4 delims=-/ " %%i in ('date /t') do (
	   set Year=%%i
	   set Month=%%j
	   set Day=%%k
	   set DayOfWeek=%%l
	)
	for /F "tokens=1-2 delims=: " %%i in ('time /t') do (
	   set Hour=%%i
	   set Minute=%%j
	)

	::设置各变量名
	set   	DateTime=%Year%-%Month%-%Day%

	rd /Q /S .\%DateTime%
	rd /Q /S .\%DateTime%_PDB
	mkdir .\%DateTime%
	mkdir .\%DateTime%_PDB

	mkdir .\%DateTime%\C++控件
	mkdir .\%DateTime%\C++控件\include
	mkdir .\%DateTime%\C++控件\vs2008
	mkdir .\%DateTime%\C++控件\vs2010
	mkdir .\%DateTime%\C++控件\vs2008\lang
	mkdir .\%DateTime%\C++控件\vs2010\lang

	mkdir .\%DateTime%_PDB\C++控件
	mkdir .\%DateTime%_PDB\C++控件\vs2008
	mkdir .\%DateTime%_PDB\C++控件\vs2010

	xcopy /Y /i /r /s ..\include .\%DateTime%\C++控件\include
	xcopy /Y /i /r /s ..\Release\eSDKClient.dll .\%DateTime%\C++控件\vs2008
	xcopy /Y /i /r /s ..\Release\eSDKClient.pdb .\%DateTime%_PDB\C++控件\vs2008
	xcopy /Y /i /r /s ..\Release\eSDKClient.lib .\%DateTime%\C++控件\vs2008
	xcopy /Y /i /r /s ..\eSDKClient\lang\*.ini .\%DateTime%\C++控件\vs2008\lang
	
del /Q .\%DateTime%\*
	
echo.
echo －－－－－ 编译 UC Control 2010－－－－－－－－－
del /Q ..\Release\*
@"%VS100COMNTOOLS%\..\IDE\devenv.com" ..\eSDKClient2010.sln /Rebuild "Release"
echo.
echo －－－－－ 编译 UC Control 2010成功 －－－－－－－－
	
	xcopy /Y /i /r /s ..\Release\eSDKClient.dll .\%DateTime%\C++控件\vs2010
	xcopy /Y /i /r /s ..\Release\eSDKClient.lib .\%DateTime%\C++控件\vs2010
	xcopy /Y /i /r /s ..\Release\eSDKClient.pdb .\%DateTime%_PDB\C++控件\vs2010
	xcopy /Y /i /r /s ..\eSDKClient\lang\*.ini .\%DateTime%\C++控件\vs2010\lang
	

	
echo －－－－－ 拷贝文件成功 －－－－－－－－