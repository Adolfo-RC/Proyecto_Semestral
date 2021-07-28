import matplotlib.pyplot as plt


if __name__ == '__main__':
    labels = "Izquierda", "Derecha", "Centro", "Libertario", "Mixto"
    sizes = [11.797, 49.0253, 6.7729, 18.3812,14.0236]    
    fig1, ax1 = plt.subplots()
    ax1.pie(sizes, labels=labels, autopct='%2.2f%%', shadow=True)
    ax1.axis('equal')
    plt.title("Tendencias políticas", fontweight="bold")
    plt.savefig("Tendencias.png")
    plt.show()

