def valid_numeric_choice(x):
	try:
		int(x)
		return int(x) > -1
	except ValueError:
		return False


# menu states
CONST_MENU = 0
CONST_CHECKOUT = 1
CONST_SHOW_BILL = 2
CONST_ADD_ITEM = 3
CONST_EXIT = 4
CONST_REMOVE_ITEM = 5
CONST_CLEAR_ITEMS = 6
CONST_MAIN_MENU =7 