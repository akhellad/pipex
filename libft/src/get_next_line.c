/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 07:05:20 by akhellad          #+#    #+#             */
/*   Updated: 2023/06/01 15:29:52 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define BUFFER_SIZE 1024

static int	read_character(char *c)
{
	return (read(0, c, 1));
}

static int	expand_buffer(char **buffer, int buffer_size, int *buffer_capacity)
{
	char	*temp;
	int		i;

	if (buffer_size >= *buffer_capacity)
	{
		*buffer_capacity += BUFFER_SIZE;
		temp = (char *)malloc(*buffer_capacity * sizeof(char));
		if (temp == NULL)
			return (-1);
		i = -1;
        while (++i < buffer_size)
            temp[i] = (*buffer)[i];
        free(*buffer);
        *buffer = temp;
    }
    return 0;
}

static int fill_buffer(char **buffer, int *buffer_size, int *buffer_capacity)
{
    char c;
    int r;
    r = read_character(&c);

    while (r > 0 && c != '\n' && c != '\0')
    {
        if (expand_buffer(buffer, *buffer_size, buffer_capacity) == -1)
        {
            free(*buffer);
            return (-1);
        }
        (*buffer)[*buffer_size] = c;
        (*buffer_size)++;
        r = read_character(&c);
    }

    return r;
}

static void append_newline(char **buffer, int *buffer_size)
{
    (*buffer)[*buffer_size] = '\n';
    (*buffer_size)++;
    (*buffer)[*buffer_size] = '\0';
}

int get_next_line(char **line)
{
    char *buffer;
    int buffer_size;
    int buffer_capacity;
    int r;

    buffer = NULL;
    buffer_size = 0;
    buffer_capacity = 0;

    r = fill_buffer(&buffer, &buffer_size, &buffer_capacity);

    if (r <= 0)
        free(buffer);
    else
        append_newline(&buffer, &buffer_size);

    *line = buffer;
    return (r);
}