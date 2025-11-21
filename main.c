/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:47:09 by nfakih            #+#    #+#             */
/*   Updated: 2025/11/21 18:34:46 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"
#include "philo.h"

// Function to print fork mutex addresses and status
void print_forks(t_rules *rules) {
    printf("\n=== FORK INFORMATION ===\n");
    printf("Total forks: %d\n", rules->num);
    printf("Fork array address: %p\n", (void*)rules->forks);
    
    for (int i = 0; i < rules->num; i++) {
        printf("Fork[%d] address: %p\n", i, (void*)&rules->forks[i]);
    }
}

// Function to print philosopher fork assignments
void print_philosophers_forks(t_philosophers *philos, int num_philos) {
    printf("\n=== PHILOSOPHER FORK ASSIGNMENTS ===\n");
    
    for (int i = 0; i < num_philos; i++) {
        printf("Philosopher %d:\n", i);
        printf("  Left fork:  %p", (void*)philos[i].left);
        printf("  Right fork: %p", (void*)philos[i].right);
        
        // Show which fork index each pointer corresponds to
        printf("  (Left=fork[%d], Right=fork[%d])\n", 
               i, (i + 1) % num_philos);
    }
    printf("=====================================\n\n");
}

// Function to verify fork assignments are correct
void verify_fork_assignments(t_philosophers *philos, t_rules *rules) {
    printf("\n=== FORK ASSIGNMENT VERIFICATION ===\n");
    
    bool all_correct = true;
    
    for (int i = 0; i < rules->num; i++) {
        // Expected addresses
        pthread_mutex_t *expected_left = &rules->forks[i];
        pthread_mutex_t *expected_right = &rules->forks[(i + 1) % rules->num];
        
        // Actual addresses
        pthread_mutex_t *actual_left = philos[i].left;
        pthread_mutex_t *actual_right = philos[i].right;
        
        printf("Philosopher %d:\n", i);
        printf("  Left fork:  Expected %p, Got %p %s\n", 
               (void*)expected_left, (void*)actual_left,
               (expected_left == actual_left) ? "✓" : "✗");
        printf("  Right fork: Expected %p, Got %p %s\n", 
               (void*)expected_right, (void*)actual_right,
               (expected_right == actual_right) ? "✓" : "✗");
        
        if (expected_left != actual_left || expected_right != actual_right) {
            all_correct = false;
        }
    }
    
    printf("\nOverall verification: %s\n", all_correct ? "✓ PASS" : "✗ FAIL");
    printf("=====================================\n\n");
}

// Function to visualize the circular table
void print_table_visual(t_rules *rules) {
    printf("\n=== CIRCULAR TABLE VISUALIZATION ===\n");
    printf("Format: P# (left[#] | right[#])\n\n");
    
    for (int i = 0; i < rules->num; i++) {
        printf("P%d (fork[%d] | fork[%d])\n", 
               i, i, (i + 1) % rules->num);
    }
    
    printf("\nCircular nature:\n");
    printf("- Philosopher 0's right fork = Philosopher 1's left fork\n");
    printf("- Philosopher %d's right fork = Philosopher 0's left fork (wraparound)\n", 
           rules->num - 1);
    printf("=====================================\n\n");
}

// Function to test fork sharing between adjacent philosophers
void print_fork_sharing(t_philosophers *philos, int num_philos) {
    printf("\n=== FORK SHARING VERIFICATION ===\n");
    
    for (int i = 0; i < num_philos; i++) {
        int next_philo = (i + 1) % num_philos;
        
        printf("Philosophers %d and %d:\n", i, next_philo);
        printf("  P%d's right fork: %p\n", i, (void*)philos[i].right);
        printf("  P%d's left fork:  %p", next_philo, (void*)philos[next_philo].left);
        
        if (philos[i].right == philos[next_philo].left) {
            printf("  ✓ SHARED CORRECTLY\n");
        } else {
            printf("  ✗ NOT SHARED!\n");
        }
        printf("\n");
    }
    printf("==================================\n\n");
}


// Function to print rules
void print_rules(t_rules *rules)
{
    printf("\n=== RULES ===\n");
    printf("Number of philosophers: %d\n", rules->num);
    printf("Time to die: %lld ms\n", rules->t_to_die);
    printf("Time to eat: %lld ms\n", rules->t_to_eat);
    printf("Time to sleep: %lld ms\n", rules->t_to_sleep);
    printf("Must eat count: %d\n", rules->must_eat);
    printf("Start time: %lld ms\n", rules->start_time);
    printf("=============\n\n");
}

// Function to print a single philosopher
void print_philosophers(t_philosophers *philo, int index)
{
    printf("--- Philosopher %d ---\n", index);
    printf("Index: %d\n", philo->index);
    printf("Alive: %s\n", philo->alive ? "true" : "false");
    printf("Ate: %s\n", philo->ate ? "true" : "false");
    printf("Left fork: %p\n", (void*)philo->left);
    printf("Right fork: %p\n", (void*)philo->right);
    printf("Rules pointer: %p\n", (void*)philo->rules);
    
    if (philo->rules) {
        printf("  Rules->num: %d\n", philo->rules->num);
        printf("  Rules->t_to_die: %lld\n", philo->rules->t_to_die);
        printf("  Rules->t_to_eat: %lld\n", philo->rules->t_to_eat);
        printf("  Rules->t_to_sleep: %lld\n", philo->rules->t_to_sleep);
        printf("  Rules->must_eat: %d\n", philo->rules->must_eat);
    }
    printf("--------------------\n");
}

long long	get_time()
{
	long long		t;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	t = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (t);
}
void	init_forks(t_rules *in)
{
	int	i;

	i = 0;
	in->forks = malloc(sizeof(pthread_mutex_t) * in->num);
	while (i < in->num)
	{
		pthread_mutex_init(&in->forks[i], NULL);
		i++;
	}
}

int	fill_in(t_rules *in, char **argv)
{
	if (argv[1] && ft_atoi(argv[1]) > 0)
		in->num = ft_atoi(argv[1]);
	else
		return (0);
	if (argv[2] && ft_atoi(argv[2]) > 0)
		in->t_to_die = ft_atoi(argv[2]);
	else
		return (0);
	if (argv[3] && ft_atoi(argv[3]) > 0)
		in->t_to_eat = ft_atoi(argv[3]);
	else
		return (0);
	if (argv[4] && ft_atoi(argv[4]) > 0)
		in->t_to_sleep = ft_atoi(argv[4]);
	else
		return (0);
	if (argv[5] && ft_atoi(argv[5]) > 0)
		in->must_eat = ft_atoi(argv[5]);
	else if (argv[5] && ft_atoi(argv[5]) <= 0)
		return (0);
	else
		in->must_eat = -1;
	in->start_time = get_time();
	init_forks(in);
	return (1);
}

t_philosophers	*new_philo(t_rules in, int i, t_philosophers *philo)
{
	t_rules			*rules;
	
	philo->index = i;
	philo->alive = true;
	philo->ate = false;
	philo->left = NULL;
	philo->right = NULL;
	philo->rules = NULL;
	//philo->thread = NULL;
	philo->rules = malloc(sizeof(t_rules));
	philo->rules->monitor = in.monitor;
	philo->rules->must_eat = in.must_eat;
	philo->rules->num = in.num;
	philo->rules->t_start = in.t_start;
	philo->rules->t_to_die = in.t_to_die;
	philo->rules->t_to_eat = in.t_to_eat;
	philo->rules->t_to_sleep = in.t_to_sleep;
	return (philo);
}

t_philosophers	*init_philo(t_rules *old)
{
	int			i;
	int			j;
	t_philosophers *philos;
	int			num;
	t_rules		*in;

	i = 0;
	in = malloc(sizeof(t_rules));
	j = 0;
	num = old->num;
	philos = malloc(sizeof(t_philosophers) * num);
	while (i < num)
	{
		new_philo(*in, i, &(philos)[i]);
		i++;
	}
	while (j < num)
	{
		philos[j].left = &(in->forks)[j];
		philos[j].right = &(in->forks)[(j + 1) % num];
		j++;
	}
	return (philos);
}

t_rules	*init_in(char **argv)
{
//	pthread_t id;
	t_rules	 *in;

	in = malloc(sizeof(t_rules));
	in->num = 0;
	in->t_to_die = 0;
	in->t_to_eat = 0;
	in->t_to_sleep = 0;
	in->t_start = 0;
	in->must_eat = 0;
	return (in);
	(void)argv;
	//in->monitor = pthread_create(&id, 
}

void philo(t_rules *in)
{
    t_philosophers	*philos;

    philos = init_philo(in);
	//philo_routine(&philos);
}

int main(int argc, char **argv)
{
	t_rules			*in;
	t_philosophers	**philos;

    if (argc != 6 && argc != 5)
        return (1);
    in = init_in(argv);
    if (!fill_in(in, argv))
        return (1);
    printf("\nRules parsed successfully:\n");
    printf("num: %d\n", in->num);
    printf("t_to_die: %lld\n", in->t_to_die);
    printf("t_to_eat: %lld\n", in->t_to_eat);
    printf("t_to_sleep: %lld\n", in->t_to_sleep);
    printf("must_eat: %d\n", in->must_eat);
    philos = init_philo(in);
    return (0);
}