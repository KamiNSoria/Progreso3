#define MAX_PRODUCTOS 100
#define MAX_CLIENTES 100
#define MAX_FACTURAS 100
#define MAX_NOMBRE_PRODUCTO 50
#define MAX_NOMBRE_CLIENTE 50


// En Operaciones.h




void cargarDatos();

void actualizarArchivo(const char* archivoNombre, const char* modo, void (*escribirDatos)());

void escribirProductos();

void escribirClientes();

void escribirFacturas();

void ingresarProducto(char *nombre, int *cantidad, float *precio);

void modificarProducto(char *nombre, int *cantidad, float *precio);

void eliminarProducto(char *nombre, int *contador_productos, char nombres_productos[][MAX_NOMBRE_PRODUCTO], int *cantidades_productos, float *precios_productos);

void listarProductos(int *contador_productos, char (*nombres_productos)[MAX_NOMBRE_PRODUCTO], int *cantidades_productos, float *precios_productos);
int validarCedula(const char* cedula);
void ingresarCliente(int *contador_clientes, char (*cedulas_clientes)[11], char (*nombres_clientes)[MAX_NOMBRE_CLIENTE]);
void modificarCliente(int *contador_clientes, char (*cedulas_clientes)[11], char (*nombres_clientes)[MAX_NOMBRE_CLIENTE]);
void listarClientes(int *contador_clientes, char (*cedulas_clientes)[11], char (*nombres_clientes)[MAX_NOMBRE_CLIENTE]);


void facturar();
void listarFacturas();


























// En Operaciones.h
extern int contador_productos;
extern int contador_clientes;
extern int contador_facturas;

