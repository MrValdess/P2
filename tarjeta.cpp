//Pablo Garcia Bravo

#include "tarjeta.hpp"



////////////////CLASE NUMERO/////////////////
// Declaracion antocipadas//
//Algoritmo de Luhn
bool luhn(const Cadena& numero);

//Todas las tarjetas
std::set<Numero> Tarjeta::List_tarjetas;

//Constructor por defecto
Numero::Numero(const Cadena& cad){
    Cadena aux;
    for(auto x:cad){
        if(x != ' '){
            if(!isdigit(x)){    //isdigit() comprueba si es un digito o no
                Numero::Incorrecto inc_digito(Razon::DIGITOS);
                throw inc_digito;
            }
            else{ //Si es digito llamamos a una cadena de tamaño 1 y de caracter x y se la sumamos a aux
                aux +=Cadena(1,x);
            }
        }
    }
    if(aux.length() > 19 || aux.length() < 13){ //Si la cadena esta fuera de la longitud valida lanzamos un error
        Numero::Incorrecto inc_long(Razon::LONGITUD);
    }
    else if(!luhn(aux)){    //Si la cadena no cumple el algoritmo de luhn, da error
        Numero::Incorrecto inc_valido(Razon::NO_VALIDO);
        throw inc_valido;
    }
    else{   //Si cumple ambos criterios, copiamos la cadena sin espacios ni caracteres invalidos
        numero_ = aux;
    }
};



////////////////CLASE TARJETA/////////////////
Tarjeta::Tarjeta(const Numero& num, Usuario* user, const Fecha& fech): numero_(num), titular_(user), caducidad_(fech), activa_(true){
    //Comprobamos que la fecha no sea anterior a la del dia de hoy
    Fecha f_actual;
    if(f_actual > fech){
        Tarjeta::Caducada caduc(fech);
        throw caduc;
    }
    else if(!List_tarjetas.insert(num).second){
        Tarjeta::Num_duplicado num_dupli(num);
        throw num_dupli;
    }
    else{
        //hacer algo
    }
}

//Observador del tipo de la tarjeta
Tarjeta::Tipo Tarjeta::tipo()const noexcept {
    //Creamos una cadena de tamaño 2 con los ultimos caracteres
    Cadena digitos(2);
    digitos[0] = numero_[0];
    digitos[1] = numero_[1];
    //Dependemos del valor de ambos caracteres para devolver un tipo
    if(digitos == "34" || digitos == "37"){
        return Tipo::AmericanExpress;
    }
    else switch(digitos[0]){
        case '3': return Tarjeta::JBC; break;
        case '4': return Tarjeta::VISA; break;
        case '5': return Tarjeta::Mastercard; break;
        case '6': return Tarjeta::Maestro; break;
        default: return Tarjeta::Otro; break;
    }
}


//Operadores de insercion en flujo
//Insercion sobrecargada de Tipo
std::ostream& operator<<(std::ostream& os, const Tarjeta::Tipo& tipo){
    //Dependiendo del tipo de la tarjeta, se mete en el flujo una cadena distinta
    switch(tipo){
        case Tarjeta::Otro: os << "Otro"; break;
        case Tarjeta::Maestro: os << "Maestro"; break;
        case Tarjeta::Mastercard: os << "Mastercard"; break;
        case Tarjeta::VISA: os << "VISA"; break;
        case Tarjeta::JBC: os << "JBC"; break;
        case Tarjeta::AmericanExpress: os << "American Express"; break;
        default: os <<"Error Tipo tarjeta";
    }
}

//Insercion Tarjeta
std::ostream& operator<<(std::ostream& os, const Tarjeta& tar){
    //Insertamos los tipos uno a uno en el os tal y como indica el enunciado
    os << tar.tipo() << std::endl;
    os << tar.numero() << std::endl;
    //Cadena para mostrar el nombre en mayusculas
    Cadena cad_mostrar = tar.titular()->nombre() + " " + tar.titular()->apellidos();
    for(auto& x:cad_mostrar){   //Con x dentro de cad_mostrar cambiamos todas las letras a mayusculas
        if(islower(x)){
            x = toupper(x);
        }
    }
    os << cad_mostrar << std::endl; //Imprimimos la cadena en mayusculas
    //Fecha de caducidad formateada(año de 2 cifras)
    os << "Caduca: " << (tar.caducidad().mes()) << "/" << (tar.caducidad().anno()%100) << std::endl;
    return os;
}