# Lab Report
## Computer Networks
### T26049 Yashank
#### Question
1) Write a script elephant that transfers a very large file between the two hosts using
FTP. If necessary, the script repeats the transfer back-to-back so that the total
duration, Texpt is tens of seconds.
2) Write a script mouse that transfers a very small file between the two hosts using scp.
The script repeats the transfer with a random inter-file gap drawn from an
exponential distribution so that the total duration is Texpt. Each script records the start
and end times and the file size of each transfer.
3) Write a control script that runs the elephant script and Nm mouse scripts in parallel.
Repeat for several values of Nm. Plot elephant throughput Xe vs. Nm for different
mouse file sizes.
4) Submit your findings in the form of a report with the codes attached. You will
receive extra credit on the basis of correctness and completeness of your findings for
the optional exercise.
### Solution
#### ```elephant.py :```
```
import time, subprocess

t_expt = 10
start_time = time.time()
total_bytes = 0

while time.time() - start_time < t_expt:
    cmd = ["curl", "-s", "ftp://192.0.2.1:2121/elephant.data", "-o", "/dev/null", "-w", "%{size_download}"]
    result = subprocess.run(cmd, capture_output=True, text=True)
    try:
        total_bytes += int(result.stdout.strip())
    except ValueError:
        pass
        
actual_time = time.time() - start_time

# Safeguard: if actual_time is somehow 0, force it to a small decimal
if actual_time <= 0:
    actual_time = 0.001
    
throughput_mbps = (total_bytes * 8) / (actual_time * 1000000)
print(throughput_mbps)
```
- ```t_expt``` here is the target duration for the experiment, where the while loop checks whether the time is over or not
- Here, we are loading an elephant flow via a TCP network to achieve full bandwidth saturation and fill the router queues.
- After the transfer finishes, it calculates the actual network speed (throughput) in Mbps and prints it so control.py can read it.

#### ```mouse.py :```
```
import time, subprocess, random, sys

t_expt = 10
mouse_file = sys.argv[1]
start_time = time.time()

with open("mouse_log.txt", "a") as f:
    while time.time() - start_time < t_expt:
        gap = random.expovariate(1.0 / 0.5) 
        time.sleep(gap)
        
        t_start = time.time()
        subprocess.run(["scp", "-q", "-o", "StrictHostKeyChecking=no", mouse_file, "breadjam@192.0.2.1:/tmp/"])
        t_end = time.time()
        
        f.write(f"{t_start},{t_end},{mouse_file}\n")
```
- We also have a target duration here ```t_expt``` to match the elephant flow
- ```mouse.py``` receives the target filename ```mouse.txt``` as a command-line argument from ```control.py```
- We use ```random.expovariate``` to create random sleep gaps between transfers, which mimics real-world unpredictable network traffic
- We know that mouse flows usually take very little time to transfer, so this logs the exact start and end timestamps of each tiny burst
#### ```control.py :```
```
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
```
- This master script runs the experiment by launching the single elephant script and Nm copies of the mouse script simultaneously
- It repeats the test for 0, 2, and 5 parallel mice flows
- Finally, it collects the throughput outputs and plots them into a graph using ```matplotlib```
#### Observations
- As the number of competing mice flows increases, the network speed (throughput) of the elephant flow decreases
- This proves TCP Congestion Control works. When the random mice flows cause congestion and saturate the network buffers, the elephant flow detects the packet delays and automatically scales back its transmission speed to share the bandwidth fairly
![throughput-plot](https://i.ibb.co/TBQ1Df07/throughput-plot.png)