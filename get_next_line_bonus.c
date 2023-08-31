/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:58:28 by azaghlou          #+#    #+#             */
/*   Updated: 2022/11/17 15:50:01 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*therest(char *str)
{
	char	*ptr;
	int		j;
	int		i;

	j = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (0);
	}
	i++;
	ptr = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!ptr)
		return (0);
	while (str[i])
		ptr[j++] = str[i++];
	ptr[j] = '\0';
	free(str);
	return (ptr);
}

char	*srchnl(char *str)
{
	int		i;
	char	*aa;

	i = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	aa = malloc(sizeof(char) * (i + 2));
	if (!aa)
		return (NULL);
	i = 0;
	while (str[i])
	{
		aa[i] = str[i];
		i++;
		if (str[i - 1] == '\n')
			break ;
	}
	aa[i] = '\0';
	return (aa);
}

char	*reader(int fd, char *str)
{
	char	*buffer;
	int		i;

	i = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (!ft_strchr(str, '\n') && i != 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(str);
			free(buffer);
			return (0);
		}
		buffer[i] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*sttc[OPEN_MAX];

	if ((fd < 0) || (BUFFER_SIZE <= 0) || fd == 1 || fd == 2)
		return (0);
	sttc[fd] = reader(fd, sttc[fd]);
	if (!sttc[fd])
		return (NULL);
	line = srchnl(sttc[fd]);
	sttc[fd] = therest(sttc[fd]);
	return (line);
}
