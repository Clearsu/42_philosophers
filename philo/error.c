/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jincpark <jincpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:17:10 by jincpark          #+#    #+#             */
/*   Updated: 2022/12/18 22:30:29 by jincpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	error_msg(int n, char *str)
{
	if (n == 0)
		printf("philo: invalid number of arguments\n");
	else if (n == 1)
		printf("philo: invalid argument : %s\n", str);
	else if (n == 2)
		printf("philo: memory allocation failed\n");
	else if (n == 3)
		printf("philo: mutex initiation failed\n");
	else if (n == 4)
		printf("philo: number out of range : %s\n", str);
	else if (n == 5)
		printf("philo: failed to create threads\n");
	else if (n == 6)
		printf("philo: failed to detach threads\n");
}
