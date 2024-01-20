@echo off
rem
rem  This command file created rar archive for current project/catalog. В архив 
rem  включаются файлы с расширением из переменной BACK_FILES из текущего
rem  каталога и всех его подкаталогов.
rem
rem   Input parameters for batch:
rem
rem     %1=="postfix" - to archiv's name from file="arc_name.dat" add "_postfix"
rem                     
rem     %1==""        - ordinary name of archive + postfix "_t"
rem
rem  рекомендуемые суффиксы в имени архивного файла:
rem     w  - предполагается постоянное хранение данного архивного файла
rem     b  - backup иного назначения
rem     t  - промежуточные версии с временными контрольными точками
rem
rem  data creation: 06 april 2007
rem
rem    Version :  V0.6   data last modification:  11 may 2007
rem    Version :  V0.7   Изменено имя каталога архива на devel-arxiv 
rem    version :  v0.8   выравнены в одну строку дата и время создания
rem
rem    version :  v0.9   вместо имени файла запрашивается "суффикс" архива
rem        03-may-2008
rem
rem  (c) designer:  Fedotov A.N.            OOO "ФРАКТАЛЬ-СБ"  
rem
rem===========================================================================

set VERS_ARX=v1.0 (archive)

set COMMENT=backup_list.txt

set RAR=rar.exe

set ARC_NAME_DIR="devel-arxiv"

set BACK_FILES=*.h *.c *.cpp *.hpp *.hxx *.cxx *.hh *.cc  *.inc *.mak *.bat *.cmd *.ini *.prj *.txt *.afc *.raw *.html *.htm *.dat MakeFile.*  *.odt  *.dll *.lib *.log *.pro *.pri *.ui *.qm *.ts *.bpr  *.dfm *.res *.rc *.dat *.fsd *.eta *.tft *.vft  *.ift *.evl  *.Debug *.Release 

rem===========================================================================

  if  "%1"=="" (
   
     set postfix=_t

   )  else  ( 

     set postfix=_%1

   )	

   FOR /F %%i IN (arc_name.dat) DO @set ARC_NAME=%%i
   
   set ARC_DIR=c:\%ARC_NAME_DIR%\%ARC_NAME%
   
   if exist %ARC_DIR% ( 
      
      goto CONT1

   )  else  (

      mkdir %ARC_DIR%
      echo  " Success make new archive catalog = %ARC_DIR%  " 
   )

:CONT1

rem Формирование подписи для файла комментариев
rem ===========================================

set sdate=%date%
set stime=%time:~0,-6%

touch %COMMENT%

echo -- Archive [ %ARC_NAME%%postfix% ] created  at:[ %sdate%  %stime% ]  %VERS_ARX% >> %COMMENT%
echo -----------------------------------------------------------------------------   >> %COMMENT%

%RAR% a -rr -r -m5 -ep1 -idp -md1024 -ag[YY-MM-DD~HH-MM] %ARC_DIR%\%ARC_NAME%%postfix%  %BACK_FILES% c -z%COMMENT%

goto _EXIT

:ERROR
   echo " Illegal call without supply name of archive"
pause
goto _EXIT2

:_EXIT      
pause
:_EXIT2                                                                                                                                                                                                  