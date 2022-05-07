# Project Description
by Kushagra Rode, 2020CS10354
& Akarsh Jain, 2020CS10318

The name of our game is SURVIVE IITD
This is a 2 player game based on IIT Delhi Campus made using SDL in C++. In this game you will find various kinds of tasks which you can do. But, why should you even do tasks ?? The reason for doing tasks is to maintain 3 most important parameters for your survival in IITD, your Health, CG and Money. Apart from this you can also enable powerups and then collide with the opponent to decrease their health. Further, there are various features like a Minimap , an Info sheet displaying the tasks left to be done and also you could even send an emoji to your opponent while you are playing.

# How to Run
For playing this game, one of the two players has to become a server and the other, a client. You also have to connect through Wi-fi Network.
Also, make sure you enter the **IP of the server(serv_ip variable)** in both main.cpp and main_client.cpp files before running.
## For Server 
Run the following two commands after setting IP
```
make server
./yourserv.out
```
## For Client
```
make client
./yourcli.out
```


# References Used

1. For SDL,
   - https://lazyfoo.net/tutorials/SDL/index.php
   - YouTube playlist: https://www.youtube.com/watch?v=QQzAHcojEKg&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx

2. For making Map,
   - Using `Tiled` software

3. For Sockets and Networking,
   - https://www.geeksforgeeks.org/socket-programming-cc/
   - https://beej.us/guide/bgnet/html/


