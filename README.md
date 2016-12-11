## ------- Cryptography using EVP  -------

This is an implementation of cryptographic functions using the EVP library provided by OpenSSL.

Details of EVP are available on the following link
https://www.openssl.org/docs/man1.0.2/crypto/evp.html


##AES Encryption : 
Implementation for using AES to perform encryption as well as decryption of clear text is is available in aes-implementation.c. This example performs AES encryption with a 128-bit key in CBC mode.

gcc -o aes aes-implementation.c
./aes


##DES Encryption : 
Implementation for using DES to perform encryption as well as decryption of clear text is is available in des-implementation.c. This example performs DES encryption in CBC mode.

gcc -o des des-implementation.c
./des


##Encryption over network 
Implementation for sending encrypted data over network (along with decryption on the other side) is present in the folder "encryption-on-network".
It contains a client.c file and a server.c file. The client and server are communicating over TCP socket.

#Steps
Clear text is provided to the client.
Client decrypts the clear text.
Clients sends the encrypted text to the server.
Server receives the encrypted text.
Server decrypts the text and displays is on screen. 

#Start Server
gcc -o server server.c
./server

#Start client
gcc -o client client.c
./client <ip address for the serer> <port number>
./client 127.0.0.1 7788

