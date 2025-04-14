/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:39:10 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/12 09:39:53 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    builtin_pwd()
{
	char *cwd;

	cwd = getcwd(NULL, 0);
    if (cwd != NULL)
	{
        printf("%s\n", cwd);
        free(cwd);
    }
	else
	{
        perror("getcwd");
        return ;
    }
}
