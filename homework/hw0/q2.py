#!/usr/bin/python3

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("nodeDegrees.txt",sep='\t')

print(df.head())

plt.figure(figsize=(12,9))
plt.xlabel("OutDegree (log-scale)")
plt.ylabel("Count (log-scale)")
plt.plot(np.log10(df.OutDegree), np.log10(df.Count))
plt.savefig("q2.png")

fit = np.polyfit(np.log10(df.OutDegree), np.log10(df.Count), deg = 1)
fitted = fit[1] + fit[0]*np.log10(df.OutDegree)
plt.figure(figsize=(12,9))
plt.xlabel("OutDegree (log-scale)")
plt.ylabel("Count (log-scale)")
plt.plot(np.log10(df.OutDegree), np.log10(df.Count))
plt.plot(np.log10(df.OutDegree), fitted, 'r-')
plt.savefig("q2-fit.png")
print(fit)
