import pyvidardb

db = pyvidardb.DB()

opts = pyvidardb.Options()
opts.create_if_missing = True

s = db.open(opts, "./simple_test")
assert(s.ok())

opts = pyvidardb.WriteOptions()
s = db.put(opts, "key1", "value1")
assert (s.ok())

opts = pyvidardb.ReadOptions()
value = db.get(opts, "key1")
assert value == "value1"

opts = pyvidardb.WriteOptions()
s = db.delete(opts, "key1")
assert(s.ok())

db.close()
