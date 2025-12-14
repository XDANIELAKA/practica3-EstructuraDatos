#ifndef AGENDACONTACTOS_H
#define AGENDACONTACTOS_H

#include <map>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include "contacto.h"

using namespace std;

/**
 * @brief TDA AgendaContactos. Gestiona un conjunto de contactos usando contenedores STL.
 *
 * Permite insertar, eliminar, buscar por nombre y filtrar por etiquetas.
 * Mantiene un índice secundario etiqueta -> nombres para búsquedas eficientes.
 */
class AgendaContactos {
private:
    map<string, Contacto> contactosPorNombre;
    multimap<string, string> indiceEtiquetaANombre;

    void indexarContacto(const Contacto &c);
    void desindexarContacto(const Contacto &c);

public:
    /**
     * @brief Inserta un contacto en la agenda.
     * @param c Contacto a insertar. Entrada.
     * @return true si se insertó, false si ya existía ese nombre.
     * @post Si se inserta, se actualiza también el índice de etiquetas.
     */
    bool insertarContacto(const Contacto &c);

    /**
     * @brief Elimina un contacto por nombre.
     * @param nombre Nombre del contacto. Entrada.
     * @return true si se eliminó, false si no existía.
     * @post Si se elimina, se actualiza el índice de etiquetas.
     */
    bool eliminarContacto(const string &nombre);

    /**
     * @brief Comprueba si existe un contacto por nombre.
     * @param nombre Nombre. Entrada.
     * @return true si existe, false si no.
     */
    bool existeContacto(const string &nombre) const;

    /**
     * @brief Busca un contacto por nombre.
     * @param nombre Nombre. Entrada.
     * @param out Salida, se copia el contacto encontrado.
     * @return true si se encontró, false si no.
     */
    bool buscarContacto(const string &nombre, Contacto &out) const;

    /**
     * @brief Devuelve el número de contactos.
     * @return size.
     */
    size_t size() const;

    /**
     * @brief Lista todos los nombres en orden.
     * @return Vector con nombres.
     */
    vector<string> listarNombres() const;

    /**
     * @brief Devuelve los contactos asociados a una etiqueta.
     * @param etiqueta Etiqueta. Entrada.
     * @return Vector de nombres de contactos con esa etiqueta.
     */
    vector<string> contactosPorEtiqueta(const string &etiqueta) const;

    /**
     * @brief Añade un teléfono a un contacto existente.
     * @param nombre Nombre del contacto. Entrada.
     * @param tel Teléfono. Entrada.
     * @return true si se modificó, false si el contacto no existe.
     */
    bool addTelefonoAContacto(const string &nombre, const string &tel);

    /**
     * @brief Añade un correo a un contacto existente.
     */
    bool addCorreoAContacto(const string &nombre, const string &correo);

    /**
     * @brief Añade una etiqueta a un contacto existente y actualiza índice.
     */
    bool addEtiquetaAContacto(const string &nombre, const string &etiqueta);

    /**
     * @brief Carga agenda desde un fichero de texto.
     * @param ruta Ruta del fichero. Entrada.
     * @return true si se cargó, false si hubo error de apertura o formato.
     */
    bool cargarDesdeFichero(const string &ruta);

    /**
     * @brief Guarda agenda a un fichero de texto.
     * @param ruta Ruta del fichero. Entrada.
     * @return true si se guardó, false si hubo error.
     */
    bool guardarEnFichero(const string &ruta) const;
};

#endif