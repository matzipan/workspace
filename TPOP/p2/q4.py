# 1 - 31
# 2 - 28/29
# 3 - 31
# 4 - 30
# 5 - 31
# 6 - 30
# 7 - 31
# 8 - 31
# 9 - 30
# 10 - 31
# 11 - 30
# 12 - 31

#tests
#01/02/1993 - true
#32/01/1993 - false
#31/04/1993 - false
#18/13/1993 - false
#28/02/1600 - true
#29/02/1600 - true
#29/02/1601 - false
#28/02/1601 - true
#31/02/1601 - false

tests = [ ["01/02/1993", True], ["32/01/1993", False], ["31/04/1993", False], ["18/13/1993", False], ["28/02/1600", True], ["29/02/1600", True], ["29/02/1601", False], ["28/02/1601", True], ["31/02/1601", 
False]]

debug= False
debug= True

def is_leap_year(x):
	if x%100==0 and x%400==0:
		return True
	if x%400!=0:
		return False
	if x%4==0:
		return True
	return False

def is_valid_date(d,m,y):
	if m == 2:
		if is_leap_year(y) :
			if d<= 29:
				return True
			else :
				return False
		elif d<= 28:
			return True
	else:
		if m<=7:
			if m%2 == 0 and d<=30: 
				return True
			if m%2 ==1 and d<=31:
				return True
		elif m<=12:
			if m%2 ==0 and d<=31:
				return True
			if m%2 ==1 and d<=30:
				return True
	
	return False		


def split_date(x):
	date = x.split("/")

	return [int(date[0]), int(date[1]), int(date[2])]

if debug == False: 
	date = split_date(str(raw_input("DD/MM/YYYY: ")))

	if is_valid_date(date[0],date[1],date[2]):
		print "It is a valid date"
	else:
		print "It is not a valid date"
else:
	for index, test in enumerate(tests):
		date = split_date(test[0])

		if is_valid_date(date[0],date[1],date[2]) == test[1]:
			print "test "+ str(index) + " passed"
		else:
			print "test "+ str(index) + " failed"  
