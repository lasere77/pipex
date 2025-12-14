/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:35:56 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/14 16:42:27 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "process.h"
#include "arg.h"

int	main(int argc, char *argv[], char *env[])
{
	t_cmd	*cmd;
	int		status;

	if (argc != 5)
	{
		write(1, "please use the format:", 22);
		write(1, "./pipex infile \"cmd1\" \"cmd2\" outfile\n", 37);
		return (1);
	}
	cmd = set_cmd(argc - 3, argv);
	if (!cmd || !env)
		return (1);
	status = pipex(cmd, env);
	unset_cmd(cmd);
	return (status);
}
