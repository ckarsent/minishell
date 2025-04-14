/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pingouin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:29:57 by qboutel           #+#    #+#             */
/*   Updated: 2025/04/11 02:42:28 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_logo(void)
{
	printf(WHITE"\n                 _nnnn_\n                dGGGGMMb\n");
	printf("               @p~qp~~qMb\n               M|"RST);
	printf(BLUE BOLD"@"RST);
	printf(WHITE"||"RST);
	printf(BLUE BOLD"@"RST);
	printf(WHITE") M|\n               @"RST);
	printf(YELLOW BOLD",----."RST);
	printf(WHITE"JM|\n              JS"RST);
	printf(YELLOW BOLD" \\__/  "RST);
	printf(WHITE"qKL\n             dZP        qKRb\n            dZP");
	printf("          qKKb\n           fZP            SMMb\n           ");
	printf("HZM            MMMM\n           FqM            MMMM\n"RST);
	printf(YELLOW BOLD"         __| ^.        |\\"RST);
	printf(WHITE"dS"RST);
	printf(YELLOW BOLD"^"RST);
	printf(WHITE"qML\n"RST);
	printf(YELLOW BOLD"         |    `.       | `' \\"RST);
	printf(WHITE"Zq\n"RST);
	printf(YELLOW BOLD"        _)      \\.___.,|");
	printf("     .'\n        \\____   )"RST);
	printf(WHITE"MMMMMP"RST);
	printf(YELLOW BOLD"|   .'\n             `-'       `--' \n"RST);
}

void	print_minishell(void)
{
	printf(BLUE BOLD"___  ___ _         _       _            _  _ \n");
	printf("|  \\/  |(_)       (_)     | |          | || |\n");
	printf("| .  . | _  _ __   _  ___ | |__    ___ | || |\n"RST);
	printf(YELLOW BOLD"| |\\/| || || '_ \\ | |/ __|| '_ \\  / _ \\| || |\n");
	printf("| |  | || || | | || |\\__ \\| | | ||  __/| || |\n"RST);
	printf(WHITE BOLD"\\_|  |_/|_||_| |_||_||___/|_| |_| \\___||_||_|\n\n"RST);
}
