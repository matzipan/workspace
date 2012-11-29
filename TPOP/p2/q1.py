#tests
#1,2,3
#1,3,2
#2,1,3
#2,3,1
#3,1,2
#3,2,1

tests = [ [1,2,3,3], [1,3,2,3], [2,1,3,3], [2,3,1,3], [3,1,2,3], [3,2,1,3] ] 

debug =False;
debug = True;
def get_max(x,y,z):
	if x>y:
		if x>z: 
			return x
		if z>x:
			return z
	if y>x:
		if y>z:
			return y
		if z>y: 
			return z
	


if debug==True:
	for index,test in enumerate(tests):
		if get_max(test[0], test[1], test[2])== test[3]: 
			print "test "+ str(index) +" passed"
		else:
			print "test "+ str(index) +" failed"		
else:
	print get_max(input("Number 1:"), input("Number 2:"), input("Number 3:"))
