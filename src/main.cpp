#include <iostream>
#include <limits>
#include "agendacontactos.h"

using namespace std;

static void pauseEnter(){
    cout << "Pulsa ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static int menu(){
    cout << "\n--- Agenda de Contactos (Practica 3 ED) ---\n";
    cout << "1. Cargar desde fichero\n";
    cout << "2. Guardar en fichero\n";
    cout << "3. Listar contactos\n";
    cout << "4. Ver contacto por nombre\n";
    cout << "5. Insertar nuevo contacto\n";
    cout << "6. Eliminar contacto\n";
    cout << "7. Filtrar por etiqueta\n";
    cout << "8. Añadir telefono a contacto\n";
    cout << "9. Añadir correo a contacto\n";
    cout << "10. Añadir etiqueta a contacto\n";
    cout << "0. Salir\n";
    cout << "Opcion: ";

    int op;
    cin >> op;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return op;
}

int main(){
    AgendaContactos agenda;
    string rutaDefault = "datos/agenda_contactos.txt";

    bool salir = false;
    while(!salir){
        int op = menu();

        if(op == 1){
            cout << "Ruta del fichero (ENTER para usar " << rutaDefault << "): ";
            string ruta; getline(cin, ruta);
            if (ruta.empty()) ruta = rutaDefault;

            bool ok = agenda.cargarDesdeFichero(ruta);
            cout << (ok ? "Carga correcta.\n" : "Error cargando el fichero.\n");
            pauseEnter();
        }
        else if(op == 2){
            cout << "Ruta de salida (ENTER para usar " << rutaDefault << "): ";
            string ruta; getline(cin, ruta);
            if (ruta.empty()) ruta = rutaDefault;

            bool ok = agenda.guardarEnFichero(ruta);
            cout << (ok ? "Guardado correcto.\n" : "Error guardando el fichero.\n");
            pauseEnter();
        }
        else if(op == 3){
            vector<string> nombres = agenda.listarNombres();
            cout << "Total: " << nombres.size() << "\n";
            for (size_t i = 0; i < nombres.size(); ++i) cout << "- " << nombres[i] << "\n";
            pauseEnter();
        }
        else if(op == 4){
            cout << "Nombre: ";
            string nombre; getline(cin, nombre);
            Contacto c;
            if (agenda.buscarContacto(nombre, c)) cout << c;
            else cout << "No existe.\n";
            pauseEnter();
        }
        else if(op == 5){
            cout << "Nombre del nuevo contacto: ";
            string nombre; getline(cin, nombre);
            Contacto c(nombre);

            cout << "Telefonos (csv, ENTER si ninguno): ";
            string tels; getline(cin, tels);
            if(!tels.empty()){
                size_t pos = 0;
                while(true){
                    size_t coma = tels.find(',', pos);
                    string t = (coma == string::npos) ? tels.substr(pos) : tels.substr(pos, coma - pos);
                    if(!t.empty()){
                        c.addTelefono(t);
                    }
                    if(coma == string::npos){
                        break;
                    }
                    pos = coma + 1;
                }
            }

            cout << "Correos (csv, ENTER si ninguno): ";
            string mails; getline(cin, mails);
            if(!mails.empty()){
                size_t pos = 0;
                while(true){
                    size_t coma = mails.find(',', pos);
                    string m = (coma == string::npos) ? mails.substr(pos) : mails.substr(pos, coma - pos);
                    if(!m.empty()){
                        c.addCorreo(m);
                    }
                    if(coma == string::npos){
                        break;
                    }
                    pos = coma + 1;
                }
            }

            cout << "Etiquetas (csv, ENTER si ninguna): ";
            string tags; getline(cin, tags);
            if(!tags.empty()){
                size_t pos = 0;
                while(true){
                    size_t coma = tags.find(',', pos);
                    string e = (coma == string::npos) ? tags.substr(pos) : tags.substr(pos, coma - pos);
                    if(!e.empty()){
                        c.addEtiqueta(e);
                    }
                    if(coma == string::npos){
                        break;
                    }
                    pos = coma + 1;
                }
            }

            bool ok = agenda.insertarContacto(c);
            cout << (ok ? "Insertado.\n" : "No se pudo insertar, nombre duplicado o invalido.\n");
            pauseEnter();
        }
        else if(op == 6){
            cout << "Nombre a eliminar: ";
            string nombre; getline(cin, nombre);
            bool ok = agenda.eliminarContacto(nombre);
            cout << (ok ? "Eliminado.\n" : "No existe.\n");
            pauseEnter();
        }
        else if(op == 7){
            cout << "Etiqueta: ";
            string e; getline(cin, e);
            vector<string> res = agenda.contactosPorEtiqueta(e);
            if(res.empty()){
                cout << "No hay contactos con esa etiqueta.\n";
            }else{
                cout << "Contactos con etiqueta '" << e << "':\n";
                for(size_t i = 0; i < res.size(); ++i){
                    cout << "- " << res[i] << "\n";
                }
            }
            pauseEnter();
        }
        else if(op == 8){
            cout << "Nombre: ";
            string nombre; getline(cin, nombre);
            cout << "Telefono: ";
            string tel; getline(cin, tel);
            bool ok = agenda.addTelefonoAContacto(nombre, tel);
            cout << (ok ? "Actualizado.\n" : "No existe el contacto.\n");
            pauseEnter();
        }
        else if(op == 9){
            cout << "Nombre: ";
            string nombre; getline(cin, nombre);
            cout << "Correo: ";
            string correo; getline(cin, correo);
            bool ok = agenda.addCorreoAContacto(nombre, correo);
            cout << (ok ? "Actualizado.\n" : "No existe el contacto.\n");
            pauseEnter();
        }
        else if(op == 10){
            cout << "Nombre: ";
            string nombre; getline(cin, nombre);
            cout << "Etiqueta: ";
            string etiqueta; getline(cin, etiqueta);
            bool ok = agenda.addEtiquetaAContacto(nombre, etiqueta);
            cout << (ok ? "Actualizado.\n" : "No existe el contacto.\n");
            pauseEnter();
        }
        else if(op == 0) {
            salir = true;
        }
        else{
            cout << "Opcion invalida.\n";
            pauseEnter();
        }
    }

    cout << "Fin.\n";
    return 0;
}