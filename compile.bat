
set start_date=%date%
set start_time=%time%
set d=-debug 
set n=10000000
::Build each needed C file into .O file
start /realtime /B /WAIT %GBDK_HOME%\bin\lcc -Wa-l -Wl-m -Wl-y -Wf--max-allocs-per-node%n% --opt-code-size %d% -c -o walksprite.o walksprite.c
start /realtime /B /WAIT %GBDK_HOME%\bin\lcc -Wa-l -Wl-m -Wl-y -Wf--max-allocs-per-node%n% --opt-code-size %d% -c -o soic_c.o soic_c.c
start /realtime /B /WAIT %GBDK_HOME%\bin\lcc -Wm-yC -Wa-l -Wl-m -Wl-y -Wf--max-allocs-per-node%n% --opt-code-size %d% -c -o cedule.o cedule.c
start /realtime /B /WAIT %GBDK_HOME%\bin\lcc -Wm-yC -Wa-l -Wl-m -Wl-y -Wf--max-allocs-per-node%n% --opt-code-size %d% -c -o fps.o fps.c
start /realtime /B /WAIT %GBDK_HOME%\bin\lcc -Wm-yC -Wa-l -Wl-m -Wl-y -Wf--max-allocs-per-node%n% --opt-code-size %d% -c -o input.o input.c
start /realtime /B /WAIT %GBDK_HOME%\bin\lcc -Wm-yC -Wa-l -Wl-m -Wl-y -Wf--max-allocs-per-node%n% --opt-code-size %d% -c -o animation.o animation.c
start /realtime /B /WAIT %GBDK_HOME%\bin\lcc -Wm-yC -Wa-l -Wl-m -Wl-y -Wf--max-allocs-per-node%n% --opt-code-size %d% -c -o greenhill1_map_compressed.o sprites\greenhill1_map_compressed.c
start /realtime /B /WAIT %GBDK_HOME%\bin\lcc -Wm-yC -Wa-l -Wl-m -Wl-y -Wf--max-allocs-per-node%n% --opt-code-size %d% -c -o grafika_compressed.o sprites\grafika_compressed.c
start /realtime /B /WAIT %GBDK_HOME%\bin\lcc -Wm-yC -Wa-l -Wl-m -Wl-y -Wf--max-allocs-per-node%n% --opt-code-size %d% -c -o ring.o ring.c
start /realtime /B /WAIT %GBDK_HOME%\bin\lcc -Wm-yC -Wa-l -Wl-m -Wl-y -Wf--max-allocs-per-node%n% --opt-code-size %d% -c -o badniks.o badniks.c
start /realtime /B /WAIT %GBDK_HOME%\bin\lcc -Wm-yC -Wa-l -Wl-m -Wl-y -Wf--max-allocs-per-node%n% --opt-code-size %d% -c -o ring_sprite.o sprites\ring_sprite.c
start /realtime /B /WAIT %GBDK_HOME%\bin\lcc -Wm-yC -Wa-l -Wl-m -Wl-y -Wf--max-allocs-per-node%n% --opt-code-size %d% -c -o waterfall.o sprites\waterfall.c
start /realtime /B /WAIT %GBDK_HOME%\bin\lcc -Wm-yC -Wa-l -Wl-m -Wl-y -Wf--max-allocs-per-node%n% --opt-code-size %d% -c -o finish_poles.o sprites\finish_poles.c
start /realtime /B /WAIT %GBDK_HOME%\bin\lcc -Wm-yC -Wa-l -Wl-m -Wl-y -Wf--max-allocs-per-node%n% --opt-code-size %d% -c -o dead.o dead.c
start /realtime /B /WAIT %GBDK_HOME%\bin\lcc -Wm-yC -Wa-l -Wl-m -Wl-y -Wf--max-allocs-per-node%n% --opt-code-size %d% -c -o printcode.o printcode.c
start /realtime /B /WAIT %GBDK_HOME%\bin\lcc -Wm-yC -Wa-l -Wl-m -Wl-y -Wf--max-allocs-per-node%n% --opt-code-size %d% -c -o badniks_sprites.o sprites\badniks_sprites.c
start /realtime /B /WAIT %GBDK_HOME%\bin\lcc -Wm-yC -Wa-l -Wl-m -Wl-y -Wf--max-allocs-per-node5000000 --opt-code-size %d% -c -o main.o main.c
rem THIS CODE GETS ALL COMPILED .O FILES FROM ABOVE
@echo off
setlocal enabledelayedexpansion
set files=
for %%f in (*.o) do (
  if not defined files (
    set files=%%f
  ) else (
    set files=!files! %%f
  )
)
rm woomy.map
@echo on
start /realtime /B /WAIT %GBDK_HOME%\bin\lcc -Wm-yC -Wl-y -Wa-l -Wl-m %d% -o WOOMY.gbc %files%
@echo off
endlocal
IF EXIST "woomy.map" (
	echo %date% %time% >> sizelog.log
	romusage woomy.map -g >> sizelog.log
	echo  >> sizelog.log
	echo 
	echo
)
@echo on
romusage woomy.map -sR -g
::del *.asm
del *.o
::del *.sym
::del *.lst
del *.rel
del *.ihx
del *.rst
set end_date=%date%
set end_time=%time%
set /a start_seconds=(1%start_date:~7,2%-100)*86400 + 1%start_time%
set /a end_seconds=(1%end_date:~7,2%-100)*86400 + 1%end_time%
set /a elapsed_seconds=%end_seconds%-%start_seconds%
echo Compile time: %elapsed_seconds% seconds
pause