from scipy import *             #scipy functions are in global namespace
from scipy import linalg        #linear algebra functions under linalg.
import matplotlib.pyplot as plt #plot functions in plt namespace
from math import *
"""
Practical 2
Use power series to evaluate functions
LU Decomposition and solving systems of linear equations
 
author Richard Wilson
version 1
"""

def mysin(x,n):
    """
    Compute n terms  bof the power series for sin(x)
    The math.factorial(x) function is defined in scipy
    mysin(double,int)->double
    """
    y=float(x)
    sign = -1;
    term = 3
    #-------------------#
    # Compute n terms of the power series for sin(x)
    #  and store the result in y
    while n>1:
        
        
        y+=float((x**term)*sign)/float(factorial(term))

        sign *= -1
        term += 2
        n-=1
    
    #-------------------#
    return y


def partA():
    # Complete the function mysin and then run this function
    
    # Generate sin data for the comparison
    n=20
    X=[ 2*i*pi/(n-1) for i in range(n) ]
    TrueY=[ sin(X[i]) for i in range(n) ]

    # We use the function mysin to see the effect of changing the number of terms in the expansion
    Y=[ mysin(X[i],1) for i in range(n) ]
    plt.subplot(221)
    plt.plot(X,Y,'r',X,TrueY,'b--')
    plt.title('Series n=1')
    
    Y=[ mysin(X[i],2) for i in range(n) ]
    plt.subplot(222)
    plt.plot(X,Y,'r',X,TrueY,'b--')
    plt.title('Series n=2')
    
    Y=[ mysin(X[i],5) for i in range(n) ]
    plt.subplot(223)
    plt.plot(X,Y,'r',X,TrueY,'b--')
    plt.title('Series n=5')
    
    Y=[ mysin(X[i],9) for i in range(n) ]
    plt.subplot(224)
    plt.plot(X,Y,'r',X,TrueY,'b--')
    plt.title('Series n=9')

    plt.show()


################################################

def myerf(x,n):
    """
    Compute n terms of the power series for erf(x)
    The math.factorial(x) function is defined in scipy
    erf(double,int)->double
    """
    y=0.0
    #-------------------#
    # Compute n terms of the power series for erf(x)
    #  and store the result in y

    
    #-------------------#
    return y



def partB():
    # Complete the function myerf and then run this function
    
    # Generate erf data for the comparison
    n=20
    X=[ 6.0*i/(n-1)-3 for i in range(n) ]
    TrueY=[ math.erf(X[i]) for i in range(n) ]

    # We use the function myerf to see the effect of changing the number of terms in the expansion
    Y=[ myerf(X[i],4) for i in range(n) ]
    plt.subplot(221)
    plt.plot(X,Y,'r',X,TrueY,'b--')
    plt.title('Series n=4')
    
    Y=[ myerf(X[i],10) for i in range(n) ]
    plt.subplot(222)
    plt.plot(X,Y,'r',X,TrueY,'b--')
    plt.title('Series n=10')
    
    Y=[ myerf(X[i],16) for i in range(n) ]
    plt.subplot(223)
    plt.plot(X,Y,'r',X,TrueY,'b--')
    plt.title('Series n=16')
    
    Y=[ myerf(X[i],25) for i in range(n) ]
    plt.subplot(224)
    plt.plot(X,Y,'r',X,TrueY,'b--')
    plt.title('Series n=25')

    plt.show()

################################################

def LUDecomposition(A):
    """
    Compute the LU decomposition of matrix A
    Should return the lower and upper triangular matrices
    and the intermediate matrix M
    LUDecomposition(matrix)->matrix L,matrix U,matrix M
    """
    n=alen(A)
    U=A.copy()
    M=matrix(identity(n))
    #-------------------#
    # Find the L and U matrices via a sequence of matrix multiplications
    # U contains the LHS matrix and M the RHS matrix.
    # At the end, L will be the inverse of M
    
    #-------------------#
    return M.I,U,M

def backSubstitution(U,c):
    """
    Solve the equation Ux=c where x and c are vectors and U is an
    upper-triangular matrix
    backSubstitution(matrix,matrix)->matrix
    """
    n=alen(U)
    x=matrix(zeros((n,1)))
    #-------------------#
    # Solve the equation using back substitution
    # x will hold the sequence of results

    
    #-------------------#
    return x

def partC():
    # Complete the functions LUDecomposition and backSubstitution then run partC

    A=matrix('[1 2 -3;2 -1 -1;3 2 1]')
    c=matrix('[3;11;-5]')

    # Decompose
    L,U,M=LUDecomposition(A)

    # Display
    print 'A='
    print A
    print 'L,U='
    print L
    print U
    print 'LU='
    print L*U

    # Solve
    cp=M*c
    x=backSubstitution(U,cp)
    print 'Solution=',x

    # Scipy solution for comparison
    print 'SciPy solution is ',linalg.solve(A,c)

    
    

################################################

partA()
