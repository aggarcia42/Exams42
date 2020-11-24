#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

//start s//
int ft_putchar(char c, int size)
{
    int len = 0;
    while (size-- > 0)
    {
        write(1, &c, 1);
        len++;
    }
    return len;
}
int ft_putstr(char *str, int size)
{
    int len = 0;
    while (size-- > 0)
    {
        write(1, &str[len], 1);
        len++;
    }
    return len;
}

int ft_str(char *format, int space, int zero, int len)
{
    int size = 0;
    if(!format)
    {
        format = "(null)";
    }
    while (format[size])
    {
        size++;
    }
    if(zero >= 0 && zero < size)
    {
        size = zero;
    }
    if(space > size)
    {
        len += ft_putchar(' ', space - size);
    }
    len += ft_putstr(format, size);
    return len;
}
//end s//

//start d//
char *ft_itoa(long int number)
{
    int len = 1;
    int aux = number;
    char *str;
    while (aux /= 10)
    {
        len++;
    }
    if(!(str = malloc(len + 1)))
    {
        return 0;
    }
    str[len] = '\0';
    while (len--)
    {
        str[len] = number % 10 + '0';
        number /= 10;
    }
    return str;
}

int ft_int(long int format, int space, int zero, int len)
{
    int size = 0;
    int negative = 0;
    if(negative < 0)
    {
        format *= -1;
        space += -1;
        negative = -1;
    }
    char *str = ft_itoa(format);
    while (str[size])
    {
        size++;
    }
    if(zero == 0 && format == 0)
    {
        size = zero;
    }
    if(space > size)
    {
        if(size >= zero)
        {
            space = space - size;
        }
        else if(size < zero)
        {
            space = space - zero;
	}
	    len += ft_putchar(' ', space);
    }
    if(negative == -1)
    {
        len+= ft_putchar('-', 1);
    }
    len += ft_putchar('0', zero -size);
    len += ft_putstr(str, size);
    return len;
}
//end d//

//start x//
char *ft_unsigneditoa(unsigned int number)
{
    int len = 1;
    unsigned int aux = number;
    char *str;
    while (aux /= 16)
    {
        len++;
    }
    if(!(str = malloc(len + 1)))
    {
        return 0;
    }
    str[len] = '\0';
    while (len--)
    {
        if((number % 16) < 10)
        {
            str[len] = number % 16 + '0';   
        }
        else if((number % 16) > 9)
        {
            str[len] = number % 16 + 'W';
        }
        number /= 16;
    }
    return str;
}

int ft_hex(unsigned int format, int space, int zero, int len)
{
    int size = 0;
    char *str = ft_unsigneditoa(format);
    while (str[size])
    {
        size++;
    }
    if(zero == 0 && format == 0)
    {
        size = zero;
    }
    if(space > size)
    {
        if(size >= zero)
        {
            space = space - size;
        }
        else if(size < zero)
        {
            space = space - zero;
        }
    }
    len += ft_putchar(' ', space);
    len += ft_putchar('0', zero -size);
    len += ft_putstr(str, size);
    return len;
}
//end x//


int ft_printf(const char *format, ...)
{
    int len = 0;
    int space = 0;
    int zero = -1;
    va_list ap;
    va_start(ap, format);

    while (*format != '\0')
    {
        if(*format == '%')
        {
            space = 0;
            zero = -1;
            format++;
            while(*format >= '0' && *format <= '9')
            {
                space = space * 10 + (*format - '0');
                format++;
            }
            if(*format == '.')
            {
                zero = 0;
                format++;
                while(*format >= '0' && *format <= '9')
                {
                    zero = zero * 10 + (*format - '0');
                    format++;
                }
            }
            if(*format == 's')
            {
                len = ft_str(va_arg(ap, char *), space, zero, len);
                format++;
            }
            else if(*format == 'd')
            {
                len = ft_int((long int)va_arg(ap, int), space, zero, len);
                format++;
            }
            else if(*format == 'x')
            {
                len = ft_hex(va_arg(ap, unsigned int), space, zero, len);
                format++;
            }
        }
        else
        {
            write(1, format, 1);
            format++;
            len++;
        }
    }
    

    va_end(ap);
    return len;
}

