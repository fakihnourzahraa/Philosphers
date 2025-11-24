void print_separator(const char *title)
{
    printf("\n");
    printf("================================================================================\n");
    printf("  %s\n", title);
    printf("================================================================================\n");
}

void test_fork_initialization(t_rules *rules)
{
    print_separator("FORK INITIALIZATION TEST");
    
    printf("Total forks allocated: %d\n", rules->num);
    printf("Forks array address: %p\n\n", (void*)rules->forks);
    
    if (rules->forks == NULL)
    {
        printf("❌ ERROR: Forks array is NULL!\n");
        return;
    }
    
    printf("Individual fork addresses:\n");
    for (int i = 0; i < rules->num; i++)
    {
        printf("  Fork[%d]: %p\n", i, (void*)&rules->forks[i]);
    }
    printf("\n✓ Fork initialization appears correct\n");
}

void test_philosopher_initialization(t_philosophers **philos, t_rules *rules)
{
    print_separator("PHILOSOPHER INITIALIZATION TEST");
    
    printf("Testing %d philosophers:\n\n", rules->num);
    
    bool all_valid = true;
    
    for (int i = 0; i < rules->num; i++)
    {
        printf("Philosopher %d:\n", i);
        printf("  Index: %d %s\n", philos[i]->index, 
               (philos[i]->index == i) ? "✓" : "❌");
        printf("  Alive: %s\n", philos[i]->alive ? "true" : "false");
        printf("  Ate: %s\n", philos[i]->ate ? "false (correct)" : "true (wrong)");
        printf("  Rules pointer: %p %s\n", (void*)philos[i]->rules,
               (philos[i]->rules != NULL) ? "✓" : "❌ NULL");
        
        if (philos[i]->rules == NULL)
        {
            printf("  ❌ ERROR: Rules pointer is NULL!\n");
            all_valid = false;
        }
        else if (philos[i]->rules != rules)
        {
            printf("  ❌ ERROR: Rules pointer doesn't match main rules!\n");
            printf("     Expected: %p, Got: %p\n", (void*)rules, (void*)philos[i]->rules);
            all_valid = false;
        }
        printf("\n");
    }
    
    printf("%s Philosopher initialization\n", all_valid ? "✓" : "❌");
}

void test_fork_assignments(t_philosophers **philos, t_rules *rules)
{
    print_separator("FORK ASSIGNMENT TEST");
    
    bool all_correct = true;
    
    printf("Testing fork assignments for %d philosophers:\n\n", rules->num);
    
    for (int i = 0; i < rules->num; i++)
    {
        pthread_mutex_t *expected_left = &rules->forks[i];
        pthread_mutex_t *expected_right = &rules->forks[(i + 1) % rules->num];
        
        printf("Philosopher %d:\n", i);
        printf("  Left fork:\n");
        printf("    Expected: %p (fork[%d])\n", (void*)expected_left, i);
        printf("    Actual:   %p", (void*)philos[i]->left);
        
        if (philos[i]->left == NULL)
        {
            printf(" ❌ NULL!\n");
            all_correct = false;
        }
        else if (philos[i]->left == expected_left)
            printf(" ✓\n");
        else
        {
            printf(" ❌ WRONG!\n");
            all_correct = false;
        }
        
        printf("  Right fork:\n");
        printf("    Expected: %p (fork[%d])\n", (void*)expected_right, (i + 1) % rules->num);
        printf("    Actual:   %p", (void*)philos[i]->right);
        
        if (philos[i]->right == NULL)
        {
            printf(" ❌ NULL!\n");
            all_correct = false;
        }
        else if (philos[i]->right == expected_right)
            printf(" ✓\n");
        else
        {
            printf(" ❌ WRONG!\n");
            all_correct = false;
        }
        printf("\n");
    }
    
    printf("Overall: %s\n", all_correct ? "✓ ALL CORRECT" : "❌ ERRORS FOUND");
}

