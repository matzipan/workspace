class MemoryBillRepository():
	def __init__ (self):
		self.data = []

	def get_data(self):
		"""
			Append item to bill. Takes parameter item data.
		"""
		return self.data

	def add(self, item):
		self.data.append()


	def remove(self, index): 
		"""
			Removes a given index item from bill. Takes parameter index.
		"""		
		del self.bill[index]

	def clear(self):
		"""
			Clear items from bill.
		"""
		self.bill = []

	def exit(self):
		"""
			Handles graceful exit. Close db connection
		"""
		return 