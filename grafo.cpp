#include <iostream> 
#include <string> 
#include <vector> 
#include <map> 
#include <limits> 
#include <utility> 
#include <set> 
#include <functional>
#include <cstdlib>
#include <ctime>

// ============================================================================
// ESTRUCTURA: SceneNode
// ============================================================================
// Representa una escena dentro de la historia.
// Cada nodo contiene:
//  - id              : Identificador único de la escena.
//  - text            : Texto narrativo mostrado al jugador.
//  - options         : Lista de opciones disponibles. Cada opción es
//                      un par <texto_visible, id_destino> que define una arista
//                      en el grafo de decisiones.
// Un nodo sin opciones es considerado un final.
// ============================================================================
struct SceneNode {
    std::string id;
    std::string text;
    std::vector<std::pair<std::string, std::string>> options;

    SceneNode() : id(""), text("") {}
    SceneNode(const std::string& node_id, const std::string& node_text)
        : id(node_id), text(node_text) {}

    // Agrega una opción que conecta esta escena con otra.
    void add_option(const std::string& option_text, const std::string& target_id) {
        options.push_back(std::make_pair(option_text, target_id));
    }

    // Un nodo es final si no ofrece decisiones al jugador.
    bool is_ending() const {
        return options.empty();
    }
};

// ============================================================================
// CLASE: StoryGraph
// ============================================================================
// Contenedor principal del grafo narrativo.
// Administro todos los nodos mediante un mapa ID → SceneNode.
// Este grafo es un DAG: cada escena apunta hacia otras sin formar ciclos.
// ============================================================================
class StoryGraph {
private:
    std::map<std::string, SceneNode> nodes;
    std::string start_node_id;

public:
    StoryGraph() : start_node_id("START") {}

    // Agrega o reemplaza un nodo dentro del grafo.
    void add_node(const SceneNode& node) {
        if (nodes.count(node.id)) {
            std::cerr << "[WARN] add_node: id duplicado: " << node.id
                      << " — sobrescribiendo nodo existente.\n";
        }
        nodes[node.id] = node;
    }

    // Devuelve un puntero al nodo solicitado o nullptr si no existe.
    const SceneNode* get_node_ptr(const std::string& id) const {
        auto it = nodes.find(id);
        return (it != nodes.end() ? &it->second : nullptr);
    }

    // Verifica existencia de un nodo.
    bool node_exists(const std::string& id) const {
        return nodes.find(id) != nodes.end();
    }

    // Define el nodo inicial del grafo.
    void set_start_node(const std::string& id) {
        start_node_id = id;
    }

    std::string get_start_node_id() const {
        return start_node_id;
    }

    // Número total de escenas creadas.
    size_t get_node_count() const {
        return nodes.size();
    }

    // Expone todos los nodos para validación o inspección.
    const std::map<std::string, SceneNode>& get_all_nodes() const {
        return nodes;
    }
};

// Instancia global del grafo narrativo, propiedad del ADA.
StoryGraph story_graph;