void test_fork_sharing(t_philosophers **philos, t_rules *rules)
{
    print_separator("FORK SHARING TEST");
    
    printf("Verifying adjacent philosophers share forks:\n\n");
    
    bool all_shared = true;
    
    for (int i = 0; i < rules->num; i++)
    {
        int next = (i + 1) % rules->num;
        
        printf("Philosophers %d and %d:\n", i, next);
        printf("  P%d's right fork: %p\n", i, (void*)philos[i]->right);
        printf("  P%d's left fork:  %p", next, (void*)philos[next]->left);
        
        if (philos[i]->right == philos[next]->left)
            printf(" ✓ SHARED\n");
        else
        {
            printf(" ❌ NOT SHARED!\n");
            all_shared = false;
        }
        printf("\n");
    }
    
    printf("Overall: %s\n", all_shared ? "✓ ALL FORKS SHARED CORRECTLY" : "❌ SHARING ERRORS");
}

void print_table_diagram(t_rules *rules)
{
    print_separator("CIRCULAR TABLE DIAGRAM");
    
    printf("The table should look like this:\n\n");
    
    for (int i = 0; i < rules->num; i++)
    {
        printf("    Philosopher %d\n", i);
        printf("    /          \\\n");
        printf("Fork[%d]      Fork[%d]\n", i, (i + 1) % rules->num);
        printf("    \\          /\n");
        if (i < rules->num - 1)
            printf("    Philosopher %d\n\n", i + 1);
    }
    
    printf("\n    (Fork[%d] connects back to Philosopher 0)\n", rules->num);
    printf("\nEach fork is shared between two adjacent philosophers.\n");
}

int main(int argc, char **argv)
{
    t_rules *rules;
    t_philosophers **philos;
    
    print_separator("PHILOSOPHERS DINING PROBLEM - COMPREHENSIVE TEST");
    
    if (argc != 5 && argc != 6)
    {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [must_eat_count]\n", argv[0]);
        printf("Example: %s 5 800 200 200 7\n", argv[0]);
        return (1);
    }
    
    // Initialize rules
    rules = init_in(argv);
    if (!rules)
    {
        printf("❌ Failed to allocate rules structure\n");
        return (1);
    }
    
    // Fill in rules with command line arguments
    if (!fill_in(rules, argv))
    {
        printf("❌ Invalid arguments provided\n");
        return (1);
    }
    
    // Print parsed rules
    print_separator("PARSED RULES");
    printf("Number of philosophers: %d\n", rules->num);
    printf("Time to die: %lld ms\n", rules->t_to_die);
    printf("Time to eat: %lld ms\n", rules->t_to_eat);
    printf("Time to sleep: %lld ms\n", rules->t_to_sleep);
    printf("Must eat count: %d %s\n", rules->must_eat, 
           (rules->must_eat == -1) ? "(unlimited)" : "");
    printf("Start time: %lld ms\n", rules->start_time);
    
    // Test 1: Fork initialization
    test_fork_initialization(rules);
    
    // Initialize philosophers
    print_separator("INITIALIZING PHILOSOPHERS");
    printf("Calling fill_philo()...\n");
    philos = fill_philo(rules);
    printf("✓ fill_philo() completed\n");
    
    // Test 2: Philosopher initialization
    test_philosopher_initialization(philos, rules);
    
    // Test 3: Fork assignments
    test_fork_assignments(philos, rules);
    
    // Test 4: Fork sharing
    test_fork_sharing(philos, rules);
    
    // Test 5: Table diagram
    print_table_diagram(rules);
    
    // Final summary
    print_separator("TEST SUMMARY");
    printf("If all tests show ✓, your initialization is correct!\n");
    printf("If you see ❌, review the corresponding section for issues.\n");
    printf("\nPress Ctrl+C to exit (threads not started in test mode)\n");
    
    // Don't actually start the threads - this is just for testing initialization
    printf("\n(Not starting philosopher threads in test mode)\n");
    
    // Cleanup would go here in a real program
    
    return (0);
}
