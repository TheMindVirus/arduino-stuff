#pip3 install -U numpy
#pip3 install matplotlib
import numpy as np
import matplotlib.pyplot as mpl

TITLE = "Activation Methods"
    
def main():
    title = "Activation Methods - Redline"
    mpl.style.use("dark_background")

    x = np.linspace(0.0, 10.0, 100)
    y = []

    y_Redline = method()
    y_Redline.label = "Redline"
    y_Redline.method = [x, ((x % 2) > 1) + 1]
    y_Redline.colour = (1.0, 0.0, 0.2)
    y_Redline.thickness = 5
    y.append(y_Redline)

    scope(x, y, title)
    
    mpl.tight_layout(pad = 1.0)
    mpl.show(block = False)

class method:
    def __init__(self):
        pass

def scope(x, y, title = TITLE + "- Scope"):
    figure, axes = mpl.subplots(1, 1, num = title)
    x_ticks = np.arange(0.0, 10.1, 1.0)
    y_ticks = np.arange(0.0, 2.1, 1.0)

    axes.set_title(title)
    axes.axis("square")
    axes.set(xlabel = "Time (ps)", ylabel = "Voltage (V)")
    axes.set(xlim = [-0.1, 10.1], ylim = [-0.1, 2.1])
    axes.xaxis.set_ticks(x_ticks)
    axes.yaxis.set_ticks(y_ticks)

    labels = []
    for i in range(0, len(y)):
        labels.append(y[i].label)
        thickness = y[i].thickness if hasattr(y[i], "thickness") else 1
        axes.plot(*(y[i].method), color = y[i].colour, linewidth = thickness)

    axes.grid(alpha = 0.5)

if __name__ == "__main__":
    main()
