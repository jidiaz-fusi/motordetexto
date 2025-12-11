# Motor de Narrativas con Grafo (C++ Narrative Engine)

Un motor modular y extensible para crear aventuras de texto basadas en grafos dirigidos acíclicos (DAG).  
Permite diseñar historias ramificadas donde cada decisión del jugador conduce a otras escenas, rutas o finales.

---

## Objetivo del Proyecto

Construir un motor narrativo mínimo pero funcional que:

- Muestre escenas y opciones.
- Capture la decisión del jugador.
- Navegue un grafo narrativo sin ciclos.
- Asegure estabilidad mediante validaciones.
- Permita ampliar la historia sin modificar la lógica central.

El motor corre en consola y está pensado como herramienta educativa.

---

# Arquitectura General

El proyecto se divide en dos componentes principales:

## 1. Motor Lógico (ADA)

Responsable de:

- Implementar las clases `SceneNode` y `StoryGraph`.
- Crear la función `BuildGraph()` y poblar el grafo.
- Ejecutar el bucle principal del juego.
- Validar entrada del usuario.
- Garantizar navegación segura entre nodos.

## 2. Narrativa e Interfaz (DNI)

Responsable de:

- Escribir la historia: escenas, decisiones y finales.
- Implementar `DisplayScene()` y `GetChoice()`.
- Diseñar el formato de presentación en consola.
- Proveer el contenido en un formato estándar para integración.

---

# Estructuras de Datos

## SceneNode

Representa una escena. Incluye:

- `id`: identificador único.
- `text`: narrativa principal.
- `options`: lista de pares `(texto_opcion, id_destino)`.

## StoryGraph

Implementado como:

```
std::map<std::string, SceneNode>
```

Ventajas:

- Acceso rápido por ID.
- Estructura ordenada y clara.
- Representación directa del grafo narrativo.

## Grafo Dirigido Acíclico (DAG)

- Nodos: escenas.
- Aristas: decisiones.
- Nodos finales: escenas sin opciones.

Evita ciclos y facilita la lectura estructural de la historia.

---

# Flujo del Programa

1. Se construye el grafo (`BuildGraph()`).
2. Se establece un nodo inicial.
3. En un ciclo:
   - Se muestra la escena actual.
   - Se leen opciones del jugador.
   - Se valida la entrada.
   - Se salta a la siguiente escena.
4. El juego termina al llegar a un nodo sin opciones.

---

# Formato Estándar para la Historia  

Ejemplo de escena proporcionada por el DNI:

```
ID del nodo: CUEVA_ENTRADA_01

Texto:
"Estás frente a la entrada de una cueva oscura."

Opciones:
1. Entrar con cautela -> CUEVA_DENTRO_02
2. Rodear la zona -> BOSQUE_RAMA_03
3. Regresar al campamento -> FINAL_RETIRADA
```

Integración correspondiente en C++:

```cpp
graph["CUEVA_ENTRADA_01"] = {
    "CUEVA_ENTRADA_01",
    "Estás frente a la entrada de una cueva oscura.",
    {
        {"Entrar con cautela", "CUEVA_DENTRO_02"},
        {"Rodear la zona", "BOSQUE_RAMA_03"},
        {"Regresar al campamento", "FINAL_RETIRADA"}
    }
};
```



---

# Compilación y Ejecución

Compilar:

```
g++ -std=c++17 -O2 main.cpp -o grafo.cpp
```

Ejecutar:

```
./grafo.cpp
```

---

# Cómo Expandir la Historia

1. El DNI escribe nuevas escenas siguiendo el formato estándar.
2. El ADA las integra en `BuildGraph()`.
3. Se prueba cada ruta para evitar:
   - ciclos
   - opciones con IDs inexistentes
   - rutas inconclusas



# Valor Educativo

Este motor sirve para practicar:

- Modelado de grafos en C++.
- Arquitectura modular entre lógica y narrativa.
- Validación y control de flujo textual.
- Construcción incremental de software.
- Prototipado narrativo estructurado.
