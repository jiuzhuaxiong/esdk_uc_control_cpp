@echo off

echo.
echo ���������� ���� UC Control 2008������������������
rd /Q /S ..\Release
@"%VS90COMNTOOLS%\..\IDE\devenv.com" ..\eSDKClient2008.sln /Rebuild "Release"
echo.
echo ���������� ���� UC Control 2008�ɹ� ����������������

echo. 
echo ���������� �����ļ� ��������������������
	::��õ�ǰʱ�䣬��Ϊ���ɰ汾��Ŀ¼��
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

	::���ø�������
	set   	DateTime=%Year%-%Month%-%Day%

	rd /Q /S .\%DateTime%
	rd /Q /S .\%DateTime%_PDB
	mkdir .\%DateTime%
	mkdir .\%DateTime%_PDB

	mkdir .\%DateTime%\C++�ؼ�
	mkdir .\%DateTime%\C++�ؼ�\include
	mkdir .\%DateTime%\C++�ؼ�\vs2008
	mkdir .\%DateTime%\C++�ؼ�\vs2010
	mkdir .\%DateTime%\C++�ؼ�\vs2008\lang
	mkdir .\%DateTime%\C++�ؼ�\vs2010\lang

	mkdir .\%DateTime%_PDB\C++�ؼ�
	mkdir .\%DateTime%_PDB\C++�ؼ�\vs2008
	mkdir .\%DateTime%_PDB\C++�ؼ�\vs2010

	xcopy /Y /i /r /s ..\include .\%DateTime%\C++�ؼ�\include
	xcopy /Y /i /r /s ..\Release\eSDKClient.dll .\%DateTime%\C++�ؼ�\vs2008
	xcopy /Y /i /r /s ..\Release\eSDKClient.pdb .\%DateTime%_PDB\C++�ؼ�\vs2008
	xcopy /Y /i /r /s ..\Release\eSDKClient.lib .\%DateTime%\C++�ؼ�\vs2008
	xcopy /Y /i /r /s ..\eSDKClient\lang\*.ini .\%DateTime%\C++�ؼ�\vs2008\lang
	
del /Q .\%DateTime%\*
	
echo.
echo ���������� ���� UC Control 2010������������������
del /Q ..\Release\*
@"%VS100COMNTOOLS%\..\IDE\devenv.com" ..\eSDKClient2010.sln /Rebuild "Release"
echo.
echo ���������� ���� UC Control 2010�ɹ� ����������������
	
	xcopy /Y /i /r /s ..\Release\eSDKClient.dll .\%DateTime%\C++�ؼ�\vs2010
	xcopy /Y /i /r /s ..\Release\eSDKClient.lib .\%DateTime%\C++�ؼ�\vs2010
	xcopy /Y /i /r /s ..\Release\eSDKClient.pdb .\%DateTime%_PDB\C++�ؼ�\vs2010
	xcopy /Y /i /r /s ..\eSDKClient\lang\*.ini .\%DateTime%\C++�ؼ�\vs2010\lang
	

	
echo ���������� �����ļ��ɹ� ����������������