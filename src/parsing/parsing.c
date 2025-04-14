/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:30:05 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/13 16:18:52 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_line(char *line, t_token **htoken, t_cmd **hcmd, int last_exit)
{
	(void)hcmd;
	if (check_quote(line) == -1)
		return (ft_putstr_fd("Bad quote\n", 2), -1);
	tokenize(line, htoken, last_exit);
	which_type(htoken);
	//print_list_token(*htoken);
	if (error_malloc_token(*htoken) == -1)
		return (ft_putstr_fd("malloc token error\n", 2), -1);
	if (error_syntaxe(*htoken) == -1)
		return (ft_putstr_fd("syntax error\n", 2), -1);
	if (init_cmd(*htoken, hcmd) == -1)
		return (ft_putstr_fd("malloc cmd error\n", 2), -1);
	//print_list_cmd(*hcmd);
	return (0);
}
