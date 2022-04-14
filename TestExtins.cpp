#include <assert.h>
#include <exception>
#include <iostream>

#include "TestExtins.h"
#include "LI.h"
#include "IteratorLI.h"

using namespace std;

void testCreare() {
	LI lista = LI();
	assert(lista.vida());
	IteratorLI it = lista.iterator();
	assert(it.valid());
	 try {
		 it.urmator();
	 }
	 catch (exception&) {
		 assert(true);
	 }
	assert(lista.dim() == 0);
}

void testAdauga() {
	LI lista = LI();
	lista.adaugaSfarsit(1);
	assert(!lista.vida());
	assert(lista.dim() == 1);
	assert(lista.element(0) == 1);
	try {
		lista.element(2);
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
	for (int i = 0; i <= 100; i++) {
		lista.adaugaSfarsit(i);
		lista.adauga(lista.dim() - 1, i);
		cout << lista.elems[i] << " ";
		try {
			lista.adauga((i + 2) * 2, i);
			assert(false);
		}
		catch (exception&) {
			assert(true);
		}
		assert(lista.dim() == 2 * (i + 1) + 1);
	}
	IteratorLI it = lista.iterator();
	assert(it.element() == 1);
	it.urmator();
	int i = 0;
	/*while (it.valid()) {
		cout << "first " << i << " " << it.index << " " << it.element() << "\n";
		assert(it.element() == i);
		it.urmator();
		cout << "second " << i << " " << it.index << " " << it.element() << "\n";
		assert(it.element() == i);
		it.urmator();
		cout << "third " << i << " " << it.index << " " << it.element() << "\n";
		i++;
	}*/
	it.prim();
	assert(it.valid());
	assert(it.element() == 1);
	i = 1;
	int v = 0;
	while (i < lista.dim()) {
		assert(lista.element(i) == v);
		i++;
		i++;
		v++;
	}
}

void testModificaStergeCauta() {
	LI lista = LI();
	for (int i = 0; i <= 100; i++) {
		lista.adaugaSfarsit(i);
	}
	assert(lista.dim() == 101);
	assert(lista.cauta(50) == 50);
	assert(lista.cauta(100) == 100);
	assert(lista.sterge(100) == 100);
	try {
		lista.sterge(100);
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
	assert(lista.dim() == 100);
	assert(lista.cauta(99) == 99);
	int v = 99;
	for (int i = 0; i < 100; i++) {
		lista.modifica(i, v);
		v--;
	}
	assert(lista.element(99) == 0);
	assert(lista.cauta(99) == 0);
	assert(lista.cauta(0) == 99);
	assert(lista.cauta(50) == 49);
	try {
		lista.modifica(v, v);
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
	IteratorLI it = lista.iterator();
	for (int i = 99; i > -1; i--) {
		assert(it.element() == i);
		it.urmator();
	}
	for (int i = 99; i > -1; i--) {
		lista.sterge(i);
		assert(lista.dim() == i);
	}
	assert(lista.vida());
	assert(lista.dim() == 0);
	it.prim();
}

void testAllExtins() {
	testCreare();
	testAdauga();
	testModificaStergeCauta();
}