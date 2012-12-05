
class CLIOutput:
	"""
		Class to handle command line interface input
	"""
	def print_menu(self, data): 
		"""
			Output helper function that handles item menu printing. Takes data parameter.
		"""
		for index,element in enumerate(data):
			if element["type"]==0:
				print str(index+1)+". "+element["name"]+" (price: "+ str(element["price"]) + ", qty: "+ str(element["quantity"])+")" 
			else:
				print str(index+1)+". "+element["name"]

	def continue_flow(self, stack, logout): 
		"""
			Output the option for flow continuation
		"""
		print "What do you want to do next?"

		if stack:
			print "1. continue shopping where i left"
			print "2. go to main menu"
			print "3. exit"
			if not logout: 
				print "4. logout"
		else:
			print "1. go to main menu"
			print "2. exit"
			if not logout: 
				print "3. logout"


	def choose_item(self, purpose, data):
		"""
			Output item choice. Takes purpose parameter which is used to determine the purpose of choosing the items. Takes data parameter.
		"""
		print purpose.title()+" items. Choose one of the following:"

		for index, element in enumerate(data): 
			print str(index+1) + ". " + element["name"]
		
		print "0. cancel"

	def confirm(self, message):
		"""
			Generic confirmation output helper
		"""
		print message

		print "1. yes"
		print "2. no"

	def confirm_remove_item(self, data):
		"""
			Output for confirmation of item removal.
		"""
		self.confirm("You chose to delete "+ data["name"] +". Do you want to proceed?")


	def confirm_clear_items(self): 
		"""
			Output for confirmation of item clearing.
		"""
		self.confirm("You are about to clear all the items in your cart. Do you want to proceed?")

	def checkout(self):
		"""
			Output for checkout confirmation.
		"""
		self.confirm("You are about to checkout. Do you want to proceed?")

	def confirm_logout(self):
		"""
			Handles output for  logout
		"""
		self.confirm("You are going to be logged out. Do you want to proceed?")

	def confirm_return_item(self):
		"""
			Output for confirmation of item return.
		"""
		self.confirm("You chose to return "+ data["name"] +". Do you want to proceed?")

	def show_bill(self, data):
		"""
			Output for showing the bill and the menu items.
		"""

		if not data:
			print "You have no items on your bill"

			print "Choose one of the following:" 

			print "1. back"
		else:
			sum = 0	

			for index, element in enumerate(data):
				sum = element["price"]
				print str(index+1) + ". " + element["name"] + " (price: "+ str(element["price"]) + ")"

			print "Total price:"+ str(sum)

			print "Choose one of the following:" 
			print "1. checkout"
			print "2. remove an item"
			print "3. clear items"
			print "4. back"

	def add_item(self, data):
		"""
			Output for adding an item and menu items.
		"""
		print "You have bought: "+ data["name"]
		print "Price: "+ str(data["price"])
		print "Choose one of the following:"
		print "1. show bill"
		print "2. back"
	
	def show_menu(self,data):
		"""
			Output for showing menu.
		"""
		if data["name"]=="main":
			print "Main menu"
		else: 
			print "Current category: "+ data["name"]

		print "Choose one of the following:"
		self.print_menu(data["children"])
	
		if data["name"]=="main":
			print "0. exit"
		else: 
			print "0. back"
		
		print "00. show bill"
		print "01. logout"


	def separator(self):
		print "------------------"

	def authentication(self):
		"""
			Output function to handle authentication
		"""

		print "This part requires authentication. Please insert your credentials below."

	def invalid_credentials(self):
		"""
			Output function to handle invalid credentials
		"""
		print "The credentials you entered are invalid. "
		print "Choose one of the following:"
		print "1. retry"
		print "2. exit"

	def no_stock(self):
		""" 
			Handle no stock message
		"""

		print "The item you are looking for is not on stock. "

	def no_stock(self):
		""" 
			Handle no stock message
		"""

		print "The item you are looking for is not on stock. "

	def insufficient_stock(self):
		"""
			Handle insufficient stock message
		"""
		print "You cannot add another item of that type. Insufficient stock."