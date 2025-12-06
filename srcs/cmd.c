/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 13:25:33 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/06 20:11:09 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "arg.h"
#include "utils.h"

static int	get_nb_valide_cmd(int argc, char **argv, char **path)
{
	int		i;
	int		result;
	char	**splited_arg;
	char	*bin_path;

	i = 0;
	result = 0;
	while (i < argc - 3)
	{
		splited_arg = ft_split(argv[2 + i], ' ');
		bin_path = get_bin_path(path, splited_arg[0]);
		if (bin_path)
			result++;
		else
			printf("command not found: %s\n", splited_arg[0]);
		free(bin_path);
		free_split(splited_arg);
		i++;
	}
	return (result);
}

static int	is_valid_cmd(char **new_arg, char **path)
{
	int		result;
	char	*bin_path;

	result = 0;
	bin_path = get_bin_path(path, new_arg[0]);
	if (bin_path)
		result = 1;
	free(bin_path);
	free_split(new_arg);
	return (result);
}

t_cmd	*set_cmd(int argc, char **argv, char **env)
{
	char	**path;
	size_t	i;
	size_t	k;
	t_cmd	*result;
	size_t	nb_valide_cmd;

	path = ft_split(get_path(env), ':');
	if (!path)
		return (NULL);
	nb_valide_cmd = get_nb_valide_cmd(argc, argv, path);
	if (!nb_valide_cmd)
		return (NULL);
	result = malloc(sizeof(t_cmd) * (nb_valide_cmd + 1));
	i = 0;
	k = 0;
	while (k < nb_valide_cmd)
	{
		if (is_valid_cmd(ft_split(argv[2 + i], ' '), path))
		{
			result[k].arg = get_arg(path, argv[2 + i]);
			result[k].env = env;
			k++;
		}
		i++;
	}
	result[k].arg = NULL;
	free_split(path);
	return (result);
}

size_t	get_nb_cmd(t_cmd *cmd)
{
	size_t	i;

	if (!cmd)
		return (0);
	i = 0;
	while (cmd[i].arg)
		i++;
	return (i);
}

void	unset_cmd(t_cmd	*cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i].arg)
		free_split(cmd[i++].arg);
	free(cmd);
}
