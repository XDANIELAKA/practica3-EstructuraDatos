#include "agendacontactos.h"
#include <sstream>

/*
 * Invariante de representación de AgendaContactos
 * 1. contactosPorNombre no contiene claves duplicadas. Lo garantiza map.
 * 2. Para cada contacto c almacenado, su nombre coincide con la clave del map.
 * 3. El índice indiceEtiquetaANombre contiene exactamente todos los pares (etiqueta, nombre)
 *    presentes en los contactos. Tras cualquier operación, se mantiene consistente.
 *
 * Función de abstracción
 * contactosPorNombre representa la agenda como diccionario nombre -> Contacto.
 * indiceEtiquetaANombre es un índice secundario para responder a consultas por etiqueta.
 */

void AgendaContactos::indexarContacto(const Contacto &c){
    const set<string> &tags = c.getEtiquetas();
    for(set<string>::const_iterator it = tags.begin(); it != tags.end(); ++it){
        indiceEtiquetaANombre.insert(make_pair(*it, c.getNombre()));
    }
}

void AgendaContactos::desindexarContacto(const Contacto &c){
    const set<string> &tags = c.getEtiquetas();
    for(set<string>::const_iterator it = tags.begin(); it != tags.end(); ++it){
        pair<multimap<string,string>::iterator, multimap<string,string>::iterator> rango =
            indiceEtiquetaANombre.equal_range(*it);

        for(multimap<string,string>::iterator jt = rango.first; jt != rango.second; ){
            if(jt->second == c.getNombre()){
                jt = indiceEtiquetaANombre.erase(jt);
            }else{
                ++jt;
            }
        }
    }
}

bool AgendaContactos::insertarContacto(const Contacto &c){
    if(c.getNombre().empty()){
        return false;
    }
    if(contactosPorNombre.find(c.getNombre()) != contactosPorNombre.end()){
        return false;
    }

    contactosPorNombre.insert(make_pair(c.getNombre(), c));
    indexarContacto(c);
    return true;
}

bool AgendaContactos::eliminarContacto(const string &nombre){
    map<string,Contacto>::iterator it = contactosPorNombre.find(nombre);
    if(it == contactosPorNombre.end()){
        return false;
    }

    desindexarContacto(it->second);
    contactosPorNombre.erase(it);
    return true;
}

bool AgendaContactos::existeContacto(const string &nombre) const{
    return contactosPorNombre.find(nombre) != contactosPorNombre.end();
}

bool AgendaContactos::buscarContacto(const string &nombre, Contacto &out) const{
    map<string,Contacto>::const_iterator it = contactosPorNombre.find(nombre);
    if(it == contactosPorNombre.end()){
        return false;
    }
    out = it->second;
    return true;
}

size_t AgendaContactos::size() const{ return contactosPorNombre.size(); }

vector<string> AgendaContactos::listarNombres() const{
    vector<string> res;
    for(map<string,Contacto>::const_iterator it = contactosPorNombre.begin();
        it != contactosPorNombre.end(); ++it){
            res.push_back(it->first);
    }
    return res;
}

vector<string> AgendaContactos::contactosPorEtiqueta(const string &etiqueta) const{
    vector<string> res;
    pair<multimap<string,string>::const_iterator, multimap<string,string>::const_iterator> rango =
        indiceEtiquetaANombre.equal_range(etiqueta);

    for(multimap<string,string>::const_iterator it = rango.first; it != rango.second; ++it){
        res.push_back(it->second);
    }
    return res;
}

bool AgendaContactos::addTelefonoAContacto(const string &nombre, const string &tel){
    map<string,Contacto>::iterator it = contactosPorNombre.find(nombre);
    if(it == contactosPorNombre.end()){
         return false;
    }
    it->second.addTelefono(tel);
    return true;
}

bool AgendaContactos::addCorreoAContacto(const string &nombre, const string &correo){
    map<string,Contacto>::iterator it = contactosPorNombre.find(nombre);
    if(it == contactosPorNombre.end()){
        return false;
    }
    it->second.addCorreo(correo);
    return true;
}

bool AgendaContactos::addEtiquetaAContacto(const string &nombre, const string &etiqueta){
    map<string,Contacto>::iterator it = contactosPorNombre.find(nombre);
    if(it == contactosPorNombre.end()){
        return false;
    }

    bool inserted = it->second.addEtiqueta(etiqueta);
    if(inserted){
        indiceEtiquetaANombre.insert(make_pair(etiqueta, nombre));
    }
    return true;
}

/*
 * Parser de fichero
 * Formato propuesto, robusto y fácil de escribir a mano:
 * nombre|tel1,tel2|mail1,mail2|tag1,tag2
 *
 * Si tu agenda_contactos.txt ya tiene otro formato, adapta esta parte únicamente.
 */
static void splitCSV(const string &s, vector<string> &out){
    out.clear();
    string token;
    for(size_t i = 0; i < s.size(); ++i){
        if(s[i] == ','){
            if(!token.empty()){
                out.push_back(token);
            }
            token.clear();
        }else{
            token.push_back(s[i]);
        }
    }
    if(!token.empty()){
        out.push_back(token);
    }
}

bool AgendaContactos::cargarDesdeFichero(const string &ruta){
    ifstream f(ruta.c_str());
    if(!f){
        return false;
    }

    contactosPorNombre.clear();
    indiceEtiquetaANombre.clear();

    string linea;
    while(getline(f, linea)){
        if(linea.empty()) continue;
        if(linea[0] == '#') continue;

        vector<string> partes;
        string cur;
        for(size_t i = 0; i < linea.size(); ++i){
            if(linea[i] == '|'){
                partes.push_back(cur); cur.clear();
            }
            else{
                cur.push_back(linea[i]);
            }
        }
        partes.push_back(cur);

        if(partes.size() < 1){
            return false;
        }

        string nombre = partes[0];
        Contacto c(nombre);

        vector<string> items;
        if(partes.size() >= 2){
            splitCSV(partes[1], items);
            for(size_t i = 0; i < items.size(); ++i){
                c.addTelefono(items[i]);
            }
        }
        if(partes.size() >= 3){
            splitCSV(partes[2], items);
            for(size_t i = 0; i < items.size(); ++i){
                c.addCorreo(items[i]);
            }
        }
        if(partes.size() >= 4){
            splitCSV(partes[3], items);
            for(size_t i = 0; i < items.size(); ++i){
                c.addEtiqueta(items[i]);
            }
        }

        insertarContacto(c);
    }
    return true;
}

bool AgendaContactos::guardarEnFichero(const string &ruta) const{
    ofstream f(ruta.c_str());
    if(!f){
        return false;
    }

    for(map<string,Contacto>::const_iterator it = contactosPorNombre.begin();
         it != contactosPorNombre.end(); ++it){

        const Contacto &c = it->second;
        f << c.getNombre() << "|";

        const set<string> &tels = c.getTelefonos();
        for(set<string>::const_iterator jt = tels.begin(); jt != tels.end(); ++jt){
            if (jt != tels.begin()) f << ",";
            f << *jt;
        }
        f << "|";

        const set<string> &mails = c.getCorreos();
        for(set<string>::const_iterator jt = mails.begin(); jt != mails.end(); ++jt){
            if(jt != mails.begin()) f << ",";
            f << *jt;
        }
        f << "|";

        const set<string> &tags = c.getEtiquetas();
        for(set<string>::const_iterator jt = tags.begin(); jt != tags.end(); ++jt){
            if (jt != tags.begin()) f << ",";
            f << *jt;
        }
        f << "\n";
    }
    return true;
}