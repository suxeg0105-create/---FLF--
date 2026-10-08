import matplotlib.pyplot as plt
import pandas as pd
import io
import numpy as np

# Вставь сюда свои 3 столбца данных
data_str = """
"""

# Читаем данные
data = pd.read_csv(io.StringIO(data_str), delim_whitespace=True, header=None)
x = data[0]
y1 = data[1]  


# Строим графики
plt.figure(figsize=(10, 6))
plt.plot(x, y1, 'bo-', linewidth=2, label='График 1', markersize=4)



plt.xlabel('x')
plt.ylabel('y')
plt.title('Графики с точками пересечения')
plt.legend()
plt.grid(True, alpha=0.3)
plt.show()
