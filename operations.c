/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:46:25 by nour              #+#    #+#             */
/*   Updated: 2025/11/30 20:06:48 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philosophers *philo, char *statement)
{
	long long	time;

	pthread_mutex_lock(philo->rules->print);
	pthread_mutex_lock(philo->rules->death);
	if (philo->rules->finish_all == 1)
	{
		time = get_time() - philo->rules->start_time;
		printf("%lld %d %s\n", time, philo->index, statement);
	}

	pthread_mutex_unlock(philo->rules->print);
	pthread_mutex_unlock(philo->rules->death);
}

void	taking_forks(t_philosophers *philo, int s)
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

// void	taking_forks(t_philosophers *philo, int s)
// {
// 	long long	time;
// 	int			first;
// 	int			second;
	
// 	if (s == 0 || s == 3)
// 	{
// 		first = pthread_mutex_lock(philo->left);
// 		second = pthread_mutex_lock(philo->right);
// 	}
// 	else
// 	{
// 		first = pthread_mutex_lock(philo->right);
// 		second = pthread_mutex_lock(philo->left);
// 	}
// 	time = get_time() - philo->rules->start_time;
// 	if (first == 0)
// 		print_status(philo, "has taken a fork");
// 	if (second == 0)
// 		print_status(philo, "has taken a fork");
// 	if (first != 0 || second != 0)
// 		releasing_forks(philo, s);
// }

void	releasing_forks(t_philosophers *philo, int s)
{
	long long time;
	
	if (s == 0 || s == 3)
		pthread_mutex_unlock(philo->left);
	else if (s == 1 || s == 2)
		pthread_mutex_unlock(philo->right);
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
	philo->last_meal = get_time();
	//philo->last_meal = time;
	philo->meals = philo->meals + 1;
	pthread_mutex_unlock(philo->rules->print);
	usleep(philo->rules->t_to_eat * 1000);
}
