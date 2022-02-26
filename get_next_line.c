/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalazhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 17:47:58 by aalazhar          #+#    #+#             */
/*   Updated: 2021/12/12 18:03:28 by aalazhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	char		*buff;
	char		*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	str = ft_read(fd, str, buff);
	if (!str)
		return (NULL);
	line = get_first_line(str);
	str = get_rest(str);
	return (line);
}
