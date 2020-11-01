from random import sample


class HospitalGenerator:
    def __init__(self, dataset_path):
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

    def generate(self, k=5, numbers=[1, 5, 10, 25, 50, 100, 200, 300, 500, 1000, 5000]):
        for number in numbers:
            print("Generating hospitals ({})...".format(number))
            hospital_number = number
            hospitals = sample(self.nodes, hospital_number)
            with open("{}_hospital.txt".format(number), 'w+') as f:
                f.write("# {}\n".format(k))
                for hospital in hospitals:
                    f.write("{}\n".format(hospital))
            print("Finish generating hospitals ({})".format(number))


if __name__ == '__main__':
    g = HospitalGenerator("dataset/roadNet-PA.txt")
    g.generate()
