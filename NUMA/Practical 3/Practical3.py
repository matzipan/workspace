from scipy import *             #scipy functions are in global namespace
from scipy import linalg        #linear algebra functions under linalg.
import matplotlib.pyplot as plt #plot functions in plt namespace
from mpl_toolkits.mplot3d import Axes3D  # 3D plot
from math import *

"""
Practical 3
Fixed-point iteration and non-linear optimisation

author Richard Wilson
version 1
"""

#################################################

def partA():
    """
    Find the golden ratio using fixed-point iteration
    """

    X=[]
    Y=[]

    phi=0.0
    gphi=1.0

    while abs(gphi-phi)>0.00001:
        phi=gphi

        #-------------------#
        # Compute the fixed-point function g(phi)

        gphi = 1+1/phi
        #-------------------#

        # Here we collect the points of the iteration for a plot
        X.append(phi)
        Y.append(gphi)
        X.append(gphi)
        Y.append(gphi)

    print "Golden ratio=",phi

    plt.plot(X,Y,color="red", linewidth=2.5, linestyle="-", label="iteration")
    plt.plot([0,3],[0,3],color="blue", linewidth=1, linestyle="--", label="X=Y")
    plt.legend(loc='upper left')
    plt.show()

#################################################

def partB(a,b,theta,startpoint):
    """
    Solve the ladder around the corner problem in lecture 9
    for any two corridor widths a,b and joining angle theta
    """
    
    X=[]
    Y=[]

    n=0
    alpha=0.0
    falpha=startpoint

    # Main loop: take steps towards the minimum
    # Finish when one of the following conditions is true
    #       The change in alpha is very small
    #       Completed more than 100 steps
    #       Outside sensible range for alpha
    while abs(falpha-alpha)>0.00001 and n<100 and falpha>0.2 and falpha<3.0:
        
        # alpha holds the current angle
        # falpha will be the next angle
        alpha=falpha
        beta=pi-theta-alpha

        #-------------------#
        # compute the value of falpha (the next angle)
        # beta is also calculated above for convenience

        # f is the gradient of the objective function
        f= (-1)*a*(sin(alpha)**(-2))*cos(alpha)+(-1)*b*((sin(pi-theta-alpha))**(-2))*cos(pi-theta-alpha)*(-1)

        # fprime is the second-order derrivate for use in Newton's method
        # Uncomment below when you implement this part
        fprime= 


        # update rule

        #falpha= falpha-f             # naive gradient descent
        #falpha= falpha-0.1*f           # scaled gradient descent
        falpha=             # Newton's method

        #-------------------#
        
        # In our plot, we will show alpha vs the function we are optimising

        X.append(alpha)
        Y.append(a/sin(alpha)+b/sin(beta))
        n+=1

    print 'Optimal angle=',alpha
    print 'Optimal length=',a/sin(alpha)+b/sin(pi-theta-alpha)
    print 'Found in ',n,' steps'

    # plot the optimisation steps
    plt.plot(X,Y,color="red", linewidth=2.5, linestyle="-", label="iteration")


    # plot the objective function
    X=[i*(1.5)/100+0.2 for i in range(100)]
    Y=[a/sin(x)+b/sin(pi-theta-x) for x in X]
    plt.plot(X,Y,color="blue", linewidth=1.0, linestyle="--", label="iteration")
    plt.axis([0.8,1.0,6.0,7])

    plt.show()

#################################################

def objective(x):
    """
    Return the value of the objective function for partC
    Input is a 2x1 matrix containing x and y
    """
    xp=x[0,0]
    yp=x[1,0]
    #-------------------#
    # return the value of the objective function
    
    #-------------------#

def grad(x):
    """
    Return the gradient of the objective function for partC
    Input is a 2x1 matrix containing x and y
    Return value is a 2x1 matrix
    """
    xp=x[0,0]
    yp=x[1,0]
    g=matrix('0;0','double')
    
    #-------------------#
    # Compute the gradient in g

    
    #-------------------#
    return g

def hessian(x):
    """
    Return the hessian of the objective function for partC
    Input is a 2x1 matrix containing x and y
    Return value is a 2x2 matrix
    """
    xp=x[0,0]
    yp=x[1,0]
    H=matrix('0 0;0 0','double')
        
    #-------------------#
    # Compute the Hessian in H
    
    #-------------------#
    return H

def partC(x):
    """
    Optimise a function of two variables and show the nature of the optimum
    Input is a 2x1 matrix which is the starting point for the optimisation
    """

    # Lists for recording the points we visit
    XC=[]
    YC=[]
    ZC=[]
    
    # Find the initial value
    g=grad(x)

    while (g[0,0]*g[0,0]+g[1,0]*g[1,0]>0.001):
        XC.append(x[0,0])
        YC.append(x[1,0])
        ZC.append(objective(x))
        #-------------------#
        # Compute the Newton update of x
        # x is the current position
        # g should be the gradient
        # H should be the Hessian 




        #-------------------#

    print 'Maximum=(',x[0][0],',',x[1][0],')'
    print 'Hessian=',H

    #-------------------#
    # Use the Hessian to find the nature of the
    #  stationary point

    
    #-------------------#

    # Generate some data to plot the fitted line
    grid=[3*x/20.0 for x in range(20)]
    FX,FY=meshgrid(grid,grid)
    FZ=zeros(FX.shape,'double')
    for index,x in ndenumerate(FX):
        y=matrix([[FX[index]],[FY[index]]])
        FZ[index]=objective(y)

    fig = plt.figure()
    ax = fig.gca(projection='3d')
    ax.plot(XC,YC,ZC,c='r',label='Newton iterations')

    ax.plot_wireframe(FX,FY,FZ)
    plt.show()
    
#################################################


partB(2.0,3.0,1.2,0.5)
