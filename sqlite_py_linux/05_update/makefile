
test:
	make clean
	@[ ! -f test.db_back ] || cp test.db_back test.db
	python test.py
clean:
	rm -rf test.db
.PHONY:test
	
