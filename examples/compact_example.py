import pyvidardb
import time

db = pyvidardb.DB()

opts = pyvidardb.Options()
opts.write_buffer_size = 4 * 1024 * 1024

db.open("./compact_example", opts)

for each in range(10000000):
    a = "key{}".format(each)
    b = "value{}".format(each)
    print(each)
    db.put(a, b)

# Commit it if you don't need to compact manually.
db.compact()

start = time.time()
for each in range(1000000):
    a = "key{}".format(each)
    db.get(a)
end = time.time()
print("Running time: " + str(end - start))

db.close()
