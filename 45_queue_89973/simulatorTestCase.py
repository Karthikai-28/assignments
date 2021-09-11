import unittest 
from project3 import Simulator

# A few test cases for the Simulator class.
class SimulatorTestCase(unittest.TestCase):
    def setUp(self):
        numberCashiers = 1
        simulationLength = 25
        probabilityOfArrival = 0.5
        averageCustomerTime = 3
        maxCheckoutLines = 10
        maxWaitThreshold = 5

        self.sim = Simulator(numberCashiers, simulationLength, probabilityOfArrival, averageCustomerTime, maxCheckoutLines, maxWaitThreshold)

        self.sim.checkOutLines[0].addRear({ "checkoutDuration": 6, "entryTimeForCurrentLine": 1})
        self.sim.currentWaitTimeByLine[0] += (6 + 1)


    def testShouldOpenNewLine(self):
        assert self.sim.shouldOpenNewLine() is True

    def testOpenNewLine(self):
        sim = self.sim
        sim.openNewLine()

        assert sim.checkOutLines[1] is not None
        assert sim.customersServedByCashierList[1] is not None        
        assert sim.cashierIdleList[1] is not None
        assert sim.currentWaitTimeByLine is not None
        assert sim.totalCustomerWaitTimeInCheckoutQueue is not None
        # We only opened one ine
        with self.assertRaises(IndexError):
            sim.checkOutLines[2]

    def testShiftCustomersToNewLine(self):
        sim = self.sim
        sim.openNewLine()  
        sim.openNewLine()

        sim.checkOutLines[0].addRear({ "checkoutDuration": 3, "entryTimeForCurrentLine": 2})
        sim.checkOutLines[0].addRear({ "checkoutDuration": 4, "entryTimeForCurrentLine": 3})
        sim.checkOutLines[0].addRear({ "checkoutDuration": 7, "entryTimeForCurrentLine": 4})
        sim.currentWaitTimeByLine[0] = (3 + 4 + 7 + 6 + (1*4)) # 6 is initial queue val. = 24 

        sim.checkOutLines[1].addRear({ "checkoutDuration": 1, "entryTimeForCurrentLine": 5})
        sim.checkOutLines[1].addRear({ "checkoutDuration": 4, "entryTimeForCurrentLine": 6})
        sim.checkOutLines[1].addRear({ "checkoutDuration": 7, "entryTimeForCurrentLine": 7})
        sim.checkOutLines[1].addRear({ "checkoutDuration": 5, "entryTimeForCurrentLine": 8})
        sim.checkOutLines[1].addRear({ "checkoutDuration": 3, "entryTimeForCurrentLine": 9})

        sim.currentWaitTimeByLine[1] = (1 + 4 + 7 + 5 + 3 + (1*5)) # 25

        sim.checkOutLines[2].addRear({ "checkoutDuration": 3, "entryTimeForCurrentLine": 10})
        sim.checkOutLines[2].addRear({ "checkoutDuration": 3, "entryTimeForCurrentLine": 11})     

        sim.currentWaitTimeByLine[2] = (3 +3 + (1*2)) # 8

        # Our shortest line by wait time should be 2, whose wait exceeds the max threshold
        # secondShortestLine = 0, whose is 24 

        print(sim.currentWaitTimeByLine)
        sim.shiftCustomersToNewLine(12)
        print(sim.currentWaitTimeByLine)   
        # Should shift 3 from line 1 to line 2, total duration 7 + (3 + 1) = 11
        # Then line 1 should be 25 - (3 + 1) = 21
        # Should shift 7 from line 0 to 2, total duration for 2 is then 11 + (7 + 1) = 19
        # Then 0's is 16
        # checkoutline 2's 19 > 16, should stop here. 
        self.assertEqual(sim.currentWaitTimeByLine[0], 16)
        self.assertEqual(sim.currentWaitTimeByLine[1], 21)
        self.assertEqual(sim.currentWaitTimeByLine[2], 20)


    def testDetermineShortestLine(self):
        sim = self.sim
        sim.openNewLine()  
        sim.openNewLine()

        sim.checkOutLines[0].addRear({ "checkoutDuration": 3, "entryTimeForCurrentLine": 2})
        sim.checkOutLines[0].addRear({ "checkoutDuration": 4, "entryTimeForCurrentLine": 3})
        sim.checkOutLines[0].addRear({ "checkoutDuration": 7, "entryTimeForCurrentLine": 4})
       # Line 0 wait time = (6 + 1) +(3 + 1) + (4+ 1) + (7+ 1) 6 is initial setup queue val. = 24 

        sim.checkOutLines[1].addRear({ "checkoutDuration": 1, "entryTimeForCurrentLine": 5})
        sim.checkOutLines[1].addRear({ "checkoutDuration": 4, "entryTimeForCurrentLine": 6})
        sim.checkOutLines[1].addRear({ "checkoutDuration": 7, "entryTimeForCurrentLine": 7})
        sim.checkOutLines[1].addRear({ "checkoutDuration": 5, "entryTimeForCurrentLine": 8})
        sim.checkOutLines[1].addRear({ "checkoutDuration": 3, "entryTimeForCurrentLine": 9})
        # Line 1 wait time: 2 + 5 + 8 + 6 + 4 = 25

        sim.checkOutLines[2].addRear({ "checkoutDuration": 3, "entryTimeForCurrentLine": 10})
        sim.checkOutLines[2].addRear({ "checkoutDuration": 3, "entryTimeForCurrentLine": 11})     
        # Line 2 Wait time is 6 + 2 = 8

        sim.currentWaitTimeByLine[0] = 24
        sim.currentWaitTimeByLine[1] = 25
        sim.currentWaitTimeByLine[2] = 8        

        smallestLine = 2

        assert smallestLine == sim.determineSmallestLine()

# unittest.main()