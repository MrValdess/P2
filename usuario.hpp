//Pablo Garcia Bravo

#include "cadena.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"

#include <iostream>
#include <iomanip>
#include <locale>
#ifndef _USUARIO_HPP_
#define _USUARIO_HPP_
////////////////////CLASE CLAVE/////////////////

class Clave{
    public:
        //Constructor
        Clave(Cadena cad);

        //Metodos observadores
        Cadena clave() const noexcept;

        //Verificar
        bool verifica();

        //Clase Incorrecta y Razon
        enum Razon{CORTA, ERROR_CRYPT};
        
        class Incorrecta{
            public:
                Incorrecta(const Clave::Razon razon): razon_(razon){};
                Clave::Razon por_que() const{return razon_;};
            private:
                Clave::Razon razon_;
        };

    private:
        Cadena clave_;
        
};
//Metodos inline
inline Cadena Clave::clave()const noexcept{return clave_;}

////////////////CLASE USUARIO/////////////////
class Usuario{
    public:
        Usuario();

    private:

};

#endif // _USUARIO_HPP_