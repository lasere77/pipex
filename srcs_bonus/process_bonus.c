/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:08:24 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/15 19:56:43 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_bonus.h"
#include "process_utils_bonus.h"
#include "get_next_line.h"

static	int	here_doc(char *limiter)
{
	char	*str;
	char	*new_limiter;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipex");
		return (-1);
	}
	new_limiter = ft_strjoin(limiter, "\n");
	str = get_next_line(0);
	while (new_limiter && str
		&& ft_strncmp(str, new_limiter, ft_strlen(new_limiter)))
	{
		if (str)
			write(pipefd[1], str, ft_strlen(str));
		free(str);
		str = get_next_line(0);
	}
	free(str);
	free(new_limiter);
	close(pipefd[1]);
	return (pipefd[0]);
}

void	get_infile_outfile(t_cmd *cmd, int i, char **argv)
{
	if (cmd[i].infile)
	{
		if (!ft_strncmp(argv[1], "here_doc", 9))
			cmd[i].fd_in = here_doc(argv[2]);
		else if (access(cmd[i].infile, F_OK | R_OK) == 0)
			cmd[i].fd_in = open(cmd[i].infile, O_RDONLY);
		else
			panic_free(cmd, "acces", EXIT_FAILURE);
	}
	if (cmd[i].outfile)
	{
		if (!ft_strncmp(argv[1], "here_doc", 9))
			cmd[i].fd_out = open(cmd[i].outfile,
					O_RDONLY | O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
		{
			if (access(cmd[i].outfile, F_OK | W_OK) == 0)
				unlink(cmd[i].outfile);
			if (!cmd[i].outfile || *(cmd[i].outfile) == 0)
				panic_free(cmd, "acces", EXIT_FAILURE);
			cmd[i].fd_out = open(cmd[i].outfile,
					O_RDONLY | O_WRONLY | O_CREAT, 0644);
		}
	}
}

void	do_child(t_cmd *cmd, int i, char **env, char **argv)
{
	char	*bin_path;
	pid_t	pid;

	pid = fork();
	cmd[i].pid = pid;
	if (pid == -1)
		panic_free(cmd, "fork", EXIT_FAILURE);
	if (pid == 0)
	{
		get_infile_outfile(cmd, i, argv);
		bin_path = get_command(cmd, i, env);
		if (do_dup2(cmd, i))
		{
			free(bin_path);
			panic_free(cmd, "dup2", EXIT_FAILURE);
		}
		execve(bin_path, cmd[i].argv, env);
		free(bin_path);
		panic_free(cmd, "execve", 127);
	}
}

int	pipex(t_cmd *cmd, char **env, char **argv)
{
	int	pipefd[2];
	int	i;

	i = 0;
	while (cmd[i].valid)
	{
		if (!cmd[i].outfile)
		{
			if (pipe(pipefd) == -1)
				panic_free(cmd, "pipe", EXIT_FAILURE);
			cmd[i].fd_out = pipefd[1];
			cmd[i + 1].fd_in = pipefd[0];
		}
		do_child(cmd, i, env, argv);
		if (cmd[i].fd_in >= 0)
			close(cmd[i].fd_in);
		if (cmd[i].fd_out >= 0)
			close(cmd[i].fd_out);
		i++;
	}
	return (get_status(cmd));
}
