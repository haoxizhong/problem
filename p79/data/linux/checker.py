import os
import sys
import math

fin = open(sys.argv[1],'r')
fout = open(sys.argv[2],'r')
fans = open(sys.argv[3],'r')
score = int(sys.argv[4])
fres = open(sys.argv[5],'w')
flog = open(sys.argv[6],'w')

strin = ""
strout = ""
strans = ""

def nonempty(x):
	return x != []

for line in fin:
	strin = strin + line.replace('\n',' ').replace('\t',' ')
strinwith = filter(nonempty,strin.replace(' ',''))

for line in fout:
	strout = strout + line.replace('\n',' ').replace('\t',' ')
stroutwith = filter(nonempty,strout.replace(' ',''))

for line in fans:
	strans = strans + line.replace('\n',' ').replace('\t',' ')
stranswith = filter(nonempty,strans.replace(' ',''))

if (stroutwith != strinwith):
	print >> fres,0
	print >> flog,"Data error"
	gg

if (stranswith != strinwith):
	print >> fres,0
	print >> flog,"Your output doesn't match the input"
	gg

def calc(l1,l2):
	id1 = 0 
	id2 = 0
	nowlen1 = 0
	nowlen2 = 0
	res = 0
	while (id1<len(l1) and id2<len(l2)):
		if (nowlen1==nowlen2 and l1[id1]==l2[id2]):
			res = res + 1
		if (nowlen1<=nowlen2):
			nowlen1 = nowlen1 + len(l1[id1])
			id1 = id1 + 1
		else :
			nowlen2 = nowlen2 + len(l2[id2])
			id2 = id2 + 1
	return res

l1 = filter(nonempty,strout.split(' '))
l2 = filter(nonempty,strans.split(' '))

A = len(l1)
B = len(l2)
C = calc(l1,l2)
D = 1.0 * C / B
E = 1.0 * C / A
F = 2.0 * D * E / ( D + E )

print >> flog,"A="+str(A)
print >> flog,"B="+str(B)
print >> flog,"C="+str(C)
print >> flog,"D="+str(D)
print >> flog,"E="+str(E)
print >> flog,"F="+str(F)

if (F <= 0.75):
	print >> fres,0
else:
	print >> fres,round((F - 0.75)/0.25*10)
