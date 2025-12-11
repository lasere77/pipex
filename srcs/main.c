/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:35:56 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/11 17:31:57 by mcolin           ###   ########.fr       */
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
		return (1);
	cmd = set_cmd(argc - 3, argv);
	status = pipex(cmd, env);
	unset_cmd(cmd);
	return (status);
}
