#include <unistd.h>
#include <stdarg.h>

int ft_putchar(char c)
{
    return (write(1, &c, 1));
}

int ft_putstr(char *s)
{
    int len;

    len = 0;
    if (!s)
        return (ft_putstr("(null)"));
    while (*s)
    {
        write(1, s++, 1);
        len++;
    }
    return (len);
}

void	ft_putnbr(int n, int *i)
{
	long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		*i += ft_putchar('-');
		nbr *= -1;
	}
	if (nbr > 9)
	{
		ft_putnbr(nbr / 10, i);
		ft_putnbr(nbr % 10, i);
	}
	else
		*i += ft_putchar(nbr + '0');
}

int	print_hex(unsigned int n)
{
	int		i;
	char	*hexa;

	i = 0;
	hexa = "0123456789abcdef";
	if (n >= 16)
		i += print_hex(n / 16);
	i += ft_putchar(hexa[n % 16]);
	return (i);
}

int ft_printf(const char *str, ... )
{
    va_list ap;
    int len;
    int i;

    va_start(ap, str);
    len = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == '%' && str[i + 1])
        {
            if (str[i + 1] == 's')
            {
                len += ft_putstr(va_arg(ap, char *));
                i++;
            }
            else if (str[i + 1] == 'x')
            {
                len += print_hex(va_arg(ap, unsigned int));
                i++;   
            }
            else if (str[i + 1] == 'd')
            {
                ft_putnbr(va_arg(ap, int), &len);
                i++;
            }
            else
                len += write(1, &str[i], 1);
        }
        else
            len += write(1, &str[i], 1);
        i++;
    }
    va_end(ap);
    return (len);
}
