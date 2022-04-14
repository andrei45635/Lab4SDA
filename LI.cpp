#include <exception>
#include <iostream>
#include "LI.h"
#include "IteratorLI.h"

LI::LI() {
	/* de adaugat */
	this->cap = INIT_CAP;
	this->size = 0;
	this->elems = new TElem[cap];
	this->urm = new int[cap];
	this->prim = 0;
	this->primLiber = -1;
	this->head = -1;
}

int LI::dim() const {
	/* de adaugat */
	return this->size;
}


bool LI::vida() const {
	/* de adaugat */
	if (this->size <= 0) return true;
	else return false;
}

void LI::check_if_resize() {
	if (this->size >= this->cap) {
		int newcap = 2 * this->cap + 1;
		TElem* new_elems = new TElem[newcap];
		TElem* new_urm = new int[newcap];
		std::copy(this->elems + 0, this->elems + cap, new_elems + 0);
		std::copy(this->urm + 0, this->urm + cap, new_urm + 0);
		delete[] this->elems;
		this->elems = new_elems;
		delete[] this->urm;
		this->urm = new_urm;
		this->cap = newcap;
	}
}

// returnare element
// arunca exceptie daca i nu e valid
TElem LI::element(int i) const {
	/* de adaugat */
	if (i < 0 || i > this->size) {
		throw std::exception("invalid\n");
	}
	else return this->elems[i];
}

// modifica element de pe pozitia i si returneaza vechea valoare
// arunca exceptie daca i nu e valid
TElem LI::modifica(int i, TElem e) {
	/* de adaugat */
	if (i < 0 || i > this->size) {
		throw std::exception("invalid\n");
	}
	else if (!vida()) {
		IteratorLI it = this->iterator();
		it.prim();
		for (int i = 0; i < this->size; i++) {
			TElem current = it.element();
			if (current == i) {
				TElem old_val = elems[i];
				elems[i] = e;
				return old_val;
			}
			it.urmator();
		}
	}
}

// adaugare element la sfarsit
void LI::adaugaSfarsit(TElem e) {
	/* de adaugat */
	check_if_resize();
	this->elems[this->size] = e;
	this->urm[this->elems[this->size]] = this->elems[e];
	this->primLiber = this->urm[this->elems[this->size]];
	this->size++;
}

// adaugare element pe o pozitie i 
// arunca exceptie daca i nu e valid
void LI::adauga(int i, TElem e) {
	/* de adaugat */
	if (i < 0 || i > this->size) {
		throw std::exception("invalid\n");
	}
	//daca elementul e pe prima pozitie
	else if (vida() && i == 0) {
		check_if_resize();
		this->elems[i] = e;
		this->urm[i] = -1;
		this->primLiber = this->urm[i];
		this->size++;
	}
	//daca elementul e pe o pozitie aleatoare (nu ultima)
	else if (!vida() && i >= 0 ) {
		check_if_resize();
		//facem loc shiftand elementele
		for (int cnt = this->size; cnt > i; cnt--) {
			this->elems[cnt] = this->elems[cnt - 1];
		}
		TElem aux = this->elems[i];
		this->elems[i] = e;
		this->urm[i] = aux;
		this->primLiber = this->urm[this->urm[i]];
		this->size++;
	}
}

// sterge element de pe o pozitie i si returneaza elementul sters
// arunca exceptie daca i nu e valid
TElem LI::sterge(int i) {
	/* de adaugat */
	if (i < 0 || i >= this->size) {
		throw std::exception("invalid\n");
	}
	TElem cautat = this->elems[i];
	for (int cnt = 0; cnt < this->size; cnt++) {
		if (cnt == i) {
			this->elems[cnt] = this->elems[cnt + 1];
			this->size--;
		}
	}
	return cautat;
}

// cauta element si returneaza prima pozitie pe care apare (sau -1)
int LI::cauta(TElem e) const {
	/* de adaugat */
	if (!vida()) {
		IteratorLI it = this->iterator();
		it.prim();
		while (it.valid()) {
			TElem current = it.element();
			if (current == e) {
				return it.index;
			}
			it.urmator();
		}
	}
	return -1;
}

IteratorLI LI::iterator() const {
	return  IteratorLI(*this);
}

// destructor
LI::~LI() {
	/* de adaugat */
	delete[] this->elems;
	delete[] this->urm;
}
