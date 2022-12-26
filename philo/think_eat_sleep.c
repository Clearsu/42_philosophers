/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think_eat_sleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jincpark <jincpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:39:12 by jincpark          #+#    #+#             */
/*   Updated: 2022/12/18 22:37:53 by jincpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "philo.h"

void	check_eat_left(t_philo *philo)
{
	philo->eat_reps--;
	pthread_mutex_lock(philo->mutex_eat);
	if (philo->eat_reps == 0)
		*philo->eat_left = *philo->eat_left - 1;
	if (*philo->eat_left > 0)
		pthread_mutex_unlock(philo->mutex_print);
	pthread_mutex_unlock(philo->mutex_eat);
}

void	philo_think_and_get_forks(t_philo *philo)
{
	print_in_mutex(philo, philo->msg.think);
	pthread_mutex_lock(philo->right_hand);
	print_in_mutex(philo, philo->msg.take);
	pthread_mutex_lock(philo->left_hand);
	print_in_mutex(philo, philo->msg.take);
}

void	philo_eat(t_philo *philo)
{
	time_t	now;
	time_t	eat_limit;

	now = get_time_in_mili();
	pthread_mutex_lock(philo->mutex_philo);
	philo->limit = now + philo->time.to_die;
	pthread_mutex_unlock(philo->mutex_philo);
	pthread_mutex_lock(philo->mutex_print);
	printf("%ld %d %s\n", get_timestamp(philo), philo->id, philo->msg.eat);
	pthread_mutex_unlock(philo->mutex_print);
	eat_limit = now + philo->time.to_eat;
	philo->eat_limit = eat_limit;
	while (get_time_in_mili() < eat_limit)
		usleep(300);
	pthread_mutex_unlock(philo->right_hand);
	pthread_mutex_unlock(philo->left_hand);
}

void	philo_eat_opt(t_philo *philo)
{
	time_t	now;
	time_t	eat_limit;

	now = get_time_in_mili();
	pthread_mutex_lock(philo->mutex_philo);
	philo->limit = now + philo->time.to_die;
	pthread_mutex_unlock(philo->mutex_philo);
	pthread_mutex_lock(philo->mutex_print);
	printf("%ld %d %s\n", get_timestamp(philo), philo->id, philo->msg.eat);
	check_eat_left(philo);
	eat_limit = now + philo->time.to_eat;
	philo->eat_limit = eat_limit;
	while (get_time_in_mili() < eat_limit)
		usleep(300);
	pthread_mutex_unlock(philo->right_hand);
	pthread_mutex_unlock(philo->left_hand);
}

void	philo_sleep(t_philo *philo)
{
	time_t	sleep_limit;

	print_in_mutex(philo, philo->msg.sleep);
	sleep_limit = philo->eat_limit + philo->time.to_sleep;
	while (get_time_in_mili() < sleep_limit)
		usleep(300);
}
