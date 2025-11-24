/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:46:25 by nour              #+#    #+#             */
/*   Updated: 2025/11/23 19:47:02 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	taking_fork(t_philosophers *philo, int s)
{
	long long	time;
	
	if (s == 0 || s == 3)
		pthread_mutex_lock(philo->left);
	else
		pthread_mutex_lock(philo->right);
	pthread_mutex_lock(philo->rules->print);
	time = get_time() - philo->rules->start_time;
	printf("%lld %d has taken a fork\n", time, philo->index);
	pthread_mutex_unlock(philo->rules->print);
}

void	thinking(t_philosophers *philo)
{
	long long time;

	pthread_mutex_lock(philo->rules->print);
	time = get_time() - philo->rules->start_time;
	printf("%lld %d is thinking\n", time, philo->index);
	pthread_mutex_unlock(philo->rules->print);
}

void	sleeping_philo(t_philosophers *philo)
{	
	long long time;

	pthread_mutex_lock(philo->rules->print);
	time = get_time() - philo->rules->start_time;
	printf("%lld %d is sleeping\n", time, philo->index);
	pthread_mutex_unlock(philo->rules->print);
	usleep(philo->rules->t_to_sleep * 1000);
}

void	eating(t_philosophers *philo)
{
	long long time;
	
	pthread_mutex_lock(philo->rules->print);
	time = get_time() - philo->rules->start_time;
	printf("%lld %d is eating\n", time, philo->index);
	philo->last_meal = time - philo->rules->start_time;
	philo->meals = philo->meals + 1;
	pthread_mutex_unlock(philo->rules->print);
	usleep(philo->rules->t_to_eat * 1000);
}
void	releasing_fork(t_philosophers *philo, int s)
{
	long long time;
	
	if (s == 0 || s == 3)
		pthread_mutex_unlock(philo->left);
	else
		pthread_mutex_unlock(philo->right);
}
