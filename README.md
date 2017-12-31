# Aral beacon tracking project
- The beacons are on the boats sending their positions using UDP to the server
- The server is receiving positions from the beacons in one thread, while he's listening on clients connections.
- A GUI client made with Qt is able to connect to the server and receive all the positions. Those positions will be displayed dynamically on a map. You'll be able to see information of the boats when clicking on them.
- You can connect multiple clients to the server, this last is multi-threaded

![alt tag](https://raw.githubusercontent.com/Sydpy/Aral/master/Aral.png?token=AIEF5EPKPScEH4YnNzdCu1JmuIRiy9SEks5Ydr7uwA%3D%3D)
