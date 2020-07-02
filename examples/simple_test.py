import pyvidardb

db = pyvidardb.DB()

opts = pyvidardb.Options()
opts.create_if_missing = True

s = db.open(opts, './simple_test')
assert(s.ok())

opts = pyvidardb.WriteOptions()
s = db.put(opts, b"key1", b"value1")
assert (s.ok())

opts = pyvidardb.ReadOptions()
blob = db.get(opts, b"key1")
print(blob.data)
print(blob.status.ok())

opts = pyvidardb.WriteOptions()
s = db.delete(opts, b"key1")
assert(s.ok())

db.close()
