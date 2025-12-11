Motor de Aventura de Texto - ADA/DNI
Descripción
Un motor de narrativa interactiva desarrollado en C++ que permite crear y recorrer historias ramificadas tipo "elige tu propia aventura". El proyecto sigue una arquitectura colaborativa donde ADA proporciona la lógica del motor y la estructura del grafo narrativo, mientras que DNI se encarga de la interfaz visual y la experiencia narrativa.

Características Principales
Grafo narrativo DAG: Estructura de escenas conectadas sin ciclos

Sistema de decisiones: Elecciones múltiples que afectan el curso de la historia

Finales múltiples: 5 diferentes desenlaces dependiendo de las decisiones

Validación automática: Detección de errores en la estructura del grafo

Interfaz interactiva: Navegación intuitiva con limpieza de pantalla y formato visual

Extensible: Fácil de modificar y ampliar con nuevas escenas y rutas

Estructura del Proyecto
Componentes Principales
SceneNode: Representa una escena individual con:

ID único

Texto narrativo

Opciones de decisión (texto visible + ID destino)

StoryGraph: Contenedor principal del grafo que:

Almacena todos los nodos en un mapa

Proporciona métodos para acceder y validar la estructura

Define el nodo inicial

Funciones de Interfaz:

DisplayScene(): Muestra la escena actual

GetChoice(): Captura la decisión del jugador

ShowWelcomeScreen(): Pantalla de inicio

ShowEndScreen(): Pantalla final

Instalación y Ejecución
Requisitos
Compilador C++ (g++, clang, o MSVC)

Terminal compatible (Windows/Linux/macOS)

Compilación
bash
# Con g++
g++ -o aventura_demo grafo.cpp

# Con clang
clang++ -o aventura_demo grafo.cpp

# En Windows con MinGW
g++ -o aventura_demo.exe grafo.cpp
Ejecución
bash
./aventura_demo      # Linux/macOS
./aventura_demo.exe  # Windows
Historia de Muestra
El proyecto incluye una demostración narrativa ambientada en un bosque misterioso:

Nodos Principales
START: Claro del bosque (punto de inicio)

BOSQUE_PROFUNDO: Cabaña solitaria

ARROYO: Encuentro con figura misteriosa

CABANA_INTERIOR: Mapa antiguo

ENCUENTRO_ERMITANO: Decisión crucial

Finales Disponibles
FINAL_ESCAPE: Escape del bosque

FINAL_MAPA: Seguir el mapa a la aldea

FINAL_TESORO: Encontrar el amuleto

FINAL_ERMITANO: Aceptar ayuda del ermitaño

FINAL_ALONE: Continuar solo

Personalización
Modificar la Historia Existente
Edita la función BuildGraph() en el archivo grafo.cpp para:

Cambiar textos narrativos

Añadir nuevas opciones

Crear nuevos nodos y conexiones

Ejemplo de Creación de Nodo
cpp
SceneNode nuevo_nodo("MI_NODO",
    "Texto narrativo de la escena.");
nuevo_nodo.add_option("Texto de opción 1", "NODO_DESTINO_1");
nuevo_nodo.add_option("Texto de opción 2", "NODO_DESTINO_2");
story_graph.add_node(nuevo_nodo);
Cargar desde Archivo (Extensión Futura)
Puedes reemplazar BuildGraph() con un sistema que cargue la narrativa desde:

Archivos JSON

Archivos de texto estructurados

Bases de datos

Validación del Grafo
El motor incluye validación automática que verifica:

Aristas válidas: Todas las conexiones apuntan a nodos existentes

Sin ciclos: Garantiza que el grafo sea un DAG (Directed Acyclic Graph)

Colaboración ADA/DNI
Responsabilidades de ADA
✅ Lógica del motor de narrativa

✅ Estructura del grafo (SceneNode, StoryGraph)

✅ Validación de integridad

✅ Contratos de interfaz

Responsabilidades de DNI
Implementación de DisplayScene()

Implementación de GetChoice()

Diseño de pantallas (welcome/end)

Experiencia narrativa completa

Posibles extensiones futuras

Estructura de Archivos
text
aventura_engine/
├── grafo.cpp          # Código fuente principal
├── README.md          # Este archivo
└── (futuros archivos)
    ├── narrativa.json # Posible formato de carga
    ├── editor.cpp     # Editor visual de escenas
    └── tests/         # Pruebas unitarias
Extensiones Futuras
Sistema de inventario: Objetos que afectan decisiones

Estadísticas del jugador: Salud, reputación, etc.

Sistema de guardado: Continuar partidas

Editor visual: Crear narrativas sin programar

Exportación a JSON: Intercambio de historias

Efectos de sonido: Inmersión auditiva

Sistema de logros: Finales especiales

Consejos para Narrativas
Variedad de opciones: Mínimo 2, ideal 3-4 por escena

Finales significativos: Cada decisión debe importar

Coherencia temática: Mantener el tono de la historia

Pistas sutiles: Información que guíe sin forzar

Rejugabilidad: Diferentes rutas para explorar

Solución de Problemas
Error de compilación
bash
# Si falta una biblioteca
g++ -std=c++11 -o aventura_demo grafo.cpp
Nodo no encontrado durante ejecución
Verifica que todos los IDs destino en add_option() existan en el grafo.

Ciclos detectados
Asegúrate de que ninguna secuencia de decisiones pueda regresar a un nodo anterior.

Licencia
Este proyecto es educativo y está disponible para modificación y distribución libre. Atribución recomendada.