// ============================================================================
// FUNCIÓN: BuildGraph
// ============================================================================
void BuildGraph() {
    SceneNode start_node("START",
        "Despiertas en un claro del bosque. La luz atraviesa las hojas y el viento es frío.");
    start_node.add_option("Seguir el sendero hacia el bosque", "BOSQUE_PROFUNDO");
    start_node.add_option("Caminar hacia el sonido del arroyo", "ARROYO");
    story_graph.add_node(start_node);

    SceneNode bosque_node("BOSQUE_PROFUNDO",
        "El bosque se vuelve denso y silencioso. Frente a ti aparece una cabaña solitaria.");
    bosque_node.add_option("Entrar en la cabaña", "CABANA_INTERIOR");
    bosque_node.add_option("Rodearla por detrás", "CABANA_TRASERA");
    story_graph.add_node(bosque_node);

    SceneNode arroyo_node("ARROYO",
        "Un arroyo cristalino fluye suavemente. Al otro lado distingues una figura.");
    arroyo_node.add_option("Llamar a la figura", "ENCUENTRO_ERMITANO");
    arroyo_node.add_option("Cruzar el puente en silencio", "FINAL_ESCAPE");
    story_graph.add_node(arroyo_node);

    SceneNode cabana_interior("CABANA_INTERIOR",
        "Dentro de la cabaña encuentras un viejo mapa sobre la mesa.");
    cabana_interior.add_option("Tomar el mapa y seguir la ruta", "FINAL_MAPA");
    cabana_interior.add_option("Buscar al ermitaño mencionado", "ENCUENTRO_ERMITANO");
    story_graph.add_node(cabana_interior);

    SceneNode cabana_trasera("CABANA_TRASERA",
        "Detrás de la cabaña hay una trampilla semienterrada y un jardín descuidado.");
    cabana_trasera.add_option("Forzar la trampilla", "FINAL_TESORO");
    cabana_trasera.add_option("Entrar a la cabaña por la puerta principal", "CABANA_INTERIOR");
    cabana_trasera.add_option("Seguir un sendero alternativo", "BOSQUE_CAMINO_ALTERNATIVO");
    story_graph.add_node(cabana_trasera);

    SceneNode ermitano_node("ENCUENTRO_ERMITANO",
        "Un anciano te observa en silencio. Extiende su mano con serenidad.");
    ermitano_node.add_option("Tomar su mano", "FINAL_ERMITANO");
    ermitano_node.add_option("Rechazar su ayuda", "FINAL_ALONE");
    story_graph.add_node(ermitano_node);

    // Finales — nodos sin opciones
    story_graph.add_node(SceneNode("FINAL_ESCAPE",
        "Cruzas el puente y encuentras finalmente la salida del bosque."));
    story_graph.add_node(SceneNode("FINAL_MAPA",
        "Sigues la ruta del mapa hasta llegar a una pequeña aldea iluminada."));
    story_graph.add_node(SceneNode("FINAL_TESORO",
        "La trampilla oculta un cofre con un antiguo amuleto. Sientes un destello y despiertas en casa."));
    story_graph.add_node(SceneNode("FINAL_ERMITANO",
        "El ermitaño te guía a través del bosque hasta tu aldea."));
    story_graph.add_node(SceneNode("FINAL_ALONE",
        "Decides continuar solo. El bosque te envuelve en un profundo silencio."));

    story_graph.add_node(SceneNode("BOSQUE_CAMINO_ALTERNATIVO",
        "Sigues un sendero distinto que se aleja del bosque principal."));

    story_graph.set_start_node("START");
}

// ============================================================================
// IMPLEMENTACIÓN DE DEMO
// ============================================================================
// Funciones básicas para mostrar la demo interactiva del motor
// ============================================================================

void ClearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void WaitForEnter() {
    std::cout << "\n[Presiona Enter para continuar...]";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void ShowWelcomeScreen() {
    ClearScreen();
    std::cout << "========================================\n";
    std::cout << "     DEMO DEL MOTOR DE NARRATIVAS\n";
    std::cout << "========================================\n\n";
    std::cout << "Un proyecto colaborativo:\n";
    std::cout << "Esta es una demostración interactiva del sistema.\n\n";
    WaitForEnter();
}

void ShowEndScreen() {
    ClearScreen();
    std::cout << "========================================\n";
    std::cout << "       FIN DE LA DEMOSTRACIÓN\n";
    std::cout << "========================================\n\n";
    std::cout << "Has llegado al final de una de las ramas narrativas.\n\n";
    std::cout << "Estadísticas:\n";
    std::cout << "• Nodos totales en el grafo: " << story_graph.get_node_count() << "\n";
    std::cout << "• Finales disponibles: 5\n\n";
    std::cout << "El motor está listo para que implementes tu propia narrativa.\n\n";
    WaitForEnter();
}

void DisplayScene(const SceneNode& node) {
    ClearScreen();
    
    std::cout << "════════════════════════════════════════\n";
    std::cout << "           ESCENA: " << node.id << "\n";
    std::cout << "════════════════════════════════════════\n\n";
    
    // Mostrar texto narrativo con formato
    std::cout << node.text << "\n\n";
    
    if (node.is_ending()) {
        std::cout << "════════════════════════════════════════\n";
        std::cout << "           [FINAL DE LA HISTORIA]\n";
        std::cout << "════════════════════════════════════════\n";
        return;
    }
    
    // Mostrar opciones disponibles
    std::cout << "════════════════════════════════════════\n";
    std::cout << "            OPCIONES DISPONIBLES\n";
    std::cout << "════════════════════════════════════════\n\n";
    
    for (size_t i = 0; i < node.options.size(); ++i) {
        std::cout << "  [" << (i + 1) << "] " << node.options[i].first << "\n";
    }
    std::cout << "\n════════════════════════════════════════\n";
}

int GetChoice(int max_options) {
    int choice = 0;
    
    while (true) {
        std::cout << "\nElige una opción (1-" << max_options << "): ";
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Por favor, ingresa un número válido.\n";
            continue;
        }
        
        if (choice >= 1 && choice <= max_options) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice - 1; // Convertir a índice base 0
        }
        
        std::cout << "Opción inválida. Por favor elige entre 1 y " << max_options << ".\n";
    }
}

