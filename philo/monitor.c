/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jincpark <jincpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:17:36 by jincpark          #+#    #+#             */
/*   Updated: 2022/12/19 16:20:49 by jincpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"

void	check_if_died(t_info *info, int n,
		pthread_mutex_t *mutex_philo, t_philo *philo)
{
	int				i;
	time_t			now;

	mutex_philo = info->mutex_philo;
	philo = info->philo;
	while (1)
	{
		i = 0;
		now = get_time_in_mili();
		while (i < n)
		{
			pthread_mutex_lock(&mutex_philo[i]);
			if (now >= philo[i].limit)
			{
				pthread_mutex_lock(&info->mutex_print);
				printf("%ld %d died\n", get_timestamp(&philo[i]), philo[i].id);
				return ;
			}
			pthread_mutex_unlock(&mutex_philo[i++]);
		}
	}
}

void	check_if_died_or_all_have_eaten(t_info *info, int n,
		pthread_mutex_t *mutex_philo, t_philo *philo)
{
	int				i;
	time_t			now;
	pthread_mutex_t	*mutex_eat;

	mutex_eat = &info->mutex_eat;
	while (1)
	{
		i = 0;
		now = get_time_in_mili();
		while (i < n)
		{
			pthread_mutex_lock(&mutex_philo[i]);
			if (now >= info->philo[i].limit)
			{
				pthread_mutex_lock(&info->mutex_print);
				printf("%ld %d died\n", get_timestamp(&philo[i]), philo[i].id);
				return ;
			}
			pthread_mutex_unlock(&mutex_philo[i++]);
			pthread_mutex_lock(mutex_eat);
			if (!info->eat_left)
				return ;
			pthread_mutex_unlock(mutex_eat);
		}
	}
}

void	monitor(t_info *info)
{
	time_t	now;

	now = get_time_in_mili();
	set_start_and_limit(info->philo, info->n, now,
		now + info->philo[0].time.to_die);
	unlock_all_philos(info->mutex_philo, info->n);
	if (!info->philo[0].opt_flag)
		check_if_died(info, info->n,
			info->mutex_philo, info->philo);
	else
		check_if_died_or_all_have_eaten(info, info->n,
			info->mutex_philo, info->philo);
}
