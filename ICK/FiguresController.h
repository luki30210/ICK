#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "xml/Figure.h"
#include "xml/tinyxml2/tinyxml2.h"
#include <vector>
/*
Klasa FiguresController s³u¿y do wczytywania figur z pliku xml, oraz do ich rysowania.
Do wczytywania plików xml z kolorem i wierzcho³kami figur zosta³ wykorzystany gotowy parser XML tinyxml2.
Do przechowywania informacji o figurze zosta³a utworzona osobna klasa o nazwie Figure, jej opis mo¿na znaleŸæ pliku nag³ówkowym Figure.h .

*/
class FiguresController
{

private:
	/*
	Zmienna przechowuj¹ca wszystkie wczytane figury.
	*/
	std::vector<Figure> figures;
	/* Funkcja s³u¿¹ca do rysowania pojedynczej figury,
	Parametry: 
	figure - jest to obiekt typu Figure, który ma byæ narysowany (opis klasy Figure znajduje siê w pliku Figure.h)
	height - wysokoœæ na jakiej maja byæ narysowana figura
	*/
	void paintFigure(Figure figure, float height);

	//int above = 0;

public:
	FiguresController();
	~FiguresController();
	/*
	Metoda zwraca wszystkie figury przechowywane w kontenerze.
	*/
	std::vector<Figure> getFigures() {
		return this->figures;
	}
	/*
	Metoda odpowiedzialna za wczytywanie figur z pliku, 
	Parametry:
	filename - œcie¿ka do pliku xml, w którym znajduj¹ siê figury.
	Do parsowania pliku xml wewn¹trz metody u¿ywany jest parser z biblioteki tinyxml2
	Wszystkie figury s¹ wczytywane do pola figures.
	Domyœlnie plik z figurami ma nazwê Resources/data/example.xml, aby j¹ zmieniæ, wystarczy
	w funkcji main w lini 97 zmieniæ nazwê pliku, na inn¹, lecz nale¿y pamiêtaæ o tym, aby
	nowy plik zachowywa³ strukturê pliku examples.xml
	*/
	void loadFiguresFromFile(char *filename);
	/*
	Metoda za pomoc¹ funkcji opengl'a rysuje wszystkie figury znajduj¹ce siê w polu figures.
	*/
	void paintFigures();
	/*
	Metoda wykonuj¹ca dok³adnie to samo, co metoda paintFigures(), w funkcji main, do rysowania t³a, tworzony jest osobny kontroler, a metoda 
	paintBackground zosta³a stworzona po to, aby kod z maina by³ czytelniejszy.
	*/
	void paintBackground();
};

