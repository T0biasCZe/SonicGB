@echo off

setlocal enabledelayedexpansion

rem Set the variable to an empty string
set files=

rem Iterate through all the files in the current directory
for %%f in (*.o) do (
  rem Append the file name to the variable
  if not defined files (
    set files=%%f
  ) else (
    set files=!files! %%f
  )
)

rem Display the list of files
echo %files%
pause
pause