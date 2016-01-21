

elements = [[1],[1,2],[3,4,5]]

for i in range(1, len(elements)+1):

	for j in range(0, len(elements[i])):
		if(element[i][j]> element[i][j+1]):
			maximum = element[i][j]
		else: 
			maximum = element[i][j+1]


