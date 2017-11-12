import matplotlib
matplotlib.use('Agg')
import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("resultado").T
case1= data[0]
case2=data[1]
plt.plot(case1)
plt.savefig("resultados_hw4.pdf")
plt.close()
plt.plot(case2)
plt.savefig("resultados1_hw4.pdf")
plt.close()

