/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alazarev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 20:29:46 by alazarev          #+#    #+#             */
/*   Updated: 2018/04/24 15:36:27 by alazarev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include "../includes/keys.h"
#include <mlx.h>

int			mouse_press(int key, int x, int y, void *param)
{
	if (key == MOUSE_KEY_LEFT)
		((t_global*)param)->fractol->factor *= 0.9348;
	else if (key == MOUSE_SCROLL_UP)
	{
		((t_global*)param)->fractol->x -= ((WINDOW_WIDTH / 2.0 - x) *
			((t_global*)param)->fractol->zoom);
		((t_global*)param)->fractol->y -= ((WINDOW_HEIGHT / 2.0 - y) *
			((t_global*)param)->fractol->zoom);
		((t_global*)param)->fractol->max_iter += 5;
		((t_global*)param)->fractol->zoom *= 0.9;
	}
	else if (key == MOUSE_SCROLL_DOWN)
	{
		((t_global*)param)->fractol->x += ((WINDOW_WIDTH / 2.0 - x) *
			((t_global*)param)->fractol->zoom);
		((t_global*)param)->fractol->y += ((WINDOW_HEIGHT / 2.0 - y) *
			((t_global*)param)->fractol->zoom);
		((t_global*)param)->fractol->max_iter -= 5;
		((t_global*)param)->fractol->zoom /= 0.9;
	}
	run_threads((t_global*)param);
	return (0);
}

static int	init_k(int prek, int k)
{
	if (prek < k)
		return (1);
	else if (prek == k)
		return (0);
	else
		return (-1);
}

int			mouse_move(int x, int y, void *param)
{
	static int	prex = 0;
	static int	prey = 0;
	int			kx;
	int			ky;

	if (!((t_global*)param)->fractol->stop)
	{
		kx = init_k(prex, x);
		ky = init_k(prey, y);
		((t_global*)param)->fractol->complex.jr += kx *
			(x - WINDOW_WIDTH / 2.0) / (WINDOW_WIDTH / 0.1);
		((t_global*)param)->fractol->complex.ji += ky *
			(y - WINDOW_HEIGHT / 2.0) / (WINDOW_HEIGHT / 0.1);
		prex = x;
		prey = y;
		run_threads((t_global*)param);
	}
	return (0);
}
