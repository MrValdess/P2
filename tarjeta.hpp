//Pablo Garcia Bravo

#ifndef _TARJETA_HPP_
#define _TARJETA_HPP_

#include <iostream>
#include <set>      //Mapas de tarjetas
#include <cctype>   //para isdigit
#include <iomanip>  

#include "fecha.hpp"
#include "cadena.hpp"
#include "usuario.hpp"

//Declaraciones anticipadas de las clases
class Usuario;

/*Declaramos primero la clase numero para que funcione la clase tarjeta*/

////////////////CLASE NUMERO/////////////////
class Numero{
    public:
        //Constructor
        Numero(const Cadena& cad);

        //Operador de conversion
        operator const char*() const noexcept;

        //Clase Incorrecta y Razon
        enum Razon{LONGITUD, DIGITOS, NO_VALIDO};
        
        class Incorrecto{
            public:
                Incorrecto(Numero::Razon razon);
                Numero::Razon razon() const noexcept{return razon_;};
            private:
                Numero::Razon razon_;
        };
    private:
        //Variables
        Cadena numero_;
};
//Metodos inline//
//Conversion a const char*
inline Numero::operator const char *()const noexcept{return numero_.c_str();}

//Operador menor que
inline bool operator <(const Numero& num1, const Numero& num2){return static_cast<Cadena>(num1) < static_cast<Cadena>(num2);};  //static cast para transformar de Numero a Cadena
//Constructor de la clase Incorrecta
inline Numero::Incorrecto::Incorrecto(Numero::Razon razon): razon_(razon){};


////////////////CLASE TARJETA/////////////////
class Tarjeta{
    public:
        //Constructores
        Tarjeta(const Numero& num, Usuario* user, const Fecha& fech);
        //Suprimimos el constructor de copia con delete, al igual que el operador de asignacion
        Tarjeta(Tarjeta& tar) = delete;
        Tarjeta& operator =(Tarjeta& tar) = delete;

        //Enumeracion tipo
        enum Tipo{Otro, VISA, Mastercard, Maestro, JBC, AmericanExpress};

        //Clases de excepciones
        class Caducada{
            public:
                Caducada(const Fecha& fech);
                const Fecha& cuando() const noexcept{return caducada_;};
            private:
                Fecha caducada_;
        };

        class Num_duplicado{
            public:
                Num_duplicado(const Numero& num);
                const Numero& que() const noexcept{return duplicado_;};
            private:
                Numero duplicado_;
        };
        
        //Metodos observadores
        const Numero& numero() const noexcept {return numero_;};
        Usuario* titular() const noexcept {return titular_;};
        const Fecha& caducidad() const noexcept {return caducidad_;};
        bool activa() const noexcept {return activa_;};
        Tipo tipo() const noexcept;

        //Metodo para activar/desactivar tarjeta(sobrecarga del metodo observador activa)
        bool activa(bool b = true) noexcept;    //default = true

        //Destructor
        ~Tarjeta();

    private:
        //Variables
        const Numero numero_;
        Usuario* const titular_;
        const Fecha caducidad_;
        bool activa_;

        //Todas las tarjetas existentes
        static std::set<Numero> List_tarjetas;
};

//Operador logico
bool operator <(const Tarjeta& ta, const Tarjeta& tb);
inline bool operator <(const Tarjeta& ta, const Tarjeta& tb){
    return (ta.numero() < tb.numero());
}

//Operador de insercion de flujo
std::ostream& operator <<(std::ostream& os, Tarjeta::Tipo& t);
std::ostream& operator <<(std::ostream& os, Tarjeta& tar) noexcept;

//Metodos inline
inline bool Tarjeta::activa(bool b) noexcept{
    activa_ = b;
    return activa_;
}
//CONSTRUCTORES DE LAS SUBCLASES//
//Constructor de Caducada
inline Tarjeta::Caducada::Caducada(const Fecha& fech): caducada_(fech){};

//Constructor de Num_duplicado
inline Tarjeta::Num_duplicado::Num_duplicado(const Numero& num): duplicado_(num){};

#endif // _TARJETA_HPP_