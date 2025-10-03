/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42amman.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:28:01 by marvin            #+#    #+#             */
/*   Updated: 2025/09/07 23:38:34 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	parse_file(const char *path, t_cfg *cfg)
{
	char	*content;

	content = file_to_str(path);
	if (!content)
		return (FALSE);
	if (!parse_content(content, cfg))
	{
		free(content);
		return (FALSE);
	}
	free(content);
	return (post_parse_validate_and_build(cfg));
}
