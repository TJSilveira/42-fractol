/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilveir <tsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:21:53 by tsilveir          #+#    #+#             */
/*   Updated: 2025/06/27 13:21:54 by tsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	mandelbrot_calc(t_coor zn, t_coor c, int iter)
{
	int		i;
	double	temp_x;

	i = 1;
	zn.x = 0;
	zn.y = 0;
	while (i < iter)
	{
		temp_x = zn.x * zn.x - zn.y * zn.y + c.x;
		zn.y = 2. * zn.x * zn.y + c.y;
		zn.x = temp_x;
		if (zn.x * zn.x + zn.y * zn.y > 20)
			break ;
		i++;
	}
	return (i);
}

int	julia_calc(t_coor zn, t_coor c, int iter)
{
	int		i;
	double	temp_x;

	i = 1;
	while (i < iter)
	{
		temp_x = zn.x * zn.x - zn.y * zn.y + c.x;
		zn.y = 2. * zn.x * zn.y + c.y;
		zn.x = temp_x;
		if (zn.x * zn.x + zn.y * zn.y > 20)
			break ;
		i++;
	}
	return (i);
}

int	tricorn_calc(t_coor zn, t_coor c, int iter)
{
	int		i;
	double	temp_x;

	i = 1;
	zn.x = 0;
	zn.y = 0;
	while (i < iter)
	{
		temp_x = zn.x * zn.x - zn.y * zn.y + c.x;
		zn.y = -2. * zn.x * zn.y + c.y;
		zn.x = temp_x;
		if (zn.x * zn.x + zn.y * zn.y > 20)
			break ;
		i++;
	}
	return (i);
}

int	fractal_choice(t_coor zn, t_coor c, t_image *img)
{
	if (img->fractal_type == MANDELBROT)
		return (mandelbrot_calc(zn, c, img->iter));
	else if (img->fractal_type == JULIA)
		return (julia_calc(zn, img->c_julia, img->iter));
	else if (img->fractal_type == TRICORN)
		return (tricorn_calc(zn, c, img->iter));
	return (0);
}

void	update_c_julia(t_engine *e, double x, double y)
{
	e->img.c_julia.x = x;
	e->img.c_julia.y = y;
}
