# Philosophers

Resolve the famous philosophers problem with 3 different programs using ```threads```,
```mutex```, ```semaphores``` and ```forks```.

### philo_one

Specific Rules:

- Forks are between each philosophers
- You have to use ```mutex``` to protect forks
- Each philosopher must be one thread

``` bash
./philo_one num_of_philosophers time_to_die time_to_eat time_to_sleep [max_eat]
```

### philo_two

Specific Rules:

- Forks are in the middle of the table
- You have to use ```sempahores``` to protect forks
- Each philosopher must be one thread

``` bash
./philo_two num_of_philosophers time_to_die time_to_eat time_to_sleep [max_eat]
```

### philo_three

Specific Rules:

- Forks are in the middle of the table
- You have to use ```sempahores``` to protect forks
- Each philosopher must be one process

``` bash
./philo_three num_of_philosophers time_to_die time_to_eat time_to_sleep [max_eat]
```

