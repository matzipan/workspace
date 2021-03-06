from util import *

class CLIInput:
	"""
		Class to handle command line interface input
	"""

	def numeric_input(self, message = "Please choose one of the above: "): 
		"""
			Helper class to handle input. Optional parameter the message to display. Returns choice. Returns 00 if 00 entered. Returns None on invalid input. 
		"""
		option = raw_input(message)

		if option == "00": 
			return "00"

		if option == "01":
			return "01"

		if not valid_numeric_choice(option):
			return None
		
		return int(option)

	def string_input(self, message):
		"""
			Helper class to handle string input. Requires parameter for the message to display. Returns input.
		"""

		return raw_input(message)

	def choose_item(self,data):
		"""
			Input class to take input and validate choosing an item. Takes paramter the options you can choose from. Returns choice. Returns None on invalid input.
		"""
		option = self.numeric_input()

		if (type(option) == bool and option==False) or len(data) < option:
			return None

		return option

	def continue_flow(self, stack, logout):
		"""
			Input class to handle flow continuation. Returns choice. Returns None on invalid input.
		"""
		option = self.numeric_input()



		if not stack:
			if option in [1,2]:
				return option
			if not logout: 
				return 3
		else: 
			if option in [1,2,3]:
				return option
			if not logout and option ==4:
				return 4

		return None

	def confirm(self):
		"""
			Input class to handle confirmation. Returns True/False. Returns None on invalid input.
		"""
		option = self.numeric_input()

		if option == 1:
			return True
		if option == 2:
			return False

		return None


	def checkout(self):
		"""
			Input class to handle checkout option handling. Returns choice. Returns None on invalid input.
		"""
		option = self.numeric_input()

		if option in [1,2]:
			return option

		return None

	def show_bill(self, data):
		"""
			Input class to handle show_bill option handling. Returns choice. Returns None on invalid input.
		"""
		option = self.numeric_input()

		if not data:
			if option == 1:
				return option
		else:
			if option in [1,2,3,4]:
				return option
			
		return None

	def add_item(self):
		"""
			Input class to handle add_item option handling. Returns choice. Returns None on invalid input.
		"""
		option = self.numeric_input("Please choose one of the above: ")

		if option in [1,2]: 
			return option

		return None

	def show_menu(self, data):
		"""
			Input class to handle menu input. Takes parameter the available menu choices. Returns choice. Returns -1 for choice 00. Returns None on invalid input.
		"""
		option = self.numeric_input()

		if type(option) == bool and option==False: #I am doing this because i'm not sure of time coercion in python
			return None

		if option == "00":
			return -1

		if option == "01":
			return -2

		if option == 0:
			return 0
		if option <= len(data):
			return option

		return None

	def authentication(self):
		"""
			Input function to handle authentication
		"""
		
		username = self.string_input("Username:")
		password = self.string_input("Password:") 

		return username, password

	def invalid_credentials(self):
		""" 
			Input funciton to handle invalid credentials
		"""

		option = self.numeric_input("Please choose one of the above:")

		if option in [1,2]:
			return option

		return None
