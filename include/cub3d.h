/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 21:39:33 by ikhalil           #+#    #+#             */
/*   Updated: 2025/09/15 14:31:18 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <stdbool.h>
# include "libft.h"
# include <math.h>

# include "MLX42/MLX42.h"
# define WIN_W 960
# define WIN_H 640
# define MOVE_SPEED 0.04
# define ROT_SPEED 0.025

# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3

# define TRUE 1
# define FALSE 0

typedef struct s_keys
{
	bool	w;
	bool	s;
	bool	a;
	bool	d;
	bool	left;
	bool	right;
}	t_keys;

typedef struct s_vec
{
	char	**data;
	int		size;
	int		cap;
}		t_vec;

typedef struct s_cfg
{
	char	*tex[4];
	int		has_tex[4];
	int		floor_color;
	int		ceil_color;
	int		has_floor;
	int		has_ceil;

	t_vec	lines;
	char	**map;
	int		map_w;
	int		map_h;
	int		player_x;
	int		player_y;
	char	player_dir;
	int		player_count;
}		t_cfg;

typedef struct s_qctx
{
	unsigned char	*vis;
	int				*qx;
	int				*qy;
	int				tail;
}		t_qctx;

typedef struct s_fillbuf
{
	unsigned char	*vis;
	int				*qx;
	int				*qy;
	int				cap;
}		t_fillbuf;

typedef struct s_tex
{
	mlx_texture_t	*t;
	mlx_image_t		*img;
	int				w;
	int				h;
	uint32_t		*pixels;
}	t_tex;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	double		px;
	double		py;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	t_cfg		cfg;
	t_tex		tex[4];
	t_keys		keys;
}	t_game;

typedef struct s_segpos
{
	size_t	i;
	size_t	j;
}		t_segpos;

typedef struct s_ray
{
	double	dx;
	double	dy;
	int		side;
	double	perp;
}	t_ray;

typedef struct s_span
{
	int		top;
	int		bot;
}	t_span;

typedef struct s_wslice
{
	int		tex_x;
	int		tex_y;
	int		line_h;
	double	step;
	double	tex_pos;
}	t_wslice;

int			map_at(t_cfg *cfg, int x, int y);
void		put_px_rgba(mlx_image_t *dst, int x, int y, const uint8_t c[4]);
void		tex_get_rgba(mlx_image_t *tex, int tx, int ty, uint8_t c[4]);
int			choose_tid(int side, double rdx, double rdy);
double		cast_one(t_game *g, t_ray *r, int *sx, int *sy);
void		draw_column(t_game *g, int x, t_ray *r);
void		draw_frame(t_game *g);
int			parse_file(const char *path, t_cfg *cfg);
int			all_identifiers_ready(t_cfg *c);
size_t		compute_seg_len(const char *ct, size_t i, size_t j);
char		*dup_segment(const char *ct, size_t i, size_t len);
int			process_pre_map_line(char *line, t_cfg *cfg, int *in_map);
int			process_map_line(char *line, t_cfg *cfg);
size_t		find_line_end(const char *ct, size_t i);
int			handle_segment(const char *ct, t_segpos pos, t_cfg *cfg,
				int *in_map);
size_t		advance_index(const char *ct, size_t j);
int			parse_content(const char *ct, t_cfg *cfg);
int			post_parse_validate_and_build(t_cfg *cfg);

/* config */
int			parse_id_line(char *line, t_cfg *cfg);
void		skip_ws(char **ps);
int			rtrim_len(const char *s);
int			expect_comma(char **ps);
int			try_open_texture(const char *p);
char		*dup_trimmed_path(char *s);
int			check_texture_path(char *path);
int			set_tex(t_cfg *c, int idx, char *s);
int			parse_int_0_255(char **ps, int *out);
int			read_component(char **ps, int *dst);
int			parse_color_triplet(char *s, int *dst, int *flag);

/* map */
int			is_map_line(const char *s);
int			push_map_line(t_cfg *cfg, char *line);
int			build_rect_map(t_cfg *cfg);
int			find_player_and_validate_chars(t_cfg *cfg);
int			grow_lines(t_cfg *cfg);
int			compute_max_w(t_cfg *cfg);
int			alloc_map(t_cfg *cfg, int w);
void		copy_and_detab_line(t_cfg *cfg, int i);
int			is_player(char c);
int			is_allowed_char(char ch);
void		mark_player(t_cfg *cfg, int x, int y);
int			scan_row(t_cfg *cfg, int y);

/* validate */
int			validate_closed(t_cfg *cfg);
int			fill_interior_spaces(t_cfg *cfg);
int			touches_void_or_edge(t_cfg *c, int y, int x);
int			is_void_cell(t_cfg *c, int x, int y);
int			is_edge(t_cfg *c, int x, int y);
void		enqueue(t_qctx *q, int x, int y);
void		push_if_void(t_cfg *c, t_qctx *q, int x, int y);
void		seed_edges(t_cfg *c, t_qctx *q);
void		expand_neighbors(t_cfg *c, t_qctx *q, int x, int y);
int			bfs_mark_outside(t_cfg *c, unsigned char *vis, int *qx, int *qy);
int			alloc_bufs(t_fillbuf *b);
void		free_bufs(t_fillbuf *b);
void		sweep_and_fill(t_cfg *c, t_fillbuf *b);

/* file io */
char		*file_to_str(const char *path);
char		*join_free(char *s, const char *buf, ssize_t n);

/* utils */
int			err(const char *msg);
int			is_space_line(const char *s);
char		*skip_spaces(char *s);
char		*sdup(const char *s);
void		free_cfg(t_cfg *cfg);
int			game_run(t_cfg *cfg);
void		draw_frame(t_game *g);
int			map_at(t_cfg *c, int mx, int my);
void		move_forward(t_game *g, double s);
void		strafe(t_game *g, double s);
void		rotate_player(t_game *g, double ang);
int			load_textures(t_game *g);
void		free_textures(t_game *g);
void		loop_hook(void *param);
void		process_movement(t_game *g);
#endif
