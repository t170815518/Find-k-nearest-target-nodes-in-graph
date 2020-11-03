from collections import defaultdict
from math import inf


class Node:
    hospitals = []

    def __init__(self):
        self.is_hospital = False
        self.adj_nodes = []
        self.top_k = []
        self.k = 0

    def set_as_hospital(self, id):
        self.is_hospital = True
        Node.hospitals.append(id)
