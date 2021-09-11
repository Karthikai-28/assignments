from priority_queue import PriorityQueue
from priority_queue import PriorityQueueEntry
from double_linked_deque import Deque
import random

class Simulator():
    def __init__(self, initialNumCashiers, simulationLength, probabilityOfArrival, 
    averageCustomerTime, maxCheckoutLines, maxWaitThreshold):
        self.initialNumCashiers = initialNumCashiers
        self.simulationLength = simulationLength
        self.probabilityOfArrival = probabilityOfArrival        
        self.averageCustomerTime = averageCustomerTime
        self.maxCheckoutLines = maxCheckoutLines
        self.maxWaitThreshold = maxWaitThreshold   

        # Parallel lists to store state of cashiers
        self.cashierIdleEventQueue = PriorityQueue()
        self.customersServedByCashierList = [0] * initialNumCashiers # Number of customers each cashier has served        
        self.cashierIdleList = [True] * initialNumCashiers # Each cashier is initially idle
        self.checkOutLines = [Deque() for i in range(initialNumCashiers)]  # Deque that holds customer checkout duration

        self.totalCustomerWaitTimeInCheckoutQueue = [0] * initialNumCashiers # Tracks total wait time in queue for already-served customers of a line #.

        self.currentWaitTimeByLine = dict.fromkeys(range(0, initialNumCashiers), 0 ) # Key is cashier #, value: current wait time until next newly enqueued customer could be checked out by line.     

    def run(self):
        """ Runs the simulator with the given parameters."""
        for clock in range(self.simulationLength):      
            self.decrementAllCashierCurrentWaitTimes()

            if len(self.checkOutLines) < self.maxCheckoutLines and self.shouldOpenNewLine():
                self.openNewLine()
                self.shiftCustomersToNewLine(clock)

            if self.customerArrived():
                self.addCustomerToShortestLine(clock)

            self.updateCashiersState(clock)
            self.startCustomersAtIdleCashiers(clock)

        self.printSimulationSummary()

    def customerArrived(self):
        """ Returns a Boolean indicating whether a customer arrives at check-out lines
            within the current minute randomly based on the probabilityOfArrival. """
        randomValue = random.random()  # random float in range [0,1)
        if randomValue < self.probabilityOfArrival:
            return True
        return False

    def shouldOpenNewLine(self):
        """ Returns true if our shortest line's wait time exceeds the maximum wait threshold."""
        shortestLine = self.determineSmallestLine()
        return True if self.currentWaitTimeByLine[shortestLine] > self.maxWaitThreshold else False

    def openNewLine(self):
        """ Opens a new line and updates existing data structures to accomodate the new line."""
        currNumCheckoutLines = len(self.checkOutLines)
        newLineIndex = currNumCheckoutLines # New index will be == current last index + 1, == len(list)

        self.checkOutLines.append(Deque())
        self.cashierIdleList.append(True)
        self.customersServedByCashierList.append(0)
        self.totalCustomerWaitTimeInCheckoutQueue.append(0)    
        self.currentWaitTimeByLine[newLineIndex] = 0

    def shiftCustomersToNewLine(self, clock):
        """ Repeatedly removes customers from the rear of the longest checkout queue
        until the wait time of the new line is equal to or greater than that of the second-shortest line 
        (the second shortest being fixed to the shortest line # before this new line opened.)

        We store the checkout line wait times and cashier #s in a priority queue checkoutLineShiftPriority 
        to see which line is currently longest (we set priority to -1*waitTime since we're using a minHeap, so the 
        longest line / highest waitTime number is the highest priority or min, so dequeue gives us the longestLine in heap deletion / O(log n) time.
        """
        sortedCashiersByWaitTimes = sorted(self.currentWaitTimeByLine, key=self.currentWaitTimeByLine.get)
        secondShortestLine = sortedCashiersByWaitTimes[1]
        newLine = len(self.checkOutLines) - 1 # Last index, since we already added the new line.
        checkoutLineShiftPriority = PriorityQueue()

        for line in range(len(self.checkOutLines)):
            checkoutLineShiftPriority.enqueue(PriorityQueueEntry(-(self.currentWaitTimeByLine[line]), line))

        while self.currentWaitTimeByLine[secondShortestLine] > self.currentWaitTimeByLine[newLine]:
            longestLine = checkoutLineShiftPriority.dequeue().getValue()
            customer = self.checkOutLines[longestLine].removeRear()
             # Reset customer's queue entry time to reflect the entry time to the new line/queue.
            customer['entryTimeForCurrentLine'] = clock
            self.checkOutLines[newLine].addRear(customer)
            # Update line wait times to reflect the dequeued/enqueued customer.            
            self.currentWaitTimeByLine[longestLine] -= (customer['checkoutDuration'] + 1) 
            self.currentWaitTimeByLine[newLine] += (customer['checkoutDuration'] + 1)
            # Re-enqueue "longestLine" with its new wait time to the priority queue.
            checkoutLineShiftPriority.enqueue(PriorityQueueEntry(-1 * self.currentWaitTimeByLine[longestLine], longestLine))

    def addCustomerToShortestLine(self, clock):
        """ Adds a customer to the open line whose current total wait time is the shortest.
        Then adds their checkout time to the line's current total wait time."""
        smallestLine = self.determineSmallestLine()
        checkOutDuration = random.randint(1, round(2*self.averageCustomerTime))        
        customer = { "checkoutDuration": checkOutDuration, "entryTimeForCurrentLine": clock}
        self.checkOutLines[smallestLine].addRear(customer)
        self.currentWaitTimeByLine[smallestLine] += (customer['checkoutDuration'] + 1) 
        # The + 1 corresponds with the customer's PriorityQueueEntry priority being customerServeTime + 1 (line 138)

    def determineSmallestLine(self):
        """ Return the cashier # with the lowest total checkout wait time."""
        return sorted(self.currentWaitTimeByLine, key=self.currentWaitTimeByLine.get)[0]

    def updateCashiersState(self, clock):
        """ Check whether cashiers become idle in this clock tick, and update their
            state if they do."""
        while not self.cashierIdleEventQueue.isEmpty() and self.cashierIdleEventQueue.peek().getPriority() <= clock:
            cashierGoingIdle = self.cashierIdleEventQueue.dequeue().getValue()
            self.cashierIdleList[cashierGoingIdle] = True
            self.customersServedByCashierList[cashierGoingIdle] += 1

    def decrementAllCashierCurrentWaitTimes(self):
        """ Used decrement the total current wait time in a cashier's line by 1 minute, if > 0."""
        for cashier in range(len(self.currentWaitTimeByLine)):
            if self.currentWaitTimeByLine[cashier] > 0:
                self.currentWaitTimeByLine[cashier] -= 1          

    def startCustomersAtIdleCashiers(self, clock):
        """ Start the next customer at cashiers which are idle and have someone in their
            check-out line.
            Updates total served customer wait time by line to reflect this dequeued customer's wait time in the checkout queue."""
        for cashier in range(len(self.cashierIdleList)):
            if self.cashierIdleList[cashier] and not self.checkOutLines[cashier].isEmpty():
                customer = self.checkOutLines[cashier].removeFront()
                self.totalCustomerWaitTimeInCheckoutQueue[cashier] += (clock - customer['entryTimeForCurrentLine'])

                customerServeTime = customer['checkoutDuration']
                self.cashierIdleList[cashier] = False
                # schedule future event for when cashier will go idle
                self.cashierIdleEventQueue.enqueue(PriorityQueueEntry(clock+customerServeTime+1, cashier))
    
    def printSimulationSummary(self):
        """ For each cashier, prints the # of customers served and the # of customers
            still waiting in their check-out line when the simulation ends, as well as the average wait time and # of customers being checked out. """
        for cashier in range(len(self.checkOutLines)):
            numCustomersServed = self.customersServedByCashierList[cashier]
            print("\nCashier", cashier, "checked out", numCustomersServed,
                "customers with", self.checkOutLines[cashier].size(),
                "customers in their line at end of simulation.")           
            print("Cashier #", cashier, 
                    "'s average customer wait time from line enqueue to beginning checkout: ", 
                    round(self.totalCustomerWaitTimeInCheckoutQueue[cashier] // numCustomersServed),
                    " minutes") if numCustomersServed > 0 else print("Their average customer wait time: 0 minutes (no customers served)")
        
        print("\nTotal average waiting time for all served customers:", 
                sum(self.totalCustomerWaitTimeInCheckoutQueue) // sum(self.customersServedByCashierList), "minutes") if len(self.customersServedByCashierList) > 0 else print("No customers were served!")
        print("\nNumber of customers in the process of being checked out:", self.cashierIdleEventQueue.size(), "\n")

def main():
    initialNumCashiers = int(input("Enter # of initial cashiers (open checkout lines): "))
    simulationLength = int(input("Enter simulation length (in minutes): "))
    probabilityOfArrival = float(input("Enter probability of customer arrival each minute (0 to 1): "))
    averageCustomerTime = int(input("Enter average # minutes for a customer: "))
    maxCheckoutLines = int(input("Enter the maximum number of checkout lines: "))
    maxWaitThreshold = int(input("Enter the maximum wait time threshold, in minutes, at which a new checkout line is opened: ")) 

    sim = Simulator(initialNumCashiers, simulationLength, probabilityOfArrival, averageCustomerTime, maxCheckoutLines, maxWaitThreshold)

    sim.run()

main()
