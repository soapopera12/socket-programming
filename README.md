# socket-programming
This repo has my code of Socket-Programming for course CSL605 - IIT Bhilai

• The client should request for the content of a file by providing the file name and server should send the
contents of that file to the client. For simplicity, assume that the file is a simple text file that contains a set of
words, with first word being your name and the last word being “EOF” (end-of-file). The server should look for
the file in the local directory, if the file is not there it should send back a message “404: File-not-Found”. After
receiving this message, the client should print an error message “File not found” and exit.

• If the file is present, the server should read the first line of the file, which contains your name, and send this
message to the client. After receiving your name, the client creates a local file (with a different file name from
the requested one) and sends a message Word_#1 to the server. This message indicates that the client is
requesting the first word. After receiving the message Word_#1, the server sends the first word after your
name to the client. The client writes this word to the local file after receiving it and sends the message
Word_#2 to request the next word and so on. This process continues until the client receives the keyword EOF.
Once the client receives the keyword EOF, it closes the local file after writing the last word to the file.

## How to run
cd to socket-prog-1 folder
make clean
make server
make client

## How to run
make sure to create the existing text file which needs to be copied