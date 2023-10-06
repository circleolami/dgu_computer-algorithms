import matplotlib.pyplot as plt

sizes, compareA, datamoveA, compareB, datamoveB, compareC, datamoveC = [], [], [], [], [], [], []

with open("results.txt", "r") as f:
    for line in f:
        n, ca, dma, cb, dmb, cc, dmc = map(int, line.split())
        sizes.append(n)
        compareA.append(ca)
        datamoveA.append(dma)
        compareB.append(cb)
        datamoveB.append(dmb)
        compareC.append(cc)
        datamoveC.append(dmc)

plt.figure(figsize=(12, 6))
# plt.plot(sizes, compareA, label="Compare A")
# plt.plot(sizes, datamoveA, label="Data Move A")
# plt.plot(sizes, compareB, label="Compare B")
# plt.plot(sizes, datamoveB, label="Data Move B")
plt.plot(sizes, compareC, label="Compare C")
plt.plot(sizes, datamoveC, label="Data Move C")
plt.xlabel("Array Size")
plt.ylabel("Operations Count")
plt.legend()
plt.grid(True)
plt.title("CountSort Operation Counts by Data Type")
plt.show()
