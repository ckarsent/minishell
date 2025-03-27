/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:30:05 by qboutel           #+#    #+#             */
/*   Updated: 2025/03/26 15:49:29 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parsing_line(char *line, t_token **head, t_cmd **cmd)
{
	if (check_quote(line) == -1)
		return (ft_putstr_fd("Bad quote\n", 2), -1);
	tokenize(line, head);
	which_type(head);
	if (error_malloc(*head) == -1)
		return (ft_putstr_fd("malloc error\n", 2), -1);
	if (error_syntaxe(*head) == -1)
		return (ft_putstr_fd("syntax error\n", 2), -1);
	print_full_list(*head);
	*cmd = split_pipe(*head);
	print_full_list_cmd(*cmd);
	return (0);
}
