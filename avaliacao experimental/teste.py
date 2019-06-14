from subprocess import check_output
#result  = int (os.system('./../bin/tp3 "tarefa2" "entradas/linetree/t145.txt"'))
a = int (check_output('./../bin/tp3 "tarefa1" "entradas/linetree/t145.txt"', shell=True))
print (a)