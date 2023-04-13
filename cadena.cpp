//Pablo Garcia Bravo 

#include "cadena.hpp"
#include <stdexcept>
#include <iostream>
#include <cstring>


using namespace std;

///////////////CONSTRUCTORES///////////////////////// 
//Constructor por defecto
Cadena::Cadena(size_t tam, char c):  tam_{tam}, s_{new char[tam+1]}{
    for(size_t i=0; i < tam_; i++){     //rellenamos todos los caracteres uno a uno. En el caso que relleno sea nulo, se convierte en un espacio.
        s_[i] = c;
    }
    s_[tam] = '\0';
};

//Constructor a partir de una cadena de bajo nivel
Cadena::Cadena(const char* c):s_{new char[strlen(c)+1]}{
    //Copiamos con la libreria cstring
    tam_ = strlen(c);
    strcpy(s_,c);
};

//Constructor de copia
Cadena::Cadena(const Cadena& c):s_{new char[c.tam_+1]}{
    //Copiamos los elementos de la cadena c con la libreria string y luego copiamos el tamaño.
    tam_ = c.tam_;
    strcpy(s_,c.s_);
};

//Constructor de movimiento
Cadena::Cadena(Cadena&& cad):tam_(cad.tam_),  s_(cad.s_){
    //Movemos los elementos de cad al this y eliminamos cad
    cad.tam_ = 0; 
    cad.s_ = new char [1];      //Asignamos espacio de cad.s_ a 1 para que sea nulo
    cad.s_[0] = '\0';
};

/////////////////OPERADORES DE ASIGNACION///////////////
Cadena& Cadena::operator =(const Cadena& c){
    if(this != &c){     //Evitamos la autoasignacion y asignamos los datos a la clase 
        delete[] s_;
        s_ = new char[c.tam_];
        tam_ = c.tam_;
        strcpy(s_,c.s_);
    }
    return *this;
};

//Asignacion de movimiento
Cadena& Cadena::operator =(Cadena&& cad){
    //Movemos los elementos de cad al this y eliminamos cad
    if(this != &cad){
        tam_ = cad.tam_;
        delete[] s_;
        s_ = cad.s_;
        cad.s_ = new char[1];
        cad.s_[0] = '\0';
        cad.tam_ = 0;
    }
    return *this;
} 

///////////OPERADOR CONCATENAR/////////////////
Cadena& Cadena::operator+=(const Cadena& c){
    //Copiamos la cadena en un auxiliar
    char* aux = new char[tam_+1];
    strcpy(aux,s_);
    //Asignamos el tamaño de la cadena concatenada como la suma de ambas
    tam_ +=c.tam_;  
    //Eliminamos la cadena actual y asignamos el tamaño
    delete[] s_;
    s_ = new char[tam_ +1];
    //Copiamos la cadena
    strcpy(s_, aux);
    strcat(s_, c.s_);
    //Eliminamos la cadena auxiliar y devolvemos *this
    delete[] aux;
    return *this;
};

Cadena& operator +(const Cadena& c1, const Cadena& c2){
    //Creamos una cadena auxiliar con el constructor a partir de una cadena
    Cadena *aux = new Cadena(c1);
    *aux += c2;
    return *aux;
};

///////////////OPERADORES LOGICOS/////////////////

bool operator ==(const Cadena& cad1, const Cadena& cad2) {
    if(strcmp((const char*) cad1, (const char*) cad2) == 0) return true;
    else return false;
};

bool operator !=(const Cadena& cad1, const Cadena& cad2) {
    if (!(cad1 == cad2)) return true;
    else return false;
};

bool operator <(const Cadena& cad1, const Cadena& cad2) {
    if (strcmp((const char*) cad1, (const char*) cad2) < 0) return true;
    else return false;
};

bool operator >=(const Cadena& cad1, const Cadena& cad2) {
    if (!(cad1 < cad2)) return true;
    else return false;
};

bool operator >(const Cadena& cad1, const Cadena& cad2) {
    if(cad2 < cad1) return true;
    else return false;
};

bool operator <=(const Cadena& cad1, const Cadena& cad2) {
    if (!(cad2 < cad1)) return true;
    else return false;
};
////////////////////OPERADORES DE INSERCION Y EXTRACCION//////////////

std::ostream& operator <<(std::ostream& os, const Cadena& cad) noexcept{
    os << (const char*)cad;
    return os;
}

std::istream& operator >>(std::istream& is, Cadena& cad){
    //Creamos primero una cadena de bajo nivel
    char linea[33] = "";
    is.width(33);
    is >> linea;
    //LLamamos al constructor de cadena a partir de una cadena de bajo nivel.
    cad = linea;
    return is;
}

/////////////////////OPERADORES DE INDICE/////////////////////
//Funcion substr
Cadena Cadena::substr(size_t i, size_t tam) const{
    //Si el indice y el tamaño no son validos se lanza un error
    if(i + tam > tam_ || tam > tam_ || i > tam_) throw std::out_of_range("La funcion esta fuera de limites");
    else{
           //En caso contrario creamos una cadena auxiliar de tamaño tamano donde copiaremos la cadena.
        Cadena cad(tam);
        strncpy(cad.s_, s_ + i, tam);
        cad.s_[tam] = '\0';
        return cad;
    }
};

char& Cadena::at(size_t i){
    //Valida si el indice no supera al tamaño de la cadena. En caso de que si lo haga lanza un error
    if(i < tam_){
        return s_[i];
    }
    else{
        throw std::out_of_range("La funcion esta fuera de limites");
    }
};

const char& Cadena::at(size_t i) const{
    //Igual que la funcion anterior.
    if(i < tam_){
        return s_[i];
    }
    else{
        throw std::out_of_range("La funcion esta fuera de limites");
    }
};

///////////////////////DESTRUCTOR ////////////////////////////////
Cadena::~Cadena(){
    delete [] s_;
    tam_ = 0;
};
