# Philosophers
Задача про обедающих философов. Threads, mutexes, processes, semaphores and so forth. 
## Usage
### threads and mutexes:
make && ./philosophers $(количество философов) $(время жизни в мс) $(время еды в мс) $(время сна в мс) $(опционально: сколько раз должен поесть каждый философ перед тем как симуляция прекратится)
### processes and semaphores:
make && ./philosophers_bonus $(количество философов) $(время жизни в мс) $(время еды в мс) $(время сна в мс) $(опционально: сколько раз должен поесть каждый философ перед тем как симуляция прекратится)
