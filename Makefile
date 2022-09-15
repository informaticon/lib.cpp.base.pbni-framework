ifdef OS
	# Windows
        DG = C:/"Program Files"/doxygen/bin/doxygen.exe
else
        # Linux/Unix
	DG = doxygen
endif

all: doxygen doxybook

serve:
	mkdocs serve

doxybook:
	doxybook2 -i doxygen/xml -o docs/doxygen -c .doxybook/mkdocs.json

doxybook-git:
	doxybook2 -i doxygen/xml -o docs/doxygen -c .doxybook/git.json

.PHONY: doxygen
doxygen:
	$(DG)
