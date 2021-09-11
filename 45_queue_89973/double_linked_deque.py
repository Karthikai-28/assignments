from node import Node

class Deque(object):
    def __init__(self):
        self._front = None
        self._rear = None
        self._size = 0

    def isEmpty(self):
        return self._size == 0

    def addFront(self, item):
        temp = Node(item)
        temp.setPrevious(self._front)
       
        if self._size == 0:
            self._rear = temp
        else:
            self._front.setNext(temp)
            
        self._front = temp
        self._size += 1

    def addRear(self, item):
        temp = Node(item)
        temp.setNext(self._rear)

        if self._size == 0:
            self._front = temp
        else:
            self._rear.setPrevious(temp)

        self._rear = temp
        self._size += 1
        
    def removeFront(self):
        """ Removes and returns the front item of the Deque. """
        if self._size == 0:
            raise AttributeError("Cannot removeFront from an empty Deque")
        
        temp = self._front
        self._front = self._front.getPrevious()
        if self._size == 1:
            self._rear = None
        else:
            self._front.setNext(None)
        self._size -= 1
        
        return temp.getData()
    
    def removeRear(self):
        """ Removes and returns the rear item of the Deque. """
        if self._size == 0:
            raise AttributeError("Cannot removeRear from an empty Deque")
        
        temp = self._rear
        self._rear = self._rear.getNext()

        if self._size == 1:
            self._front = None
        else:
            self._rear.setPrevious(None)
        self._size -= 1
        
        return temp.getData()
    
    def peekFront(self):
        """ Returns the front item of the Deque without removing it. """
        if self._size == 0:
            raise AttributeError("Cannot peekFront from an empty Deque")
        return self._front.getData()

    def peekRear(self):
        """ Returns the rear item of the Deque without removing it. """
        if self._size == 0:
            raise AttributeError("Cannot peekFront from an empty Deque")
        return self._rear.getData()
        
    def size(self):
        return self._size

    def __str__(self):
        """ Returns a string representation of all items from rear to front."""
        resultStr = "(rear)"
        current = self._rear
        while current != None:
            resultStr = resultStr + " " + str(current.getData())
            current = current.getNext()
        resultStr = resultStr + " (front)"
        return resultStr
    
        
