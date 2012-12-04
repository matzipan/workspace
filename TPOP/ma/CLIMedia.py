from util import *

class CLIMedia: #should be implemented as a interface... but python does not have such a thing.
	"""
		Media class that handles the command line interface. It handles the interaction between I/O and the Applcation class. 
	"""
	def __init__(self, input_handler, output_handler):
		"""
			Class to handle Media init. Injects dependencies for I/O. Takes parameter i/o class instances
		"""
		#bind input/output to media
		self.input = input_handler 
		self.output = output_handler 

		self.stack = []
		self.menu = 0 

	def bind_application(self,application):
		"""
			Dependency injection for the application class. Takes parameter application class instance.
		"""
		self.application = application

	def run(self):
		"""
			Handles the main application loop.
		"""

		try: 

			if not self.authenticate():
				self.terminate()
			
			self.output.separator()

			while True:
				menu = self.get_menu()

				if menu == CONST_MENU:
					self.show_menu(self.resolve_menu())
				elif menu == CONST_CHECKOUT:
					self.checkout()
				elif menu == CONST_SHOW_BILL:
					self.show_bill(self.application.get_bill())
				elif menu == CONST_ADD_ITEM:
					self.add_item(self.resolve_menu())
				elif menu == CONST_EXIT:
					self.terminate()
				elif menu == CONST_REMOVE_ITEM: 
					self.remove_item(self.application.get_bill())
				elif menu == CONST_CLEAR_ITEMS:
					self.clear_items()

				self.output.separator()
		except EnvironmentError:
			self.output.error("Something is wrong with the environment. Sorry.")

			raise RuntimeError()
		except StandardError:

			raise RuntimeError()

	def authenticate(self):
		"""
			Handles authentication. Returns true/false depending on authentication succeding.
		"""
		while True:
			self.output.authentication()
			username, password = self.input.authentication()

			if self.application.authenticate_user(username, password):
				return True
			else: 
				self.output.invalid_credentials()
				item = self.input.invalid_credentials()

				if item == 1:
					continue
				if item == 2
					return False


	def set_menu(self,menu):
		"""
			Handles setting menu for the next application loop iteration. Takes parameter menu choice.
		"""
		if menu == CONST_MAIN_MENU: 
			self.menu_stack_empty()
			menu = CONST_MENU

		self.menu = menu

	def get_menu(self):
		"""
			Get menu setting.
		"""
		return self.menu

	def menu_stack_back(self):
		"""
			Pops the last item from the menu stack.
		"""
		self.stack.pop()

	def menu_stack_add(self,index):
		"""
			Adds the menu index as the last menu stack item. Takes parameter menu index. 
		"""
		self.stack.append(index)

	def menu_stack_empty(self):
		"""
			Empty the menu stack. When you want to show the main menu.
		"""
		self.stack = []

	def resolve_menu(self):
		"""
			Helper class to resolve the menu stack to a particular menu item in the tree.
		"""
		options = self.application.get_data()

		if len(self.stack) > 0:
			working_stack = self.stack
			current = options

			while len(working_stack) >0:
				 	current = current["children"][working_stack[0]]
					working_stack= working_stack[1:]

			return current

		return options

	def remove_item(self,data):
		"""
			Media function to handle removing items. Takes parameter the bill items. 
		"""
		cart_item = self.choose_item("Remove", data)
		
		if cart_item != None:
			while True:
				self.output.confirm_remove_item(data[cart_item-1])
				item = self.input.confirm()

				if item == None:
					continue

				if item == True:
					self.application.remove_item(cart_item-1)
					break

				if item == False:
					break
		
		self.continue_flow()

	def continue_flow(self):
		"""
			Media function to handle flow continuation.
		"""
		while True:
			self.output.continue_flow()
			item = self.input.continue_flow()
			
			if item == None:
				continue 

			if item == 1:
				self.set_menu(CONST_MENU)
				break
			if item == 2: 
				self.set_menu(CONST_MAIN_MENU)
				break 
			if item == 3:
				self.set_menu(CONST_EXIT)
				break

	def choose_item(self, purpose, data):
		"""
			Media function to handle choosing an item index from a given set. Takes purpose parameter needed for outputting the choice. Takes data parameter with all the different item choices. Returns choice. Returns None for back choice.
		"""
		while True: 
			self.output.choose_item(purpose, data)
			item = self.input.choose_item(data)

			if item == None:
				continue
			if item == 0:
				return None
			return item
			
	def clear_items(self):
		"""
			Media function to handle clearing the items in the bill.
		"""
		while True:
			self.output.confirm_clear_items()
			item = self.input.confirm()

			if item == None:
				continue
			if item == True: 
				self.application.clear_items()
				break
			if item == False:
				break

		self.continue_flow()

	def checkout(self):
		"""
			Media function to handle checkout. 
		"""
		while True: 
			self.output.checkout()
			item = self.input.checkout()

			if item == 1:
				self.application.checkout()
				break
			if item == 2:
				break

		self.continue_flow() 

	def terminate(self):
		"""
			Media function to transmit terminate command.
		"""
		self.application.exit()

	def exit(self):
		"""
			Media function to exit media
		"""
		sys.exit() 

	def show_bill(self,data):
		"""
			Media function to handle showing the bill. Takes parameter the bill data.
		"""
		while True: 
			self.output.show_bill(data)
			item = self.input.show_bill()

			if item == None:
				continue

			if item == 1:
				self.set_menu(CONST_CHECKOUT)
				break
			if item == 2:
				self.set_menu(CONST_REMOVE_ITEM)
				break
			if item == 3:
				self.set_menu(CONST_CLEAR_ITEMS)
				break
			if item == 4:
				break

		if item == 4:
			self.continue_flow()


	def add_item(self,data):
		"""
			Media function to handle adding item to bill. Takes parameter the given item.
		"""
		self.application.add_item(data)

		self.menu_stack_back()

		while True:
			self.output.add_item(data)
			item = self.input.add_item()

			if item==None:
				continue
			if item == 1:
				self.set_menu(CONST_SHOW_BILL)
				break
			if item == 2: 
				break

		if item==2: 
			self.continue_flow()		

	def show_menu(self,data):
		"""
			Media function to handle showing menu. Takes parameter current menu subtree.
		"""
		while True:
			self.output.show_menu(data)
			item = self.input.show_menu(data)

			if item==None:
				continue

			if item == False:
				self.output.no_stock()
				continue

			if item==0:
				if data["name"] == "main":
					self.set_menu(CONST_EXIT)
				else:
					self.menu_stack_back()
				break
			elif item==-1: 
				self.set_menu(CONST_SHOW_BILL)
				break
			else: 
				self.menu_stack_add(item-1)

				if data["children"][item-1]["type"]==1:
					self.set_menu(CONST_MENU)
				else:
					self.set_menu(CONST_ADD_ITEM)
				break		