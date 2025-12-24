import matplotlib.pyplot as plt

x = []
y = []

path = "E:\\new_proj\\assets\\data\\hit_marker.txt"
with open(path, 'r') as f:
    for line in f:
        try:
            parts = line.split()
            if len(parts) == 2:
                x.append(float(parts[0]))
                y.append(float(parts[1]))
        except ValueError:
            continue

plt.figure(figsize=(10, 6))
plt.scatter(x, y, s=1, color='blue', alpha=0.5)

plt.title("Winning Throw Trajectories")
plt.xlabel("Horizontal Power (Velocity X)")
plt.ylabel("Vertical Power (Velocity Y)")
plt.grid(True)
plt.show()