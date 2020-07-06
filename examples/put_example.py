import pyvidardb
import time

db = pyvidardb.DB()

opts = pyvidardb.Options()
# Default size now is 512M
# opts.write_buffer_size = 512 * 1024 * 1024

db.open("./put_example", opts)

start = time.time()
for each in range(1000000):
    a = "key{}".format(each)
    b = "value{}".format(each)
    print(each)
    db.put(a, b)
end = time.time()
print("Running time: " + str(end-start))

db.close()
