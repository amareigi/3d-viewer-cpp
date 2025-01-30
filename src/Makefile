CC 							= c++ 
FLAG_COV 				= -O1 -g --coverage -fno-inline 
FLAG_ER 				= -Wall -Wextra -Werror -std=c++17 -fPIC
MODEL 					= model/*.cpp
CONTROLLER 			= controller/*.cpp
VIEW						= view/*.cpp
MAIN_CPP				= main.cpp
OUTDIR 					= BUILD
TESTDIR 				= TESTS/*.cc
VIEWER 					= $(MODEL) $(CONTROLLER) $(VIEW) $(MAIN_CPP)
VIEWER_TESTS 		= $(MODEL)
GTESTS_O 				= gtest_*.o
FLAG_TESTS 			= -fPIC -L/usr/local/lib -lgtest -pthread -lgtest_main -lm -lgcov -I/usr/lib/qt5/bin -I/usr/local/include -I/usr/include -DQT_CORE_LIB -DQT_WIDGETS_LIB -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets-I/usr/include/x86_64-linux-gnu/qt5 -lGL -lQt5Core -lQt5Widgets -lQt5Gui -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5
INCPATH       	= -I../3dviewer -I. -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtOpenGL -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I. -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++

all: tests install gcov_report

tests: clean build
	for file in $(TESTDIR); do \
		$(CC) -c $(FLAG_ER) $(INCPATH) -c -o $(OUTDIR)/$$(basename $$file .cpp).o $$file; \
	done
	$(CC) $(FLAG_COV) $(FLAG_ER) $(INCPATH) -o $(OUTDIR)/tests $(VIEWER_TESTS) $(OUTDIR)/$(GTESTS_O) $(FLAG_TESTS) -DTESTS_MAIN
	./$(OUTDIR)/tests 

install: uninstal
	@echo "Начало установки"
	@tmpfile=$$(mktemp); \
	{	\
		mkdir ./BUILD; \
		cd ./BUILD && qmake ../view/ && make && cp viewer ../3dviewer; \
		cd ../; \
	} > $$tmpfile 2>&1; \
	rm $$tmpfile
	@echo "Установка успешно завершена."

uninstal:
	@rm -rf ./BUILD
	@rm -rf 3dviewer
	@echo "Программа удалена."

gcov_report: make_report report

make_report: 
	@gcovr --html-details --exclude-unreachable-branches $(TESTDIR) -o $(OUTDIR)/report.html
	@gcovr --html-details --object-directory=BUILD --exclude-unreachable-branches \
	--filter=model/'model.cpp' \
	--filter=model/'edge.cpp' \
	--filter=model/'figure.cpp' \
	--filter=model/'file_reader.cpp' \
	--filter=model/'model_operation_result.cpp' \
	--filter=model/'normalization_parameters.cpp' \
	--filter=model/'scene.cpp' \
	--filter=model/'three_d_point.cpp' \
	--filter=model/'vertex.cpp' \
	-o $(OUTDIR)/report.html;

report:
	@echo "..открытие отчета."
	@open $(OUTDIR)/report.html

style_check:
	@echo "Проверка стиля кода..."
	@cp ../materials/linters/.clang-format ./
	@find . -name "*.cpp" -o -name "*.h" | xargs clang-format -n > tmp.log 2>&1
	@if ! grep -q "warning" tmp.log; then \
		echo "\033[32mСтиль кода соответствует.\033[0m"; \
		else \
		echo "\033[31mСтиль кода не соответствует.\033[0m"; \
		fi
	@rm -rf .clang-format tmp.log

style_fix:
	@cp ../materials/linters/.clang-format ./
	@find . -name "*.cpp" -o -name "*.h" | xargs clang-format -i
	@echo "\033[33mСтиль кода исправлен.\033[0m";
	@rm -rf .clang-format

clean:
	@-rm -rf BUILD
	@-rm -rf dist
	@echo "Папка очищена."

build:
	@-rm -rf BUILD/*
	@mkdir -p BUILD

dist: 
	mkdir dist
	mkdir dist/src
	cp -r controller/ TESTS/ model/ obj_files/ view/ Makefile *.md dist/src/
	cd ./dist && tar cvzf $(TARGET)_v2.0.tgz *
	rm -rf dist/src/

dvi:
	@open ./readmeViewer.md
	@echo "Инструкция открыта."
