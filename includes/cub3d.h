/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:48:12 by cisis             #+#    #+#             */
/*   Updated: 2021/01/27 17:55:38 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

typedef struct	s_parsed
{
	int			res_width;
	int			res_height;
	char		*north_texture_path;
	char		*south_texture_path;
	char		*west_texture_path;
	char		*east_texture_path;
	char		*sprite_texture_path;
	int			floor_color;
	int			ceiling_color;
	char		**map;
}				t_parsed;

int				parse_file(char *filepath);
int				process_error(void);
int				validate_list(t_parsed **parsed, t_list *lst);

#endif
