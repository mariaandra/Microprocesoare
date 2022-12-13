import matplotlib.pyplot as plt
import pyqtgraph as pg
import numpy as np


def main():
    file = open("values.txt", "r")
    num_list = [float(num) for num in file.read().split()]
    counter = len(num_list)
    max_val = max(num_list)
    min_val = min(num_list)
    med_val = (max_val + min_val) / 2;

    x = np.arange(counter)
    y = num_list

    vector_sec = np.vectorize(np.float_)
    vector_hz = np.vectorize(np.float_)

    sec = vector_sec(x)
    hz = vector_hz(y)

    # am luat range-ul pentru valoare medie ca fiind [med_val - 0.7, med_val + 0.7]
    upper = med_val + 0.7
    lower = med_val - 0.7

    supper = np.ma.masked_where(hz < upper, hz)  # prag mare -> verde
    slower = np.ma.masked_where(hz > lower, hz)  # prag mic -> portocaliu
    smiddle = np.ma.masked_where((hz < lower) | (hz > upper), hz)  # prag mediu -> albastru

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
