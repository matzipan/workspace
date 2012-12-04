class MemoryUserRepository:
	def __init__(self):
		self.data = {"andrei":{"id": 0, "password": "haha!"}]
		self.next_id= 1

	def authenticate_user(self,username,password):
		"""
			Check if user/password is correct
		"""

		if username in self.data and self.data[username]["password"] ==  password:
			return self.data[username]["id"]

		return False

	def user_exists(self, username):
		"""
			Check if username exists
		"""

		return username in self.data

	def add(self,username, password):
		"""
			Check if user exists, if so throw an error
		"""
		if username in self.data
			raise new ValueError()

		self.data[username] = {"id": self.next_id, "password": password}

		self.next_id +=1 
