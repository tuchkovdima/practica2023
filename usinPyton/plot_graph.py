import matplotlib.pyplot as plt

# Чтение данных из файла
data = []
with open("data.txt", "r") as file:
    for line in file:
        x, y = line.split()
        data.append((float(x), float(y)))

# Извлечение координат X и Y
x_coords, y_coords = zip(*data)

# Построение графика
plt.plot(x_coords, y_coords)
plt.xlabel("X")
plt.ylabel("Y")
plt.title("График")
plt.grid(True)
plt.show()
