## Performance Experiments

This folder contains performance experiments scripts and results for
[PyVidarDB](https://github.com/vidardb/PyVidarDB),
[py-lmdb](https://github.com/jnwatson/py-lmdb), and
[python-lsm-db](https://github.com/coleifer/python-lsm-db).

To run the experiments:

```bash
sh ./run.sh
```

The default data amount for putting is 1 million. To change to another number, e.g.,
200 million, change the value of `put_range` to `200000000` in `vidardb_experiment.py`,
`lmdb_experiment.py`, and `lsmdb_experiment.py`.
