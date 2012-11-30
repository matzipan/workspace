class MemoryUserRepository:
	def __init__(self):
		self.data = {"andrei":{"id": 0, "password": "haha!"}]

	def authenticate_user(self,username,password):
		"""
			Check if user/password is correct
		"""

		if username in self.data and self.data[username]["password"] ==  password:
			return self.data[username]["id"]

		return False

	def add(self):
		#@TODO