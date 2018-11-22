/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alazarev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:40:35 by alazarev          #+#    #+#             */
/*   Updated: 2018/04/24 15:41:48 by alazarev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FRACTOL_H
# define _FRACTOL_H

# include <stdio.h>
# include <fcntl.h>
# include "../lib/libft/includes/libft.h"
# define THREADS 8
# define MAX_ITER 100
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define DX 40
# define DY 40
# define ALPHA 3
# define R 2
# define G 1
# define B 0

typedef union			u_rgb
{
	int				rgba;
	unsigned char	c[4];
}						t_rgb;

typedef struct			s_image
{
	void			*img;
	char			*ptr;
	int				bpp;
	int				size_line;
	int				endian;
}						t_image;

typedef struct			s_complex
{
	double			cr;
	double			ci;
	double			jr;
	double			ji;
}						t_complex;

typedef struct			s_fractol
{
	int				is_julia;
	int				stop;
	int				mouse_move;
	double			max_iter;
	double			factor;
	double			zoom;
	double			x;
	double			y;
	t_complex		complex;
	int				(*set)(int max_iter, t_complex complex);
}						t_fractol;

typedef struct			s_global
{
	void			*mlx;
	t_image			*image;
	void			*window;
	t_fractol		*fractol;
	int				start;
	int				end;
	int				status;
	int				*status_addr;
}						t_global;

void					run_threads(t_global *global);
int						set_mandelbrot(int max_iter, t_complex complex);
int						set_tricorn(int max_iter, t_complex complex);
int						set_julia(int max_iter, t_complex complex);
int						set_burningship(int max_iter, t_complex complex);
int						set(t_fractol *fractol, int x, int y);
void					draw(t_global *global);
void					fill_image(t_image *image, int x, int y, int rgb);
void					clear_image(t_image *image);
int						check_translate(int key, t_fractol *fractol);
int						mouse_press(int key, int x, int y, void *param);
int						mouse_release(int key, int x, int y, void *param);
int						mouse_move(int x, int y, void *param);
void					init_fractol(t_fractol *fractol);
int						deal_key(int key, void *param);
int						exit_x(void *param);

#endif
