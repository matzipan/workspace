stuff = str(raw_input()).lower()

x=stuff.split()

for id, value in enumerate(x):
	x[id] = value.title()

stuff = " ".join(x)

print stuff


