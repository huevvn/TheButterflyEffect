import pyqtgraph as pg
import pyqtgraph.opengl as gl
from pyqtgraph.Qt import QtWidgets, QtCore
import numpy as np
import pandas as pd
import sys
import os

# === Qt app ===
app = QtWidgets.QApplication(sys.argv)

# === OpenGL window ===
w = gl.GLViewWidget()
w.show()
w.setCameraPosition(distance=160, elevation=10)

# === Key press override (press "S" to save screenshot) ===
# def keyPressEvent(self, event):
#     if event.key() == QtCore.Qt.Key_S:
#         # use grabFramebuffer() for raw OpenGL pixels, or grab() for Qt rendering
#         self.grabFramebuffer().save("shot.png")
#         print("✅ Saved shot.png")
#     else:
#         super(gl.GLViewWidget, self).keyPressEvent(event)
#
# # attach our override
# w.keyPressEvent = keyPressEvent.__get__(w, gl.GLViewWidget)

# === Grid ===
g = gl.GLGridItem()
g.scale(5, 5, 5)
g.translate(0, 0, -10)   # lowered grid
w.addItem(g)

# === Load CSV data ===
script_dir = os.path.dirname(__file__)
csv_file = sys.argv[1]
csv_path = os.path.join(script_dir, csv_file)
method = os.path.splitext(csv_file)[0].split("_")[-1]
w.setWindowTitle("Lorenz Attractor | Real-time | " + method)
print("Reading Plotted Data ...")

df = pd.read_csv(csv_path)
points = df[["x", "y", "z"]].to_numpy()
n_points = len(points)

# === Precompute gradient colors (violet -> yellow) ===
colors = np.zeros((n_points, 4))
violet = np.array([139/255, 92/255, 246/255, 1.0])
yellow = np.array([1.0, 1.0, 1.0, 1.0])

for i in range(n_points):
    t = i / (n_points - 1)
    colors[i] = (1 - t) * violet + t * yellow

# === Line plot (initially empty) ===
pts = np.empty((0, 3))
clr = np.empty((0, 4))
plt = gl.GLLinePlotItem(
    pos=pts,
    color=clr,
    width=2,
    antialias=True
)
w.addItem(plt)

# === Animation state ===
frame_idx = 0
def update():
    global frame_idx, pts, clr
    if frame_idx < n_points:
        pts = np.vstack([pts, points[frame_idx]])
        clr = np.vstack([clr, colors[frame_idx]])
        frame_idx += 1
        plt.setData(pos=pts, color=clr)
    else:
        timer.stop()

# === Timer for animation ===
timer = QtCore.QTimer()
timer.timeout.connect(update)
timer.start(0)  # (lower = faster)

# === Start Qt event loop ===
if __name__ == "__main__":
    sys.exit(app.exec())
