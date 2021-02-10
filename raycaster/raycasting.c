/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 17:03:54 by cisis             #+#    #+#             */
/*   Updated: 2021/02/10 15:09:30 by cisis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			cast_rays(t_all *all)
{
	int		x;

	x = 0;
	while (x < all->parsed.res_width)
	{
		double		camera_x;

		camera_x = 2 * x / (double)all->parsed.res_width - 1;

		t_vector	ray;

		ray.x = all->plr_pos.dir.x + all->plr_pos.plane.x * camera_x;
		ray.y = all->plr_pos.dir.y + all->plr_pos.plane.y * camera_x;

	// GOOD TILL THIS	

		t_point		map; 

		map.x = (int)all->plr_pos.x;
		map.y = (int)all->plr_pos.y;

		t_vector	side_dist;

		t_vector	delta_dist;

		if (ray.y == 0)
			delta_dist.x = 0;
		else
		{
			if (ray.x == 0)
				delta_dist.x = 1;
			else
				delta_dist.x = fabs(1 / ray.x);
		}

		if (ray.x == 0)
			delta_dist.y = 0;
		else
		{
			if (ray.y == 0)
				delta_dist.y = 1;
			else
				delta_dist.y = fabs(1 / ray.y);
		}

		double		perp_wall_dist;

		int			step_x;
		int			step_y;

		int			hit;
		hit = 0;

		int			side;

		//calculate stepdist and stepxy
		
		if (ray.x < 0)
		{
			step_x = -1;
			side_dist.x = (all->plr_pos.x - map.x) * delta_dist.x;
		}
		else
		{
			step_x = 1;
			side_dist.x = (map.x + 1.0 - all->plr_pos.x) * delta_dist.x;
		}

		if (ray.y < 0)
		{
			step_y = -1;
			side_dist.y = (all->plr_pos.y - map.y) * delta_dist.y;
		}
		else
		{
			step_y = 1;
			side_dist.y = (map.y + 1.0 - all->plr_pos.y) * delta_dist.y;
		}
		
		// DDA


		while (hit == 0)
		{
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				map.x += step_x;
				side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map.y += step_y;
				side = 1;
			}
			if (all->parsed.map[map.y][map.x] == '1')
				hit = 1;
		}

		
		if (side == 0)
			perp_wall_dist = (map.x - all->plr_pos.x + (1 - step_x) / 2) / ray.x;
		else
			perp_wall_dist = (map.y - all->plr_pos.y + (1 - step_y) / 2) / ray.y;

		//Drawing

		int		line_height;

		line_height = (int)(all->parsed.res_height / perp_wall_dist);
		
		int		draw_start;
		int		draw_finish;

		int		y;
		y = 0;


		draw_start = -line_height / 2 + all->parsed.res_height / 2;
		if (draw_start < 0)
			draw_start = 0;

		draw_finish = line_height / 2 + all->parsed.res_height / 2;
		if (draw_finish >= all->parsed.res_height)
			draw_finish = all->parsed.res_height - 1;

		// Draw ceiling
		while (y < draw_start)
		{
			my_mlx_pixel_put(&(all->window),
					all->parsed.res_width - x - 1, y, all->parsed.ceiling_colour);
			y++;
		}

		// Draw wall
		while (y < draw_finish)
		{
			my_mlx_pixel_put(&(all->window),
					all->parsed.res_width - x - 1, y, GREEN);
			y++;
		}

		//Draw floor
		while (y < all->parsed.res_height)
		{
			my_mlx_pixel_put(&(all->window),
					all->parsed.res_width - x - 1, y, all->parsed.floor_colour);
			y++;
		}


		x++;
	}
	return (0);
}
