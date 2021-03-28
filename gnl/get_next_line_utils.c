/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:51:29 by magostin          #+#    #+#             */
/*   Updated: 2021/03/28 18:22:02 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_gnl_strlen(const char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*dest;

	if (!(dest = malloc(sizeof(char) * (ft_gnl_strlen(s1) + ft_gnl_strlen(s2) + 1))))
		return (0);
	i = -1;
	if (s1)
		while (s1[++i])
			dest[i] = s1[i];
	else
		i = 0;
	j = -1;
	if (s2)
		while (s2[++j])
			dest[i + j] = s2[j];
	else
		j = 0;
	dest[i + j] = 0;
	return (dest);
}

char	*ft_gnl_strchr(char *s, int c)
{
	int i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (s + i);
	return (NULL);
}

char	*ft_gnl_strndup(const char *str, int n)
{
	int		size;
	char	*dest;

	if (!str)
		return (NULL);
	if (!(dest = malloc((n + 1) * sizeof(char))))
		return (0);
	size = 0;
	while (str[size] && size < n)
	{
		dest[size] = str[size];
		size++;
	}
	dest[size] = 0;
	return (dest);
}

char	*ft_gnl_strdup(const char *str)
{
	int		size;
	char	*dest;

	size = 0;
	if (!str)
		return (NULL);
	if (*str == '\n')
		str++;
	while (str[size])
		size++;
	if (!(dest = malloc((size + 1) * sizeof(char))))
		return (0);
	size = 0;
	while (str[size])
	{
		dest[size] = str[size];
		size++;
	}
	dest[size] = 0;
	return (dest);
}
