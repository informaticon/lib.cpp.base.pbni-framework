.Phony=clean build tests
SHELL=cmd.exe

build:
	if not exist build mkdir build
	
	pbc170 /f /m n /d test.pbt
	
	move /Y *.pbd build
	move /Y *.exe build
	copy /Y *.dll build

tests: build
	build\test.exe --run-all --testdata-dir test\testdata

clean:
	if exist build rmdir /S /Q build
