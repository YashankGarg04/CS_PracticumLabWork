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