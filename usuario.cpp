//Pavlo Garcia Bravo

#include "usuario.hpp"


////////////////CLASE CLAVE/////////////////
//Constructores//
Clave::Clave(Cadena cad){
    if (cad.length() < 5){
        Clave::Incorrecta corta(CORTA);
        throw corta;
    }
    else{
        //Seleccionamos aleatoriamente caracteres dentro de un string que almacene todos los caracteres
        const char* caracteres = "abcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
        /*Cosas*/

        throw Clave::Incorrecta(ERROR_CRYPT);
    }
}

////////////////CLASE USUARIO/////////////////
//Constructores//
Usuario::Usuario(const Cadena& id, const Cadena& nom, const Cadena& apel, const Cadena& dir, Clave& con):ID_(id), nombre_(nom), apellidos_(apel), direccion_(dir), contrasena_(con){}