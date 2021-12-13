import inspect
import sys
import matplotlib.pyplot as plt
import numpy
import operator
from robot import Robot
from sweeper import Sweeper
from dfs_sweeper import DFSSweeper

P = numpy.identity(2)
X = numpy.array([[0], [0]])
count = 0
import random

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

def plot_color(dict1):
    #calculates color for bar graphs
    max_val=max(dict1.items(), key=operator.itemgetter(1))

    color=[]
    for key in dict1:
        if dict1[key] < max_val[1]:
            color.append('b')
        else:
            color.append('r')
    return color


#bayes filter function for calculating probability of robot's location and for plotting bar graphs
def bayes_filter(bel_x, z,step):
    
    #outputs the likelihood of where the robot is before sensing a wall or door
    if step==0:
        print("\nInitial Position: ")
        for key in bel_x:
            print(f"bel(x{step} = {key}) = ", round(bel_x[key],3))

    #initialization of variables
    #number of subplots
    nplt=4
    #subplots size
    plt.figure(figsize=(10,8))
    w=0.5
    #first subplot of the probability of the robot's position at step =0
    plt.subplot(nplt,1,1)
    plt.title(f"bel(x{step})")
    plt.bar(*zip(*bel_x.items()),color=plot_color(bel_x),width=w)
    
    #70% likelihood that the robot moves to next grid(p1)
    first_grid=.7
    #20% likelihood that the robot stays on same grid(p0)
    same_grid=.2
    #10% likelihood that the robot moves to the grid after the next grid (p2)
    second_grid=0.1
    #0% likelihood that the robot moves to the yellow grid after p3
    yellow_grid=0.0
    
    #state transition probability matrix
    state_trans_prob={f"x{step+1} = p0":[same_grid,0,0,0],f"x{step+1} = p1":[first_grid,same_grid,0,0],
                      f"x{step+1} = p2":[second_grid,first_grid,same_grid,0],f"x{step+1} = p3":[0,second_grid,first_grid,same_grid]}
    
    #state space matrix details
    print(f"\nAt step t={step+1}, after the control u{step+1}, the robot returns a measurement of z{step+1} ={z}.\n")
    
    print("State Transition Probability: ")
    for key in state_trans_prob:
        print(f"({key}|u{step+1},x{step}=p0, x{step}=p1,x{step}=p2, x{step}=p3)= ",state_trans_prob[key])
    
    #location of door and wall
    door=['p1','p3']
    wall=['p0','p2']
    
    #chances of sensing a wall or door 
    door_sense={"wall_p0":.3,"door_p1":.8,"wall_p2":.3,"door_p3":.8}
    wall_sense={"wall_p0":.7,"door_p1":.2,"wall_p2":.7,"door_p3":.2}
    
    
    #calculates the bel_bar values for all potential locations (p0~p3)
    bel_vals=bel_x.values()
    bel_bar={}
    print(f"\nCalculations of bel_bar for all potential locations (p0~p3): ")
    for key in state_trans_prob:
        bel_bar[key[-2:]]=sum([bel*prob for bel,prob in zip(bel_vals,state_trans_prob[key])])
        print(f"bel_bar(x{step+1}={key[-2:]})= ",round(bel_bar[key[-2:]],3))
    
    #bel_bar plot
    plt.subplot(nplt,1,2)
    plt.title(f"bel_bar(x{step+1})")
    plt.bar(*zip(*bel_bar.items()),color=plot_color(door_sense),width=w)

    sum_bel=[]
    print(f"\nProbability of the robot sensing the {z} at step = {step+1}:")
    
    #plots probability of the robot detecting a door or wall
    if z == "door":
        #print("If Measurement: ", z)
        plt.subplot(nplt,1,3)
        plt.title(f"p(z{step+1}={z}|x{step+1})")
        plt.bar(*zip(*door_sense.items()),color=plot_color(door_sense),width=w)
        for key in door_sense:
            print(f"p(z{step+1} = {z}|x{step+1}={key[-2:]})=", door_sense[key])
        for key in bel_bar:
            
            if key in door:
                #print("if door: ",key)
                sum_bel.append(bel_bar[key]*.80)
                bel_bar[key]*=.80
                
                
                
            else:
                #print("else door: ",key)
                sum_bel.append(bel_bar[key]*.30)
                bel_bar[key]*=.30
                
                
                
    else:
        plt.subplot(nplt,1,3)
        plt.title(f"p(z{step+1}={z}|x{step+1})")
        plt.bar(*zip(*wall_sense.items()),color=plot_color(wall_sense),width=w)
        #print("Else Measurement: ", z)
        for key in wall_sense:
            print(f"p(z{step+1} = {z}|x{step+1}={key[-2:]})=", wall_sense[key])
        for key in bel_bar:
            
            if key in wall:
                #print("if wall: ",key)
                sum_bel.append(bel_bar[key]*.70)
                bel_bar[key]*=.70
               
                
            else:
                #print("else wall: ",key)
                sum_bel.append(bel_bar[key]*.20)
                bel_bar[key]*=.20
               
    print(f"\nNormalization and η calculation: ")
    
    #η (normalization value) is calculated
    for i in range(len(sum_bel)):
        print(f"bel(x{step+1} = p{i}) = p(z{step+1} = {z}|x{step+1}=p{i})*bel_bar(x{step+1} = p{i})*η = {round(sum_bel[i],3)}*η")
                
    η=1/sum(sum_bel)
    print(f"η = 1/{round(sum(sum_bel),3)} = ", round(η,3))
    η_dict={"η":η}
    step_dict={"step":step+1}
