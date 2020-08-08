import os
import random
import shutil
import time
from datetime import datetime

import lmdb

# def random_string_generator(n):
#     return ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(n))


db_name = "lmdb_experiment.lmdb"
put_range = 1000000  # 200000000
latest_data_num = 5000
random_get_range = 5000

data_list = list()
latest_data_list = list()

if os.path.exists(db_name):
    shutil.rmtree(db_name)

env = lmdb.open(db_name, map_size=80 * 1024 * 1024 * 1024)

now = datetime.now()
current_time = now.strftime("%H:%M:%S")

print("-------------------------------------")
print("Experiment start at: ", current_time)
print("[Put Data Number]: ", put_range)
print("[Latest Data Number]:", latest_data_num)
print("[Random Get Number]:", random_get_range)

put_start = time.time()
with env.begin(write=True) as txn:
    for each in range(put_range):
        k = str(random.uniform(1, 10000)).encode()
        txn.put(k, k)
        if each < random_get_range:
            data_list.append(k)
        else:
            d = random.randint(0, each)
            if d < random_get_range:
                data_list[d] = k
        if each > (put_range - latest_data_num):
            latest_data_list.append(k)
put_end = time.time()
print("[Put]:", str(put_end - put_start))

get_start = time.time()
with env.begin() as txn:
    for each in latest_data_list:
        txn.get(each)
get_end = time.time()
print("[Get latest data]:", str(get_end - get_start))

get_start = time.time()
with env.begin(write=True) as txn:
    for each in range(random_get_range):
        k = data_list[random.randint(0, len(data_list) - 1)]
        txn.get(k)
        txn.delete(k)
get_end = time.time()
print("[Get random data & delete]:", str(get_end - get_start))

print("-------------------------------------")
print()
