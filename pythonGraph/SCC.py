import networkx as nx
import matplotlib.pyplot as plt

if __name__ == '__main__':

    x = ["ManuRiosG",
         "indignadobiobio",
         "mendygaete",
         "HMomberg",
         "OctavaBioBio"]
    G = nx.DiGraph()
    G.add_edge(x[0], x[1])
    G.add_edge(x[1], x[2])
    G.add_edge(x[2], x[3])
    G.add_edge(x[3], x[4])
    G.add_edge(x[4], x[0])

    nx.draw(G, node_color='#b3d9ff', with_labels=True)
    plt.show()
    plt.savefig("SCC.png")
