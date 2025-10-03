/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 03:30:32 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/09/15 14:31:21 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player_from_cfg(t_game *g, t_cfg *c)
{
	g->px = c->player_x + 0.5;
	g->py = c->player_y + 0.5;
	g->dirx = (c->player_dir == 'E') - (c->player_dir == 'W');
	g->diry = (c->player_dir == 'S') - (c->player_dir == 'N');
	if (g->dirx != 0)
	{
		g->planex = 0.0;
		g->planey = 0.66 * g->dirx;
	}
	else
	{
		g->planex = -0.66 * g->diry;
		g->planey = 0.0;
	}
	g->keys.w = false;
	g->keys.s = false;
	g->keys.a = false;
	g->keys.d = false;
	g->keys.left = false;
	g->keys.right = false;
}

static void	key_hook(mlx_key_data_t k, void *param)
{
	t_game	*g;
	bool	is_pressed;

	g = (t_game *)param;
	is_pressed = (k.action == MLX_PRESS || k.action == MLX_REPEAT);
	if (k.key == MLX_KEY_ESCAPE && is_pressed)
		mlx_close_window(g->mlx);
	if (k.key == MLX_KEY_W || k.key == MLX_KEY_UP)
		g->keys.w = is_pressed;
	if (k.key == MLX_KEY_S || k.key == MLX_KEY_DOWN)
		g->keys.s = is_pressed;
	if (k.key == MLX_KEY_A)
		g->keys.a = is_pressed;
	if (k.key == MLX_KEY_D)
		g->keys.d = is_pressed;
	if (k.key == MLX_KEY_LEFT)
		g->keys.left = is_pressed;
	if (k.key == MLX_KEY_RIGHT)
		g->keys.right = is_pressed;
}

void	process_movement(t_game *g)
{
	double	move_speed;
	double	rot_speed;

	move_speed = MOVE_SPEED;
	rot_speed = ROT_SPEED;
	if (g->keys.w)
		move_forward(g, move_speed);
	if (g->keys.s)
		move_forward(g, -move_speed);
	if (g->keys.a)
		strafe(g, -move_speed);
	if (g->keys.d)
		strafe(g, move_speed);
	if (g->keys.left)
		rotate_player(g, -rot_speed);
	if (g->keys.right)
		rotate_player(g, rot_speed);
}

static int	init_graphics(t_game *g)
{
	g->mlx = mlx_init(WIN_W, WIN_H, "cub3D", false);
	if (!g->mlx)
	{
		err("Error\nmlx_init failed\n");
		return (0);
	}
	g->img = mlx_new_image(g->mlx, WIN_W, WIN_H);
	if (!g->img)
	{
		mlx_terminate(g->mlx);
		err("Error\nmlx_new_image failed\n");
		return (0);
	}
	if (mlx_image_to_window(g->mlx, g->img, 0, 0) < 0)
	{
		mlx_delete_image(g->mlx, g->img);
		mlx_terminate(g->mlx);
		err("Error\nimage_to_window failed\n");
		return (0);
	}
	return (1);
}

int	game_run(t_cfg *cfg)
{
	t_game	g;

	g.cfg = *cfg;
	if (!init_graphics(&g))
		return (1);
	set_player_from_cfg(&g, cfg);
	if (!load_textures(&g))
	{
		mlx_delete_image(g.mlx, g.img);
		mlx_terminate(g.mlx);
		return (1);
	}
	mlx_key_hook(g.mlx, &key_hook, &g);
	mlx_loop_hook(g.mlx, &loop_hook, &g);
	mlx_loop(g.mlx);
	free_textures(&g);
	mlx_delete_image(g.mlx, g.img);
	mlx_terminate(g.mlx);
	return (0);
}
