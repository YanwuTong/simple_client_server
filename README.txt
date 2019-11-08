//README.txt


for UDP client & server
* The client will first receive an input, it will recognize that is there any non-integer in the input, if so. it will reject the input and send a message to the user. Also it will take a look of the length the input, if it is larger than 128. it will also reject the input 
* When the client get a valid input, it will send the input to the server, the server will calculate the sum of the input and send back to the client. if the sum is more than one digit, it will recursivly add the number together and send the result to client
* The client will keep receiving the result until it get one digit result, then it will close


for TCP client & server
* The client will first receive an input. It will check the length the input, if it is larger than 128. it will also reject the input
* Then the client will send the the input to the server. the server will check whether the input is all integer, if not, it will send a message to client that the input in not valid
* if the input is valid, it will keep calculate the sum of the integer list and send the result to the client until the result is one digit. once it send the last result, the server will close
* Client will keep receiving results until the server is close 