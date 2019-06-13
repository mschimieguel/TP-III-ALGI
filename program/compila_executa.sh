#!/bin/bash
make clean
make
if [ $3 == 1 ];then
	clear
	clear
fi
cd bin 

if [ $1 == 1 ];then
	./tp3 "tarefa1" "../entradas/trilha$2.txt"
fi
if [ $1 == 2 ];then
	./tp3 "tarefa2" "../entradas/trilha$2.txt"
fi


