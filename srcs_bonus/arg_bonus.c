/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:14:24 by mewen             #+#    #+#             */
/*   Updated: 2025/12/12 14:41:27 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg_bonus.h"

char	**get_path(char *env[])
{
	int		cond;
	size_t	i;
	char	**splited_path;	

	i = 0;
	cond = 1;
	while (env[i] && cond)
		cond = ft_strncmp(env[i++], "PATH=", 5);
	if (!env[i])
		return (NULL);
	splited_path = ft_split(env[i - 1] + 5, ':');
	return (splited_path);
}

char	*get_bin_path(char **path, char *name_bin)
{
	char	*res;
	size_t	i;
	size_t	len_path;
	size_t	len_name_bin;

	if (!name_bin || !path)
		return (NULL);
	len_name_bin = ft_strlen(name_bin);
	i = 0;
	while (path[i])
	{
		len_path = ft_strlen(path[i]);
		res = malloc(sizeof(char) * (len_name_bin + 1 + len_path + 1));
		if (!res)
			return (NULL);
		ft_memcpy(res, path[i], len_path);
		res[len_path] = '/';
		ft_memcpy(res + len_path + 1, name_bin, len_name_bin);
		res[len_name_bin + 1 + len_path] = 0;
		if (access(res, F_OK | X_OK) == 0)
			return (res);
		free(res);
		i++;
	}
	return (NULL);
}

void	free_split(char **strs)
{
	size_t	i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}
