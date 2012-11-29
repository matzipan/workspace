import sys

options = [ 1, "main", [[1, "movie", [[0, "DVD movie", 2.50], [0, "BluRay movie", 3.50]]], [1, "games", [[0, "new game", 4.00],[0, "old game", 2.50]]]]]

bill = []

stack = []

menu = 0

# menu states
# 0 menu
# 1 checkout
# 2 bill
# 3 add_product
# 4 exit
# 5 remove_item
# 6 clear_items

#@TODO comment
#@TODO implement constants for menu options
#@TODO dinamic menu display
#@TODO add the notion of quantity
#@TODO add the notion of category price
#@TODO classes
#@TODO add console GUI
#@TODO add gtk GUI

def valid_numeric_choice(x):
	try:
		int(x)
		return int(x) > -1
	except ValueError:
		return False

def wait_input(message = "Please choose one of the above: "):
	option = raw_input(message)

	if option == "00" 
		return "00"

	if not valid_numeric_choice(option):
		return False
	
	return int(option)

def remove_item():
	while True: 
		print "Delete items. Choose one of the following:"

		for index, element in enumerate(bill):
				print str(index+1) + ". " + element[1]
		
		print "0. cancel"

		option = wait_input()

		if (type(option) == bool and option==False) || len(bill) < option : 
				print "Invalid option. Try again"
				continue

		if option != 0:
			while True:
				print "You chose to delete "+ bill[option][1] +". Are you sure?"

				print "1. yes"
				print "2. no"

				option = wait_input()

				if (type(option) == bool and option==False) || option >2 || option = 0: 
						print "Invalid option. Try again"
						continue

				if option == 1:
					del bill[option]
					flag = "break"
					break
				if option == 2:
					flag = "continue"
					break

			if flag == "continue":
				continue
			if flag == "break": 
				break


	while True:
		print "What do you want to do next?"

		print "1. continue shopping where i left" #TODO check if stack empty
		print "2. go to main menu"
		print "3. exit"

		option = wait_input()

		if (type(option) == bool and option==False) || option >3 || option = 0: 
				print "Invalid option. Try again"
				continue

		if option == 1:
				global menu = 0
				return
		if option == 2:
				global stack = []
				global menu = 0
				return
		if option == 3:
				global menu = 4
				return


def clear_items():
	while True:
		print "You are about to clear all the items in your cart. Do you want to proceed?"

		print "1. yes"
		print "2. no"

		option = wait_input()

		if (type(option) == bool and option==False) || option >2 || option = 0: 
				print "Invalid option. Try again"
				continue

		if option == 1:
			global bill = []

	while True:
		print "What do you want to do next?"

		print "1. continue shopping where i left" #TODO check if stack empty
		print "2. go to main menu"
		print "3. exit"

		option = wait_input()

		if (type(option) == bool and option==False) || option >3 || option = 0: 
				print "Invalid option. Try again"
				continue

		if option == 1:
				global menu = 0
				return
		if option == 2:
				global stack = []
				global menu = 0
				return
		if option == 3:
				global menu = 4
				return

def checkout():
	while True: 
		print "You are about to checkout. Do you want to proceed?"

		print "1. yes"
		print "2. no"

		option = wait_input()

		if (type(option) == bool and option==False) || option >2 || option = 0: 
				print "Invalid option. Try again"
				continue

		if option == 1:
			global bill = []
	
	while True:
		print "What do you want to do next?"

		print "1. continue shopping where i left" #TODO check if stack empty
		print "2. go to main menu"
		print "3. exit"

		option = wait_input()

		if (type(option) == bool and option==False) || option >3 || option = 0: 
				print "Invalid option. Try again"
				continue

		if option == 1:
				global menu = 0
				return
		if option == 2:
				global stack = []
				global menu = 0
				return
		if option == 3:
				global menu = 4
				return

def exit():
	sys.exit()

def show_bill():
	while True: 
		print "Your bill contains:"

		sum = 0	

		for index, element in enumerate(bill):
			sum = element[2]
			print str(index+1) + ". " + element[1] + " ("+ str(element[2]) + ")"

		print "Total price:"+ str(sum)

		print "Choose one of the following:" 
		print "1. checkout"
		print "2. remove an item"
		print "3. clear items"
		print "4. continue shopping where i left" #TODO check if stack empty
		print "5. go to main menu"
		print "6. exit"

		option = wait_input()

		if (type(option) == bool and option==False) || option >6 || option = 0: 
			print "Invalid option. Try again"
			continue

		if option == 1:
			global menu = 1
			return
		if option == 2:
			global menu = 5
			return
		if option == 3:
			global menu = 6
			return
		if option == 4:
			global menu = 0
			return
		if option == 5:
			global stack = []
			global menu = 0
			return
		if option == 6:
			global menu = 4
			return


def add_item():
	current = resolve(stack)

	bill.append(current) 

	stack.pop()

	while True: 	
		print "You have bought: "+ current[1]
		print "Price: "+ str(current[2])
		print "Choose one of the following:"
		print "1. show bill"
		print "2. continue shopping where i left" #@TODO check if stack empty
		print "3. go to main menu"
		print "4. exit"

		option = wait_input("Please choose one of the above: ")

		if (type(option) == bool and option==False) || option > 4 || option = 0: 
			print "Invalid option. Try again"
			continue

		if option==1:
			global menu = 2
			return
		if option==2:
			global menu = 0
			return 
		if option==3:
			global stack = []
			global menu = 0
			return 
		if option==4:
			global menu =4
			return

def print_menu(elements):
	for index,element in enumerate(elements):
		if element[0]==0:
			print str(index+1)+". "+element[1]+" ("+ str(element[2]) + ")"
		else:
			print str(index+1)+". "+element[1]

def show_menu():
	current = resolve(stack)

	while True:
		if not stack:
			print "Main menu"
		else: 
			print "Current category: "+ current[1]

		print "Choose one of the following:"
		print_menu(current[2])
	
		if not stack:
			print "0. exit"
		else: 
			print "0. back"
		
		print "00. show bill"

		option = wait_input()

		if type(option) == bool and option==False: 
			print "Invalid option. Try again"
			continue

		if option == "00":
			menu = 2 
			return
		else 
			if option == 0: 
				if not stack:
					global menu = 4
				else:
					stack.pop()
					current = resolve(stack) # change current menu. no need to go back to the main loop
					continue
			else:
				if len(current) < option:
					print "Invalid option. Try again"
					continue
				else:
					stack.append(option)
		
					if current[2][option][0] == 1:
						current = reslove(stack) #change current menu. no need to go back to the main loop
						continue
					else:
						global menu =3
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
	if menu == 0:
		show_menu()
	elif menu == 1:
		checkout()
	elif menu == 2:
		show_bill()
	elif menu == 3:
		add_item()
	elif menu == 4:
		exit()
	elif menu == 5: 
		remove_item()
	elif menu == 6:
		clear_items()

