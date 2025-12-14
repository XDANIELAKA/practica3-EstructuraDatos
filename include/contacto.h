#ifndef CONTACTO_H
#define CONTACTO_H

#include <string>
#include <set>
#include <ostream>

using namespace std;

/**
 * @brief TDA Contacto. Representa un contacto personal con nombre, teléfonos, correos y etiquetas.
 *
 * Un Contacto encapsula la información de una persona identificada por su nombre.
 * Gestiona colecciones de teléfonos, correos y etiquetas sin duplicados.
 */
class Contacto{
private:
    string nombre;
    set<string> telefonos;
    set<string> correos;
    set<string> etiquetas;

public:
    /**
     * @brief Constructor por defecto. Crea un contacto vacío.
     * @post El contacto queda con nombre vacío y colecciones vacías.
     */
    Contacto();

    /**
     * @brief Constructor con nombre.
     * @param n Nombre del contacto. Entrada.
     * @pre n no debería ser vacío.
     * @post El contacto queda con nombre n y colecciones vacías.
     */
    explicit Contacto(const string &n);

    /**
     * @brief Devuelve el nombre del contacto.
     * @return Nombre.
     */
    string getNombre() const;

    /**
     * @brief Cambia el nombre del contacto.
     * @param n Nuevo nombre. Entrada.
     * @pre n no debería ser vacío.
     * @post El nombre queda actualizado.
     */
    void setNombre(const string &n);

    /**
     * @brief Inserta un teléfono si no existe.
     * @param t Teléfono. Entrada.
     * @return true si se insertó, false si ya existía.
     */
    bool addTelefono(const string &t);

    /**
     * @brief Elimina un teléfono si existe.
     * @param t Teléfono. Entrada.
     * @return true si se eliminó, false si no existía.
     */
    bool removeTelefono(const string &t);

    /**
     * @brief Inserta un correo si no existe.
     * @param c Correo. Entrada.
     * @return true si se insertó, false si ya existía.
     */
    bool addCorreo(const string &c);

    /**
     * @brief Elimina un correo si existe.
     * @param c Correo. Entrada.
     * @return true si se eliminó, false si no existía.
     */
    bool removeCorreo(const string &c);

    /**
     * @brief Inserta una etiqueta si no existe.
     * @param e Etiqueta. Entrada.
     * @return true si se insertó, false si ya existía.
     */
    bool addEtiqueta(const string &e);

    /**
     * @brief Elimina una etiqueta si existe.
     * @param e Etiqueta. Entrada.
     * @return true si se eliminó, false si no existía.
     */
    bool removeEtiqueta(const string &e);

    /**
     * @brief Devuelve el conjunto de teléfonos.
     * @return Referencia constante al set de teléfonos.
     */
    const set<string>& getTelefonos() const;

    /**
     * @brief Devuelve el conjunto de correos.
     * @return Referencia constante al set de correos.
     */
    const set<string>& getCorreos() const;

    /**
     * @brief Devuelve el conjunto de etiquetas.
     * @return Referencia constante al set de etiquetas.
     */
    const set<string>& getEtiquetas() const;

    /**
     * @brief Devuelve un resumen del contacto en formato texto.
     * @return Cadena con información del contacto.
     */
    string toString() const;
};

ostream& operator<<(ostream &os, const Contacto &c);

#endif