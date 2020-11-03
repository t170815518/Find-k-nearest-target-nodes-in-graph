from numpy.random import normal
from random import randint
from collections import defaultdict
import os


class RandomGraphGenerator:
    def __init__(self, node_size, average_degree):
        if isinstance(node_size, list):
            assert len(node_size) == len(average_degree)
            self.node_size = node_size
            self.average_degree = average_degree
        else:
            assert isinstance(node_size, int) and (isinstance(average_degree, float) or (isinstance(average_degree, int)))
            # convert to list to make it iterable
            self.node_size = [node_size]
            self.average_degree = [average_degree]

    def execute(self):
        for size, degree in zip(self.node_size, self.average_degree):
            print("generate {} {}".format(size, degree))
            adjacency_list = self.generate(size, degree)
            self.export("{}size_{}degree.txt".format(size, degree), adjacency_list)
            print("Completes!")

    def generate(self, size, degree):
        adjacency_list = defaultdict(lambda: [])
        for i in range(size):
            node_degree = normal(degree, 0.5)
            while len(adjacency_list[i]) < node_degree:
                adj_node = randint(0, size-1)
                if adj_node not in adjacency_list[i] and adj_node != i:
                    adjacency_list[i].append(adj_node)
                    adjacency_list[adj_node].append(i)
        return adjacency_list

    def export(self, file_name, adjacency_list):
        with open(os.path.join("dataset", "random_graph", "graph.txt"), 'w+') as f:
            for i in adjacency_list.keys():
                try:
                    for adj_node in adjacency_list[i]:
                        f.write("{}\t{}\n".format(i, adj_node))
                except TypeError:  # for empty list
                    continue


if __name__ == '__main__':
    g = RandomGraphGenerator(node_size=[10], average_degree=[1])
    g.execute()
