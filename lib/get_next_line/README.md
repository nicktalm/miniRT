# Get_Next_Line project
## Instruction
This project is about programming a function that allows you to read content line by line. This is done by returning a line read from a file descriptor.
## Mandatory part
+ Repeated calls (e.g., using a loop) to your get_next_line() function should let you read the text file pointed to by the file descriptor, one line at a time.
+ Your function should return the line that was read.
+ If there is nothing else to read or if an error occurred, it should return NULL.
+ Make sure that your function works as expected both when reading a file and when reading from the standard input.
+ Please note that the returned line should include the terminating \n character, except if the end of file was reached and does not end with a \n character.
+ Your header file get_next_line.h must at least contain the prototype of the get_next_line() function.
+ Add all the helper functions you need in the get_next_line_utils.c file.
+ Because you will have to read files in get_next_line(), add this option to your compiler call: -D BUFFER_SIZE=nIt will define the buffer size for read(). The buffer size value will be modified by your peer-evaluators and the Moulinette in order to test your code.
+ You will compile your code as follows (a buffer size of 42 is used as an example): cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c
+ We consider that get_next_line() has an undefined behavior if the file pointed to by the file descriptor changed since the last call whereas read() didn’t reach the end of file.
+ We also consider that get_next_line() has an undefined behavior when reading a binary file. However, you can implement a logical way to handle this behavior if you want to.
## My Result
![5AD76DC8-E6BA-4597-B113-3365A9A9947A_4_5005_c](https://github.com/Lucabhm/Get_Next_Line/assets/144374574/5392f592-5d8f-4c00-8fa9-a36e88a38b05)
