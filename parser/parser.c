/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:47:50 by cisis             #+#    #+#             */
/*   Updated: 2021/01/27 17:57:12 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		free_str(void *line)
{
	if (line)
		free(line);
}

static void		print_list(t_list *head) //PRINTF
{
	int 		i;

	i = 0;
	while (head)
	{
		printf("%d - %s\n", i, (char*)head->content);
		head = head->next;
		i++;
	}
}

static int		list_append(t_list **head, char *line)
{
	char 		*line_copy;

	if (!(line_copy = ft_strdup(line)))
		return (-1);
	ft_lstadd_back(head, ft_lstnew(line_copy));
	return (0);
}

static int		init_list(int fd, t_list **head)
{
	int			gnl;
	char		*line;

	gnl = 1;
	while (gnl == 1)
	{
		if ((gnl = get_next_line(fd, &line)) == -1)
		{
			free_str(line);
			return (-1);
		}
		list_append(head, line);
		free(line);
	}
	return (0);
}

int				parse_file(char *filepath)
{
	int			fd;
	t_list		*head;
	t_parsed	*parsed;

	head = NULL;
	if (((fd = open(filepath, O_RDONLY)) == -1) ||
		(init_list(fd, &head) == -1) ||
	 	(validate_list(&parsed, head)) == -1)
		return (process_error());
	print_list(head); //PRINTF
	ft_lstclear(&head, free_str);
	return (0);
}
