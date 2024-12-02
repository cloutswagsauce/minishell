/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:01:50 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/11/13 14:05:30 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_safe(char	**ptr)
{
	if (*ptr && ptr)
	{
		free(*ptr);
		*ptr = 0;
	}
}

static char	*get_line_from_stash(char *stash)
{
	char	*new_line_pos;
	char	*line;
	size_t	len;

	if (!*stash && !stash)
		return (0);
	new_line_pos = ft_memchr(stash, '\n', ft_strlen(stash));
	if (new_line_pos)
	{
		len = new_line_pos - stash + 1;
		line = (char *) malloc(sizeof(char) * ((int)len + 1));
		if (!line)
		{
			free_safe(&stash);
			return (0);
		}
		ft_memmove(line, stash, len);
		line[len] = '\0';
	}
	else
		line = ft_strdup(stash);
	return (line);
}

static char	*update_stash(char	*stash)
{
	char	*new_line_pos;
	char	*new_stash;

	if (!stash)
		return (0);
	new_line_pos = ft_memchr(stash, '\n', ft_strlen(stash));
	if (!new_line_pos)
	{
		free_safe(&stash);
		return (0);
	}
	new_stash = ft_strdup(new_line_pos + 1);
	if (!new_stash)
	{
		free_safe(&stash);
		return (0);
	}
	free_safe(&stash);
	return (new_stash);
}

static char	*stash_join_buffer(char	*stash, char *buffer)
{
	char	*temp;

	if (!buffer)
		return (0);
	if (stash)
		temp = ft_strjoin(stash, buffer);
	else
		temp = ft_strjoin("", buffer);
	if (!temp)
	{
		free_safe(&stash);
		return (0);
	}
	free_safe(&stash);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		stash = stash_join_buffer(stash, buffer);
		if (ft_memchr(stash, '\n', ft_strlen(stash)) || bytes_read == 0)
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (!stash || !*stash || bytes_read == -1)
	{
		free_safe(&stash);
		return (0);
	}
	line = get_line_from_stash(stash);
	stash = update_stash(stash);
	return (line);
}
