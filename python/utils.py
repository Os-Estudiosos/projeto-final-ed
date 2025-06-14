import time

def execution_time(func):
    def wrapper(*args, **kwargs):
        start = time.perf_counter()

        func(*args, **kwargs)

        end = time.perf_counter()

        total = end - start

        print(f"Demorou {total} segundos")
    
    return wrapper
