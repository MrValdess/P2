//Pablo Garcia Bravo 

#include "fecha.hpp"
#include <ctime>
#include <stdexcept>
#include <locale>
#include <iostream>
#include <cstdio>

using namespace std;

////////////////////CONSTRUCTORES//////////////////////
//Constructor por defecto
Fecha::Fecha(int d, int m, int a):dia_(d), mes_(m), anno_(a){
    std::time_t tiempo_calendario = std::time(nullptr);
    std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);  //almacenamos en una variable el tiempolocal del sistema con std::tm. En el caso de que alguno de los campos sea 0, se le asigna tm
    if(dia_ == 0) 
        dia_ = tiempo_descompuesto->tm_mday;
    if(mes_ == 0) 
        mes_ = tiempo_descompuesto->tm_mon +1;
    if(anno_ == 0) 
        anno_ = tiempo_descompuesto->tm_year + 1900;

    valida(dia_, mes_, anno_);
};

//Cambio de fecha a cadena
const char*Fecha::cadena () const{
    std::locale::global(locale("es_ES.utf8")); 
    char *aux = new char[100];
    //Creamos un auxiliar dinámico donde almacenaremos la fecha ya almacenada como cadena.
    tm fecha_actual{};

    fecha_actual.tm_mday = dia_;
    fecha_actual.tm_mon = mes_ -1;
    fecha_actual.tm_year = anno_ -1900;
    mktime(&fecha_actual);
    //Con el comando mktime realizamos en fecha_actual la fecha de los parametros dados.
    
    strftime(aux,100, "%A %e de %B de %Y", &fecha_actual);
    
    return aux;
};

//Constructor a partir de cadena de bajo nivel
Fecha::Fecha(const char* c){
    //Almacenamos lo contenido entre / en las variables privadas de la clase fecha. SI da error lanzamos un error de cadena incorrecta.
    if(sscanf(c,"%d/%d/%d", &dia_, &mes_, &anno_)!= 3){
        Invalida cad_incorrecta("Cadena incorrecta");
        throw cad_incorrecta;
    }
    *this = Fecha(dia_,mes_,anno_);     
};

//En el caso de que el dia, mes o el año no sea correcto, se lanza un mensaje de error
void Fecha::valida(int dia, int mes, int ano){
    if(ano <= AnnoMaximo && ano >= AnnoMinimo){     //Si los años estan entre los valores permitidos 
    //Una vez tratado febrero se comprueban el resto de los meses.
    
        //Si el dia es incorrecto en cualquiera de los meses, se lanza un error de dia incorrecto.
        if(ano%4==0 && (ano % 400 == 0 || ano % 100 != 0)) {  //Comprueba que el año sea bisiesto y comprobamos el mes de febrero.
            if (mes == 2 && (dia > 29 || dia < 0)){    //Si el dia en febrero no es valido, se lanza un error de dia incorrecto.
                Fecha::Invalida dia_noVal("Dia no valido");
                throw dia_noVal;
            }
        }
        else{   //Comprobamos febrero cuando el año no es bisiesto.
            if (mes == 2 && (dia > 28 || dia < 0)) {
                Fecha::Invalida dia_noVal("Dia no valido");
                throw dia_noVal;
            }
        }
        
        if ((mes < 13 && mes > 0)){    //Si el mes no es valido, se lanza un error de mes incorrecto.
            if(((mes  == 1 || mes  == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12) && (dia > 31 || dia < 0)) || ((mes  == 4 || mes  == 6 || mes == 9 || mes == 11) && (dia > 30 || dia < 0))){
                Fecha::Invalida dia_noVal("Dia no valido");
                throw dia_noVal;
            }
        }
        else{
            Fecha::Invalida mes_noVal("Mes no valido");
            throw mes_noVal;
        }
    } 
    else{  //En el caso de que el anno sea mayor que el maximo o menos que el minimo se lanza un error de anno incorrecto
        Fecha::Invalida anno_noVal("Anno no valido");
        throw anno_noVal;
    }
};


///////////////OPERADORES/////////////////
//Empleamos la funcion += como referencia para el resto de funciones de operadores lógicos, es decir, haremos operaciones a partir del operador +=
Fecha& Fecha::operator +=(int i){
    //Creamos una estructura de tiempo f con std::fm
    std:: tm f{};
    f.tm_mday = dia_ +i;
    f.tm_mon = mes_ - 1;
    f.tm_year = anno_ - 1900;
    std::mktime(&f);

    //Pasamos los parámetros a las variables y comprobamos que sean correctas
    dia_ = f.tm_mday;
    mes_ = f.tm_mon + 1;
    anno_ = f.tm_year + 1900;
    valida(dia_, mes_, anno_);
    return *this;
};

//En el resto de operadores usaremos el operador += como referencia.
Fecha& Fecha::operator ++(){
    *this += 1;
    return *this;
};

Fecha& Fecha::operator ++(int){
    Fecha *f = new Fecha(*this);
    *this += 1;           
    return *f;
};

//En los operadores -- y -= vemos que es igual que un += -i y += -1, respectivamente.
Fecha& Fecha::operator --(){
    *this += -1;
    return *this;
};

Fecha& Fecha::operator --(int){
    Fecha *f = new Fecha(*this);
    *this += -1;           
    return *f;
};

Fecha& Fecha::operator -=(int i){
    *this += -i;
    return *this;
};

/////////////OPERADORES ARITMETICOS///////////////

//Al igual que los operadores anteriores, se emplea el += como referencia.
Fecha& Fecha::operator +(int i) const{
    Fecha *f = new Fecha(*this);             
    return *f += i;
};

Fecha& Fecha::operator -(int i) const{
    Fecha *f = new Fecha(*this);
    return *f += -i;
};

///////////////OPERADORES LOGICOS/////////////////

bool operator ==(const Fecha& f1, const Fecha& f2) {
    if (!(f1 < f2) && !(f2 < f1)) return true;
    else return false;
    
};

bool operator !=(const Fecha& f1, const Fecha& f2) {
   if(!(f1 == f2)) return true;
   else return false;
};

bool operator <(const Fecha& f1, const Fecha& f2) {
    if (((f1.anno() == f2.anno()) && (f1.mes() == f2.mes()) && (f1.dia() < f2.dia())) || ((f1.anno() == f2.anno())&&(f1.mes() < f2.mes()))|| (f1.anno() < f2.anno())) return true;
    else return false;
};

bool operator >=(const Fecha& f1, const Fecha& f2) {
    if (!(f1 < f2)) return true;
    else return false;
};

bool operator >(const Fecha& f1, const Fecha& f2) {
     if(f2 < f1) return true;
     else return false;
};

bool operator <=(const Fecha& f1, const Fecha& f2) {
    if (!(f2 < f1)) return true;
    else return false;
};
	

////////////////OPERADORES DE INSERCION Y EXTRACCION////////////////////

std::ostream& operator <<(std::ostream& os, const Fecha& f) noexcept{       //Extraccion.

    os << f.cadena();       //Manda la fecha al output del sistema y lo devuelve
    return os;
};

std::istream& operator >>(std::istream& is, Fecha& f){
    char linea[11];     //Comprobamos que la fecha introducida en is es igual a la mandada. En caso de que no lo sea mandamos el error
    is.width(11);    
    is >> linea;
    try{
        f = Fecha{linea};
    }catch(const Fecha::Invalida e){
        is.setstate(ios::failbit);
        throw;
    }
    return is;
};
/////////////////////CONSTRUCTOR DE INVALIDA/////////////////////
Fecha::Invalida::Invalida(const char* inf):info_(inf){};



