@ECHO OFF
cd loader
CALL osdk_build.bat
cd ..\titlescreen
CALL osdk_makedata.bat
cd ..\main
CALL osdk_build_en.bat
CALL osdk_build_fr.bat
cd ..
md release
taptap join .\loader\build\loader.tap+.\titlescreen\build\titlescreen.tap+.\main\build\main_en.tap ".\release\OricKong_en.tap
taptap join .\loader\build\loader.tap+.\titlescreen\build\titlescreen.tap+.\main\build\main_fr.tap ".\release\OricKong_fr.tap

::sets auto start to off for the main program
.\tools\taptap autooff 2 release\OricKong_en.tap
.\tools\taptap autooff 2 release\OricKong_fr.tap

::displays the catalog of the built tapes
.\tools\taptap cat release\OricKong_en.tap
.\tools\taptap cat release\OricKong_fr.tap
pause