#########################################
#                                       #
#                                       #
#  ==  SOKOBAN STUDENT AGENT CODE  ==   #
#                                       #
#      Written by: [YOUR FULL NAME]     #
#                                       #
#                                       #
#########################################


# SOLVER CLASSES WHERE AGENT CODES GO
from helper import *
import random
import math


# Base class of agent (DO NOT TOUCH!)
class Agent:
    def getSolution(self, state, maxIterations):

        '''
        EXAMPLE USE FOR TREE SEARCH AGENT:


        #expand the tree until the iterations runs out or a solution sequence is found
        while (iterations < maxIterations or maxIterations <= 0) and len(queue) > 0:
            iterations += 1

            [ POP NODE OFF OF QUEUE ]

            [ EVALUATE NODE AS WIN STATE]
                [ IF WIN STATE: BREAK AND RETURN NODE'S ACTION SEQUENCE]

            [ GET NODE'S CHILDREN ]

            [ ADD VALID CHILDREN TO QUEUE ]

            [ SAVE CURRENT BEST NODE ]


        '''


        '''
        EXAMPLE USE FOR EVOLUTION BASED AGENT:
        #expand the tree until the iterations runs out or a solution sequence is found
        while (iterations < maxIterations or maxIterations <= 0) and len(queue) > 0:
            iterations += 1

            [ MUTATE ]

            [ EVALUATE ]
                [ IF WIN STATE: BREAK AND RETURN ]

            [ SAVE CURRENT BEST ]

        '''


        return []       # set of actions


#####       EXAMPLE AGENTS      #####
# Do Nothing Agent code - the laziest of the agents
class DoNothingAgent(Agent):
    def getSolution(self, state, maxIterations):
        if maxIterations == -1:     # RIP your machine if you remove this block
            return []

        #make idle action set
        nothActionSet = []
        for i in range(20):
            nothActionSet.append({"x":0,"y":0})

        return nothActionSet

# Random Agent code - completes random actions
class RandomAgent(Agent):
    def getSolution(self, state, maxIterations):

        #make random action set
        randActionSet = []
        for i in range(20):
            randActionSet.append(random.choice(directions))

        return randActionSet

#####    ASSIGNMENT 1 AGENTS    #####
# BFS Agent code
class BFSAgent(Agent):
    def getSolution(self, state, maxIterations=-1):
        intializeDeadlocks(state)
        iterations = 0
        bestNode = None
        queue = [Node(state.clone(), None, None)]
        visited = set()

        #expand the tree until the iterations runs out or a solution sequence is found
        while (iterations < maxIterations or maxIterations <= 0) and len(queue) > 0:
            # YOUR CODE HERE
            currentNode = queue.pop(0)
            iterations += 1
            # Check if already Visited
            if currentNode.getHash() not in visited:
                # Check if Winning State
                if currentNode.checkWin():
                    bestNode = currentNode
                    break
                visited.add(currentNode.getHash())
                queue.extend(currentNode.getChildren())
                if bestNode is None or currentNode.getHeuristic() < bestNode.getHeuristic():
                    bestNode = currentNode
                elif currentNode.getHeuristic() == bestNode.getHeuristic() and currentNode.getCost() < bestNode.getCost():
                    bestNode = currentNode
        return bestNode.getActions()   #uncomment me

# DFS Agent Code
class DFSAgent(Agent):
    def getSolution(self, state, maxIterations=-1):
        intializeDeadlocks(state)
        iterations = 0
        bestNode = None
        stackDFS = [Node(state.clone(), None, None)]
        visited = set()
        
        #expand the tree until the iterations runs out or a solution sequence is found
        while (iterations < maxIterations or maxIterations <= 0) and len(stackDFS) > 0:
            iterations += 1

            # YOUR CODE HERE
            currentNode = stackDFS.pop()
            # Check if already Visited
            if currentNode.getHash() not in visited:
                # Check if Winning State
                if currentNode.checkWin():
                    bestNode = currentNode
                    break
                visited.add(currentNode.getHash())
                stackDFS.extend(currentNode.getChildren())
                if bestNode is None or currentNode.getHeuristic() < bestNode.getHeuristic():
                    bestNode = currentNode
                elif currentNode.getHeuristic() == bestNode.getHeuristic() and currentNode.getCost() < bestNode.getCost():
                    bestNode = currentNode

        return bestNode.getActions()   #uncomment me

