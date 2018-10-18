.PHONY:	clean default
default:
	@echo "Commands:"
	@echo "    make svgtest"
	@echo "    make graphtest"
svgtest:	svgtest.cpp
	g++ svgtest.cpp -o svgtest --std=c++11 `pkg-config gtkmm-2.4 --cflags --libs`
graphtest:	graphtest.cpp
	g++ graphtest.cpp -o graphtest --std=c++11 `pkg-config gtkmm-2.4 --cflags --libs`
clean:
	rm -f svgtest image.svg graphtest
