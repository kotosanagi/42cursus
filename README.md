# 42cursus
Record of study at 42Tokyo

The following functions are used to create these projects. 
 
-Basic system call functions such as "write" and "read" 

-Basic library functions such as "malloc" and "va_arg"


## ft_mini_ls
This program is a reproduction of Linux command "ls -1tr".

## ft_printf
This program is a reproduction of "printf".
It also applies the output method by conversion for two or more arguments.  It can also output strings, decimal and hexadecimal numbers.
In addition, this function outputs like the original function even if a flag such as minus, width, or precision is specified.

Output example...

ft_printf("hello [%-8.5s]\n", "kotoyori shota");
>> hello [kotoy   ]

ft_printf("decimal: [%*d]\n", 10, 12345678);
>> decimal: [  12345678]

ft_printf("hexadecimal: [%*x]\n", 10, 12345678);
>> hexadecimal: [    bc614e]

## get_next_line
Calling this function will read from the file specified by the file descriptor.  
It also reads the contents of the file line by line and stores it in a "char *" type argument.

## libft
Reproduced the functions of more than 40 libc libraries.
