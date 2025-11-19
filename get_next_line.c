/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarbosa <nbarbosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:50:29 by nbarbosa          #+#    #+#             */
/*   Updated: 2025/11/19 10:56:16 by nbarbosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static char	*ft_str_after_new_line(char *line, char *stock)
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
	static char		*stock = NULL;
	int				bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&stock));
	bytes = 1;
	while (ft_find_new_line(stock) <= 0 && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (ft_free(&buffer), ft_free(&stock));
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		stock = ft_strjoin(stock, buffer);
		if (!stock)
			return (ft_free(&buffer));
	}
	line = ft_str_before_new_line(stock);
	return (ft_free(&buffer), stock = ft_str_after_new_line(line, stock), line);
}
