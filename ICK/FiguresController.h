#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "xml/Figure.h"
#include "xml/tinyxml2/tinyxml2.h"
#include <vector>
/*
Klasa FiguresController s�u�y do wczytywania figur z pliku xml, oraz do ich rysowania.
Do wczytywania plik�w xml z kolorem i wierzcho�kami figur zosta� wykorzystany gotowy parser XML tinyxml2.
Do przechowywania informacji o figurze zosta�a utworzona osobna klasa o nazwie Figure, jej opis mo�na znale�� pliku nag��wkowym Figure.h .

*/
class FiguresController
{

private:
	/*
	Zmienna przechowuj�ca wszystkie wczytane figury.
	*/
	std::vector<Figure> figures;
	/* Funkcja s�u��ca do rysowania pojedynczej figury,
	Parametry: 
	figure - jest to obiekt typu Figure, kt�ry ma by� narysowany (opis klasy Figure znajduje si� w pliku Figure.h)
	height - wysoko�� na jakiej maja by� narysowana figura
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
	filename - �cie�ka do pliku xml, w kt�rym znajduj� si� figury.
	Do parsowania pliku xml wewn�trz metody u�ywany jest parser z biblioteki tinyxml2
	Wszystkie figury s� wczytywane do pola figures.
	Domy�lnie plik z figurami ma nazw� Resources/data/example.xml, aby j� zmieni�, wystarczy
	w funkcji main w lini 97 zmieni� nazw� pliku, na inn�, lecz nale�y pami�ta� o tym, aby
	nowy plik zachowywa� struktur� pliku examples.xml
	*/
	void loadFiguresFromFile(char *filename);
	/*
	Metoda za pomoc� funkcji opengl'a rysuje wszystkie figury znajduj�ce si� w polu figures.
	*/
	void paintFigures();
	/*
	Metoda wykonuj�ca dok�adnie to samo, co metoda paintFigures(), w funkcji main, do rysowania t�a, tworzony jest osobny kontroler, a metoda 
	paintBackground zosta�a stworzona po to, aby kod z maina by� czytelniejszy.
	*/
	void paintBackground();
};

