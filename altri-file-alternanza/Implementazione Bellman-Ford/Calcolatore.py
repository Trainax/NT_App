archi= open("Archi.txt","r")
nodi= open("Nodi.txt","r")
output=open("Output.txt","w")

contenutoArchi=archi.read()
contenutoNodi=nodi.read()

arrayArchi=['A','B','C','Pippo']
arrayCollegamenti=[['A','A','B'],['B','C','Pippo'],[3,2,2],[3,999,2]]

numeroNodi=len(arrayArchi)
i=0
output.write("Nodo di partenza: "+arrayArchi[0]+"\n")
ciclo=range(1,numeroNodi)

output.write(arrayArchi[0]+"    0\n")
a=1
for count in ciclo:
    output.write(arrayArchi[a]+"    Infinito\n")
    a=a+1;
a=0
b=1
for count in ciclo:
    output.write("Iterazione: "+str(a)+"\n")
    output.write(arrayArchi[0]+"    0\n")
    for count in ciclo:
        output.write(arrayArchi[b]+"    Infinito\n")
        b=b+1;
    a=a+1

archi.close()
nodi.close()
output.close()
