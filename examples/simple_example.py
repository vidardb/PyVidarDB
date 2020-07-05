import pyvidardb

db = pyvidardb.DB()

opts = pyvidardb.Options()
opts.write_buffer_size = 512 * 1024 * 1024

s = db.open(opts, "./simple_example")
assert(s.ok())

s = db.put("key1", "value1")
assert (s.ok())

value = db.get("key1")
assert value == "value1"

s = db.delete("key1")
assert(s.ok())

db.close()
