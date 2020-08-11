#!/usr/bin/env bash

set -e

echo "Running VidarDB experiment..."
python3 vidardb_experiment.py >> vidardb_result.txt

echo "Running LMDB experiment..."
python3 lmdb_experiment.py >> lmdb_result.txt

echo "Running LSM experiment..."
python3 lsmdb_experiment.py >> lsm_result.txt

echo "All the experiments are finished! Please find the result in each [Database Name]_result.txt."
