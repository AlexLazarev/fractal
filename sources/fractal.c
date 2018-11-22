/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alazarev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:19:05 by alazarev          #+#    #+#             */
/*   Updated: 2018/04/24 13:21:21 by alazarev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include <math.h>

int	set_mandelbrot(int max_iter, t_complex complex)
{
	int		i;
	double	zr;
	double	zi;
	double	temp;

	i = 0;
	zr = 0;
	zi = 0;
	while (i < max_iter && zr * zr + zi * zi < 4.0)
	{
		temp = zr * zr - zi * zi + complex.cr;
		zi = 2.0 * zr * zi + complex.ci;
		zr = temp;
		i++;
	}
	return (i);
}

int	set_tricorn(int max_iter, t_complex complex)
{
	int		i;
	double	zr;
	double	zi;
	double	temp;

	i = 0;
	zr = 0;
	zi = 0;
	while (i < max_iter && zr * zr + zi * zi < 4.0)
	{
		temp = zr * zr - zi * zi + complex.cr;
		zi = -2 * zr * zi + complex.ci;
		zr = temp;
		i++;
	}
	return (i);
}

int	set_julia(int max_iter, t_complex complex)
{
	int		i;
	double	zr;
	double	zi;
	double	temp;

	i = 0;
	zr = complex.cr;
	zi = complex.ci;
	while (i < max_iter && zr * zr + zi * zi < 4.0)
	{
		temp = zr * zr - zi * zi;
		zi = 2.0 * zr * zi + complex.jr;
		zr = temp + complex.ji;
		i++;
	}
	return (i);
}

int	set_burningship(int max_iter, t_complex complex)
{
	int		i;
	double	zr;
	double	zi;
	double	temp;

	i = 0;
	zr = 0;
	zi = 0;
	while (i < max_iter && zr * zr + zi * zi < 4.0)
	{
		temp = fabs(zr * zr - zi * zi + complex.cr);
		zi = fabs(2 * zr * zi + complex.ci);
		zr = temp;
		i++;
	}
	return (i);
}

int	set(t_fractol *fractol, int x, int y)
{
	fractol->complex.cr = (x - WINDOW_WIDTH / 2.0) *
		fractol->zoom + fractol->x;
	fractol->complex.ci = (y - WINDOW_HEIGHT / 2.0) *
		fractol->zoom + fractol->y;
	return (fractol->set(fractol->max_iter, fractol->complex));
}
