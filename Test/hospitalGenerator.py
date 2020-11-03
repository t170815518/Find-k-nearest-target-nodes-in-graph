from random import sample
import os


class HospitalGenerator:
    def __init__(self, dataset_path):
        """

        :param dataset_path: the path of the dataset
        """
        self.max_nodeID = -1
        with open(dataset_path, 'r') as f:
            for line in f:
                try:
                    out_node, in_node = line.strip().split('\t')
                    out_node = int(out_node)
                    in_node = int(in_node)
                except ValueError:
                    print("Ignored: ", line)
                    continue

                if out_node > self.max_nodeID:
                    self.max_nodeID = out_node
                if in_node > self.max_nodeID:
                    self.max_nodeID = in_node
        print("Finish loading the dataset file.")
        print("Number of nodes = {}".format(self.max_nodeID+1))
        assert self.max_nodeID >= 0
        self.nodes = [x for x in range(self.max_nodeID+1)]

    def generate(self, k=20, numbers=[1000]):
        """

        :param k: number of nearest hospitals
        :param numbers: number of hospitals you want to generate
        :return: no return value, but the hospital files will be created automatically
        """
        for number in numbers:
            if number < k:
                continue
            print("Generating hospitals ({})...".format(number))
            hospital_number = number
            hospitals = sample(self.nodes, hospital_number)
            with open(os.path.join("dataset", "roadNet-PA", "hospital.txt"), 'w+') as f:
                f.write("# {}\n".format(k))
                for hospital in hospitals:
                    f.write("{}\n".format(hospital))
            print("Finish generating hospitals ({})".format(number))


if __name__ == '__main__':
    g = HospitalGenerator("dataset/roadNet-PA/graph.txt")
    g.generate()
