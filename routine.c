/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 14:55:36 by nfakih            #+#    #+#             */
/*   Updated: 2025/12/11 21:09:16 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*single_routine(void *arg)
{
	t_philosophers	*philo;
	long long		time;

	philo = (t_philosophers *)arg;
	pthread_mutex_lock(philo->rules->print);
	pthread_mutex_lock(philo->left);
	time = get_time() - philo->rules->start_time;
	printf("%lld %d has taken a fork\n", time, philo->index);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->rules->print);
	usleep(philo->rules->t_to_die * 1000);
	return (NULL);
}

void	kill_rules(t_rules *rules)
{
	if (rules->print)
	{
		free(rules->print);
		rules->print = NULL;
	}
	if (rules->death)
	{
		free(rules->death);
		rules->death = NULL;
	}
	if (rules->forks)
	{
		free(rules->forks);
		rules->forks = NULL;
	}
	if (rules)
	{
		free(rules);
		rules = NULL;
	}
}

void	kill_philo(t_philosophers **philo)
{
	int	i;
	int	amount;

	i = 0;
	amount = philo[0]->rules->philo_amount;
	kill_rules(philo[0]->rules);
	while (i < amount && philo && philo[i])
	{
		if (philo[i])
		{
			free(philo[i]);
			philo[i] = NULL;
		}
		i++;
	}
	if (philo)
	{
		free(philo);
		philo = NULL;
	}
}

void	philo_acting(t_philosophers *philo, int s)
{
	taking_forks(philo, s);
	eating(philo);
	releasing_forks(philo, s);
	sleeping_philo(philo);
	print_status(philo, "is thinking");
	usleep(1000);
}

void	*philos_routine(void *arg)
{
	t_philosophers	*philo;
	int				s;

	philo = (t_philosophers *)arg;
	if (philo->rules->philo_amount % 2 == 1 && philo->index
		== philo->rules->philo_amount)
		usleep(philo->rules->t_to_eat * 1000);
	while (1)
	{
		pthread_mutex_lock(philo->rules->death);
		if (philo->rules->finish_all == 1)
		{
			pthread_mutex_unlock(philo->rules->death);
			break ;
		}
		pthread_mutex_unlock(philo->rules->death);
		if (philo->index % 2 == 0)
			s = 0;
		else
			s = 1;
		philo_acting(philo, s);
	}
	return (NULL);
}

//void	*philos_routine(void *arg)
// {
// 	t_philosophers *philo;
// 	int				s;

// 	philo = (t_philosophers *)arg;
// 	while (1)
// 	{
// 		pthread_mutex_lock(philo->rules->death);
// 		if (philo->rules->finish_all == 1)
// 		{
// 			pthread_mutex_unlock(philo->rules->death);
// 			break;
// 		}
// 		pthread_mutex_unlock(philo->rules->death);
// 		if (philo->index % 2 == 0)
// 			s = 0;
// 		else
// 			s = 1;
// 		taking_forks(philo, s);
// 		taking_forks(philo, s + 2);
// 		eating(philo);
// 		releasing_forks(philo, s);
// 		releasing_forks(philo, s + 2);
// 		sleeping_philo(philo);
// 		print_status(philo, "is thinking");
// 		usleep(1000);
// 	}
// 	return (NULL);
// }