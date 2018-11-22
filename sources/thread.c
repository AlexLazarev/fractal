/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alazarev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 15:36:33 by alazarev          #+#    #+#             */
/*   Updated: 2018/04/24 15:38:11 by alazarev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include <mlx.h>
#include <pthread.h>

void	run_threads(t_global *global)
{
	pthread_t	threads[THREADS];
	t_global	globals[THREADS];
	int			i;
	int			y;

	i = -1;
	y = 0;
	while (++i < THREADS)
	{
		globals[i] = *global;
		globals[i].start = y;
		y += WINDOW_HEIGHT / THREADS;
		globals[i].end = y;
		pthread_create(&threads[i], NULL,
			(void*)draw, (void *)&globals[i]);
	}
	while (i-- > 0)
		global->status = pthread_join(threads[i],
			(void **)&global->status_addr);
	mlx_put_image_to_window(global->mlx, global->window,
			global->image->img, 0, 0);
}
