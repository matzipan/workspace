

function getOccurences(needle, haystack):
	occurences = []

	haystackPointer = 0
	needlePointer = 0

	#we do not need to compute the length everytime
	haystackLength = len(haystack)
	needleLength = len(needle)

	#we calculate the last relevant position for comparison 
	while haystackPointer+needlePointer < haystackLength - needleLength+1:

		if haystack[haystackPointer+needlePointer] == needle[needlePointer]:
			needlePointer +=1 

			if needlePointer == needleLength:
				occurences.append(str(haystackPointer))

				#restart from the next starting character
				needlePointer=0
				haystackPointer +=1
		else: 
			#false alarm, restart from the next starting character
			haystackPointer +=1 
			needlePointer = 0

	return occurences

haystack = "The cat has a hat."
needle = "at"

print ", ".join(getOccurences(needle, haystac))