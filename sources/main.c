/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alazarev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 20:58:00 by alazarev          #+#    #+#             */
/*   Updated: 2018/04/17 20:58:02 by alazarev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "../lib/libft/includes/libft.h"
#include "../includes/fractol.h"
#include "../includes/keys.h"

static void		usage(void)
{
	ft_putendl("usage: ./fractol name");
	ft_putendl("name : ");
	ft_putendl("	Julia");
	ft_putendl("	Mandelbrot");
	ft_putendl("	Tricorn");
	ft_putendl("	Burning ship");
	ft_putendl("Max window: 8");
}

void			init_fractol(t_fractol *fractol)
{
	fractol->max_iter = MAX_ITER;
	fractol->factor = 1;
	fractol->zoom = 0.004;
	fractol->x = 0;
	fractol->y = 0;
	fractol->complex.jr = 0;
	fractol->complex.ji = 0;
	fractol->is_julia = 0;
	fractol->stop = 0;
}

void			init_global(t_global *global, void *mlx, char *set)
{
	global->mlx = mlx;
	global->window = mlx_new_window(global->mlx,
				WINDOW_WIDTH, WINDOW_HEIGHT, set);
	global->image = (t_image*)malloc(sizeof(t_image));
	global->image->img = mlx_new_image(global->mlx,
		WINDOW_WIDTH, WINDOW_HEIGHT);
	global->image->ptr = mlx_get_data_addr(global->image->img,
		&global->image->bpp, &global->image->size_line, &global->image->endian);
	global->image->bpp /= 8;
	global->fractol = (t_fractol*)malloc(sizeof(t_fractol));
	init_fractol(global->fractol);
	if (ft_strcmp(set, "Julia") == 0)
	{
		global->fractol->is_julia = 1;
		global->fractol->set = &set_julia;
	}
	else if (ft_strcmp(set, "Mandelbrot") == 0)
		global->fractol->set = &set_mandelbrot;
	else if (ft_strcmp(set, "Tricorn") == 0)
		global->fractol->set = &set_tricorn;
	else if (ft_strcmp(set, "Burning ship") == 0)
		global->fractol->set = &set_burningship;
}

static int		check_argv(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
	{
		if (ft_strcmp(argv[i], "Julia") &&
			ft_strcmp(argv[i], "Mandelbrot") &&
			ft_strcmp(argv[i], "Tricorn") &&
			ft_strcmp(argv[i], "Burning ship"))
			return (0);
		i++;
	}
	return (1);
}

int				main(int argc, char **argv)
{
	int			i;
	t_global	*global;
	void		*mlx;

	if (argc > 1 && argc <= 8 && check_argv(++argv))
	{
		global = (t_global*)malloc(sizeof(t_global) * (argc - 1));
		mlx = mlx_init();
		i = 0;
		while (i < argc - 1)
		{
			init_global(global + i, mlx, argv[i]);
			run_threads(&(global[i]));
			mlx_hook(global[i].window, 2, 0, deal_key, &global[i]);
			mlx_hook(global[i].window, 4, 0, mouse_press, &global[i]);
			if (global[i].fractol->is_julia)
				mlx_hook(global[i].window, 6, 0, mouse_move, &global[i]);
			mlx_hook(global[i].window, 17, 0, exit_x, &global[i]);
			i++;
		}
		mlx_loop(mlx);
	}
	else
		usage();
	return (0);
}
