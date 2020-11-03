import argparse
import preprocess
import memory_profiler as mp
from BFS import BFS
import time
from mBFS import mBFS


# parse the command line argument
parser = argparse.ArgumentParser(description="please specify the algorithm and dataset.")
parser.add_argument("-a", default="bfs", type=str, choices=["mbfs"], required=False,
                    help="The algorithm used.", dest="algorithm")
parser.add_argument("-d", default="random_graph", type=str, required=False,
                    help="The directory contained in dataset.", dest="dataset")
args = parser.parse_args()

# load graph and hospital information
graph = preprocess.parse_graph(args.dataset)
args.k = preprocess.parse_hospital(args.dataset, graph)

start_mem = mp.memory_usage(max_usage=True)
start_time = time.time()
if args.algorithm == "mbfs":
    mBFS(graph, args)
    # res = mp.memory_usage(proc=(mBFS, [graph, args, False]), max_usage=True, retval=True)

end_time = time.time()
print(-start_time + end_time)

# print('start mem', start_mem)
# print('max mem', res[0])
# print('used mem', res[0]-start_mem)
# print('fun output', res[1])