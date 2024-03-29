/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvercell <hvercell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:38:55 by hvercell          #+#    #+#             */
/*   Updated: 2023/01/24 21:38:49 by hvercell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	ssize_t		size;
	ssize_t		rest_s;
	static char	rest[BUFFER_SIZE + 1] = {0};
	char		buf[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	rest_s = ft_memchr_i(rest, '\n');
	if (rest_s != -1)
		ft_extract_line_from_rest(&line, rest, rest_s);
	else
	{
		while (ft_memchr_i(line, '\n') == -1)
		{
			line = ft_strnjoin(line, rest, ft_strlen(rest) + 1);
			ft_memset(rest, '\0', BUFFER_SIZE + 1);
			ft_memset(buf, '\0', BUFFER_SIZE + 1);
			size = read(fd, buf, BUFFER_SIZE);
			if (size == 0 || size == -1)
				return (ft_handle_end_of_file(size, &line));
			buf[size] = '\0';
			ft_append_buf_to_line(buf, &line, rest);
		}
	}
	return (line);
}

void	ft_extract_line_from_rest(char **line, char *rest, ssize_t rest_s)
{
	*line = ft_strnjoin(*line, rest, rest_s + 1);
	ft_strlcpy(rest, rest + rest_s + 1, ft_strlen(rest + rest_s) + 1);
}

//
char	*ft_handle_end_of_file(ssize_t size, char **line)
{
	if (size == 0 && *line[0] != '\0')
		return (*line);
	else
		return (free(*line), NULL);
}

void	ft_append_buf_to_line(char *buf, char **line, char *rest)
{
	ssize_t	buf_s;

	if (ft_memchr_i(buf, '\n') == -1)
	{
		*line = ft_strnjoin(*line, buf, ft_strlen(buf) + 1);
		ft_memset(buf, '\0', BUFFER_SIZE + 1);
	}
	else
	{
		buf_s = ft_memchr_i(buf, '\n');
		*line = ft_strnjoin(*line, buf, buf_s + 1);
		ft_memset(rest, '\0', BUFFER_SIZE + 1);
		ft_strlcpy(rest, buf + buf_s + 1, ft_strlen(buf + buf_s) + 1);
	}
}