# AStar Agent Code
class AStarAgent(Agent):
    def getSolution(self, state, maxIterations=-1):
        #setup
        intializeDeadlocks(state)
        iterations = 0
        bestNode = None

        #initialize priority queue
        queue = PriorityQueue()
        queue.put(Node(state.clone(), None, None))
        visited = set()

        while (iterations < maxIterations or maxIterations <= 0) and queue.qsize() > 0:
            iterations += 1

            ## YOUR CODE HERE ##
            currentNode = queue.get()
            # check if Node is not already visited
            if currentNode.getHash() not in visited:
                # check if Node is in goal state, then set node as bestNode and break while loop
                if currentNode.state.checkWin():
                    bestNode = currentNode
                    break
                # if not goal state continue and add node to set of visited node
                visited.add(currentNode.getHash())

                # extract the children of the node and put in an array
                nodeChildren = []
                nodeChildren.extend(currentNode.getChildren())

                # insert the children nodes into the priority queue
                for child in nodeChildren:
                    queue.put(child)

                # update bestNode if the Heuristics of currNode is better, break tie with Cost
                if bestNode is None or currentNode.getHeuristic() < bestNode.getHeuristic():
                    bestNode = currentNode
                elif currentNode.getHeuristic() == bestNode.getHeuristic() and currentNode.getCost() < bestNode.getCost():
                    bestNode = currentNode

        return bestNode.getActions()   #uncomment me


#####    ASSIGNMENT 2 AGENTS    #####
# Hill Climber Agent code
class HillClimberAgent(Agent):
    def getSolution(self, state, maxIterations=-1):
        #setup
        intializeDeadlocks(state)
        iterations = 0
        
        seqLen = 50            # maximum length of the sequences generated
        coinFlip = 0.5          # chance to mutate

        #initialize the first sequence (random movements)
        bestSeq = []
        for i in range(seqLen):
            bestSeq.append(random.choice(directions))

        #mutate the best sequence until the iterations runs out or a solution sequence is found
        while (iterations < maxIterations):
            iterations += 1
            
            ## YOUR CODE HERE ##
            # clone state as bestState and update bestState to reflect bestSeq
            bestState = state.clone()
            for direction in bestSeq:
                bestState.update(direction['x'], direction['y'])

            # check if bestState is goal state, else start mutation process
            if bestState.checkWin():
                return bestSeq
            # mutate the bestSeq and store in mutatedSeq
            mutatedSeq = []
            for i in range(seqLen):
                # coinFlip mutation
                if random.random() < coinFlip:
                    mutatedSeq.append(random.choice(directions))
                else:
                    mutatedSeq.append(bestSeq[i])

            # clone state as mutatedState and apply the mutatedSeq to it
            mutatedState = state.clone()
            for direction in mutatedSeq:
                mutatedState.update(direction['x'], direction['y'])

            # check if mutated state is goal state else compare heuristic to update bestSeq
            if mutatedState.checkWin():
                return mutatedSeq
            elif getHeuristic(mutatedState) < getHeuristic(bestState):
                for i in range(seqLen):
                    bestSeq[i] = mutatedSeq[i]
        #return the best sequence found
        return bestSeq  

