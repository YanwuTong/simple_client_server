# simple_client_server

* after build the connection, the client will send a integer with length smaller than 128.
* once the server received the integer, it will add the sum of every single digit number for the integer and send back the result
* the server will take the sum result as the new input and recursively calculate the sum until the result is one digit
* the client will keep receiving result until the result is one digit