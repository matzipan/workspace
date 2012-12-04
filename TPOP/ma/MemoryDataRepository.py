class MemoryDataRepository:
	def __init__(self):
		self.data = {
					"type": 1,
					"name": "main",
					"id": "main-1",
					"children": [
							{
							"type": 1,
							"name": "movie",
							"id": "movie-1",
							"children": [
									{
										"type":0,
										"name": "DVD movie",
										"id": "movie-dvd-1",
										"quantity": 10,
										"price": 2.5
									},
									{
										"type":0,
										"name": "BluRay movie",
										"id": "movie-bluray-1",
										"quantity": 2,
										"price": 3.5
									}
								]
							}	
						,
							{
							"type": 1,
							"name": "game",
							"id": "game-1",
							"children": [
									{
										"type":0,
										"name": "new game",
										"id": "game-new-1",
										"quantity": 1,
										"price": 4
									},
									{
										"type":0,
										"name": "old game",
										"id": "game-old-1",
										"quantity", 2,
										"price": 2.5
									}
								]
							}
						]
					}
		self.borrowed_by_user = {}

	def get_data(self):
		return self.data

	def get_rent_items(self, user_id):
		"""
			Get items rent by user
		"""
		
		return map(self.borrowed_by_user[user_id], lambda x: return self.lookup(x))

	def lookup(self, lookup_id, data=None):
		"""
			Lookup the element with a given id
		"""
		if data==None:
			data = self.data

		if self.data["id"] == lookup_id:
			return self.data
		else:
			lookup_fun = lambda x: if x["id"] == lookup_id: return x elif x["type"] == 1: return map(lookup_fun, x["children"])[0]

			return map(lookup_fun, self.data)[0]

	def add(self, parent, id_x, name, type_id, price= None):
		"""
			Append an element to a parent with a given id
		"""
		parent_element = self.lookup(parent)

		if parent_element["type"] == 0:
			raise new ValueError()

		element = {"type": type_id, "name": name, "id": id_x}

		if type_id == 1: 
			element["children"] = []
		else: 
			element["price"] = price

		parent_element["children"].append(element)

	def borrow_item(self, user_id, borrow_id):
		"""
			Mark item as borrowed by user_id
		"""

		if not user_id in self.borrowed_by_user:
			self.borrowed_by_user[user_id] = []

		t=1
		for i,x in enumerate(self.borrowed_by_user):
			if x["id"]==borrow_id: 
				self.borrowed_by_user[i]["quantity"] +=1
				t=0
				break

		if t==1: 
			self.borrowed_by_user[user_id].append({"id": borrow_id, "quantity": 1})

		element = self.lookup(borrow_id)

		element.quantity -= 1

	def return_item(self,user_id, borrow_id):
		"""
			Return item by user_id
		"""

		element = self.lookup(borrow_id)

		element.quantity += 1

		for i,x in enumerate(self.borrowed_by_user):
			if x["id"]==borrow_id:
				if x["quantity"] == 1
					del self.borrowed_by_user[i]
				else:
					self.borrowed_by_user -= 1

				break