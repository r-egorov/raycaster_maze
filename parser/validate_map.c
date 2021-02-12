/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:53:24 by cisis             #+#    #+#             */
/*   Updated: 2021/02/12 14:00:00 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	make_map(t_list *head, int lst_size, t_parsed *parsed)
{
	char		**map;
	size_t		i;

	if (!(map = ft_calloc(lst_size + 1, sizeof(char*))))
		return (-1);
	i = 0;
	while (head)
	{
		if (*(char*)head->content == '\0')
			break ;
		if (!(map[i++] = ft_strdup(head->content)))
			return (-1);
		head = head->next;
	}
	map[i] = NULL;
	parsed->map = map;
	parsed->map_height = i;
	return (0);
}

static int	valid_char_in_map(char c)
{
	if ((c == '1') ||
		(c == '0') ||
		(c == '2') ||
		(c == ' ') ||
		(c == 'N') ||
		(c == 'S') ||
		(c == 'E') ||
		(c == 'W'))
		return (1);
	g_errno = 18;
	return (0);
}

static int	if_player_set(int x, int y, t_parsed *parsed)
{
	if (((parsed->map)[y][x] == 'N') ||
		((parsed->map)[y][x] == 'S') ||
		((parsed->map)[y][x] == 'E') ||
		((parsed->map)[y][x] == 'W'))
	{
		if (parsed->player_dir)
		{
			g_errno = 21;
			return (-1);
		}
		parsed->player_pos.x = x;
		parsed->player_pos.y = y;
		parsed->player_dir = (parsed->map)[y][x];
	}
	return (0);
}

static int	valid_map(t_parsed *parsed)
{
	size_t		x;
	size_t		y;
	char		**map;

	map = parsed->map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if ((!(valid_char_in_map(map[y][x]))) ||
				((map[y][x] == '0') && (!(valid_zero_map(parsed, x, y)))) ||
				((map[y][x] == ' ') && (!(valid_space_map(parsed, x, y)))) ||
				(if_player_set(x, y, parsed)))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

void		validate_map(t_list **begin, t_parsed *parsed)
{
	t_list		*head;

	head = *begin;
	if ((make_map(head, ft_lstsize(head), parsed)) == -1)
	{
		g_errno = 2;
		return ;
	}
	*begin = NULL;
	if (!(valid_map(parsed)))
		return ;
}
