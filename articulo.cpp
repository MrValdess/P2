//Pablo Garcia Bravo

#include "articulo.hpp"

using namespace std;

////////////CONSTRUCTORES/////////
//Constructor por defecto
Articulo::Articulo(const Cadena& r, const Cadena& t, const Fecha& f, double p, size_t st):
referencia_(r), titulo_(t), f_publi_(f), precio_(p), stock_(st){}

//////////////OPERADOR DE FLUJO/////////////////
std::ostream& operator <<(std::ostream& os, const Articulo& art) noexcept{
    os <<"[ "<< art.referencia()<<"] " << "[\" "<< art.titulo()<<"\"], "<< art.f_publi()<<". "<< setprecision(2) <<fixed << art.precio()<<" €";    
    return os;
}
