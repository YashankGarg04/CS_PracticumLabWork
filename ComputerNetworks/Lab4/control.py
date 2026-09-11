import subprocess
import matplotlib.pyplot as plt

N_m_values = [0, 2, 5]
throughputs = []

for N_m in N_m_values:
    print(f"Testing with N_m = {N_m} mice...")
    mice = [subprocess.Popen(["python3", "mouse.py", "mouse.txt"]) for _ in range(N_m)]
    elephant = subprocess.Popen(["python3", "elephant.py"], stdout=subprocess.PIPE, text=True)
    
    out, _ = elephant.communicate()
    try:
        throughputs.append(float(out.strip()))
    except ValueError:
        throughputs.append(0.0)
    
    for m in mice:
        m.wait()
        
plt.plot(N_m_values, throughputs, marker='o', linestyle='-', color='r')
plt.xlabel("Number of Mice Flows (Nm)")
plt.ylabel("Elephant Throughput (Mbps)")
plt.title("Impact of Mice Flows on Elephant Throughput")
plt.grid(True)
plt.savefig("throughput_plot.png")
print("Graph saved as throughput_plot.png")