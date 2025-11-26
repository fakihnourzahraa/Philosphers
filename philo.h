/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:08:50 by nfakih            #+#    #+#             */
/*   Updated: 2025/11/26 17:47:58 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "stdio.h"
# include "unistd.h"
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h>
# include "stdlib.h"

typedef struct s_philospher t_philosophers;
typedef struct s_rules
{
	int				philo_amount;
	long long		t_to_die;
	long long		t_to_eat;
	long long		t_to_sleep;
	int				to_eat;
	int				must_eat;
	long long		start_time;
	int				finish_all;
	pthread_mutex_t	*print;
	pthread_mutex_t	*death;
	pthread_t		monitor;
	t_philosophers	**philos;
	pthread_mutex_t *forks;
}	t_rules;


typedef struct s_philospher
{
	int				index;
	bool			alive;
	long long		last_meal;
	int				meals;
	pthread_t		thread;
	pthread_mutex_t *left;
	pthread_mutex_t	*right;
	t_rules			*rules;
}	t_philosophers;

int				ft_atoi(const char *nptr);
void			*philos_routine(void *arg);
long long		get_time();
void			init_forks(t_rules *in);
int				fill_in(t_rules *in, char **argv);
t_philosophers	*new_philo(t_rules *rules, int i, t_philosophers *philo);
t_philosophers	**fill_philo(t_rules *old);
t_rules			*init_in(void);
void			taking_fork(t_philosophers *philo, int s);
void			thinking(t_philosophers *philo);
void			sleeping_philo(t_philosophers *philo);
void			eating(t_philosophers *philo);
void			releasing_fork(t_philosophers *philo, int s);
void			dying(t_philosophers *philo);
void			*single_routine(void *arg);
void			*monitor_thread(void *arg);

#endif
