
def getNeedleLength(needle): 

	count = 0

	for x in needle:
		if x!="?":
			count++

	return count

def computeMatch(needle, haystack, needlePointer, haystackPointer):
	if needle[needlePointer] == haystack[haystackPointer]:
		return True

	if needlePointer < len(needle)-1 and needle[needlePointer+1] == "?":
		return True

	return False

def getOccurences(needle, haystack):
	occurences = []

	haystackPointer = 0
	haystackStartPointer = 0
	needlePointer = 0

	#we do not need to compute the length everytime
	haystackLength = len(haystack)
	needleLength = getNeedleLength(needle)

	#we calculate the last relevant position for comparison 
	while haystackPointer+haystackStartPointer < haystackLength - needleLength+1:

		if computeMatch(needle, haystack, needlePointer, haystackPointer+haystackStartPointer):
			if needlePointer < len(needle)-1 and needle[needlePointer+1] == "?":
				needlePointer +=3 #one for next char, one to skip ?, and increment ... not sure
			else:
				needlePointer +=1 
			haystackPointer +=1

			if needlePointer >= needleLength:
				occurences.append(str(haystackStartPointer))

				#restart from the next starting character
				needlePointer = 0
				haystackPointer = 0
				haystackStartPointer +=1
		else: 
			#false alarm, restart from the next starting character
			haystackStartPointer +=1 
			haystackPointer = 0 
			needlePointer = 0

	return occurences

haystack = "The incolor cat has a coloured hat."
needle = "colou?r"

print ", ".join(getOccurences(needle, haystack))