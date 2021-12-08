import inspect
import sys
import matplotlib.pyplot as plt
import numpy
P = numpy.identity(2)
X = numpy.array([[0], [0]])
count = 0

'''
Kalman 2D
'''


def kalman2d(data):
    global X
    global P
    dt = 5
    A = numpy.array([[1, dt], [0, 1]])
    B = numpy.array([[dt*dt/2], [dt]])
    Q = numpy.array([[.0001, .00002], [.00002, .0001]])
    R = numpy.array([[.01, .005], [.005, .02]])
    estimated = []
    H = numpy.identity(2)
    I = numpy.identity(2)
    print("X")
    print(X)
    for i in data:
        u1 = i[0]
        u2 = i[1]
        u_k = numpy.array([[u1], [u2]])
        z1 = i[2]
        z2 = i[3]
        z_k = numpy.array([[z1], [z2]])
        # prediction
        X = X + u_k
        P = A*P*A.T + Q
        # kalman gain/measurement
        K = P/(P + R)
        Y = numpy.dot(H, z_k).reshape(2, -1)

        # new X and P
        X = X + numpy.dot(K, Y - numpy.dot(H, X))
        P = (I - K*H)*P
        estimated.append(X)
    return estimated


'''
Plotting
'''


def plot(data, output):
    experimentX = []
    experimentY = []
    observerX = []
    observerY = []
    for x in data:
        observerX.append(x[2])
        observerY.append(x[3])
    for y in output:
        experimentX.append(y[0])
        experimentY.append(y[1])
    plt.plot(observerX, observerY, color="blue", marker="o", ms=5, label="observed")
    plt.plot(experimentX, experimentY, color="red", marker="o", ms=5, label="estimated")
    plt.show()
    return


if __name__ == "__main__":
    
    # Retrive file name for input data
    if(len(sys.argv) < 5):
        print ("Four arguments required: python kalman2d.py [datafile] [x1] [x2] [lambda]")
        exit()
    
    filename = sys.argv[1]
    x10 = float(sys.argv[2])
    x20 = float(sys.argv[3])
    scaler = float(sys.argv[4])

    # Read data
    lines = [line.rstrip('\n') for line in open(filename)]
    data = []
    for line in range(0, len(lines)):
        _map = list(map(float, lines[line].split(' ')))
        data.append(_map)

    # Print out the data
    print ("The input data points in the format of 'k [u1, u2, z1, z2]', are:")
    for it in range(0, len(data)):
        print (str(it + 1) + ": ", end = '')
        print (*data[it])
        
    P = P*scaler
    X = numpy.array([[x10], [x20]])
    output = kalman2d(data)
    plot(data, output)

