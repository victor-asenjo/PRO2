/**
    @file program.cc
    @brief Programa principal de la Práctica de PRO2 cuatrimestre de primavera 2020.
 */

#ifndef NO_DIAGRAM
#include <iostream>
#endif

#include "Cjt_especies.hh"
#include "Cjt_clusters.hh"

using namespace std;

int main()
{
    Cjt_especies cjt_esp;
    Cjt_clusters cjt_clus;

    cjt_esp.lee_k();

    bool fin = false;

    while (not fin)
    {
        string comando;
        cin >> comando;

        if (comando == "crea_especie")
        {
            string id, gen;
            cin >> id >> gen;
            cout << "# " << comando << " " << id << " " << gen << endl;
            cjt_esp.anyadir_especie(id, gen);
        }
        else if (comando == "obtener_gen")
        {
            string id;
            cin >> id;

            cout << "# " << comando << " " << id << endl;
            
            string gen = cjt_esp.obtener_gen(id);
            if ( gen != "" )
            {
                cout << gen << endl;
            }
        }
        else if (comando == "distancia")
        {
            string id1, id2;
            cin >> id1 >> id2;
            
            cout << "# " << comando << " " << id1 << " " << id2 << endl;

            double dist = cjt_esp.distancia(id1, id2);
            if (dist != -1.0)
            {
                cout << dist << endl;
            }
        }
        else if (comando == "elimina_especie")
        {
            string id;
            cin >> id;

            cout << "# " << comando << " " << id << endl;
            cjt_esp.elimina_especie(id);
        }
        else if (comando == "existe_especie")
        {
            string id;
            cin >> id;
            cout << "# " << comando << " " << id << endl;
            cjt_esp.verifica_especie(id);
        }
        else if (comando == "lee_cjt_especies")
        {
            cout << "# " << comando << endl;
            cjt_esp.lee_cjt_especies();
        }
        else if (comando == "imprime_cjt_especies")
        {
            cout << "# " << comando << endl;
            cjt_esp.imprime_cjt_especies();
        }
        else if (comando == "tabla_distancias")
        {
            cout << "# " << comando << endl;
            cjt_esp.imprime_tabla_distancias();
        }
        else if (comando == "inicializa_clusters")
        {
            cout << "# " << comando << endl;
            cjt_clus.inicializa_clusters(cjt_esp);
        }
        else if (comando == "ejecuta_paso_wpgma")
        {
            cout << "# " << comando << endl;
            cjt_clus.ejecuta_paso_wpgma();
        }
        else if (comando == "imprime_cluster")
        {
            string id;
            cin >> id;
            cout << "# " << comando << " " << id << endl;
            cjt_clus.imprime_cluster(id);
        }
        else if (comando == "imprime_arbol_filogenetico")
        {
            cout << "# " << comando << endl;
            cjt_clus.imprime_arbol_filogenetico(cjt_esp);
        }
        else if (comando == "fin")
        {
            fin = true;
        }
        else
        {
            cout << "ERROR: Comando no reconocido." << endl;
            fin = true;
        }
        
        // Salto de línea
        if (not fin)
        {
            cout << endl;
        }
    }
}

/**
 * @mainpage Árbol filogenético.

   Este programa permite construir i modificar el árbol filogenético para un conjunto de N especies utilizando el método conocido como WPGMA (weighted pair group with arithmetic mean).
   Los comandos que ofrece el programa son:
        1. crea_especie: Crea una especie con el identificador y gen (dos strings) dados. Escribe un mensaje de error si ya existe una especie con el mismo identificador. La especie creada, si no hay error, se agrega al conjunto de especies.
        2. obtener_gen: Dado un identificador de especie, imprime el gen asociado a la especie. Escribe un mensaje de error si no existe una especie con el identificador dado.
        3. distancia: Dados dos identificadores de especies, imprime la distancia entre las dos especies. Se escribe un mensaje de error si alguna de las dos especies cuyos identificadores se dan no existen.
        4. elimina_especie: Dado el identificador de una especie e la elimina del conjunto de especies. Escribe un mensaje de error si la especie con el identificador dado no existe.
        5. existe_especie: Dado el identificador de una especie e imprime una indicación de si dicha especie existe (es decir, es parte del conjunto de especies).
        6. lee_cjt_especies: Lee del canal estándar de entrada un entero n >= 0 y a continuación una secuencia de n especies (pares identificador-gen). Las n especies dadas tienen identificadores distintos entre sí. Los contenidos previos del conjunto de especies se descartan —las especies dejan de existir— y las n especies leídas se agregan al conjunto de especies.
        7. imprime_cjt_especies: Imprime en el canal estándar de salida el conjunto de especies. Si el conjunto es vacío, no imprime ninguna información.
        8. tabla_distancias: Imprime la tabla de distancias entre cada par de especies del conjunto de especies. Si el conjunto es vacío, no imprime ninguna información.
        9. inicializa_clusters: Inicializa el conjunto de clústers con el conjunto de especies en el estado en el que esté en ese momento, e imprime los clústers resultantes, así como la tabla de distancias entre clústers. Al imprimir la tabla de distancias se usarán los identificadores de los clústers para indexar filas y columnas. Si el conjunto es vacío, no imprime ninguna información.
        10. ejecuta_paso_wpgma: ejecuta un paso del algoritmo WPGMA (fusiona los dos clústers a menor distancia en uno nuevo) e imprime la tabla de distancias entre clústers resultante. Al imprimir la tabla de distancias se usarán los identificadores de los clústers para indexar filas y columnas. En caso de que el número de clústers del conjunto sea menor o igual que uno solamente se debe imprimir un mensaje de error.
        11. imprime_cluster: dado un identificador alpha, imprime el clúster (su “estructura arborescente”) con el identificador dado, o un error si no existe un clúster con dicho identificador en el conjunto de clústers.
        12. imprime_arbol_filogenetico: imprime el árbol filogenético para el conjunto de especies actual; dicho árbol es el clúster que agrupa todas las especies, resultante de aplicar el algoritmo WPGMA. El contenido del conjunto de clústers previo se descarta y se reinicializa con el conjunto de especies en el estado en el que esté en ese momento, para a continuación aplicar el algoritmo. El conjunto de clústers final es el que queda después de aplicar el algoritmo. Se imprimirá la estructura arborescente del clúster con los identificadores de los clústers (raíces de los subárboles) y la distancia entre cada clúster y sus hojas descendientes (véase la figura 3; dichas distancias son los números a la izquierda, y se pueden calcular fácilmente a partir de la distancia entre los clústers cuya combinación da origen a cada clúster). El formato preciso en el que se ha de imprimir el árbol se mostrará en los juegos de pruebas públicos. Si el nuevo conjunto de clústers es vacío, solamente se ha de escribir un mensaje de error.
        13. fin: finaliza la ejecución del programa.
 */