#     print("η: ", η)

   #after η is calculated then the robot's localization belief is updated for step t=1 and 2 for u=1
    new_bel={key:bel_bar[key]*η for key in bel_x}
    #print(new_bel)
    print(f"\nNew updated belief of the robot's localization probability after step {step+1}: ")
    for key in new_bel:
        print(f'bel(x{step+1} = {key}) = ', round(new_bel[key],3))
    
    #plotting localization probability after update of belief at t=1 and t=2
    plt.subplot(nplt,1,4)
    plt.title(f"bel(x{step+1})")
    plt.bar(*zip(*new_bel.items()),color=plot_color(new_bel),width=w)
    plt.tight_layout()
    plt.show()
   
    if z=="door":
        
        
        return new_bel
    else:
        
        
        
        return new_bel #,df

#the robot_localization function initializes the robot's belief of its initial position and sets what features it can detect
#the robot_localization function also runs the function bayes_filter 
def robot_localization(t):
    sense=["door","wall","door","wall"]
    bel_x=[{"p0":0.25,"p1":0.25,"p2":0.25,"p3":0.25}]
    #state_trans_prob,bel_bar,η_dict,step_dict,new_bel,sense=0

   
    for step in range(t):
        #bayes_filter function returns a new belief of where the robot thinks it's at 
        bel=bayes_filter(bel_x[step],sense[step],step)
        bel_x.append(bel)


def random_matrix(no_rows, no_cols, no_obs):
    arr = []
    for i in range(no_rows * no_cols):
        if i < no_obs:
            arr.append(1)
        else:
            arr.append(0)

    random.shuffle(arr)

    start_position = {'x': 0, 'y': 0}
    rand_pos = random.randint(0, no_rows * no_cols - no_obs - 1)

    matrix = []
    count = 0
    for i in range(no_rows):
        row = []
        for j in range(no_cols):
            row.append(arr[i * no_cols + j])
            if arr[j] == 0:
                if count == rand_pos:
                    start_position = {'x': j, 'y': i}
                count += 1
        matrix.append(row)
    return matrix, start_position

def main():
    no_rows = 10
    no_cols = 9
    no_obs = 10
    no_matrix = 1

    total_elapsed_bfs = 0
    total_steps_bfs = 0
    total_turns_bfs = 0

    total_elapsed_dfs = 0
    total_steps_dfs = 0
    total_turns_dfs = 0

    import time
    for i in range(no_matrix):
        matrix, start_position = random_matrix(no_rows, no_cols, no_obs)
        start_direction = random.randint(0, 3)

        # run with dfs
        robot = Robot(matrix, start_position, start_direction)
        # robot.log()
        sweeper = DFSSweeper(robot)
        sweeper.loggable = False
        robot.loggable = True

        start = time.time()
        sweeper.sweep()
        elapsed = time.time() - start

        total_elapsed_dfs += elapsed
        total_steps_dfs += robot.move_count
        total_turns_dfs += robot.turn_count

        print('steps taken by dfs: %d, turns taken: %d, time taken: %.2fms'
              % (robot.move_count, robot.turn_count, elapsed * 1000))

        # run with bfs
        robot = Robot(matrix, start_position, start_direction)
        sweeper = Sweeper(robot)
        sweeper.loggable = False
        robot.loggable = True

        # start = time.time()
        # sweeper.sweep()
        # elapsed = time.time() - start

        total_elapsed_bfs += elapsed
        total_steps_bfs += robot.move_count
        total_turns_bfs += robot.turn_count

        print('steps taken by planned bfs: %d, turns taken: %d, time taken: %.2fms'
              % (robot.move_count, robot.turn_count, elapsed * 1000))

        # sweeper.print_map()
        # robot.log()

    print('DFS: average steps taken: %d, turns taken: %d, time taken: %.2fms'
         % (int(total_steps_dfs / no_matrix), int(total_turns_dfs / no_matrix), total_elapsed_dfs * 1000 / no_matrix))

    print('Planned BFS: average steps taken: %d, turns taken: %d, time taken: %.2fms'
         % (int(total_steps_bfs / no_matrix), int(total_turns_bfs / no_matrix), total_elapsed_bfs * 1000 / no_matrix))

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
    robot_localization(3)
    main()