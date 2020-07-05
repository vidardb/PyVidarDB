import pyvidardb

db = pyvidardb.DB()

opts = pyvidardb.Options()
opts.write_buffer_size = 512 * 1024 * 1024

db.open(opts, "./simple_example")

db.put("key1", "value1")

value = db.get("key1")
assert value == "value1"

key_not_exist = db.get("key2")
assert key_not_exist is None

db.delete("key1")

db.close()
