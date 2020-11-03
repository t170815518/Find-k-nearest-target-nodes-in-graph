from Node import Node
import os
from math import inf


def improved_BFS(graph, args, is_print=True):
    node_num = max(graph.keys()) + 1
    hospitals = Node.hospitals[:]
    hospitals_layer_queue = {}
    is_visited_by_hospital = {}

    # initialize
    for hospital in hospitals:
        hospitals_layer_queue[hospital] = [hospital]
        is_visited_by_hospital[hospital] = [False] * node_num
        is_visited_by_hospital[hospital][hospital] = True
        graph[hospital].k = 1
        graph[hospital].top_k.append((hospital, 0))

    distance = 1
    while hospitals:
        for hospital in hospitals:
            layer_nodes = hospitals_layer_queue[hospital][:]
            if not layer_nodes:
                hospitals.remove(hospital)
            hospitals_layer_queue[hospital] = []  # prepare for next layer
            for layer_node in layer_nodes:
                for adj_node in graph[layer_node].adj_nodes:
                    if is_visited_by_hospital[hospital][adj_node] == False:
                        is_visited_by_hospital[hospital][adj_node] = True
                        is_occur = False
                        max_i = -1
                        max_distance = -inf
                        for i, (index, distance_) in enumerate(graph[adj_node].top_k):
                            if index == hospital:
                                is_occur = True
                                if distance < distance_:
                                    graph[adj_node].top_k[i] = (hospital, distance)
                                break
                            if max_distance < distance_:
                                max_i = i
                                max_distance = distance_

                        if is_occur == False:
                            if graph[adj_node].k < args.k:
                                graph[adj_node].top_k.append((hospital, distance))
                                graph[adj_node].k += 1
                                hospitals_layer_queue[hospital].append(adj_node)
                            elif distance < max_distance:
                                graph[adj_node].top_k[max_i] = (hospital, distance)
                                hospitals_layer_queue[hospital].append(adj_node)

        distance += 1

    if is_print:
        with open(os.path.join("dataset", args.dataset, "output_mBFS.txt"), "w+") as f:
            for index, node in graph.items():
                f.write(str(index) + ": ")
                for hospital, distance in node.top_k:
                    f.write("{}(d={})\t".format(hospital, distance))
                f.write("\n")