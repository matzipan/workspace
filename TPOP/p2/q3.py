#tests
#
#test1 
#---------
#speed limit: 100
#speed: 110
#fine: 350
#
#test2
#----------
#speed limit: 80
#speed: 85
#fine: 125
#
#test3
#---------
#speed limit: 80
#speed: 75
#no fine

speed_limit = input("Speed limit:") 
clocked_speed = input("Clocked speed:")

if speed_limit >= clocked_speed:
	print "The speed is not over the limit"
else:
	fine=100
	
	if clocked_speed > 90:
		fine += 200

	fine += (clocked_speed - speed_limit) *5

	print "The fine is: "+ str(fine)
