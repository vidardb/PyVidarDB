import pyvidardb
import time

db = pyvidardb.DB()

opts = pyvidardb.Options()
opts.write_buffer_size = 512 * 1024 * 1024

db.open(opts, "./put_example")

start = time.time()
for each in range(1000000):
    a = "key{}".format(each)
    b = "value{}".format(each)
    print(each)
    db.put(a, b)
end = time.time()
print("Running time: " + str(end-start))

db.close()
