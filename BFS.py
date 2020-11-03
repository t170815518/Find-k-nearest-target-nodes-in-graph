import os
from memory_profiler import profile

# @profile()
def BFS(graph, args, is_print=True):
    for index in graph.keys():
        paths = BFS_for_single_node(graph, index, args.k)
        if is_print:
            with open(os.path.join("dataset", args.dataset, "output_BFS.txt"), "a+") as f:
                for path in paths:
                    f.write('->'.join([str(x) for x in path]) + '\n')
                print("Processing {}".format(index))


def BFS_for_single_node(graph, index, k):
    max_node_id = max(graph.keys())
    is_visited = [False] * (max_node_id + 1)
    searching_parent = [None] * (max_node_id + 1)
    queue = []
    queue.append(index)
    is_visited[index] = True
    current_k = 0
    shortest_paths = []

    while queue and current_k < k:
        node_id = queue.pop()
        # is_visited[index] = True
        if graph[node_id].is_hospital == True:
            current_k += 1
            # back-tracing for the shortest path
            tree_node = node_id
            shortest_path = [tree_node]
            while searching_parent[tree_node] != None:
                shortest_path.insert(0, searching_parent[tree_node])
                tree_node = searching_parent[tree_node]
            shortest_paths.append(shortest_path)
        for adj_node in graph[node_id].adj_nodes:
            if is_visited[adj_node] == False:
                queue.append(adj_node)
                is_visited[adj_node] = True
                searching_parent[adj_node] = node_id

    return shortest_paths



