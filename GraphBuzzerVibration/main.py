import PyQt5.QtWidgets as QtWidgets
import pyqtgraph as pg
import sys
import serial
from pyqtgraph.Qt import QtCore


class MainWindow(QtWidgets.QMainWindow):

    def __init__(self, *args, **kwargs):
        super(MainWindow, self).__init__(*args, **kwargs)

        # graph
        self.graphWidget = pg.PlotWidget()
        self.setCentralWidget(self.graphWidget)
        self.graphWidget.setBackground((245, 245, 245))
        self.graphWidget.setTitle("\nGetting values\n", color="black", size="18px123")

        styles = {'color': 'black', 'font-size': '12px'}
        self.graphWidget.setLabel('left', 'Frequency (V)', **styles)
        self.graphWidget.setLabel('bottom', 'Time (s)', **styles)
        self.graphWidget.showGrid(x=True, y=True)
        self.graphWidget.setYRange(0, 3.3, padding=0)  # range la Hz (0,3.3)

        # frecventa si secundele ar veni aici
        self.x = list(range(10))
        self.y = [0] * 10

        # pen
        pen = pg.mkPen(color=(0, 204, 0), width=2)
        self.data_line = self.graphWidget.plot(self.x, self.y, pen=pen)

        # port
        self.serialPort = serial.Serial(
            port="COM5", baudrate=115200, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE
        )

        # timer
        self.timer = QtCore.QTimer()
        self.timer.setInterval(30)
        self.timer.timeout.connect(self.update_plot_data)
        self.timer.start()


    def update_plot_data(self):
        if self.serialPort.in_waiting > 0:
            f = open("values.txt", "a")
            serialString = self.serialPort.readline()
            linedec = serialString.decode("Ascii")
            linefloat = float(linedec)

            self.x = self.x[1:]  # Remove the first y element.
            self.x.append(self.x[-1] + 1)  # Add a new value 1 higher than the last.

            self.y = self.y[1:]  # Remove the first
            self.y.append(linefloat)  # Add a new random value.

            f.write(f"{linefloat}\n")
            print(linefloat)
            self.data_line.setData(self.x, self.y)  # Update


def main():
    with open('values.txt', 'w'):
        pass
    app = QtWidgets.QApplication(sys.argv)
    main = MainWindow()
    main.show()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
