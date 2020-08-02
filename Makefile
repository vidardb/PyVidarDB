reformat:
		@black setup.py
		@clang-format \
		-style=file -i -sort-includes \
		src/pyvidardb/db.cpp \
 		src/pyvidardb/iterator.cpp \
 		src/pyvidardb/options.cpp \
 		src/pyvidardb/pyvidardb.cpp \
 		src/pyvidardb/db.hpp \
 		src/pyvidardb/iterator.hpp \
 		src/pyvidardb/pyvidardb.hpp
		@echo "Reformat complete."

clean:
		@rm -rf \
		build \
		dist \
		src/*.egg-info \
		compact_example \
		iter_example \
		put_example \
		simple_example \
		examples/compact_example \
		examples/iter_example \
		examples/put_example \
		examples/simple_example || true
		@echo "The caches and generated files are removed successfully."


package:
		@rm dist/* || true
		@python3 setup.py sdist
		@echo "PyVidarDB is packaged successfully."


upload:
		@twine upload --repository=pypi dist/*


.PHONY: reformat clean package upload
