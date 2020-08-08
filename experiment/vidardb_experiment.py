import os
import random
import shutil
import time
from datetime import datetime

import pyvidardb

# def random_string_generator(n):
#     return ''.join(random.choice(string.digits) for _ in range(n))

db_name = "vidardb_experiment.vidardb"
put_range = 1000000  # 200000000
latest_data_num = 5000
random_get_range = 5000

data_list = list()
latest_data_list = list()

if os.path.exists(db_name):
    shutil.rmtree(db_name)

db = pyvidardb.DB()
db.open(db_name)

now = datetime.now()
current_time = now.strftime("%H:%M:%S")

print("-------------------------------------")
print("Experiment start at: ", current_time)
print("[Put Data Number]: ", put_range)
print("[Latest Data Number]:", latest_data_num)
print("[Random Get Number]:", random_get_range)

put_start = time.time()
for each in range(put_range):
    # k = random_string_generator(10).encode()
    k = str(random.uniform(1, 10000)).encode()
    db.put(k, k)
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
for each in latest_data_list:
    db.get(each)
get_end = time.time()
print("[Get latest data]:", str(get_end - get_start))

db.compact()

get_start = time.time()
for each in data_list:
    db.get(each)
get_end = time.time()
print("[Get random data]:", str(get_end - get_start))

delete_start = time.time()
for each in data_list:
    db.delete(each)
delete_end = time.time()
print("[Delete random data]:", str(delete_end - delete_start))

print("-------------------------------------")
print()

db.close()
