@ECHO OFF

::clean loader directory
if exist .\loader\build (echo o|del .\loader\build\*.*)
if exist .\loader\build (rd .\loader\build)

::clean titlescreen directory
if exist .\titlescreen\build (echo o|del .\titlescreen\build\*.*)
if exist .\titlescreen\build (rd .\titlescreen\build)

::clean main directory
if exist .\main\build (echo o|del .\main\build\*.*)
if exist .\main\build (rd .\main\build)

::clean release directory
if exist .\release (echo o|del .\release\*.*)
if exist .\release (rd .\release)

echo "Directories are clean"
pause


