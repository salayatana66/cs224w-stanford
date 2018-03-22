#!/opt/conda/bin/python3

import numpy as np
import matplotlib.pyplot as plt
plt.switch_backend('agg')
import pandas as pd

df = {}
df["EReny"] = pd.read_csv("/mnt/notebooks/ERenyDegs.txt",sep='\t')
df["Small"] = pd.read_csv("/mnt/notebooks/SmallWorldDeg.txt",sep='\t')
df["Cosmo"] = pd.read_csv("/mnt/notebooks/CosmologyDeg.txt",sep='\t')

plt.figure(figsize=(12,9))
plt.xlabel("Degree (log-scale)")
plt.ylabel("Count (log-scale)")
plt.plot(np.log10(df["EReny"].OutDegree), np.log10(df["EReny"].Count),label="EReny",color="black")
plt.plot(np.log10(df["Small"].OutDegree), np.log10(df["Small"].Count),'b',label="SmallWorld")
plt.plot(np.log10(df["Cosmo"].OutDegree), np.log10(df["Cosmo"].Count),'orange',label="Cosmology")
plt.legend()
plt.savefig("q1-degree-distro.png")

print("Computing Degree Distribution")
for v in df.values():
    v["OutExcessDeg"] = v["OutDegree"]-1
    v["q"] = v.Count*v.OutDegree
    total_excess = np.sum(v["q"])
    v["ExcessDistro"] = v["q"]/total_excess

plt.figure(figsize=(12,9))
plt.xlabel("Degree (log-scale)")
plt.ylabel("Excess Distro (log-scale)")
plt.plot(np.log10(df["EReny"].OutDegree), np.log10(df["EReny"].ExcessDistro),label="EReny",color="black")
plt.plot(np.log10(df["Small"].OutDegree), np.log10(df["Small"].ExcessDistro),'b',label="SmallWorld")
plt.plot(np.log10(df["Cosmo"].OutDegree), np.log10(df["Cosmo"].ExcessDistro),'orange',label="Cosmology")
plt.legend()
plt.savefig("q1-excess-degree-distro.png")

for k,v in df.items():
    total_count = np.sum(v["Count"])
    total_excess = np.sum(v["q"])
    print("For {} expected degree {}, expected excess degree {}".format(
          k, np.sum(v.Count*v.OutDegree)/total_count,
          np.sum(v.OutExcessDeg*v.ExcessDistro)))
