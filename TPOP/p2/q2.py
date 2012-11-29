



#tests
#
#test 1
#------
#46 1.5
#hours paid: 49 total paid: 73.5 total paid on overtime: 13.5
#
#test 2
#------
#40 20
#hours paid: 40 total paid: 800 total paid on overtime: 0

hours = input("No. of hours:")
hourly_rate = input("Hourly rate:")

hours_paid = ((hours-40)*0.5+hours)

print "Hours paid: "+ str(hours_paid) 
print "Total paid: "+ str(hours_paid * hourly_rate)
print "Total paid on overtime: "+ str((hours_paid-40) * hourly_rate) 
