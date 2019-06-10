#!/bin/bash
cd ../
ls
make clean
make 
if [ $2 == 1 ];then
	clear
	clear
fi
cd bin 
./tp3 "../entradas/$1.txt"
