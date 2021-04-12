# 42cursus
Record of study at 42Tokyo

The following functions are used to create these projects. 
 
-Basic system call functions such as "write" and "read".

-Basic library functions such as "malloc", "va_arg" and more...


## ft_mini_ls
This program is a reproduction of Linux command "ls -1tr".

For example...

Now, you are on directory like below.
```
drwxr-xr-x@ 2 koto  staff  64  1  8 07:53 dir01
drwxr-xr-x@ 2 koto  staff  64  1  8 07:55 dir02
drwxr-xr-x@ 2 koto  staff  64  1  8 08:00 dir03
-rw-r--r--  1 koto  staff   0  1  8 07:48 file01
-rw-r--r--  1 koto  staff   0  1  8 07:51 file02
-rw-r--r--  1 koto  staff   0  1  8 07:52 file03
```

Then,you execute "ft_mini_ls" file, it works as follows. 
This is the same behavior as'ls'.

```
file01
file02
file03
dir01
dir02
dir03
```

## ft_printf
This program is a reproduction of "printf".
It also applies the output method by conversion for two or more arguments.  It can also output strings, decimal and hexadecimal numbers.
In addition, this function outputs like the original function even if a flag such as minus, width, or precision is specified.

Output example...(␣ is whitespace)

ft_printf("hello [%-8.5s]\n", "kotoyori shota");

```hello [kotoy␣␣␣]```

ft_printf("decimal: [%*d]\n", 10, 12345678);

```decimal: [␣␣12345678]```

ft_printf("hexadecimal: [%*x]\n", 10, 12345678);

```hexadecimal: [␣␣␣␣bc614e]```

## get_next_line
Calling this function will read from the file specified by the file descriptor.  
It also reads the contents of the file line by line and stores it in a "char *" type argument.

When read the file successfully, this function returns 1.

If the reading is finished, this function returns 0.

If the read fails, this function returns -1.

For example, there is the following file "testfile".

```
this is first line.
this is second line.
this is third line.
```

Prepare the following main.c file.

```c
#include <stdio.h>
#include “get_next_line.h”

int main(){
    char *line;
    int ret;
    int fd;

    fd = open(“testfile”, O_RDONLY);
    while ((ret = get_next_line(fd, &line)) > 0)
        printf("ret:%d, line:%s\n", ret, line);
    printf("ret:%d, line:%s\n", ret, line);
    close(fd);
    return 0;
}
```

Compile by specifying the buffer size as shown below.

This is the size of the buffer that will be stored when reading.

```gcc -D BUFFERSIZE=1000 get_next_line.c get_next_line_utils.c main```

When you execute the "a.out" file, the output will be as follows.

```
ret:1, line: this is first line.
ret:1, line: this is second line.
ret:0, line: this is third line.
```
As you can see from this output, each time of the "get_next_line" function is called, each line of file is stored in variable "line".


## libft
Reproduced the functions of more than 40 libc libraries.

for example...
```
strlen
atoi
strlcpy
strlcat
memmove
strdup
```
and more functions....

