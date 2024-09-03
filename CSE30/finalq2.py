class Node(object):
    def __init__(self, x):
        self.data = x
        self.next = None
# end
# end
class Queue:
 """Implements a queue using a linked list."""
    def __init__(self):
        self.front = None
        self.back = None
        self.length = 0

    def __len__(self):
        return self.length

    def enqueue(self, x):
        """Insert x at the back of the queue."""
        self.length += 1
        if self.back is None:
            self.back = [x]
        else:
            self.back.append(x)

        if self.front is None:
            self.front = [x]
        else:
            self.front.append(x)

    def dequeue(self):
        """Delete and return element at the front of the queue."""
        if len(self) == 0:
            raise ValueError('queue: cannot dequeue() empty queue')
        button = self.front.pop(0)
        self.back.pop(0)
        self.length = len(self.front)
        return button