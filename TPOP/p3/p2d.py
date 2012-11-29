
def getNeedleLength(needle): 

	count = 0

	for x in needle:
		if x != "*" AND x!="?" AND x!= "+":
			count++

	return count

# * zero o more
# + one or more
# ? zero or one

def getOccurences(needle, haystack):
	occurences = []

	haystackPointer = 0
	haystackStartPointer = 0
	needlePointer = 0

	#we do not need to compute the length everytime
	haystackLength = len(haystack)
	needleLength = getNeedleLength(needle)
	actualNeedleLength = len(needle)

	#we calculate the last relevant position for comparison 
	while haystackPointer+haystackStartPointer < haystackLength - needleLength+1:
		if needlePointer +1 < actualNeedleLength and needle[needlePointer] == "*":
			while needle[needlePointer] == haystack[haystackStartPointer+ haystackPointer]:
				haystackPointer += 1

			needlePointer += 2

			if needlePointer == needleLength:
				occurences.append(str(haystackPointer))

				#restart from the next starting character
				needlePointer = 0
				haystackStartPointer = 0
				haystackPointer +=1

		elif needlePointer +1 < actualNeedleLength and needle[needlePointer] == "?":
			haystackPointer += 1
			needlePointer += 2

			if needlePointer == needleLength:
				occurences.append(str(haystackPointer))

				#restart from the next starting character
				needlePointer = 0
				haystackStartPointer = 0
				haystackPointer +=1

		elif needlePointer +1 < actualNeedleLength and needle[needlePointer] == "+":
			if needle[needlePointer] != haystack[haystackStartPointer+ haystackPointer]:
				haystackPointer = 0
				needlePointer = 0
				haystackStartPointer += 1

			while needle[needlePointer] == haystack[haystackStartPointer+ haystackPointer]:
				haystackPointer += 1

			needlePointer += 2

			if needlePointer == needleLength:
				occurences.append(str(haystackPointer))

				#restart from the next starting character
				needlePointer = 0
				haystackStartPointer = 0
				haystackPointer +=1

		else: 
			if needle[needlePointer] == haystack[haystackStartPointer+ haystackPointer]:
				haystackPointer += 1
				needlePointer += 1

				if needlePointer == needleLength:
					occurences.append(str(haystackPointer))

					#restart from the next starting character
					needlePointer = 0
					haystackStartPointer = 0
					haystackPointer +=1
					
			else: 
				haystackPointer = 0
				needlePointer = 0
				haystackStartPointer += 1


	return occurences

haystack = "The incolor cat has a coloured hat."
needle = "co*l+ou?r"

print ", ".join(getOccurences(needle, haystack))