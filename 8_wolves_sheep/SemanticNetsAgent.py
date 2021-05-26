from os import curdir
import pandas as pd
import numpy as np
class SemanticNetsAgent:
    def __init__(self):
        #If you want to do any initial processing, add it here.
        initial_state = [0,0]
        goal_state = pd.Series([1,1])
        goal_state_index = ['wolf', 'sheep']
        state = pd.DataFrame(columns=["wolf", "sheep"])
        state = state.append({'wolf': 0, 'sheep': 0})
        state_col = state.columns
        pass

    def solve(self, initial_sheep, initial_wolves):
        #Add your code here! Your solve method should receive
        #the initial number of sheep and wolves as integers,
        #and return a list of 2-tuples that represent the moves
        #required to get all sheep and wolves from the left
        #side of the river to the right.
        #
        #If it is impossible to move the animals over according
        #to the rules of the problem, return an empty list of
        #moves.
        current_state = state.loc[len(state) - 1][state_col]
        if (current_state == goal_state).all():
            return state
        
        elif (current_state['wolf'] == 1 and current_state['sheep'] == 1) 
        pass

