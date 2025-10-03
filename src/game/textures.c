/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 04:49:53 by marvin            #+#    #+#             */
/*   Updated: 2025/09/15 14:30:03 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static const char	*ext_of(const char *p)
{
	const char	*dot;

	dot = NULL;
	if (!p)
		return (NULL);
	while (*p)
	{
		if (*p == '.')
			dot = p;
		p++;
	}
	if (dot)
		return (dot + 1);
	return (NULL);
}

static mlx_texture_t	*load_texture_file(const char *path, xpm_t **xpm)
{
	const char		*ext;
	mlx_texture_t	*tex;

	*xpm = NULL;
	tex = NULL;
	ext = ext_of(path);
	if (ext && (!ft_strncmp(ext, "png", 3) || !ft_strncmp(ext, "PNG", 3)))
		tex = mlx_load_png(path);
	else if (ext && (!ft_strncmp(ext, "xpm42", 5)
			|| !ft_strncmp(ext, "XPM42", 5)))
		*xpm = mlx_load_xpm42(path);
	else
	{
		err("Error\nUnsupported texture format. Use .png or .xpm42\n");
		return (NULL);
	}
	if (*xpm)
		tex = &(*xpm)->texture;
	return (tex);
}

static int	load_one_tex(t_game *g, int id, const char *path)
{
	mlx_texture_t	*tex;
	xpm_t			*xpm;

	tex = load_texture_file(path, &xpm);
	if (!tex)
		return (0);
	g->tex[id].img = mlx_texture_to_image(g->mlx, tex);
	if (xpm)
		mlx_delete_xpm42(xpm);
	else
		mlx_delete_texture(tex);
	if (!g->tex[id].img)
	{
		err("Error\ntexture_to_image failed\n");
		return (0);
	}
	g->tex[id].w = (int)g->tex[id].img->width;
	g->tex[id].h = (int)g->tex[id].img->height;
	g->tex[id].pixels = (uint32_t *)g->tex[id].img->pixels;
	return (1);
}

int	load_textures(t_game *g)
{
	if (!load_one_tex(g, TEX_NO, g->cfg.tex[TEX_NO]))
		return (0);
	if (!load_one_tex(g, TEX_SO, g->cfg.tex[TEX_SO]))
		return (0);
	if (!load_one_tex(g, TEX_WE, g->cfg.tex[TEX_WE]))
		return (0);
	if (!load_one_tex(g, TEX_EA, g->cfg.tex[TEX_EA]))
		return (0);
	return (1);
}

void	free_textures(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (g->tex[i].img)
			mlx_delete_image(g->mlx, g->tex[i].img);
		i++;
	}
}
