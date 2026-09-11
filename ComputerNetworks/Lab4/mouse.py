import time, subprocess, random, sys

t_expt = 40
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