# Genetic Algorithm code
class GeneticAgent(Agent):
    def getSolution(self, state, maxIterations=-1):
        #setup
        intializeDeadlocks(state)

        iterations = 0
        seqLen = 50             # maximum length of the sequences generated
        popSize = 10            # size of the population to sample from
        parentRand = 0.5        # chance to select action from parent 1 (50/50)
        mutRand = 0.3           # chance to mutate offspring action

        bestSeq = []            #best sequence to use in case iterations max out

        #initialize the population with sequences of POP_SIZE actions (random movements)
        population = []
        for p in range(popSize):
            bestSeq = []
            for i in range(seqLen):
                bestSeq.append(random.choice(directions))
            population.append(bestSeq)

        #mutate until the iterations runs out or a solution sequence is found
        while (iterations < maxIterations):
            iterations += 1

            #1. evaluate the population
            evaluatedPopulation = []
            for individual in population:
                individualState = state.clone()
                for direction in individual:
                    individualState.update(direction['x'], direction['y'])
                if(individualState.checkWin()):
                    return individual
                fitness = getHeuristic(individualState)
                evaluatedPopulation.append((fitness, individual))
           
            #2. sort the population by fitness (low to high)
            evaluatedPopulation.sort(key=(lambda x: x[0]))

            #2.1 save bestSeq from best evaluated sequence
            bestSeq = []
            for i in range(seqLen):
                bestSeq.append(evaluatedPopulation[0][1][i])

            #3. generate probabilities for parent selection based on fitness
            currRank = 5
            parentRouletteWheel = []

            # allocate area in the roulette wheel based on fitness
            for i in range(int(popSize/2)):
                for j in range(currRank):
                    parentRouletteWheel.append(i)
                currRank = currRank-1

            #4. populate by crossover and mutation
            new_pop = []
            for i in range(int(popSize/2)):
                #4.1 select 2 parents sequences based on probabilities generated
                par1 = evaluatedPopulation[random.choice(
                    parentRouletteWheel)][1]
                par2 = evaluatedPopulation[random.choice(
                    parentRouletteWheel)][1]
                
                #4.2 make a child from the crossover of the two parent sequences
                offspring = []
                for seq in range(seqLen):
                    if(random.random() < parentRand):
                        offspring.append(par1[seq])
                    else:
                        offspring.append(par2[seq])

                #4.3 mutate the child's actions
                for seq in range(seqLen):
                    if(random.random() < mutRand):
                        offspring[seq] = random.choice(directions)

                #4.4 add the child to the new population
                new_pop.append(list(offspring))


            #5. add top half from last population (mu + lambda)
            for i in range(int(popSize/2)):
                new_pop.append(evaluatedPopulation[i][1])


            #6. replace the old population with the new one
            population = list(new_pop)

        #return the best found sequence 
        return bestSeq

# MCTS Specific node to keep track of rollout and score
class MCTSNode(Node):
    def __init__(self, state, parent, action, maxDist):
        super().__init__(state,parent,action)
        self.children = []  #keep track of child nodes
        self.n = 0          #visits
        self.q = 0          #score
        self.maxDist = maxDist      #starting distance from the goal (heurstic score of initNode)

    #update get children for the MCTS
    def getChildren(self,visited):
        #if the children have already been made use them
        if(len(self.children) > 0):
            return self.children

        children = []

        #check every possible movement direction to create another child
        for d in directions:
            childState = self.state.clone()
            crateMove = childState.update(d["x"], d["y"])

            #if the node is the same spot as the parent, skip
            if childState.player["x"] == self.state.player["x"] and childState.player["y"] == self.state.player["y"]:
                continue

            #if this node causes the game to be unsolvable (i.e. putting crate in a corner), skip
            if crateMove and checkDeadlock(childState):
                continue

            #if this node has already been visited (same placement of player and crates as another seen node), skip
            if getHash(childState) in visited:
                continue

            #otherwise add the node as a child
            children.append(MCTSNode(childState, self, d, self.maxDist))

        self.children = list(children)    #save node children to generated child

        return children

    #calculates the score the distance from the starting point to the ending point (closer = better = larger number)
    def calcEvalScore(self,state):
        return self.maxDist - getHeuristic(state)

    #compares the score of 2 mcts nodes
    def __lt__(self, other):
        return self.q < other.q

    #print the score, node depth, and actions leading to it
    #for use with debugging
    def __str__(self):
        return str(self.q) + ", " + str(self.n) + ' - ' + str(self.getActions())


