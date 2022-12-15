import matplotlib.pyplot as plt
import pyqtgraph as pg
import numpy as np


def main():
    file = open("values.txt", "r")
    num_list = [float(num) for num in file.read().split()]
    counter = len(num_list)
    max_val = max(num_list)
    min_val = min(num_list)
    med_val = (max_val + min_val) / 2

    x = np.arange(counter)
    y = num_list

    vector_sec = np.vectorize(np.float_)
    vector_v = np.vectorize(np.float_)

    sec = vector_sec(x)
    v = vector_v(y)

    # am luat range-ul pentru valoare medie ca fiind [med_val - 0.7, med_val + 0.7]
    print(med_val)
    upper = med_val + 0.4
    lower = med_val - 1.4
    print(upper)
    print(lower)

    supper = np.ma.masked_where(v < upper, v)  # prag mare -> verde
    slower = np.ma.masked_where(v > lower, v)  # prag mic -> portocaliu
    smiddle = np.ma.masked_where((v < lower) | (v > upper), v)  # prag mediu -> albastru

    fig, ax = plt.subplots()
    ax.plot(sec, smiddle, sec, slower, sec, supper)
    plt.grid(linestyle='--')
    font = {'family': 'serif', 'color': 'darkred', 'size': 16}
    plt.title("Results", fontdict=font)
    plt.xlabel("Index", fontdict=font)
    plt.ylabel("Frequency", fontdict=font)
    plt.show()


if __name__ == '__main__':
    main()
