ifdef OS
	# Windows
        DG = C:/"Program Files"/doxygen/bin/doxygen.exe
	RMr = del /S /Q ".\docs\doxygen\*.*" && for /d %p in (".\docs\doxygen\*.*") do rmdir "%p" /s /q
else
        # Linux/Unix
	DG = doxygen
	RMr = rm -rf docs/doxygen/*
endif

all: doxygen doxybook

serve:
	mkdocs serve

doxybook:
	# This version of doxybook is used only for MKDocs and does not work on Github
	$(RMr)
	doxybook2 -i doxygen/xml -o docs/doxygen -c .doxybook/mkdocs.json

doxybook-git:
	# doxybook-git has different naming rules, so the documentation works on Github
	$(RMr)
	doxybook2 -i doxygen/xml -o docs/doxygen -c .doxybook/git.json

.PHONY: doxygen
doxygen:
	$(DG)
