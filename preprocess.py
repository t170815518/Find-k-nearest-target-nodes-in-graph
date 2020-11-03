import os
from Node import Node
from collections import defaultdict


def parse_graph(dataset):
    graph = defaultdict(lambda : Node())
    with open(os.path.join("dataset", dataset, "graph.txt"), 'r') as f:
        for line in f:
            if line[0] == '#':
                continue
            out_node, in_node = line.strip().split('\t')
            out_node = int(out_node)
            in_node = int(in_node)
            graph[out_node].adj_nodes.append(in_node)
    return graph


def parse_hospital(dataset, graph):
    k = 0
    with open(os.path.join("dataset", dataset, "hospital.txt"), 'r') as f:
        for line in f:
            if line[0] == '#':
                k = int(line.strip().split()[1])
                continue
            hospital_id = int(line.strip())
            graph[hospital_id].set_as_hospital(hospital_id)
    return k