import math

def load_cache():
	try:
		cache_string = open('m4.cache', 'r').read()
	except IOError as e:
		return {} 

	cache_aux = cache_string.split(" ")

	i = 0

	l = len(cache_aux)

	cache = {}

	while i< l:
		cache[cache_aux[i]] = cache_aux[i+1]

		i+=2

	return cache

def is_prime(x, cache={}):	
	prime =True

	assert x!= 0 or x !=1

	if str(x) in cache:
		print "Hitting cache"
		prime = cache[str(x)]
	else:
		for i in range(2,int(math.sqrt(x))):
			if x%i == 0:
				prime=False
				break

		cache[str(x)] = prime

	return prime		

def save_cache(cache):
	cache_str = []

	for index, value in enumerate(cache):
		cache_str.append(str(value) + " " + str(index))

	cache_file = open('m4.cache', 'w')

	cache_file.write(" ".join(cache_str))



print "Loading cache..."
cache = load_cache()
print "Cache loaded"

x = int(raw_input())

if x==0 or x==1:
	print "You cannot check 0,1"
else:
	if is_prime(x,cache): 
		print x, "is prime"
	else:
		print x, "is not prime"
 
	print "Saving cache..."
	save_cache(cache)
	print "Cache saved"