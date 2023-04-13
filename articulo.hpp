//Pablo Garcia Bravo

#include "fecha.hpp"
#include "cadena.hpp"
#include <iostream>
#include <locale>
#include <iomanip>

#ifndef _ARRTICULO_HPP_
#define _ARTICULO_HPP_



class Articulo{
    public:
        //Constructores
        explicit Articulo(const Cadena& r, const Cadena& t, const Fecha& f, double p, size_t st = 0);

        //Metodos observadores
        const Cadena& referencia() const noexcept; 
        const Cadena& titulo()const noexcept;
        const Fecha& f_publi() const noexcept;
        double precio() const noexcept;
        double& precio() noexcept;
        size_t stock() const noexcept;
        size_t& stock() noexcept;

        //Destructor por defecto
        ~Articulo() = default;

    private:
        //Variables de la clase
        const Cadena referencia_;
        const Cadena titulo_;
        const Fecha f_publi_;
        size_t stock_;
        double precio_;
};

//Metodos inline
//Observadores
inline const Cadena& Articulo::referencia() const noexcept{return referencia_;}
inline const Cadena& Articulo::titulo() const noexcept{return titulo_;}
inline const Fecha& Articulo::f_publi() const noexcept{return f_publi_;}
inline double Articulo::precio() const noexcept{return precio_;}
inline size_t Articulo::stock() const noexcept{return stock_;}
//Observadoras devolviendo referencia
inline double& Articulo::precio() noexcept{return precio_;}
inline size_t& Articulo::stock() noexcept{return stock_;}

//Operador de flujo
std::ostream& operator<<(std::ostream& os, const Articulo& art) noexcept;



#endif // _ARTICULO_HPP_