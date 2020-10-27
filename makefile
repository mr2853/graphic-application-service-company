FLTK_HEADERS = "C:\library\fltk-1.3.5"
FLTK_LIBS = "C:\library\fltk-1.3.5\lib"
LINK = -mwindows -lfltk -lole32 -luuid -lcomctl32
OUTPUT = projekat
build:
	g++ *.cpp Class/*.cpp gui/*.cpp -I$(FLTK_HEADERS) -L$(FLTK_LIBS) $(LINK) -o $(OUTPUT).exe
	$(OUTPUT).exe