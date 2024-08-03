flag = -I"C:/SFML-2.6.1/include" -DSFML_STATIC -L"C:/SFML-2.6.1/lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg
all: TicTacToe run

TicTacToe:
	g++ *.cpp -o TicTacToe $(flag)

clean:
	del *.o 

run:
	.\TicTacToe.exe