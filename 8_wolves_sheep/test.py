#!/usr/bin/python
# D. Vrajitoru, C463/B551 Spring 2008 

# Implementation of a depth-first search for a solution to the
# goat-wolf-cabbage puzzle.

# Problem: a man is transporting a goat, a wolf, and a cabbage. He
# must cross a river and has a boat that can only carry 1 item
# beside himself at a time. He cannot leave the goat alone on one
# side of the river with the cabbage because the goat will eat the
# cabbage. The same thing with the wolf and the goat. Find a sequence
# of actions that the man can execute to get everybody on the other
# side safely.

entity = ['goat', 'wolf', 'cabbage']
path = []

# Defines who can eat whom
def eats(x, y):
    if x == 'goat' and y == 'cabbage':
        return True
    elif x == 'wolf' and y == 'goat':
        return True
    else:
        return False

# Defines if a pair of entities is safe to be left alone on one side
# of the river.
def safe_pair(x, y):
    if eats(x, y) or eats(y, x):
        return False
    else:
        return True

# Returns the state of the symbol who in the dictionary al. It
# returns its value and not a reference to it so it can be used for
# testing but not modified. If the symbol who is not part of the list
# it return nil.
def state_of(who, state):
    try:
        return state[who]
    except KeyError:
        state[who] = False
        return False

# Verifies if the state defined as an dictionary is safe. If the
# goat is on the same side as the man, then we're safe. Otherwise if
# the cabbage or the wolf is also on the other side, then we're not
# safe.
def safe_state(state):
    if state_of('man', state) == state_of('goat', state):
        return True
    elif state_of('goat', state) == state_of('wolf', state):
        return False
    elif state_of('goat', state) == state_of('cabbage', state):
        return False
    else:
        return True

# Moves the entity from one side to the other in the sate al. It is a
# list mutator. The positions of all the entities are defined by 0
# and 1 so the move replaces the current position with 1 - it. It
# returns the resulting list.
def move(who, state):
    if state[who] == 'left':
        state[who] = 'right'
    else:
        state[who] = 'left'
    return state

# Tests if the state has reached the goal. This is the case if all
# four entities are on the other side.
def goal_reach(state):
    if not state:
        return False
    return (state_of('man', state)=='right' and
            state_of('goat', state)=='right' and
            state_of('wolf', state)=='right' and
            state_of('cabbage',state)=='right')

# Checks if child is a safe state to move into, and if it is, it adds
# it to the list of states.
def check_add_child(child, list_states):
    if safe_state(child):
        list_states.append(child)
        return list_states

def expand_states(state):
    children = []
    child = state.copy()
    # the man can also move alone
    move('man', child)
    check_add_child(child, children)
    for ent in entity:
        # Move one object on the same side as the man
        if state_of(ent, state) == state_of('man', state):
            child = state.copy()
            move('man', child)
            move(ent, child)
            check_add_child(child, children)
        #else:
	#print "unsafe state", child
    return children

# Searches for a solution from the initial state
def search_sol(state):
    path.append(state)
    next = state.copy()
    while next and not goal_reach(next):
        nl = expand_states(next)
        next = {}
        for child in nl:
            if not (child in path):
                next = child
                path.append(next)
                break
    return next


# Initialization of the global variables
initial_state = {}
initial_state['man'] = 'left'
for e in entity:
    initial_state[e] = 'left'

#print initial_state
#{'cabbage': 'left', 'wolf': 'left', 'goat': 'left', 'man': 'left'}

# To see what all the child states from the current one look like
print ("Expanding initial state")
print ("expand_states", initial_state)

# Construct the full olution after evaluating the previous statements
print ("Searching for a solution from the initial state:")
print ("search_sol", initial_state)

# Evaluate the variable path to see the solution backwards.
print ("The full path is:")
for s in path:
    print (s)