void RunGameDemo() {
    std::string current_node_id = story_graph.get_start_node_id();
    bool game_running = true;
    
    while (game_running) {
        const SceneNode* current_node = story_graph.get_node_ptr(current_node_id);
        
        if (!current_node) {
            std::cerr << "[ERROR] Nodo '" << current_node_id << "' no encontrado.\n";
            break;
        }
        
        DisplayScene(*current_node);
        
        if (current_node->is_ending()) {
            WaitForEnter();
            break;
        }
        
        int choice = GetChoice(current_node->options.size());
        
        // Verificar que la elección sea válida
        if (choice >= 0 && choice < static_cast<int>(current_node->options.size())) {
            current_node_id = current_node->options[choice].second;
        } else {
            std::cerr << "[ERROR] Opción inválida seleccionada.\n";
            break;
        }
    }
}

// ============================================================================
// VALIDACIÓN DEL GRAFO
// ============================================================================
// Compruebo dos condiciones esenciales del DAG narrativo:
//   1. Todas las aristas deben apuntar a un ID existente.
//   2. No debe haber ciclos entre escenas.
// Si algo falla, informo el error y retorno false.
// ============================================================================
bool validate_graph(const StoryGraph& g) {
    bool ok = true;
    const auto& nodes = g.get_all_nodes();

    // 1. Aristas válidas
    for (const auto& kv : nodes) {
        const SceneNode& node = kv.second;
        for (const auto& opt : node.options) {
            if (!g.node_exists(opt.second)) {
                std::cerr << "[ERROR] Nodo '" << node.id
                          << "' apunta a ID inexistente: " << opt.second << "\n";
                ok = false;
            }
        }
    }

    // 2. Detección de ciclos
    std::map<std::string, int> color; // 0=blanco, 1=gris, 2=negro
    for (const auto& kv : nodes) color[kv.first] = 0;

    std::function<bool(const std::string&)> dfs_cycle =
    [&](const std::string& id) -> bool {
        color[id] = 1;
        const SceneNode* node = g.get_node_ptr(id);
        if (!node) return false;

        for (const auto& opt : node->options) {
            const std::string& tgt = opt.second;
            if (!g.node_exists(tgt)) continue;
            if (color[tgt] == 1) {
                std::cerr << "[ERROR] Ciclo detectado: " << id
                          << " -> " << tgt << "\n";
                return true;
            }
            if (color[tgt] == 0 && dfs_cycle(tgt)) return true;
        }

        color[id] = 2;
        return false;
    };

    for (const auto& kv : nodes)
        if (color[kv.first] == 0)
            if (dfs_cycle(kv.first)) ok = false;

    return ok;
}

// ============================================================================
// FUNCIÓN: main
// ============================================================================
// Construyo el grafo, lo valido y ejecuto la demo interactiva
// ============================================================================
int main() {
    srand(time(0)); // Para cualquier aleatoriedad futura
    
    BuildGraph();

    if (!validate_graph(story_graph)) {
        std::cerr << "\n[ERROR] La validación del grafo falló. Debes corregirlo antes de iniciar el juego.\n";
        WaitForEnter();
        return 2;
    }

    std::cout << "[INFO] Grafo construido y validado correctamente. Nodos totales: "
              << story_graph.get_node_count() << "\n\n";
    WaitForEnter();

    // Ejecutar la demostración interactiva
    ShowWelcomeScreen();
    
    char play_again;
    do {
        RunGameDemo();
        
        std::cout << "\n¿Quieres probar otra ruta? (s/n): ";
        std::cin >> play_again;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (play_again == 's' || play_again == 'S');
    
    ShowEndScreen();
    
    std::cout << "\n>>> FIN — El motor está listo para tu integración narrativa.\n";
    std::cout << "Puedes modificar los textos en BuildGraph() o implementar tu propio sistema de carga.\n";

    return 0;
}