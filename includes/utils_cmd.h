/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 10:31:25 by mcolin            #+#    #+#             */
/*   Updated: 2025/12/07 10:38:29 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_CMD_H
# define UTILS_CMD_H

# include "utils.h"

char	is_last_cmd_valid(int argc, char *argv[], char *env[]);
char	is_valid_cmd(char **new_arg, char **path);

#endif