/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 07:09:02 by akhellad          #+#    #+#             */
/*   Updated: 2023/01/24 17:26:02 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_includes/get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*s1;

	s1 = (char *)s;
	i = 0;
	while (s1[i])
	{
		if (s1[i] == (char)c)
			return (s1 + i);
		i ++;
	}
	if (s1[i] == (char)c)
		return (s1 + i);
	return (0);
}

void	ft_bzero(void *str, size_t n)
{
	size_t	i;
	char	*str1;

	str1 = (char *)str;
	i = 0;
	while (i < n)
	{
		str1[i] = '\0';
		i ++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(size * nmemb);
	if (!ptr)
		return (ptr);
	ft_bzero (ptr, size * nmemb);
	return (ptr);
}



