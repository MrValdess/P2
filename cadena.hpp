//Pablo Garcia Bravo 

#include <iostream>
#include <iterator>
#ifndef _CADENA_HPP_
#define _CADENA_HPP_

class Cadena{
    public:
        //Constructores
        explicit Cadena(size_t tam = 0, char c= ' ');
        Cadena(const Cadena& cad); //Constructor de copia
        Cadena(const char* cad);   //Costructor a partir de cadena de bajo nivel
        Cadena (Cadena&& cad); //Constructor de movimiento

        //Conversor a const char*
        explicit operator const char*() const;

        //Operadores de asignacion
        Cadena& operator =(const Cadena& cad);   
        Cadena& operator =(Cadena&& cad);


        //Observador
        size_t length() const noexcept;

        //Operadores de concatenacion   
        Cadena& operator +=(const Cadena& c);

        //Operadores de los índices
        char& operator[](int i);
        const char& operator[](int i) const;
        char& at(size_t i);
        const char& at(size_t i) const;

        //Funcion subcadena
        Cadena substr(size_t i, size_t tam) const;

        //Definicion de los iteradores
        typedef char* iterator;
        typedef const char* const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        //Funciones de los iteradores:
        //Iniciar los iteradores begin(iteradores normales), rbegin(iteradores inversos), cbegin(iteradores constantes) y rcbegin(iterador inverso y constante)
        iterator begin() noexcept;
        const_iterator begin() const noexcept;
        reverse_iterator rbegin() noexcept;
        const_reverse_iterator rbegin() const noexcept;
        const_iterator cbegin() const noexcept;
        const_reverse_iterator crbegin() const noexcept;

        //Finalizar los iteradores end(iteradores normales), rend(iteradores inversos), cend(iteradores constantes) y crend(iterador inverso y constante)
        iterator end() noexcept;
        const_iterator end() const noexcept;
        reverse_iterator rend() noexcept;
        const_reverse_iterator rend() const noexcept;
        const_iterator cend() const noexcept;
        const_reverse_iterator crend() const noexcept;
    
        //Destructor
        ~Cadena();
        
    private:
        //Variables
        size_t tam_;
        char* s_;
        
};
//Operadores de inserccion y extraccion
std::ostream& operator <<(std::ostream& os, const Cadena& cad) noexcept;
std::istream& operator >>(std::istream& is, Cadena& cad);

//Operadores logicos
bool operator ==(const Cadena& cad1, const Cadena& cad2);
bool operator !=(const Cadena& cad1, const Cadena& cad2);
bool operator <(const Cadena& cad1, const Cadena& cad2);
bool operator >(const Cadena& cad1, const Cadena& cad2);
bool operator <=(const Cadena& cad1, const Cadena& cad2);
bool operator >=(const Cadena& cad1, const Cadena& cad2);
        

//Funciones inline observadoras
inline size_t Cadena::length() const noexcept {return tam_;};
inline Cadena::operator const char*() const {return s_;}

//Funcion de concatenacion
Cadena& operator +(const Cadena& c1, const Cadena& c2);

/*Funciones inline operator[]
Las funciones operator[] devuelven el elemento i de la cadena.*/
inline char& Cadena::operator[](int i){return s_[i];};
inline const char& Cadena::operator[](int i) const{return s_[i];};

//Funciones begin de iteradores
inline Cadena::iterator Cadena::begin() noexcept{
    return s_;
}

inline Cadena::const_iterator Cadena::begin()const noexcept{
    return const_iterator(s_);
}

inline Cadena::reverse_iterator Cadena::rbegin() noexcept
{
    return reverse_iterator(end());
}

inline Cadena::const_reverse_iterator Cadena::rbegin()const noexcept{
    return const_reverse_iterator(end());
}

inline Cadena::const_iterator Cadena::cbegin()const noexcept{
    return const_iterator(s_);
}

inline Cadena::const_reverse_iterator Cadena::crbegin()const noexcept{
    return const_reverse_iterator(end());
}

//Funciones end de iteradores
inline Cadena::iterator Cadena::end() noexcept{
    return s_ + tam_;
}

inline Cadena::const_iterator Cadena::end()const noexcept{
    return const_iterator(s_ + tam_);
}

inline Cadena::reverse_iterator Cadena::rend() noexcept
{
    return reverse_iterator(begin());
}

inline Cadena::const_reverse_iterator Cadena::rend()const noexcept{
    return const_reverse_iterator(begin());
}

inline Cadena::const_iterator Cadena::cend()const noexcept{
    return const_iterator(s_ + tam_);
}

inline Cadena::const_reverse_iterator Cadena::crend()const noexcept{
    return const_reverse_iterator(begin());
}

namespace std { // Estaremos dentro del espacio de nombres std.
    template <> // Es una especializaci ón de una plantilla para Cadena.
    struct hash<Cadena> { // Es una clase con solo un operador público.
        size_t operator() (const Cadena& cad) const // El operador función.
        {
            hash<string> hs; // Creamos un objeto hash de string.
            auto p{(const char*)(cad)}; // Convertimos Cadena a cadena de bajo nivel.
            string s{p}; // Creamos un string desde la cadena de b. nivel .
            size_t res{hs(s)}; // El hash del string . Como hs.operator()(s);
            return res; // Devolvemos el hash del string.
            // En forma abreviada:
            // return hash<string>{}((const char*)(cad));
        }
    };
}


#endif //_CADENA_HPP_
