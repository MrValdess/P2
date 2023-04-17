//Pablo Garcia Bravo

#ifndef _USUARIO_HPP_
#define _USUARIO_HPP_

#include "cadena.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"

#include <map>              //Mapa de tarjetas
#include <unordered_map>    //Mapa de articulos
#include <unordered_set>    //Set de usuarios
#include <iostream>
#include <cstdlib>          // para rand
#include <cstring>          //Comparar strcmp
#include <unistd.h>         //encriptar 

//Declaraciones adelantadas
class Numero;
class Tarjeta;


////////////////////CLASE CLAVE/////////////////

class Clave{
    public:    
        //Constructor
        Clave(Cadena cad);

        //Metodos observadores
        Cadena clave() const noexcept;

        //Verificar
        bool verifica(const char* c) const;

        //Clase Incorrecta y Razon
        enum Razon{CORTA, ERROR_CRYPT};
        
        class Incorrecta{
            public:
                Incorrecta(const Clave::Razon razon): razon_(razon){};
                Clave::Razon razon() const noexcept{return razon_;};
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
        //Definicion de los mapas de tarjetas y articulos
        typedef std::map<Numero,Tarjeta*> Tarjetas;
        typedef std::unordered_map<Articulo*, unsigned int> Articulos;

        //Constructores
        Usuario(const Cadena& id, const Cadena& nom, const Cadena& apel, const Cadena& dir, Clave& con);
        //Suprimimos el constructor de copia y el operador de asignacion
        Usuario(const Usuario& user) = delete;
        Usuario& operator=(const Usuario& user) = delete;

        //Metodos observadores
        const Cadena& id() const noexcept;
        const Cadena& nombre() const noexcept;
        const Cadena& apellidos() const noexcept;
        const Cadena& direccion() const noexcept;
        const Tarjetas& tarjetas() const noexcept;
        const Articulos& articulo() const noexcept;

        //Relaciones con la clase Tarjeta
        void es_titular_de(const Tarjeta& tar);
        void no_es_titular_de(const Tarjeta& tar);

        //Clase Id_duplicado
        class Id_duplicado{
            public:
                Id_duplicado(const Cadena& id);
                const Cadena& idd() const noexcept;
            private:
                Cadena idd_;
        };
        
        //Destructor
        ~Usuario();

    private:
        const Cadena ID_, nombre_, apellidos_, direccion_;
        Clave contrasena_;
        //Declaramos una variable con cada mapa
        Tarjetas tarjetas_;
        Articulos articulos_;

        //Set en el que guardamos los usuarios
        static std::unordered_set<Cadena> usuarios_;
};
//Metodos inline
inline Usuario::Id_duplicado::Id_duplicado(const Cadena& id): idd_(id){}
inline const Cadena& Usuario::Id_duplicado::idd() const noexcept {return idd_;};

#endif // _USUARIO_HPP_