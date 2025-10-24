.PHONY: build-cpro test-go install-dependencies test-clib

all:
	@make build-cpro
	@make test-go

build-cpro:
	@rm -rf clib/build || true
	@cd clib && cmake -B build && cd build && cmake --build .

test-go:
	go test -v .

install-dependencies:
	apt update && apt install libgtest-dev cmake

test-clib:
	@rm -rf clib/build || true
	@rm -r clib/log || true
	@cd clib && cmake -B build
	@mkdir clib/log
	@cd clib/build && cmake -DTEST=ON .. > cmakelog.txt && make > makelog.txt && ./tests/cryptopro_test > ../log/test_log.txt
