/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:22:08 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/14 16:29:16 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_bonus.h"
#include "process_bonus.h"
#include "arg_bonus.h"

#include <stdio.h>

int	main(int argc, char *argv[], char *env[])
{
	t_cmd	*cmd;
	int		status;
	int		is_here_doc;

	if (argc < 5)
	{
		write(1, "please use the format:\n", 23);
		write(1, "./pipex infile \"cmd1\" ... \"cmdx\" outfile\n", 41);
		write(1, "./pipex here_doc LIMIT \"cmd1\" ... \"cmdx\" outfile\n", 49);
		return (1);
	}
	is_here_doc = 0;
	if (!ft_strncmp(argv[1], "here_doc", 9))
		is_here_doc = 1;
	cmd = set_cmd(argc - 3 - is_here_doc, &argv[is_here_doc]);
	if (!cmd || !env)
		return (1);
	status = pipex(cmd, env, argv);
	unset_cmd(cmd);
	return (status);
}
