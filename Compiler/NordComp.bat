@echo off

color 7

g++ -o done scripts\say_done.cpp
g++ -o temp scripts\source.cpp

set /p filename=Enter the name of the file you want to compile:
echo Openning file: "%filename%"
done

echo Precompiling...
temp %filename%
done

echo Sending to the compiler...
stc.ttl
done

del done.exe
del temp.exe
cmd /k
