// Server-Client lottery application.
// Draw how the processes interact with each other
// (client-server and inside the server,  any diagram is fine) of the following exercise.
// ( we will discuss it before you write the code)
// Every client connect to the server
// and gives a number (1 to 90) of the lottery.
// The server creates a process for each client (called client-process).
// The client-process communicate to a internal process that collect all the numbers.
// At a specific time the extractor process choose randomly a number.
// The process-client that has  won receive  a IPC message from the extractor process,
// and sends a message to the client. The clients will print if they won or not.
