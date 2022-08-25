all: doxygen doxybook

serve:
	mkdocs serve

doxybook:
	doxybook2 -i doxygen/xml -o docs/doxygen -c doxybook.json

.PHONY: doxygen
doxygen:
	C:/"Program Files"/doxygen/bin/doxygen.exe