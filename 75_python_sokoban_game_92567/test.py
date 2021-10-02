from helper import readLevel
from agent import BFSAgent, DFSAgent, AStarAgent

#Load Level number 0
state = readLevel(0)

#Initialize Different Agents
astar = AStarAgent()
bfs = BFSAgent()
dfs = DFSAgent()

#Get Solution and Priting them
print(state)
state.render('image').save('start.png')
sol, bestNode, steps = astar.getSolution(state, 1)
bestNode.state.render('image').save('astar.png')
sol, bestNode, steps = bfs.getSolution(state)
bestNode.state.render('image').save('bfs.png')
sol, bestNode, steps = dfs.getSolution(state)
bestNode.state.render('image').save('dfs.png')
print(bestNode.state)
