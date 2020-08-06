import lmdb
import time
import random
import string


# def random_string_generator(n):
#     return ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(n))


env = lmdb.open('./lmdb_experiment.lmdb', map_size=80*1024*1024*1024)
# latest_data = []

put_start = time.time()
with env.begin(write=True) as txn:
    for each in range(200000000):
        k = str(random.uniform(1, 10000)).encode()
        v = str(random.uniform(1, 10000)).encode()
        txn.put(k, v)
        # if each > 990000:
        #     latest_data.append(k)
put_end = time.time()
print("[Put]:", str(put_end - put_start))

# get_start = time.time()
# with env.begin() as txn:
#     for each in latest_data:
#         txn.get(each)
# get_end = time.time()
# print("[Get]:", str(get_end - get_start))
