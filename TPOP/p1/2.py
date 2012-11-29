#date = str(raw_input())
date = "00:6n0:00"

x = date.split(":")

if int(x[0]) <= 60 or int(x[1]) <= 60: 
	minutes = 60* int(x[0]) + int(x[1])
	seconds = 60* minutes + int(x[2])
else :
	print "Your have more than 60 seconds or minutes. Stop violating the standards!" 

print seconds, "seconds"
