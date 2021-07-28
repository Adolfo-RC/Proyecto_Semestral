import matplotlib.pyplot as plt
import networkx as nx
import os

if __name__ == '__main__':
    g = nx.DiGraph()

    g.add_edge("Cooperativa", "carlosmellado21")
    g.add_edge("carlosmellado21", "Party_Hack")
    g.add_edge("carlosmellado21", "CalcumilCaro")
    g.add_edge("soyvaldiviacl", "CalcumilCaro")

    pos = nx.spring_layout(g)

    nx.draw_networkx_nodes(g, pos, nodelist=["Cooperativa",
                                         "carlosmellado21",
                                         "Party_Hack"], node_color='#ffe6ff')

    nx.draw_networkx_nodes(g, pos, nodelist=["soyvaldiviacl"], node_color='#b3d9ff')

    nx.draw_networkx_nodes(g, pos, nodelist=["CalcumilCaro"], node_color=	'#ccccff')



    nx.draw_networkx_edges(g, pos, edgelist=[("Cooperativa", "carlosmellado21"),
                                             ], edge_color='#ffe6ff', width=7)
    nx.draw_networkx_edges(g, pos, edgelist=[("carlosmellado21", "Party_Hack"),
                                             ("carlosmellado21", "CalcumilCaro")], edge_color='#ffe6ff', width=4)
    nx.draw_networkx_edges(g, pos, edgelist=[("soyvaldiviacl", "CalcumilCaro")], edge_color='#b3d9ff', width=7)


    nx.draw_networkx_labels(g, pos, font_size=8)
    plt.axis("off")
    plt.savefig("Graph.png")
    plt.show()

