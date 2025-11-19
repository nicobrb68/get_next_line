/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarbosa <nbarbosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:37:15 by nbarbosa          #+#    #+#             */
/*   Updated: 2025/11/17 09:37:15 by nbarbosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	ft_find_new_line(char *stock)
{
	int	i;

	if (!stock)
		return (0);
	i = 0;
	while (stock[i])
	{
		if (stock[i] == '\n')
			return (1);
		i++;
	}
	return (-1);
}

static char	*ft_str_before_new_line(char *stock)
{
	char	*res_line;
	int		x;
	int		i;

	i = 0;
	x = 0;
	if (!stock)
		return (NULL);
	while (stock[i] && stock[i] != '\n')
		i++;
	if (stock[i] == '\n')
		i++;
	res_line = malloc(sizeof(char) * (i + 1));
	if (!res_line)
		return (ft_free(&stock));
	while (x < i)
	{
		res_line[x] = stock[x];
		x++;
	}
	return (res_line[x] = '\0', res_line);
}

static char	*ft_after_nl(char *line, char *stock)
{
	char	*res_stock;
	int		i;
	int		x;

	i = 0;
	x = 0;
	if (!line || !stock)
		return (NULL);
	while (line[i])
		i++;
	if (!stock[i])
		return (ft_free(&stock));
	res_stock = malloc(sizeof(char) * (ft_strlen(stock) - i + 1));
	if (!res_stock)
		return (ft_free(&stock));
	while (stock[i])
		res_stock[x++] = stock[i++];
	ft_free(&stock);
	return (res_stock[x] = '\0', res_stock);
}

char	*get_next_line(int fd)
{
	char			*buffer;
	char			*line;
	static char		*stock[5000];
	int				bytes;

	if (fd < 0 || fd >= 5000 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&stock[fd]));
	bytes = 1;
	while (ft_find_new_line(stock[fd]) <= 0 && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (ft_free(&buffer), ft_free(&stock[fd]));
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		stock[fd] = ft_strjoin(stock[fd], buffer);
		if (!stock[fd])
			return (ft_free(&buffer));
	}
	line = ft_str_before_new_line(stock[fd]);
	return (ft_free(&buffer), stock[fd] = ft_after_nl(line, stock[fd]), line);
}
