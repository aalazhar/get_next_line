/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalazhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:45:50 by aalazhar          #+#    #+#             */
/*   Updated: 2021/12/13 11:47:54 by aalazhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_first_line(char *s)
{
	int		i;
	char	*line;

	i = 0;
	if (!s[i])
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_rest(char *s)
{
	int		i;
	int		j;
	char	*rline;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	if (s[i] == '\0')
	{
		free(s);
		return (NULL);
	}
	rline = malloc(ft_strlen(s) - i + 1);
	if (!rline)
		return (NULL);
	while (s[i])
		rline[j++] = s[i++];
	rline[j] = '\0';
	free(s);
	return (rline);
}

char	*ft_read(int fd, char *str, char *buff)
{
	char	*tmp;
	int		i;

	i = 1;
	while (!ft_strchr(str, '\n') && i != 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[i] = '\0';
		tmp = str;
		if (!tmp)
		{
			tmp = malloc(1);
			tmp[0] = '\0';
		}
		str = ft_strjoin(tmp, buff);
		free(tmp);
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buff;
	static char	*str[1024];

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	str[fd] = ft_read(fd, str[fd], buff);
	if (!str[fd])
		return (NULL);
	line = get_first_line(str[fd]);
	str[fd] = get_rest(str[fd]);
	return (line);
}
