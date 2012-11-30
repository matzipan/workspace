class MemoryDataRepository:
	def __init__(self):
		self.data = {
					"type": 1,
					"name": "main",
					"children": [
							{
							"type": 1,
							"name": "movie",
							"children": [
									{
										"type":0,
										"name": "DVD movie",
										"price": 2.5
									},
									{
										"type":0,
										"name": "BluRay movie",
										"price": 3.5
									}
								]
							}	
						,
							{
							"type": 1,
							"name": "game",
							"children": [
									{
										"type":0,
										"name": "new game",
										"price": 4
									},
									{
										"type":0,
										"name": "old game",
										"price": 2.5
									}
								]
							}
						]
					}

	def get_data(self):
		return self.data

	def add(self):
		#@TODO