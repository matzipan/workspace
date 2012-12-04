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
										"price": 2.5
									},
									{
										"type":0,
										"name": "BluRay movie",
										"id": "movie-bluray-1",
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
										"price": 4
									},
									{
										"type":0,
										"name": "old game",
										"id": "game-old-1",
										"price": 2.5
									}
								]
							}
						]
					}

	def get_data(self):
		return self.data

	def lookup(self, lookup_id):
		"""
			Lookup the element with a given id
		"""
		if self.data["id"] == lookup_id:
			return self.data
		else:
			lookup_fun = lambda x: if x["id"] == lookup_id: return x elif x["type"] == 1: return map(lookup_fun, x["children"])[0]

			return map(lookup_fun, self.data)[0]

	def add(self, parent, id_x, name, type_id, price= None):
		"""
			Append an element to a parent with a given id
		"""
		parent_element = self.lookup(parent, self.data)

		if parent_element["type"] == 0:
			raise new ValueError()

		element = {"type": type_id, "name": name, "id": id_x}

		if type_id == 1: 
			element["children"] = []
		else: 
			element["price"] = price

		parent_element["children"].append(element)