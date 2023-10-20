#include <stdio.h>
#include <stdlib.h>
#include <string.h>
///ESTRUCTURAS
/// Estructura para representar un usuario
typedef struct Usuario {
    char nombre[20];
    int contrasena;
    int rol; // 0 para admin, 1 para medico, 2 para recepcion
} Usuario;
///Estructura para arreglo de listas
/*typedef struct celdaEstudios {
    int idPaciente;
    char estudio[50];
    char resultados[100];
    char fecha[20];
    char medico[50];
    nodo *listaDeEstudios;
    // Otras propiedades
} celdaEstudios;
*/
typedef struct Paciente {
    char nombre[50];
    int dni;
    char direccion[100];
    char telefono[20];
    int idPaciente;
    char obraSocial[50];

    // Otras propiedades
} Paciente;

/*typedef struct celdaPacientes {
int idPaciente;
char nombre[50];
nodoArbol* arbolPaciente;
}celdaPacientes;
*/
///PROTOTIPADOS

int main()
{
    int opcion;
    crearArchivoUsuarios();
     Usuario usuarios[3];
    int numUsuarios = cargarUsuarios(usuarios);

    if (numUsuarios == 0) {
        printf("Error al cargar usuarios desde el archivo.\n");
        return 1;
    }

    int rol = iniciarSesion(usuarios, numUsuarios);

    printf("Inicio de sesion exitoso. Rol: %s\n", (rol == 0) ? "Admin" : (rol == 1) ? "Medico" : "Recepcionista");

///    mostrarMenuPrincipal(usuarios, numUsuarios, rol);



///    mostrarMenuPrincipal(usuarios, numUsuarios, rol);

return 0;
}



///FUNCIONES PARA CREAR USUARIOS , E INICIAR SESION
int iniciarSesion(Usuario usuarios[], int numUsuarios) {
    int rol;
    char nombreUsuario[20];
    int contrasena;

    do {
        printf("Ingrese su nombre de usuario: ");
        scanf("%s", nombreUsuario);
        printf("Ingrese su contraseña (4 digitos enteros): ");
        scanf("%d", &contrasena);

        rol = verificarCredenciales(usuarios, numUsuarios, nombreUsuario, contrasena);

        if (rol == -1) {
            printf("Credenciales incorrectas. Intente de nuevo.\n");
        }
    } while (rol == -1);

    return rol; // Retorna el rol del usuario autenticado
}
void crearArchivoUsuarios() {
    FILE *archivo = fopen("usuarios.txt", "w");
    if (archivo == NULL) {
        printf("No se pudo crear el archivo de usuarios.\n");
        return;
    }

    fprintf(archivo, "3\n");
    fprintf(archivo, "admin 1234 0\n");
    fprintf(archivo, "medico 5678 1\n");
    fprintf(archivo, "recepcion 9876 2\n");

    fclose(archivo);
}
int verificarCredenciales(Usuario usuarios[], int numUsuarios, char nombreUsuario[], int contrasena) {
    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(usuarios[i].nombre, nombreUsuario) == 0 && usuarios[i].contrasena == contrasena) {
            return usuarios[i].rol;
        }
    }
    return -1; // -1 indica que las credenciales son incorrectas
}

int cargarUsuarios(Usuario usuarios[]) {
    FILE *archivo = fopen("usuarios.txt", "r");
    if (archivo == NULL) {
        return 0; // No se pudo abrir el archivo
    }

    int numUsuarios;
    fscanf(archivo, "%d", &numUsuarios);

    for (int i = 0; i < numUsuarios; i++) {
        fscanf(archivo, "%s %d %d", usuarios[i].nombre, &usuarios[i].contrasena, &usuarios[i].rol);
    }

    fclose(archivo);

    return numUsuarios;
}

void guardarUsuarios(Usuario usuarios[], int numUsuarios) {
    FILE *archivo = fopen("usuarios.txt", "w");
    if (archivo == NULL) {
        printf("Error al guardar usuarios en el archivo.\n");
        return;
    }

    fprintf(archivo, "%d\n", numUsuarios);
    for (int i = 0; i < numUsuarios; i++) {
        fprintf(archivo, "%s %d %d\n", usuarios[i].nombre, usuarios[i].contrasena, usuarios[i].rol);
    }

    fclose(archivo);
}

///FUNCIONES PARA MENU PRINCIPAL
void mostrarMenuPrincipal(Usuario usuarios[], int numUsuarios, int rol) {


int opcion;

    while (1) {
        printf("\nMenu Principal:\n");


printf("1\t Ingresar Paciente \n");
        printf("2\t Mostrar Archivo Pacientes \n");
        printf("3. Salir\n");
        printf("Ingrese su elección: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                cargaArchivoPaciente();
                system("pause");
                break;

            case 2:
              mostrarArchivoPacientes("archivoPaciente.bin");
              system("pause");
              break;
        }

        }
}
 ///OPCION 1 INGRESAR PACIENTE

 Paciente crearNuevoPaciente(){
 Paciente nuevo;

 printf("Nombre y Apellido del Paciente: ");
 fflush(stdin);
 gets(nuevo.nombre);

 printf(" DNI del Paciente: ");
 scanf("%d", &nuevo.dni);

 printf("Direccion del Paciente: ");
 fflush(stdin);
 gets(nuevo.direccion);

 printf("Telefono del Paciente: ");
 scanf("%d", &nuevo.telefono);

 printf("id del Paciente: ");
 scanf("%d", &nuevo.idPaciente);

 printf("Obra Social del Paciente: ");
 fflush(stdin);
 gets(nuevo.obraSocial);

 return nuevo;
 }

 void guardarNuevoPacienteArchivo(Paciente aux){
 FILE*buf=fopen("archivoPaciente.bin", "ab");
 if(buf)
 {
     fwrite(&aux, sizeof(Paciente),1,buf);
     fclose(buf);
 }
 }
 void cargaArchivoPaciente(){
 char control;
 do{
    guardarNuevoPacienteArchivo(crearNuevoPaciente());
    printf("Desea continuar cargando? s/n");
    fflush(stdin);
    control=getche();
    printf("\n");
 }while (control =='s'|| control =='S');
 }
 void mostrarPaciente(Paciente aux)
 {
     printf("Nombre y Apellido Paciente: %s\n",aux.nombre);
       printf("DNI Paciente: %d\n",aux.dni);
         printf("Direccion Paciente: %s\n",aux.direccion);
           printf("telefono Paciente: %d\n",aux.telefono);
        printf("ID Paciente: %d\n",aux.idPaciente);
     printf("Obra Social Paciente: %s\n",aux.obraSocial);
     printf("----------------------------------------\n");

 }
 void mostrarArchivoPacientes(char nombreArchivo [])
 {
     FILE*buf=fopen(nombreArchivo, "rb");
     Paciente aux;

     if(buf)
     {
         while(fread(&aux, sizeof(Paciente), 1, buf)>0)
            mostrarPaciente(aux);
         fclose(buf);
     }
 }



