import pyvidardb
import time
import random
import string


# def random_string_generator(n):
#     return ''.join(random.choice(string.digits) for _ in range(n))

db = pyvidardb.DB()
db.open("vidardb_experiment.vidardb")
# latest_data = []

put_start = time.time()
for each in range(200000000):
    # k = random_string_generator(10).encode()
    # v = random_string_generator(10).encode()
    k = str(random.uniform(1, 10000)).encode()
    v = str(random.uniform(1, 10000)).encode()
    db.put(k, v)
put_end = time.time()
print("[Put]:", str(put_end - put_start))

# get_start = time.time()
# for each in latest_data:
#     db.get(each)
# get_end = time.time()
# print("[Get]:", str(get_end - get_start))

db.close()
