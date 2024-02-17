import pandas as pd
import matplotlib.pyplot as plt

# Read the data from the CSV file
data = pd.read_csv('p2.csv', header=None, names=['x', 'y'])

# Plotting the data
plt.plot(data['x'], data['y'])
plt.xlabel('X axis')
plt.ylabel('Y axis')
plt.title('Plot of Data')
plt.show()
