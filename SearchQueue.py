class SearchQueue:
    def __init__(self):
        self.elements = []

    def push_in(self, element):
        self.elements.append(element)

    def pop_front(self):
        return self.elements.pop()
