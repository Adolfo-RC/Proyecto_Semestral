x = [ 0.281262,
      1.29458,
     1.549,
     1.5122,
     0.60332]

labels = ["Insertar","Influencia", "Influenciados", "Influyentes", "Kosaraju"]

import matplotlib.pyplot as plt

plt.style.use("seaborn-bright")
plt.title("Tiempo consumido", fontweight='bold')
plt.bar(labels[0], x[0], color='b', width=0.3)
plt.bar(labels[1], x[1], color='g',width=0.3)
plt.bar(labels[2], x[2], color='y',width=0.3)
plt.bar(labels[3], x[3], color='r',width=0.3)
plt.bar(labels[4], x[4], color='k',width=0.3)
#plt.grid(False)
plt.xlabel("Operación")
plt.ylabel("Tiempo (s)")

plt.show()
plt.savefig("Time.png")
