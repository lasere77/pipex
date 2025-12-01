/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 10:00:00 by mcolin            #+#    #+#             */
/*   Updated: 2025/11/27 16:38:03 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "libft.h"

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int creat_process(char **argv, char *env[], int fd)
{
    pid_t	cpid;
    int     pipefd[2];

    pipe(pipefd);
    cpid = fork();
    if (cpid == -1)
	{
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (cpid == 0)
	{
        dup2(fd, STDIN_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        close(fd);
        close(pipefd[0]);
        close(pipefd[1]);
        execve(argv[0], argv, env);
    }
    close(pipefd[1]);
    close(fd);
    waitpid(cpid, NULL, 0);
    return (pipefd[0]);
}
