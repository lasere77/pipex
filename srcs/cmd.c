/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 13:25:33 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/07 17:11:40 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "arg.h"
#include "utils.h"
#include "utils_cmd.h"
#include "ft_printf.h"

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
		if (bin_path || is_in_dir(ft_split(argv[2 + i], ' ')))
			result++;
		else
			ft_printf("command not found: %s\n", splited_arg[0]);
		free(bin_path);
		free_split(splited_arg);
		i++;
	}
	return (result);
}

static t_cmd	*set_cmd_loop(size_t nb_valid_cmd, char **argv,
							char **env, char **path)
{
	size_t	i;
	size_t	k;
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), (nb_valid_cmd + 1));
	if (!cmd)
		return (NULL);
	i = 0;
	k = 0;
	while (k < nb_valid_cmd)
	{
		if (is_in_dir(ft_split(argv[2 + i], ' '))
			|| is_valid_cmd(ft_split(argv[2 + i], ' '), path))
		{
			cmd[k].arg = get_arg(path, argv[2 + i]);
			printf("la -> %s\n", cmd[k].arg[0]);
			cmd[k].env = env;
			k++;
		}
		i++;
	}
	return (cmd);
}

t_cmd	*set_cmd(int argc, char **argv, char **env)
{
	char	**path;
	size_t	nb_valid_cmd;
	t_cmd	*cmd;

	path = ft_split(get_path(env), ':');
	if (!path)
		return (NULL);
	nb_valid_cmd = get_nb_valide_cmd(argc, argv, path);
	if (!nb_valid_cmd)
		return (NULL);
	cmd = set_cmd_loop(nb_valid_cmd, argv, env, path);
	free_split(path);
	return (cmd);
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
