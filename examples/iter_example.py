import pyvidardb

db = pyvidardb.DB()

db.open("./iter_example")

for each in range(10):
    a = "key{}".format(each).encode()
    b = "value{}".format(each).encode()
    db.put(a, b)

db_iter = db.iter()
db_iter.seek()

while db_iter.valid():
    key, value = db_iter.key(), db_iter.value()
    print(key, value)
    db_iter.next()

db.deleteIterator(db_iter)

db.close()
