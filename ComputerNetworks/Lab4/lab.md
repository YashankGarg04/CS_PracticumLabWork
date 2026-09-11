# Network Namespaces

### Creating Network Namespaces
```
sudo ip netns add NetNsA \\add a Network Namespace
sudo ip link add macvlanA link eth0 type macvlan mode bridge \\add macvlan in a network namespace
sudo ip link set macvlanA netns NetNsA \\ Link a macvlan to a Network NameSpace
```
Now to Assign IP we use
```
sudo ip netns exec NetNsA ifconfig macvlanA 192.0.2.1/24
```
but in most mordern WSL this may not work, so we need to use below instead
```
sudo ip netns exec NetNsA ip addr add 192.0.2.1/24 dev macvlanA
sudo ip netns exec NetNsA ip link set macvlanA up
```
We have successfully created a Network Namespace and linked it to an IP and a Macvlan

### Ping From one NameSpace to another
```
sudo ip netns exec NetNsA ping -c 5 192.0.2.2
```
Here, ```-c``` is used to tell number of packets to send to another namespace if not provided it will keep on sending infinite number of ping untill not stopped
#### Delay
```
sudo ip netns exec NetNsA tc qdisc add dev macvlanA root netem delay 50ms
sudo ip netns exec NetNsA ping -c 5 192.0.2.2
```
This adds delay of 50ms between the ping packets
```
sudo ip netns exec NetNsA tc qdisc del dev macvlanA root \\to delete the delay from a NameSpace
```
Above we were adding Static Delay, How about Variable Delay
```
sudo ip netns exec NetNsA tc qdisc add dev macvlanA root netem delay 50ms 10ms
sudo ip netns exec NetNsA ping -c 5 192.0.2.2
```
Here, 50ms is the static time and 10ms here is the jitter of +-10 

### Configure Passwordless SSH
```
ssh-keygen -t rsa -b 4096 -N "" -f ~/.ssh/id_rsa
cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys
chmod 600 ~/.ssh/authorized_keys
```
To verify, run ```cat ~/.ssh/authorized_keys``` this will output the current generated public keys
#### Start the SSH Daemon in NameSpace
```
sudo mkdir -p /run/sshd
sudo ip netns exec NetNsA /usr/sbin/sshd -o PidFile=/run/sshd-NetNsA.pid
```
To verify run ```sudo ip netns exec NetNsA ps aux | grep sshd```

#### Start Packet Capture
```
sudo ip netns exec NetNsA wireshark -i macvlanA
```
#### Connect via SSH from NetNsB
Open another terminal and use below command
```
sudo ip netns exec NetNsB sudo -u breadjam ssh breadjam@192.0.2.1
```
by this we are connecting to the terminal while also monitoring with Wireshark
Now we can try commands like ```ls``` and ```pwd```

## Flow
A flow in a network is a sequence of related packets from one source end-point to one destination end-point. A flow may carry one or more files over a single TCP connection or a sequence of TCP connections.  There is no concurrence in one flow
### Elephant Flow
An elephant flow transfers a large amount of data, typically MB to GB in size. The
metric of interest is high throughout. A network has relatively few elephant flows.
### Mice Flow
Mice flows transfer a small amount of data, typically a few B to a few KB in size.
The metric of interest is low delay. A network has large numbers of mice flows.
#### Creating Elephant and Mouse Flows
```
dd if=/dev/urandom of=elephant.data bs=1M count=100
echo "This is a tiny file for the mice flow." > mouse.txt
```
To verify we need to run ```ls -lh elephant.data mouse.txt```
#### Test Difference Between Elephant and Mouse Flow in WireShark
Run Wireshark in ```Tab1```, then in ```tab2``` run:
```
sudo ip netns exec NetNsB sudo -u breadjam scp mouse.txt breadjam@192.0.2.1:~/
```
We will observe how fast the file was transfered and how small transactions it required in Wireshark
Now we will check for ```Elephant Flow```, in ```tab2``` again:
```
sudo ip netns exec NetNsB sudo -u breadjam scp elephant.data breadjam@192.0.2.1:~/
```
In Elephant flow we can see a lot of Transactions in Wireshark and it took a bit time to load also

