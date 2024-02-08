#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h> // Add this header for va_list and va_arg

int print_char(int c)
{
    return write(1, &c, 1);
}

int print_str(char *str)
{
    int count = 0;
    while (*str)
    {
        print_char((int)*str);
        count++;
        str++;
    }
    return count;
}

int print_digit(long n, int base)
{
    int count = 0;
    char *symbols = "0123456789abcdef"; // Corrected symbols string
    if (n < 0)
    {
        write(1, "-", 1);
        count = print_digit(-n, base) + 1;
    }
    else if (n < base)
    {
        count = print_char(symbols[n]);
    }
    else
    {
        count = print_digit(n / base, base);
        count += print_digit(n % base, base);
    }
    return count;
}

int print_format(char specifier, va_list ap)
{
    int count = 0;
    if (specifier == 'c')
    {
        count = print_char(va_arg(ap, int));
    }
    else if (specifier == 's')
    {
        count = print_str(va_arg(ap, char *));
    }
    else if (specifier == 'd')
    {
        count = print_digit(va_arg(ap, int), 10);
    }
    else if (specifier == 'x')
    {
        count = print_digit(va_arg(ap, unsigned int), 16);
    }
    else
    {
        count = write(1, &specifier, 1);
    }
    return count;
}

int my_printf(const char *format, ...)
{
    va_list ap;
    int count = 0;

    va_start(ap, format);
    while (*format != '\0')
    {
        if (*format == '%')
        {
            count += print_format(*(++format), ap);
        }
        else
        {
            count += write(1, format, 1);
        }
        format++;
    }
    va_end(ap);
    return count;
}

int main()
{
    int count;

    count = my_printf("Hello %s\n", "John");
    my_printf("The chars written are %d\n", count);
    count = my_printf("%x\n", 42);
    my_printf("The chars written are %d\n", count);
    return 0;
}

