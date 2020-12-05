

class Node:
    def __init__(self,tag,valid_bit = 1,next = None,previous = None):
        self.tag = tag
        self.valid_bit = valid_bit
        self.next = next
        self.previous = previous

    def set_next_pointer(self,next):
        self.next = next

    def set_previous_pointer(self,previous):
        self.previous = previous

    def get_tag(self):
        return self.tag

    def get_index(self):
        return self.index

    def get_next_pointer(self):
        return self.next

    def get_previous_pointer(self):
        return self.previous

