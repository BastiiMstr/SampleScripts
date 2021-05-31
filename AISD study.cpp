#include <iostream>
using namespace std;

struct elem
{
	int dane;
	elem *prev;
};

void push(elem*& stos,int x)
{
	elem *nowy = new elem;
	nowy->dane = x;
	nowy->prev = stos;
	stos = nowy;
}
int pop(elem*& stos)
{
	if(stos != NULL)
	{
		int w = stos->dane;
		stos = stos->prev;
		return w;
	}
	return 0;
}
int topEl(elem *& stos)
{
	return stos->dane;
}

bool isEmpty(elem* stos) {
	if (stos == NULL)
		return true;
	return false; // usuń tą część
}

void reverseEl(elem*& stos)
{
	elem *nowy = new elem;
	while(!isEmpty(stos))
	{
		push(nowy, pop(stos));
	}
	stos = nowy;
}

void sortElementsWithAdditionalStack(elem*& stos)
{
	elem* nowy = NULL;

	int a;
	int b;
	bool ab = true;
	bool skip = true;
	bool sort = false;

	while (!sort)
	{
		ab = true;
		while (!isEmpty(stos))
		{
			if (ab == true)
			{
				a = pop(stos);
				ab = false;
			}
			else
				b = pop(stos);

			if(!skip)
				if (a >= b)
				{
				push(nowy, a);
				ab = true;
				}
				else
				{
				push(nowy, b);
				ab = false;
				}
			if (skip == true)
				skip = false;
		}

		stos = nowy;
		sort = true;

		a = pop(nowy);
		while (sort)
		{
			if (nowy != NULL)
			{
				b = pop(nowy);
				if (a < b)
					sort = false;
				a = b;
			}
			else
				break;
		}
	}
}


int main()
{
	elem* stos1 = NULL;

	cout << "Dodawanie elementów do stosu oraz pobranie wierzchołka" << endl;
	push(stos1, 1);
	push(stos1, 2);
	push(stos1, 3);
	push(stos1, 4);
	cout << topEl(stos1) << endl; // powinno być 4

	cout << "Pobranie wierzchołka i zdjęcie elementu" << endl;
	cout << pop(stos1) << endl; // powinno być 4
	cout << topEl(stos1) << endl; // powinno być 3

	cout << "Odwracanie elementów na stosie" << endl;
	reverseEl(stos1);
	cout << topEl(stos1) << endl; // powinno być 1

	cout << "Sortowanie elementów na stosie" << endl;
	sortElementsWithAdditionalStack(stos1);
	cout << topEl(stos1) << endl; // powinno być 3

	cout << "Przenoszenie elementów między stosami" << endl;
	elem* stos2 = NULL;
	elem* stos3 = NULL;
	// moveElementsWithAdditionalStack(stos1, stos2);
	// moveElementsWithAdditionalVariables(stos1, stos3);
	// cout << topEl(stos2) << endl; // powinno być 3
	// cout << topEl(stos3) << endl; // powinno być 3
}
