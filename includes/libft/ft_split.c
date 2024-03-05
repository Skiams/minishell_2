/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:23:25 by ahayon            #+#    #+#             */
/*   Updated: 2024/02/28 15:13:53 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "ft_strlen.c"

static int	ft_nstr(char const *s, char c)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] != c)
			n++;
		while (s[i] != c && s[i])
			i++;
		if (s[i])
			i++;
	}
	return (n);
}

static void	*ft_free(char **d)
{
	int	i;

	i = 0;
	while (d[i])
		free(d[i++]);
	free(d);
	return (0x0);
}
size_t	ft_strlenc(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] == c)
		i++;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char *s, char c)
{
	int		nstr;
	int		i;
	char	**d;

	if (!s)
		return (0x0);
	nstr = ft_nstr(s, c);
	d = malloc(sizeof(char *) * (nstr + 1));
	if (!d)
		return (0x0);
	d[nstr] = 0;
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			d[i] = ft_substr(s, 0, ft_strlenc(s, c));
			if (!d[i++])
				return (ft_free(d));
			s += ft_strlenc(s, c);
		}
		else
			s++;
	}
	return (d);
}


// #include "ft_substr.c"


// char	*ft_substr(char *s, size_t start, size_t len)
// {
// 	char			*subs;
// 	size_t			i;
// 	size_t			s_size;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	s_size = ft_strlen(s);
// 	if (start >= s_size)
// 		len = 0;
// 	if (len > s_size - start)
// 		len = s_size - start;
// 	subs = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!subs)
// 		return (NULL);
// 	while (i < len)
// 	{
// 		subs[i] = s[start];
// 		start++;
// 		i++;
// 	}
// 	subs[i] = '\0';
// 	return (subs);
// }

// #include <unistd.h>

// int	ft_nstr(char *s, char c)
// {
// 	int	i;
// 	int	n;

// 	n = 0;
// 	i = 0;
// 	while (s[i] == c && s[i])
// 		i++;
// 	while (s[i])
// 	{
// 		if (s[i] != c)
// 			n++;
// 		while (s[i] != c && s[i])
// 		{
// 			if (!(s[i] >= 48 && s[i] <= 57))
// 			{
// 				write(2, "Error\n", 6);
// 				return (0);
// 			}
// 			i++;
// 		}
// 		if (s[i])
// 			i++;
// 	}
// 	return (n);
// }
#include <stdio.h>


int	main()
{
 	unsigned int i;
 	int j;
 	char c = ' ';
 	char s[] = "  lorem ipsum dolor sit amet, consecteturs";
	char s1[] = "l 48 -5343 42";
 	char **strsplit;

 	i = 0;
	ft_split(s, ' ');
 	/*strsplit = ft_split(s1, c);
 	while (strsplit[i])
 	{
 		j = 0;
 		while (strsplit[i][j])
		{
 			printf("%c", strsplit[i][j]);
 			j++;
 		}
 		printf("\n");
 		i++;
	}*/
}
