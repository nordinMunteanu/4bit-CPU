#!/bin/bash
if [ "$1" = "-c" ]
then 
    g++ -o precompile precompiler.cpp -std=c++11
    g++ -o compile compiler.cpp -std=c++11
    g++ -o upload uploader.cpp -std=c++11
    ./precompile $2
    ./compile
    ./upload

    touch compf.2p4fab
    touch compf_out.2p4hex

    echo "Process finished"
    rm compf.2p4fab
    if [ "$2" = "--keep-hex" ]
    then 
        echo "kept compf_out.2p4hex"
    else
        rm compf_out.2p4hex
    fi
    rm precompile
    rm compile
    rm upload
else 
    echo "Not enough arguments"
fi