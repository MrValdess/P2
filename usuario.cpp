//Pavlo Garcia Bravo

#include "usuario.hpp"



//////////////CONSTRUCTOR////////////
Clave::Clave(Cadena cad){
    if (cad.length() < 5){
        throw Clave::Incorrecta(CORTA);
    }
    if(/*lo cifrado*/){
        throw Clave::Incorrecta(ERROR_CRYPT);
    }
    else{
        
    }
}