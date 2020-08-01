import pyvidardb

db = pyvidardb.DB()

db.open("./simple_example")

db.put(b"key1", b"value1")

value = db.get(b"key1")
assert value == [b"value1"]

key_not_exist = db.get(b"key2")
assert key_not_exist is None

db.compact()

db_iter = db.iter()

while db_iter.valid():
    key, value = db_iter.key(), db_iter.value()
    assert key == b"key1"
    assert value == b"value1"
    db_iter.next()

db.delete(b"key1")

db.put(b"key1", [b"value1", b"value2"])
value = db.get(b"key1")
assert value == [b"value1", b"value2"]

db.close()