/*
int main(void)
{
    ft_printf("%10.2s\n", "toto");
    ft_printf("Magic %s is %5d\n", "number", 42);
    ft_printf("Hexadecimal for %d is %x\n", 42, 42);
    
    char *str = NULL;
    printf("\n___TEST %%.2s___\n");
	printf("No original - %d\n", ft_printf("|%.2s|\n", str));
	printf("Original - %d\n", printf("|%.2s|\n", str));

}
*/
int main(void)
{
	char *str = NULL;
	printf("\n\nTEST %%s\n\n");
	printf("\n___TEST %%s___\n");
	printf("No original - %d\n", ft_printf("|%s|\n", str));
	printf("Original - %d\n", printf("|%s|\n", str));

	printf("\n___TEST %%ss___\n");
	printf("No original - %d\n", ft_printf("|%ss|\n", str));
	printf("Original - %d\n", printf("|%ss|\n", str));

	printf("\n___TEST %%20s___\n");
	printf("No original - %d\n", ft_printf("|%20s|\n", str));
	printf("Original - %d\n", printf("|%20s|\n", str));

	printf("\n___TEST %%2s___\n");
	printf("No original - %d\n", ft_printf("|%2s|\n", str));
	printf("Original - %d\n", printf("|%2s|\n", str));

	printf("\n___TEST %%.2s___\n");
	printf("No original - %d\n", ft_printf("|%.2s|\n", str));
	printf("Original - %d\n", printf("|%.2s|\n", str));

	printf("\n___TEST %%.20s___\n");
	printf("No original - %d\n", ft_printf("|%.20s|\n", str));
	printf("Original - %d\n", printf("|%.20s|\n", str));

	printf("\n___TEST %%2.20s___\n");
	printf("No original - %d\n", ft_printf("|%2.20s|\n", str));
	printf("Original - %d\n", printf("|%2.20s|\n", str));

	printf("\n___TEST %%22.20s___\n");
	printf("No original - %d\n", ft_printf("|%22.20s|\n", str));
	printf("Original - %d\n", printf("|%22.20s|\n", str));

	printf("\n___TEST %%12.20s___\n");
	printf("No original - %d\n", ft_printf("|%12.20s|\n", str));
	printf("Original - %d\n", printf("|%12.20s|\n", str));

	printf("\n___TEST %%12.s___\n");
	printf("No original - %d\n", ft_printf("|%12.s|\n", str));
	printf("Original - %d\n", printf("|%12.s|\n", str));

	printf("\n___TEST %%.s___\n");
	printf("No original - %d\n", ft_printf("|%.s|\n", str));
	printf("Original - %d\n", printf("|%.s|\n", str));

	printf("\n___TEST %%20.s___\n");
	printf("No original - %d\n", ft_printf("|%20.s|\n", str));
	printf("Original - %d\n", printf("|%20.s|\n", str));

	printf("\n___TEST %%2.s___\n");
	printf("No original - %d\n", ft_printf("|%2.s|\n", str));
	printf("Original - %d\n", printf("|%2.s|\n", str));



	printf("\n\nTEST %%d\n\n");
	int num = 0;
	printf("\n___TEST %%d___\n");
	printf("No original - %d\n", ft_printf("|%d|\n", num));
	printf("Original - %d\n", printf("|%d|\n", num));

	printf("\n___TEST %%dd___\n");
	printf("No original - %d\n", ft_printf("|%dd|\n", num));
	printf("Original - %d\n", printf("|%dd|\n", num));

	printf("\n___TEST %%20d___\n");
	printf("No original - %d\n", ft_printf("|%20d|\n", num));
	printf("Original - %d\n", printf("|%20d|\n", num));

	printf("\n___TEST %%2d___\n");
	printf("No original - %d\n", ft_printf("|%2d|\n", num));
	printf("Original - %d\n", printf("|%2d|\n", num));

	printf("\n___TEST %%.2d___\n");
	printf("No original - %d\n", ft_printf("|%.2d|\n", num));
	printf("Original - %d\n", printf("|%.2d|\n", num));

	printf("\n___TEST %%.20d___\n");
	printf("No original - %d\n", ft_printf("|%.20d|\n", num));
	printf("Original - %d\n", printf("|%.20d|\n", num));

	printf("\n___TEST %%2.20s___\n");
	printf("No original - %d\n", ft_printf("|%2.20d|\n", num));
	printf("Original - %d\n", printf("|%2.20d|\n", num));

	printf("\n___TEST %%22.20d___\n");
	printf("No original - %d\n", ft_printf("|%22.20d|\n", num));
	printf("Original - %d\n", printf("|%22.20d|\n", num));

	printf("\n___TEST %%12.20d___\n");
	printf("No original - %d\n", ft_printf("|%12.20d|\n", num));
	printf("Original - %d\n", printf("|%12.20d|\n", num));

	printf("\n___TEST %%12.d___\n");
	printf("No original - %d\n", ft_printf("|%12.d|\n", num));
	printf("Original - %d\n", printf("|%12.d|\n", num));

	printf("\n___TEST %%.d___\n");
	printf("No original - %d\n", ft_printf("|%.d|\n", num));
	printf("Original - %d\n", printf("|%.d|\n", num));

	printf("\n___TEST %%20.d___\n");
	printf("No original - %d\n", ft_printf("|%20.d|\n", num));
	printf("Original - %d\n", printf("|%20.d|\n", num));

	printf("\n___TEST %%2.d___\n");
	printf("No original - %d\n", ft_printf("|%2.d|\n", num));
	printf("Original - %d\n", printf("|%2.d|\n", num));

	printf("\n\nTEST %%x\n\n");
	unsigned int un = 0;
	printf("\n___TEST %%x___\n");
	printf("No original - %d\n", ft_printf("|%x|\n", un));
	printf("Original - %d\n", printf("|%x|\n", un));

	printf("\n___TEST %%xx___\n");
	printf("No original - %d\n", ft_printf("|%xx|\n", un));
	printf("Original - %d\n", printf("|%xx|\n", un));

	printf("\n___TEST %%20x___\n");
	printf("No original - %d\n", ft_printf("|%20x|\n", un));
	printf("Original - %d\n", printf("|%20x|\n", un));

	printf("\n___TEST %%2x___\n");
	printf("No original - %d\n", ft_printf("|%2x|\n", un));
	printf("Original - %d\n", printf("|%2x|\n", un));

	printf("\n___TEST %%.2x___\n");
	printf("No original - %d\n", ft_printf("|%.2x|\n", un));
	printf("Original - %d\n", printf("|%.2x|\n", un));

	printf("\n___TEST %%.20x___\n");
	printf("No original - %d\n", ft_printf("|%.20x|\n", un));
	printf("Original - %d\n", printf("|%.20x|\n", un));

	printf("\n___TEST %%2.20x___\n");
	printf("No original - %d\n", ft_printf("|%2.20x|\n", un));
	printf("Original - %d\n", printf("|%2.20x|\n", un));

	printf("\n___TEST %%22.20x___\n");
	printf("No original - %d\n", ft_printf("|%22.20x|\n", un));
	printf("Original - %d\n", printf("|%22.20x|\n", un));

	printf("\n___TEST %%12.20x___\n");
	printf("No original - %d\n", ft_printf("|%12.20x|\n", un));
	printf("Original - %d\n", printf("|%12.20x|\n", un));

	printf("\n___TEST %%12.x___\n");
	printf("No original - %d\n", ft_printf("|%12.x|\n", un));
	printf("Original - %d\n", printf("|%12.x|\n", un));

	printf("\n___TEST %%.x___\n");
	printf("No original - %d\n", ft_printf("|%.x|\n", un));
	printf("Original - %d\n", printf("|%.x|\n", un));

	printf("\n___TEST %%20.x___\n");
	printf("No original - %d\n", ft_printf("|%20.x|\n", un));
	printf("Original - %d\n", printf("|%20.x|\n", un));

	printf("\n___TEST %%2.x___\n");
	printf("No original - %d\n", ft_printf("|%2.x|\n", un));
	printf("Original - %d\n", printf("|%2.x|\n", un));
    printf("\n");
    printf("No original - %d\n",ft_printf("%d and %s and %x\n", 42, "cuarenta", 42));
    printf("Original - %d\n",printf("%d and %s and %x\n", 42, "cuarenta", 42));

	return (0);
}
