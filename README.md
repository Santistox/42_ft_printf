## ft_printf📚

#### Ecole 42 project (21 school) 

------

The purpose of this project is to create own ft_printf function to use it in future projects instead of putstr and putnbr.

Programmed by rlintill ([@elisawolia](https://github.com/elisawolia)) and mnidoque ([@santistox](https://github.com/elisawolia))

------

##### Project in developing.

------

**Usage:**

1. Compile project by use command:

```
$ make
```

2. Clean object files

```
$ make clean
```

3. Clean object files and lbift.a file

```
$ make fclean
```
------

**Example**

Code is:

```c
int i;

i = 42;
ft_printf("21 + 21 = %d\n", i);
```

Output is:

`21 + 21 = 42`

------

**Helpful links:**

1. [Format Specification Syntax: printf and wprintf Functions](https://docs.microsoft.com/en-us/cpp/c-runtime-library/format-specification-syntax-printf-and-wprintf-functions?view=vs-2019)
2. [Printf source code](https://sourceware.org/git/?p=glibc.git;a=blob;f=stdio-common/printf_fp.c;h=e9ff1684ce2c3157429016a3dc0a87e901ef9fdc;hb=3321010338384ecdc6633a8b032bb0ed6aa9b19a)
3. [For flag f IEEE754](https://www.softelectro.ru/ieee754.html)
