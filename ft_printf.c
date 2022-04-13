/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneves-c <rneves-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:13:59 by rneves-c          #+#    #+#             */
/*   Updated: 2022/04/13 16:43:40 by rneves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

int		ft_putchar(char c);
int		ft_putstr(char *s);
void		ft_putnbr(long nb, int *total);
void    ft_checkconversion(char c, va_list *ap, int *total);
void ft_base(unsigned long nb, char *base, int size_base, int *total);

int ft_printf(const char *str, ...)
{
	int     i;
	int     total;
	va_list ap;
	char	*s;

	s = (char *)str;
	i = -1;
	total = 0;
	va_start(ap, str);

	while (s[++i] != '\0')
	{
		if (s[i] == '%' && s[i + 1] != '%')
		{
			ft_checkconversion(s[++i], &ap, &total);
			continue ;
		}
		total += ft_putchar(s[i]);
	}
	va_end(ap);
	
	return(total);
}

void    ft_checkconversion(char c, va_list *ap, int *total)
{
	if (c == 'c')
		*total += ft_putchar(va_arg(*ap, int));
	if (c == 's')
		*total += ft_putstr(va_arg(*ap, char *));
	if (c== 'p')
		ft_base(va_arg(*ap, unsigned long), "0123456789abcdef", 16, total);
	if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(*ap, int), total);
	if (c == 'u')
		ft_putnbr(va_arg(*ap, unsigned int), total);
	if (c == 'x')
		ft_base(va_arg(*ap, unsigned int), "0123456789abcdef", 16, total);
	if (c == 'X')
		ft_base(va_arg(*ap, unsigned int), "0123456789ABCDEF", 16, total);
	return;
}

int	ft_putchar(char c)
{
	return (write(1, &c, sizeof(char)));
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i += ft_putchar(s[i]);
	return (i);
}

void	ft_putnbr(long nb, int *total)
{
	char	c;

	if (nb < 0)
	{
		*total += write(1, "-", 1);
		nb = nb * -1;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10, total);
		c = nb % 10 + 48;
		*total += write(1, &c, sizeof(char));
	}
	else
	{
		c = nb + 48;
		*total += write(1, &c, sizeof(char));
	}
	return ;
}

void ft_base(unsigned long nb, char *base, int size_base, int *total)
{
	char	c;
	
	if (nb / size_base > size_base)
	{
		ft_base(nb/size_base, base, size_base, total);
		c = base[nb % size_base];
		*total += write(1, &c, sizeof(char));
	}
	else
	{
		c = base[nb];
		*total += write(1, &c, sizeof(char));
	}
	return ;
}

// int main()
// {
// 	char s[10] = "sttt";
// 	unsigned int p = 4294967295;
// 	unsigned long ptr = &p;
// 	int i = ft_printf("ola\n%s%u\n%p\n", s, p, ptr);
// 	printf("%p", ptr);
// 	printf("%i", i);
// 	return (0);
// }

#include <limits.h>

int main()
{
    char chr = 'D';
    char chr2 = 'o';
    char chr3 = 'B';
    char num = '0';
    char num2 = '1';
    char num3 = '3';
    char num4 = '0';
    int numero_pos = 13;
    int numero_neg = -13;
    char *short_string = "42 Lisboa";
    char *long_string = "Eu sou um aluno da 42 Lisboa!";
    int text_fake;
    int text_original;
    int hex_number_pos = 1;
    int hex_number_neg = -1;
    char *addr_null = NULL;
    
    printf("\n-------- ORIGINAL --------\n");
    text_original = printf("hello World\n");
    printf("%d\n", text_original);
    text_original = printf("Escapes -> \\\\\\");
    printf("\n");
    printf("%d\n", text_original);
    //%c
    text_original = printf("Texto -> %ci%cgo\nTexto -> %cea\n", chr, chr2, chr3);
    printf("%d\n", text_original);
    text_original = printf("Char Num -> %c%c%c%c\n", num, num2, num3, num4);
    printf("%d\n", text_original);
    //%%
    text_original = printf("%% Char -> %%%%\n");
    printf("%d\n", text_original);
    //%d and %i
    text_original = printf("Numero Inteiro (+) ->  %i\n", numero_pos);
    printf("%d\n", text_original);
    text_original = printf("Numero Inteiro (-) -> %d\n", numero_neg);
    printf("%d\n", text_original);
    //%u
    text_original = printf("Numero Inteiro Unsigned (+) -> %u\n", numero_pos);
    printf("%d\n", text_original);
    text_original = printf("Numero Inteiro Unsigned (-) -> %u\n", numero_neg);
    printf("%d\n", text_original);
    // //%s
    // text_original = printf("Short String -> %s\n", short_string);
    // printf("%d\n", text_original);
    // text_original = printf("Long String  -> %s\n", long_string);
    // printf("%d\n", text_original);
    // //%x
    // text_original = printf("Hex Number (Lower) (+) -> %x\n", hex_number_pos);
    // printf("%d\n", text_original);
    // text_original = printf("Hex Number (Lower) (-) -> %x\n", hex_number_neg);
    // printf("%d\n", text_original);
    // //%X
    // text_original = printf("Hex Number (Upper) (+) -> %X\n", hex_number_pos);
    // printf("%d\n", text_original);
    // text_original = printf("Hex Number (Upper) (-) -> %X\n", hex_number_neg);
    // printf("%d\n", text_original);
    //%p
    text_original = printf("Addres Pointer -> %p\n", LONG_MIN);
    printf("%d\n", text_original);
    text_original = printf("Addres Pointer (Null) -> %p\n", addr_null);
    printf("%d\n", text_original);
    text_original = printf("--------------------------\n");
    
    printf("---------- FAKE ----------\n");
    text_fake = ft_printf("hello World\n");
    ft_printf("%d\n", text_fake);
    text_fake = ft_printf("Escapes -> \\\\\\");
    ft_printf("\n");
    ft_printf("%d\n", text_fake);
    //%c
    text_fake = ft_printf("Texto -> %ci%cgo\nTexto -> %cea\n", chr, chr2, chr3);
    ft_printf("%d\n", text_fake);
    text_fake = ft_printf("Char Num -> %c%c%c%c\n", num, num2, num3, num4);
    ft_printf("%d\n", text_fake);
    //%%
    text_fake = ft_printf("%% Char -> %%%%\n");
    ft_printf("%d\n", text_fake);
    //%d and %i
    text_fake = ft_printf("Numero Inteiro (+) ->  %i\n", numero_pos);
    ft_printf("%d\n", text_fake);
    text_fake = ft_printf("Numero Inteiro (-) -> %d\n", numero_neg);
    ft_printf("%d\n", text_fake);
    //%u
    text_fake = ft_printf("Numero Inteiro Unsigned (+) -> %u\n", numero_pos);
    ft_printf("%d\n", text_fake);
    text_fake = ft_printf("Numero Inteiro Unsigned (-) -> %u\n", numero_neg);
    ft_printf("%d\n", text_fake);
    //%s
    text_fake = ft_printf("Short String -> %s\n", short_string);
    ft_printf("%d\n", text_fake);
    text_fake = ft_printf("Long String  -> %s\n", long_string);
    ft_printf("%d\n", text_fake);
    //%x
    text_fake = ft_printf("Hex Number (Lower) (+) -> %x\n", hex_number_pos);
    ft_printf("%d\n", text_fake);
    text_fake = ft_printf("Hex Number (Lower) (-) -> %x\n", hex_number_neg);
    ft_printf("%d\n", text_fake);
    //%X
    text_fake = ft_printf("Hex Number (Upper) (+) -> %X\n", hex_number_pos);
    ft_printf("%d\n", text_fake);
    text_fake = ft_printf("Hex Number (Upper) (-) -> %X\n", hex_number_neg);
    ft_printf("%d\n", text_fake);
    //%p
    text_fake = ft_printf("Addres Pointer -> %p\n", LONG_MIN);
    ft_printf("%d\n", text_fake);
    text_fake = ft_printf("Addres Pointer (Null) -> %p\n", addr_null);
    ft_printf("%d\n", text_fake);
	printf("--------------------------\n");   
}
