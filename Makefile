ifdef OS
#	Windows
    DG = C:/"Program Files"/doxygen/bin/doxygen.exe
	RMr = del /S /Q .\docs\doxygen\*.* && for /d %%p in (.\docs\doxygen\*.*) do rmdir "%%p" /s /q
	LS = dir /B src
else
#	Linux/Unix
	DG = doxygen
	RMr = rm -rf docs/doxygen/*
	LS = ls src
endif

all: doxygen doxybook

serve:
	mkdocs serve

# This version of doxybook is used only for MKDocs and does not work on Github
doxybook:
	$(RMr)
	doxybook2 -i doxygen/xml -o docs/doxygen -c .doxybook/mkdocs.json

# doxybook-git has different naming rules, so the documentation works on Github
doxybook-git:
	$(RMr)
	doxybook2 -i doxygen/xml -o docs/doxygen -c .doxybook/git.json

format:
	cd src && clang-format -i $(shell $(LS))

.PHONY: doxygen
doxygen:
	$(DG)
