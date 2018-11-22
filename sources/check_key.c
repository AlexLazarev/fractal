/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alazarev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 15:50:05 by alazarev          #+#    #+#             */
/*   Updated: 2018/04/23 20:44:08 by alazarev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include "../includes/keys.h"
#include <mlx.h>

int		exit_x(void *param)
{
	exit(1);
	return (1);
}

int		check_translate(int key, t_fractol *fractol)
{
	if (key == KEY_LEFT)
		fractol->x += DX * fractol->zoom;
	else if (key == KEY_RIGHT)
		fractol->x -= DX * fractol->zoom;
	else if (key == KEY_UP)
		fractol->y += DY * fractol->zoom;
	else if (key == KEY_DOWN)
		fractol->y -= DY * fractol->zoom;
	else
		return (0);
	return (1);
}

int		deal_key(int key, void *param)
{
	if (!check_translate(key, ((t_global*)param)->fractol))
	{
		if (key == KEY_ESC)
			exit(0);
		else if (key == KEY_SPACE)
			init_fractol(((t_global*)param)->fractol);
		else if (key == KEY_TAB)
			((t_global*)param)->fractol->stop = 1;
	}
	run_threads((t_global*)param);
	return (0);
}
