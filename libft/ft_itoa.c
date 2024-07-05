/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 01:38:40 by yechakim          #+#    #+#             */
/*   Updated: 2023/10/06 10:52:34 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static void	ft_strswap(char *a, char *b)
{
	char	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	ft_strrev(char *str)
{
	int	head;
	int	tail;

	head = 0;
	tail = ft_strlen(str) - 1;
	while (head < tail)
	{
		ft_strswap((str + head), (str + tail));
		head++;
		tail--;
	}
}

static int	fill_digits(char *dst, int base, int n)
{
	int	len;

	len = 0;
	if (n == 0)
	{
		*dst = '0';
		return (1);
	}
	while (n >= 0)
	{
		*(dst + len) = (n % base) + '0';
		len++;
		if (n < base)
			break ;
		n /= base;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*ret;
	char	stack[12];
	int		len;

	ft_memset(stack, 0, 12);
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = fill_digits(stack, 10, ft_abs(n));
	if (n < 0)
		len++;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	ft_strrev(stack);
	if (n > 0)
	{
		ft_strlcpy(ret, stack, len +1);
		return (ret);
	}
	*ret = '-';
	ft_strlcpy((ret + 1), stack, len);
	*(ret + len) = 0;
	return (ret);
}
