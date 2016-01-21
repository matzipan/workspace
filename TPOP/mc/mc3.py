import math

x = int(raw_input())

prime =True

if x==0 or x==1:
	print "You cannot check 0,1"
else:
	for i in range(2,int(math.sqrt(x))):
		if x%i == 0:
			prime=False
			break
	
	if prime: 
		print x, "is prime"
	else:
		print x, "is not prime"		

