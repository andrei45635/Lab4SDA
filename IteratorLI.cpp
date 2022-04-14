#include "IteratorLI.h"
#include "LI.h"
#include <exception>

IteratorLI::IteratorLI(const LI& li) : lista(li) {
    /* de adaugat */
    this->index = lista.prim;
}

void IteratorLI::prim() {
    /* de adaugat */
    this->index = this->lista.prim;
}

void IteratorLI::urmator() {
    /* de adaugat */
    if (!valid()) {
        throw std::exception("iterator invalid!\n");
    }
    else {
        this->index++;
    }
}

bool IteratorLI::valid() const {
    /* de adaugat */
    return this->index >= 0;
}

TElem IteratorLI::element() const {
    /* de adaugat */
    if (!valid()) {
        throw std::exception("iterator invalid!\n");
    } else return this->lista.elems[this->index];
}
