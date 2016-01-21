import math

class Cell:
	up = 0
	down = 0
	left = 0
	right = 0
	visited =0

	def __str__(self):
		return str(self.up)+" "+str(self.right)+" "+ str(self.down)+ " "+ str(self.left)


def generate(filedump):
	x = filedump

	n = int(round(math.sqrt(len(x))))

	m = []
	m.append([])

	i =0
	j =0 

	for row in x:
		row = str.split(row, " ")

		sell = Cell()

		sell.up = int(row[0])
		sell.right = int(row[1])
		sell.down = int(row[2])
		sell.left = int(row[3])

		if row[4] == 1:
			startx = i
			starty =j

		if row[4] == 2:
			enbx = i
			endy =j


		m[i].append(sell)

		j+=1

		if n-1 == j:
			j=0
			i+=1
			m.append([])

	return (m, startx, starty, endx, endy)

def solve(m,x,y,endx,endy,solution, partial):
	if x==endx and y==endy and len(partial) < len(solution): # todo
		solution=partial

	#todo

	solve(m, x+1, y, endx,endy,solution)
	solve(m, x, y+1, endx,endy,solution)
	solve(m, x-1, y, endx,endy,solution)
	solve(m, x, y-1, endx,endy,solution)



f = open('maze.def', 'r')

m, startx,starty, endx,endy = generate(f.readlines())

solution = solve(m, startx,starty,endx,endy, solution)

#draw turtle stuff