# Monte Carlo Tree Search Algorithm code
class MCTSAgent(Agent):
    def getSolution(self, state, maxIterations=-1):
        #setup
        intializeDeadlocks(state)
        iterations = 0
        bestNode = None
        initNode = MCTSNode(state.clone(), None, None, getHeuristic(state))

        while(iterations < maxIterations):
            #print("\n\n---------------- ITERATION " + str(iterations+1) + " ----------------------\n\n")
            iterations += 1

            #mcts algorithm
            rollNode = self.treePolicy(initNode)
            score = self.rollout(rollNode)
            self.backpropogation(rollNode, score)

            #if in a win state, return the sequence
            if(rollNode.checkWin()):
                return rollNode.getActions()

            #set current best node
            bestNode = self.bestChildUCT(initNode)

            #if in a win state, return the sequence
            if(bestNode and bestNode.checkWin()):
                return bestNode.getActions()


        #return solution of highest scoring descendent for best node
        #if this line was reached, that means the iterations timed out before a solution was found
        return self.bestActions(bestNode)
        
    #returns the descendent with the best action sequence based
    def bestActions(self, node):
        #no node given - return nothing
        if node == None:
            return []

        bestActionSeq = []
        while(len(node.children) > 0):
            node = self.bestChildUCT(node)

        return node.getActions()

    ####  MCTS SPECIFIC FUNCTIONS BELOW  ####
    #determines which node to expand next
    def treePolicy(self, rootNode):
        curNode = rootNode
        visited = []

        ## YOUR CODE HERE ##
        while not curNode.checkWin():
            visited.append(getHash(curNode.state))
            curNodeChildren = curNode.getChildren(visited)
            unvisitedChildren = []
            for child in curNodeChildren:
                if child.n == 0:
                    unvisitedChildren.append(child)

            if len(unvisitedChildren) > 0:
                curNode = random.choice(unvisitedChildren)
                return curNode

            curNode = self.bestChildUCT(curNode)

        return curNode

    # uses the exploitation/exploration algorithm
    def bestChildUCT(self, node):
        c = 1               #c value in the exploration/exploitation equation
        bestChild = None

        ## YOUR CODE HERE ##
        # get all the children of the node
        children = node.getChildren([])

        # find the visited node to prevent zero
        # division for child's value
        visitedChildren = []
        for child in children:
            if child.n > 0:
                visitedChildren.append(child)

        valueChildren = []
        for child in visitedChildren:
            value = (child.q/child.n) + \
                (c * math.sqrt((2 * math.log(node.n))/child.n))
            valueChildren.append((child, value))

        if valueChildren:
            valueChildren.sort(key=lambda x: x[1], reverse=True)
            bestChild = valueChildren[0][0]
        else:
            bestChild = node
        return bestChild

     #simulates a score based on random actions taken
    def rollout(self,node):
        numRolls = 7        #number of times to rollout to

        ## YOUR CODE HERE ##
        # clone the state of the node
        state = node.state.clone()

        # now apply 7 random direction to the state
        for i in range(numRolls):
            direction = random.choice(directions)
            state.update(direction['x'], direction['y'])
            if state.checkWin():
                return node.calcEvalScore(state)

        return node.calcEvalScore(state)

     #updates the score all the way up to the root node
    def backpropogation(self, node, score):
        
        ## YOUR CODE HERE ##
        currNode = node

        # starting with the node propagate up the tree
        # and update the n and q values
        while currNode is not None:
            currNode.n += 1
            currNode.q += score
            currNode = currNode.parent

        return