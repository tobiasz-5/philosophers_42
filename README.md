Implementation of Dijkstra's Dining Philosophers Problem [1965] to explore concurrency and synchronization.

Concurrency: Simulates philosophers' actions (eating, thinking, sleeping) using threads. <br/>
Synchronization: Ensures safe resource sharing with mutexes.<br/>
Deadlock Avoidance: Implements strategies to prevent circular dependencies.<br/>
Data Race Prevention: Protects shared variables with mutex locks for consistent state management.<br/>
Efficiency: Optimized for minimal overhead in managing shared resources.<br/>

Run:
./philosophers <philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number of meals(optional)]
