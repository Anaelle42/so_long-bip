/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:41:54 by ahenault          #+#    #+#             */
/*   Updated: 2024/04/05 17:38:39 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error(char *error)
{
	printf("Error\n%s\n", error);
	exit(1);
}

size_t	ft_strlen_number2(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

void	flood2(char **map, t_number *number, int y, int x)
{
	if (map[y][x] == 'C')
		number->c--;
	map[y][x] = '1';
	if (map[y][x + 1] && (map[y][x + 1] == 'E'))
		number->e = 0;
	if (map[y][x - 1] && (map[y][x - 1] == 'E'))
		number->e = 0;
	if (map[y + 1][x] && (map[y + 1][x] == 'E'))
		number->e = 0;
	if (map[y - 1][x] && (map[y - 1][x] == 'E'))
		number->e = 0;
	if (map[y + 1][x] && (map[y + 1][x] == '0' || map[y + 1][x] == 'C'))
		flood2(map, number, y + 1, x);
	if (map[y - 1][x] && (map[y - 1][x] == '0' || map[y - 1][x] == 'C'))
		flood2(map, number, y - 1, x);
	if (map[y][x + 1] && (map[y][x + 1] == '0' || map[y][x + 1] == 'C'))
		flood2(map, number, y, x + 1);
	if (map[y][x - 1] && (map[y][x - 1] == '0' || map[y][x - 1] == 'C'))
		flood2(map, number, y, x - 1);
}

void	flood_fill(char **map, t_number number)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				flood2(map, &number, y, x);
			}
			x++;
		}
		y++;
	}
	if (number.c != 0 || number.e != 0)
		ft_error(ERROR7);
}
char	**copy_map(char **map, int nb)
{
	char	**copy;
	int		i;

	i = 0;
	copy = malloc(sizeof(char *) * nb);
	if (!copy)
		ft_error(ERROR2);
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	parsing(t_data *str)
{
	t_number	number;
	int			i;
	size_t		size;

	number.c = 0;
	number.p = 0;
	number.e = 0;
	i = 0;
	size = 0;
	size = ft_strlen_number2(str->data_map.map[i]);
	is_closed_by_walls(str);
	while (str->data_map.map[i])
	{
		count_characters(str->data_map.map[i], &number);
		if (!is_valid_characters(str->data_map.map[i]))
			ft_error(ERROR3);
		if (size != ft_strlen_number2(str->data_map.map[i]))
			ft_error(ERROR5);
		i++;
	}
	if (number.e != 1 || number.p != 1 || number.c < 1)
		ft_error(ERROR4);
	flood_fill(copy_map(str->data_map.map, i), number);
}
