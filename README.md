Gestor de Agenda de Contactos
Práctica 3 – Estructuras de Datos (STL, clases parametrizadas, TDA e índices)

Este proyecto implementa dos Tipos de Datos Abstractos (TDA), apoyándose en la STL:

TDA Contacto → representa un contacto con nombre, teléfonos, correos y etiquetas, evitando duplicados.

TDA AgendaContactos → gestiona un conjunto de contactos indexados por nombre y permite búsquedas eficientes por etiqueta mediante un índice secundario.

El programa permite cargar contactos desde un fichero, añadir y eliminar contactos, consultar por nombre, listar en orden, filtrar por etiqueta y guardar cambios mediante un menú interactivo.

# 1. Estructura del Proyecto
```
.
├── include/
│   ├── contacto.h
│   └── agendacontactos.h
├── src/
│   ├── contacto.cpp
│   ├── agendacontactos.cpp
│   └── main.cpp
├── datos/
│   ├── agenda_contactos.txt
│   ├── agenda_contactos_duplicados.txt
│   ├── agenda_contactos_etiquetas.txt
│   └── agenda_contactos_errores_formato.txt
├── build/
├── doc/
│   └── Doxyfile
├── Makefile
└── README.md
```

# 2. Compilación y ejecución

### Compilar el programa
make

### Ejecutar
./programa

### Limpiar ficheros generados
make clean

### Generar documentación Doxygen
Desde la raiz del proyecto, ejecutamos:
  make doc

Para abrirlo,
Desde Linux:
  xdg-open doc/html/index.html
Desde Windows:
  start doc/html/index.html

(es necesario tener doc/Doxyfile ya configurado)

---

# 3. Formato del fichero de entrada

Cada línea del fichero representa un contacto. Se usa un formato simple y editable a mano, con separadores claros.

Formato de línea:
  nombre|telefonos|correos|etiquetas

Cada uno de los tres últimos campos es una lista separada por comas. Si no hay datos, el campo puede ir vacío.

Ejemplo:
  Ana Perez|600111222,600333444|ana@gmail.com|uni,amigos
  Carlos Ruiz||carlos@outlook.com|trabajo
  Lucia Martinez|722000111||familia

Notas importantes
- El nombre es obligatorio y se usa como clave única en la agenda.
- Los teléfonos, correos y etiquetas no se duplican dentro del mismo contacto.
- Las etiquetas sirven para filtrar contactos de forma rápida.
- Se permiten líneas en blanco.
- Se permiten comentarios si la línea comienza por #.

---

# 4. Uso del programa interactivo

El menú ofrece:
1. Cargar agenda desde fichero
2. Guardar agenda en fichero
3. Listar contactos
4. Ver contacto por nombre
5. Insertar nuevo contacto
6. Eliminar contacto
7. Filtrar por etiqueta
8. Añadir teléfono a contacto
9. Añadir correo a contacto
10. Añadir etiqueta a contacto
0. Salir

Ejemplo:
  Ruta del fichero (ENTER para usar datos/agenda_contactos.txt):
  Carga correcta.

---

# 5. Ficheros de prueba

### agenda_contactos.txt
Fichero principal de pruebas, sin errores de formato y con etiquetas variadas.

### agenda_contactos_duplicados.txt
Incluye contactos repetidos por nombre para comprobar que la agenda evita claves duplicadas y que el programa informa correctamente.

### agenda_contactos_errores_formato.txt
Incluye líneas con separadores incorrectos, nombres vacíos y conversiones problemáticas para demostrar robustez.

### agenda_contactos_etiquetas.txt
Incluye etiquetas repetidas para poder comprobar un filtrado eficiente con multimap.

---

# 6. Retroalimentación del programa

### Archivos no encontrados
  [ERROR] No se ha podido abrir el fichero: datos/agenda_contactos.txt

### Lectura correcta
  Carga correcta.

### Nombre duplicado al insertar
  No se pudo insertar, nombre duplicado o invalido.

### Eliminación correcta
  Eliminado.

### Eliminación fallida
  No existe.

### Etiqueta sin resultados
  No hay contactos con esa etiqueta.

---

# 7. TDA Contacto

### Operaciones fundamentales
- Constructores
- getNombre()
- setNombre()
- addTelefono() y removeTelefono()
- addCorreo() y removeCorreo()
- addEtiqueta() y removeEtiqueta()
- getTelefonos(), getCorreos(), getEtiquetas()

### Operaciones no fundamentales
- toString()
- operator<<

### Invariante del TDA Contacto
- El nombre no debería ser vacío
- No hay teléfonos, correos ni etiquetas duplicadas

---

# 8. TDA AgendaContactos

### Representación interna
- map<string, Contacto> para almacenar contactos por nombre en orden
- multimap<string, string> como índice secundario etiqueta → nombre
- set<string> en Contacto para garantizar no duplicados

### Función de Abstracción (FA)
El map representa la agenda como diccionario ordenado nombre → Contacto.
El multimap representa un índice secundario que asocia cada etiqueta con los nombres que la contienen.

### Invariante de Representación (IR)
- No hay nombres duplicados en el map
- Para cada etiqueta de un contacto existe su entrada correspondiente en el índice
- El índice se actualiza al insertar, eliminar o añadir etiquetas

### Operaciones fundamentales
- insertarContacto()
- eliminarContacto()
- buscarContacto()
- size() y existeContacto()
- cargarDesdeFichero() y guardarEnFichero()

### Operaciones no fundamentales
- listarNombres()
- contactosPorEtiqueta()
- addTelefonoAContacto(), addCorreoAContacto(), addEtiquetaAContacto()
