#implement item quantity
#implement item names

import sys

options = [ 1, "main", [[1, "movie", [[0, "DVD movie", 2.50], [0, "BluRay movie", 3.50]]], [1, 
"games", [[0, "new game", 4.00],[0, "old game", 2.50]]]]]

stack = []

bill = []

def valid_int(x):
	try:
		int(x)
		return True
	except ValueError:
		return False

def wait_input(message):
	option = raw_input(message)

	if not valid_int(option):
		return False
	
	return int(option)

def show_bill():
	print "Your bill includes the following items:"
	for index,element in enumerate(elements):
		print str(index+1)+". "+element[1]+" ("+str(element[2]) +")"

	print "Choose one of the following:"
	print "1. remove an item"
	print "2. buy"

def show_checkout(current):
	bill.append(current)

	print "You have added to your shopping cart: "+ current[1]
	print "Price: "+ str(current[2])
	print "Choose one of the following:"
	print "1. view bill"
	print "2. back"
	print "3. restart"
	print "4. exit"

	option = wait_input("Please choose one of the following: ")

	if option==1: 
		show_bill()
	if option==2:
		stack.pop()
	if option==3:
		global stack = []
	if option==4:
		sys.exit()

def print_menu(elements):
	for index,element in enumerate(elements):
		if element[0]==0:
			print str(index+1)+". "+element[1]+" ("+ str(element[2]) + ")"
		else:
			print str(index+1)+". "+element[1]

def show(current):

	if current[0]==0: 
		show_checkout(current)
	else: 
		while True:
			if not stack:
				print "Main menu"
				print "Choose one of the following:"
				print_menu(current[2])
				print "0. exit"
			else:
				print "Current category: "+ current[1]
				print "Choose one of the following:"
				print_menu(current[2])
				print "0. back"

			option = wait_input("Please choose one of the following: ")

			if type(option) != int and option==False: 
				continue
		
			if option == 0: 
				if not stack:
					sys.exit()
				else:
					stack.pop()
					return
			else:
				if len(current) < option-1:
					print "Invalid option. Try again"
					continue
				else:
					stack.append(option)
					return

def resolve(stack): 
	if len(stack) > 0:
		working_stack = stack
		current = options

		while len(working_stack) >0:
			 	current = current[2][working_stack[0]]
				working_stack= working_stack[1:]

		return current

	return options

while True:
	show(resolve(stack))
