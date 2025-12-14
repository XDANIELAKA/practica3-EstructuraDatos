#include "contacto.h"
#include <sstream>

/*
 * Invariante de representación de Contacto
 * 1. El nombre es una cadena que idealmente no debería ser vacía.
 * 2. telefonos, correos y etiquetas no contienen duplicados. Lo garantiza set.
 *
 * Función de abstracción
 * Un Contacto representa a una persona identificada por 'nombre', asociada a tres colecciones
 * sin repetición de teléfonos, correos y etiquetas.
 */

Contacto::Contacto() : nombre(""){}

Contacto::Contacto(const string &n) : nombre(n){}

string Contacto::getNombre() const{ return nombre; }

void Contacto::setNombre(const string &n){ nombre = n; }

bool Contacto::addTelefono(const string &t){
    return telefonos.insert(t).second;
}

bool Contacto::removeTelefono(const string &t){
    return telefonos.erase(t) > 0;
}

bool Contacto::addCorreo(const string &c){
    return correos.insert(c).second;
}

bool Contacto::removeCorreo(const string &c){
    return correos.erase(c) > 0;
}

bool Contacto::addEtiqueta(const string &e){
    return etiquetas.insert(e).second;
}

bool Contacto::removeEtiqueta(const string &e){
    return etiquetas.erase(e) > 0;
}

const set<string>& Contacto::getTelefonos() const{ return telefonos; }
const set<string>& Contacto::getCorreos() const{ return correos; }
const set<string>& Contacto::getEtiquetas() const{ return etiquetas; }

string Contacto::toString() const{
    ostringstream oss;
    oss << "Nombre: " << nombre << "\n";

    oss << "Telefonos: ";
    for(set<string>::const_iterator it = telefonos.begin(); it != telefonos.end(); ++it){
        if (it != telefonos.begin()) oss << ", ";
        oss << *it;
    }
    oss << "\n";

    oss << "Correos: ";
    for(set<string>::const_iterator it = correos.begin(); it != correos.end(); ++it){
        if (it != correos.begin()) oss << ", ";
        oss << *it;
    }
    oss << "\n";

    oss << "Etiquetas: ";
    for(set<string>::const_iterator it = etiquetas.begin(); it != etiquetas.end(); ++it){
        if (it != etiquetas.begin()) oss << ", ";
        oss << *it;
    }
    oss << "\n";

    return oss.str();
}

ostream& operator<<(ostream &os, const Contacto &c){
    os << c.toString();
    return os;
}