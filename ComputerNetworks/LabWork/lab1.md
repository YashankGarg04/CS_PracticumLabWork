# Lab1
- Networks are complex with many pieces
- Different Layers Handling different tasks
#### Example
end to end transfer of person plus baggage
- ticket (purchase)
- baggage (check)
- gates (load)
- runway takeoff
- airplane routing
on the other half
- airplane routing
- runway landing
- gates (unload)
- baggage (claim)
- ticket (complain if not recieved)

#### Each layer implements a service

### Socket Programming
To talk to the transport layer through application layer we must understand Socket Programming
#### socket
socket is a analogus door between application and transport layer
- it opens a service between layers like UDP, TCP 
- should take care of both what is written into layer and what is taken out of it

### with TCP
- client must contact server
