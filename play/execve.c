/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:57:21 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/25 11:57:26 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main()
{
	char *args[3];

	args[0] = "ls";
	args[1] = "-l";
	args[2] = NULL;
	execve("/bin/ls", args, NULL);
	printf("This line will not be executed.\n");

	return (0);
}
