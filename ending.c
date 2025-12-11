/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:46:06 by nour              #+#    #+#             */
/*   Updated: 2025/12/11 21:53:05 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dying(t_philosophers *philo)
{
	long long	time;

	pthread_mutex_lock(philo->rules->print);
	time = get_time() - philo->rules->start_time;
	printf("%lld %d died\n", time, philo->index);
	pthread_mutex_unlock(philo->rules->print);
	pthread_mutex_lock(philo->rules->death);
	philo->rules->finish_all = 1;
	pthread_mutex_unlock(philo->rules->death);
}

long long	get_time(void)
{
	long long		t;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	t = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (t);
}
