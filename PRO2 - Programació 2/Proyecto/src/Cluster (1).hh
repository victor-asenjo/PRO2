/** @file Cluster.hh
    @brief Especificación de la clase Cluster
*/

#ifndef CLUSTER_HH
#define CLUSTER_HH

#ifndef NO_DIAGRAM
#include <string>
#endif

using namespace std; 

/**
    @class Cluster
    @brief Representa un árbol de especies.
    @brief Tipo de módulo: datos.
*/

class Cluster
{

private:
    /**
    @brief Identificador del nodo raíz del árbol.
    */
    string id;
    
    /**
    @brief Índice del nodo raíz dentro del vector de Clusters.
    */
    int indice;
    
    /**
    @brief Índice del nodo izquierdo.
    */
    int indice_izquierdo;
    
    /**
    @brief Índice del nodo derecho.
    */
    int indice_derecho;
    
    /**
    @brief La distancia del nodo raíz a cada uno de sus hijos (que es la mitad de la distancia entre los hijos).
    */
    double distancia;
    
public:

    /* Constructoras */

    /**
    @brief Constructora por defecto de un cluster.
    \pre Cierto.
    \post El resultado es un cluster vacío.
    */
    Cluster();

    /* Destructora */

    /**
    @brief Destructora de Cluster.
    */
    ~Cluster();
   
    /* Modificadoras */
    /**
    @brief Asignar un identificador al nodo del cluster y el índice del nodo raíz.
    \pre Cierto.
    \post Cierto.
    */
    void modificar_identidad(string id, int indice);

    /**
    @brief Asignar los índices de los dos hijos y la distancia del nodo raíz a cada uno de ellos.
    \pre Cierto.
    \post Cierto.
    */
    void modificar_hijos(int izquierdo, int derecho, double distancia);
  
    /* Consultoras */
    /**
    @brief Devolver el identificador del nodo raíz.
    \pre Cierto.
    \post Devuelve el identificador del nodo raíz.
    */
    string consultar_id() const;
    
    /**
    @brief Devolver el identificador del hijo izquierdo.
    \pre Cierto.
    \post Devuelve el identificador del hijo izquierdo.
    */
    int consultar_hijo_izquierdo() const;
    /**
    @brief Devolver el identificador del hijo derecho.
    \pre Cierto.
    \post Devuelve el identificador del hijo derecho.
    */
    int consultar_hijo_derecho() const;
    
    /**
    @brief Devolver la distancia del nodo raíz a cada uno de sus hijos.
    \pre Cierto.
    \post Devuelve la distancia del nodo raíz a cada uno de sus hijos.
    */
    double consultar_distancia() const;
};

#endif