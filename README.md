# winsockTCPMessageFraming

**A small message framing library for C++**

A library to deal with the message Framing problem in tcp it has 2 methods a safe send method which sends the size of a message before the message is sent then the actual message and a recieve method which recieves from the safe send method.
These practices ensure that the right thing is read from the tcp buffer the whole time and uses length based encoding to achieve this.

This was made as something for myself to deal with an issue I encountered when making a messaging app and so likely will not be updated

Requirements 

Winsock2


