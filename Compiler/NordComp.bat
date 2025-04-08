@echo off

color 7

g++ -o done scripts\say_done.cpp
g++ -o precompile scripts\precompiler.cpp
g++ -o compile scripts\compiler.cpp

set /p filename=Enter the name of the file you want to compile:
echo Openning file: "%filename%"
done

echo Precompiling...
precompile %filename%
done

echo Compiling...
compile
done

echo Sending to the programmer...
stc.ttl
done

del done.exe
del precompile.exe
del compile.exe
del compf.2p4hex
cmd /k
