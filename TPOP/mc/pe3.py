import math

def fermat(N):
    a = int(math.ceil(math.sqrt(N)))

    bs = math.sqrt(a*a - N)

    while not int(bs) == int(math.floor(bs)):
        a = a+1
        bs = math.sqrt(a*a - N)

    b = int(math.ceil(bs))
    
    return a - b

div = []
queue = []

number = int(raw_input())

if number % 2 == 0:
    div.append(2)
    while number %2 == 0:
        div.append(2)
        number = number/2

n = fermat(number)

if not n==1:
    #n is a divisor, so it can be both 1... n,
    # but since fermat returns a-b, it can never have the value n,
    # so we only compare it to n
    queue.append(n)
    queue.append(number/n)
    
while queue: #@TODO
    print(queue)
    n= fermat(queue.pop(0))

    if n==1: #it is a prime number
        print "x"
        #while number %n == 0:
        #   number /= 2
    else:
        div.append(n)
        queue.append(n)
        queue.append(number/n)

print div