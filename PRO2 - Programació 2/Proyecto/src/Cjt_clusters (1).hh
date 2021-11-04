/**
    @file Cjt_clusters.hh
    @brief Especificación de la clase Cjt_clusters
*/

#ifndef CONJ_CLUSTERS_HH
#define CONJ_CLUSTERS_HH

#include "Cluster.hh"
#include "Cjt_especies.hh"

#ifndef NO_DIAGRAM
#include <map>
#include <string>
#include <vector>
#endif


using namespace std; 

/**
    @class Cjt_clusters
    @brief Representa un conjunto de clusters que se pueden consultar y modificar sus elementos.
    @brief Tipo de módulo: datos.
*/

class Cjt_clusters
{

private:
    /**
    @brief La clave es el identificador del clsuter y el valor es el índice del cluster.
    */
    typedef map<string, int> Mapa;
    
    /**
    @brief Diccionario con los clusters actualmente en juego: la clave es el identificador del clsuter y el valor es el índice del cluster.
    */
    Mapa clusters_activos;
    

    /**
    @brief Cantidad de clústers con una sola especie
    */
    int clusters_sencillos;   // Cantidad de clústers con una sola especie
    
    /**
    @brief Cantidad de clústers con varias especies
    */
    int clusters_complejos;   // Cantidad de clústers con varias especies
    
    /**
    @brief Cantidad de clústers
    */
    int clusters_ambos;       // Cantidad de clústers
    
    /**
    @brief Índice del nuevo clúster
    */
    int cluster_actual;       // Índice del nuevo clúster
    
    /**
    @brief Vector con todos los clsuters
    */
    vector<Cluster> clusters;
    
    /**
    @brief Tabla de distancias
    */
    vector<vector<double>> distancias;
    
    
public:

    /* Constructoras */

    /**
    @brief Constructora Cjt_clusters.
    \pre Cierto.
    \post El resultado es un conjunto de clusters vacío.
    */
    Cjt_clusters();

    /* Destructora */

    /**
    @brief Destructora de Cjt_clusters.
    */
    ~Cjt_clusters();

    /* Modificadoras */

    /**
    @brief A partir del conjunto de especies, imprime la tabla de distancias.
    \pre Cierto.
    \post Cierto.
    */
    void inicializa_clusters(Cjt_especies& cjt_esp);

    /**
    @brief Ejecuta un paso del algoritmo WPGMA (fusiona los dos clústers a menor distancia en uno nuevo) e imprime la tabla de distancias entre clústers resultante.
    \post Ejecuta un paso del algoritmo e imprmie la tabla de distancias entre clústers resultante.
    */
    void ejecuta_paso_wpgma(); 

    /* Lectura y escritura */

    /**
    @brief Imprime el cluster en preorden.
    \pre Cierto.
    \post Se ha escrito por el canal estándar de salida el clúster con el identificador dado.
    */
    void imprime_cluster(const string& id);

    /**
    @brief Imprime la tabla de distancias entre clústers.
    \pre Cierto.
    \post Se ha escrito por el canal estándar de salida la tabla de distancias.
    */
    void imprime_tabla_distancias();
    
    /**
    @brief Inicializa los clsuters, ejecuta el algoritmo WPGMA por completo e imprime el árbol filogenético para el conjunto de especies actual.
    \pre Cierto.
    \post Se ha escrito por el canal estándar de salida el árbol filogenético para el conjunto de especies actual después de aplicar el algoritmo WPGMA.
    */
    void imprime_arbol_filogenetico(Cjt_especies& especies);

private:
    /**
    @brief Borrar todo el contenido del conjunto. Forma parte de la inicialización de clusters.
    \pre Cierto.
    \post Conjunto borrado.
    */
    void vaciar();
    
    /**
    @brief Crea los clusters a partir del conjunto de especies y forma parte de la inicialización.
    \pre Cierto.
    \post Cierto.
    */
    void crear_clusters(Cjt_especies& especies);
    
    /**
    @brief Crear la tabla de distancias a partir del conjunto de especies y forma parte de la inicialización.
    \pre Cierto.
    \post Cierto.
    */
    void crear_tabla_distancias(Cjt_especies& especies);
 
    /**
    @brief Inicializa los clusters sin imprimir la tabla de distancias.
    \pre Cierto.
    \post Cierto.
    */
    void inicializar(Cjt_especies& especies);
    
    /**
    @brief Llamada recursiva de imprime_clsuter. Dado un índice válido, imprime el árbol en preorden.
    \pre Cierto.
    \post Imprime el árbol en preorden.
    */
    void imprime_cluster_rec(int indice);
    
    /**
    @brief Busca la distancia mínima en la tabla de distancias (es parte de ejecutar_paso_wpgma).
    \pre Cierto.
    \post Devuelve un falso cluster con la información de la distancia mínima.
    */
    Cluster encontrar_distancia_minima();
    
    /**
    @brief Calcula las distancias del nuevo cluster a los clusters restantes.
    \pre Cierto.
    \post Cierto.
    */
    void promediar_distancias(int x, int y);
    
    /**
    @brief Crea un nuevo cluster a aprtir de sus hijos y los borra.
    \pre Cierto.
    \post Cierto.
    */
    void nuevo_cluster(Cluster& minimo);
    
    /**
    @brief Ejecuta un paso del algoritmo sin imprimir la tabla de distancias.
    \pre Cierto.
    \post Devuelve cierto si había dos cluster para unir y falso si había menos de dos.
    */
    bool unir_clusters();
    
    /**
    @brief Dados los índices de los hijos, genera el identificador del padre.
    \pre Dos hijos que existen.
    \post Devuelve el identificador del padre.
    */
    string combinar_ids(int x, int y);
};

#endif
