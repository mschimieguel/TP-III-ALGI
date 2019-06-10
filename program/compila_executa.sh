#!/bin/bash
cd ../
ls
make clean
make
if [ $3 == 1 ];then
	clear
	clear
fi
cd bin 

if [ $2 == 1 ];then
	./tp3 "tarefa1" "../entradas/$trilha1.txt"
fi
if [$2 == 2 ];then
	./tp3 "tarefa2" "../entradas/$trilha1.txt"
fi


