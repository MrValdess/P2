//Pablo Garcia Bravo 

#ifndef _FECHA_HPP_
#define _FECHA_HPP_

#include <iostream>

class Fecha{             
    public:
        //Constructores
        explicit Fecha(int d = 0, int m = 0, int a = 0);    //Por defecto
        Fecha(const Fecha& f) = default;  //Constructor de copia
        Fecha(const char* c);  //A partir de una cadena de caracteres f. Fecha formato dd/mm/aaaa

        //Operador de asignacion
        Fecha& operator =(const Fecha& f) = default;  

        //Cambio de cadena de fecha a const char*
        const char* cadena() const;

        //Clase Fecha Invalida
        class Invalida{
            public:
                Invalida(const char* inf); //Constructor de la clase invalida
                const char* por_que() const;    //Observador del fallo(inline)
            private:
                const char* info_;
        };
        
        //Observadores(metodos inline)
        int dia() const noexcept;
        int mes() const noexcept;
        int anno() const noexcept;

        //Valores Constantes
        static const int AnnoMinimo = 1902;
        static const int AnnoMaximo = 2037;

        //Operadores
        Fecha& operator ++();
        Fecha& operator ++(int);
        Fecha& operator --();
        Fecha& operator --(int);
        Fecha& operator +=(int i);      
        Fecha& operator -=(int i);

        //Operadores aritméticos
        Fecha& operator +(int i) const;
        Fecha& operator -(int i) const;    
        

        //Destructor
        ~Fecha() = default;
        
    private:
        //Variables
        int dia_, mes_, anno_;
        
        //Validar fecha correcta
        void valida(int dia, int mes, int anno);
};


//Operadores logicos
bool operator ==(const Fecha& f1, const Fecha& f2);
bool operator !=(const Fecha& f1, const Fecha& f2);
bool operator <(const Fecha& f1, const Fecha& f2);
bool operator <=(const Fecha& f1, const Fecha& f2);
bool operator >(const Fecha& f1, const Fecha& f2);
bool operator >=(const Fecha& f1, const Fecha& f2);

    
//Operadores de insercion y extraccion.
std::ostream& operator <<(std::ostream& os, const Fecha& f) noexcept;
std::istream& operator >>(std::istream& is, Fecha& f);

//Inline clase Invalida
inline const char* Fecha::Invalida::por_que() const{return info_;}

//Inline metodos observadores
inline int Fecha::dia() const noexcept{return(dia_);};
inline int Fecha::mes() const noexcept{return(mes_);};
inline int Fecha::anno() const noexcept{return(anno_);};

#endif //_FECHA_HPP_
