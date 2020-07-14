import pyvidardb

db = pyvidardb.DB()

db.open("./simple_example")

db.put("key1", "value1")

value = db.get("key1")
assert value == b"value1"

key_not_exist = db.get("key2")
assert key_not_exist is None

db.compact()

db.delete("key1")

db.close()
