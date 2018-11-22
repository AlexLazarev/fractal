/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alazarev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 20:44:25 by alazarev          #+#    #+#             */
/*   Updated: 2018/04/24 15:37:38 by alazarev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include <mlx.h>

static int	get_color(int iter, int max_iter)
{
	t_rgb color;

	if (iter == max_iter)
		return (0);
	color.c[R] = max_iter * 0.66 * (iter * 0.1);
	color.c[G] = max_iter * 0.32 * (iter * 0.1);
	color.c[B] = max_iter * 0.32;
	return (color.rgba);
}

void		draw(t_global *global)
{
	int i;
	int j;

	i = global->start;
	while (i < global->end)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			fill_image(global->image, j, i,
					get_color(set(global->fractol, j, i),
					global->fractol->max_iter));
			j++;
		}
		i++;
	}
}
