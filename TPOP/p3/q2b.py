string = "Dammit, I'm mad!"
#string = "Damm, I'm mad!" #not palindrome

i=0
j=len(string)-1

def alpha(character):
	x= ord(character)
	
	if x > ord('z') or x < ord('A') or (x > ord('Z') and x < ord('a')):
		return False
	return True

while i<j:
	while not alpha(string[i]):
		i+=1

	while not alpha(string[j]):
		j-=1

	if(string[i].lower()!=string[j].lower()):
		print "Not palindrome"
		break
	i+=1
	j-=1

if i>j: 
	print "Palindrome"

