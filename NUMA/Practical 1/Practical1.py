from scipy import *             #scipy functions are in global namespace
from scipy import linalg        #linear algebra functions under linalg.
import matplotlib.pyplot as plt #plot functions in plt namespace
from mpl_toolkits.mplot3d import Axes3D  # 3D plot

"""
Practical 1
Use the idea of least-squares fitting to fit functions to data
 
author Richard Wilson
version 1
"""
      
def simpleLeastSquares(X,Y):
    """
    Compute the least-squares fit of y=ax+b
    Input: X is a list of sample x values, Y is a list of the
        corresponding Y values
    Output: A 2x1 matrix [a; b]
    """
    # Complete this function

    A=matrix('0 0;0 0','double')
    c=matrix('0;0','double')
    #-------------------#
    # Calculate the values of matrices A and c
    # and return the value of p
    Sxx=0
    Syy=0
    Sxy=0
    Sx=0
    Sy=0

    for i in range(0,len(X)):
        Sxx+= X[i]*X[i]
        Syy += Y[i]*Y[i]
        Sxy += X[i]*Y[i]
        Sx += X[i]
        Sy += Y[i]
    
    A=matrix([[Sxx, Sx],[Sx, len(X)]])
    c=matrix([[Sxy],[Sy]])

    R = A.I*c

    return R
    
    #-------------------#


def partA():
    # Complete the function simpleLeastSquares and then run partA() to see the results
    
    # A test dataset
    X=[ 1,2,3,4,5 ]
    Y=[ 1.1,2.25,2.89,4.1,5.3 ]

    # Fit the data using least squares
    p=simpleLeastSquares(X,Y)

    # Generate some data to plot the fitted line
    FittedX=[ 0,3,6 ]
    FittedY=[ p[0,0]*x+p[1,0] for x in FittedX ]

    plt.scatter(X,Y,100,'r','+')
    plt.plot(FittedX,FittedY,'b--')
    plt.title('Straight line fit')

    plt.show()


################################################

def threeDLeastSquares(X,Z):
    """
    Compute the least-squares fit of y=a*x1+b*x2+c
    Input: X is a matrix containing sample x1 and x2 values as
        pairs; the first column is x1, the second x2. Y is a list of the
        corresponding Y values
    Output: A 3x1 matrix [a; b; c]
    """
    # Complete this function

    A=matrix(zeros((3,3),'double'))
    c=matrix('0;0;0','double')
    #-------------------#
    # Calculate the matrix A and vector c
    #  and return the value of p
    # You will need to work out the correct formulas
    # We store everything as a matrix for consistency
    

    #-------------------#

def partB():
    # Complete the function threeDLeastSquares and then run partB() to see the results
    
    # A test dataset
    X=mat('1 1; 2 2; 3 1; 1 3; 3 3; 4 2; 2 4','double')
    Y=[ 0.5, 3, 4, 4.5, 5.5, 6, 7 ]

    # Fit the data using least squares
    p=threeDLeastSquares(X,Y)

    # Generate some data to plot the fitted line
    FX,FY=meshgrid([0,1,2,3,4,5],[0,1,2,3,4,5]);
    FZ=zeros((6,6),'double')
    for index,x in ndenumerate(FX):
        FZ[index]=p[0,0]*FX[index]+p[1,0]*FY[index]+p[2,0]

    fig = plt.figure()
    ax = fig.gca(projection='3d')
    ax.scatter(X[:,0],X[:,1],Y,c='r')

    ax.plot_wireframe(FX,FY,FZ)

    plt.show()


################################################

def complexLeastSquares(X,Y):
    """
    Compute the least-squares fit of y=a*x**2+b*x+c
    Input: X is a list of sample x values, Y is a list of the
        corresponding Y values
    Output: A 3x1 matrix [a; b; c]
    """
    # Complete this function
    # You will need to calculate the correct formulae

    A=matrix(zeros((3,3),'double'))
    c=matrix('0;0;0','double')
    #-------------------#
    # Calculate the matrix A and vector c
    #  and return the value of p
    # You will need to work out the correct formulas

    
    #-------------------#

def partC():
    # Complete the function simpleLeastSquares and then run partC() to see the results
    
    # A test dataset
    X=[ 0,1,2,3,4,5 ]
    Y=[ 3.1,5.8,7.1,6.1,2.7,-2.0 ]

    # Fit the data using least squares
    p=complexLeastSquares(X,Y)

    # Generate some data to plot the fitted line
    FittedX=[ x*6.0/19 for x in range(20)]
    FittedY=[ p[0,0]*x*x+p[1,0]*x+p[2,0] for x in FittedX ]

    plt.scatter(X,Y,100,'r','+')
    plt.plot(FittedX,FittedY,'b--')
    plt.title('Quadratic fit')

    plt.show()


################################################
partA()
