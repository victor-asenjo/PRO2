/**
    @file Cjt_clusters.cc
    @brief Código de la clase Cjt_clusters
*/

#include "Cjt_clusters.hh"
#ifndef NO_DIAGRAM
#include <algorithm>  // max, swap
#include <iostream>
#endif

Cjt_clusters::Cjt_clusters()
{
    clusters_sencillos = 0;
    clusters_complejos = 0;
    clusters_ambos = 0;
    
    cluster_actual = 0;
}
  
Cjt_clusters::~Cjt_clusters()
{
}

void Cjt_clusters::vaciar()
{
    clusters_sencillos = 0;
    clusters_complejos = 0;
    clusters_ambos = 0;
    
    cluster_actual = 0;
    
    clusters.clear();
    clusters_activos.clear();
    distancias.clear();
}

void Cjt_clusters::crear_clusters(Cjt_especies& especies)
{
    vector<string> ids = especies.obtener_ids();
    
    // Índices
    clusters_sencillos = ids.size();
    clusters_complejos = max(clusters_sencillos - 1, 0);
    clusters_ambos = clusters_sencillos + clusters_complejos;
    
    // Rellenar con 'c'
    Cluster c;
    clusters.resize( clusters_ambos, c );

    // Clusters sencillos
    for (int i = 0; i < clusters_sencillos; ++i)
    {
        clusters[i].modificar_identidad( ids[i], i );
        clusters_activos[ids[i]] = i;
    }

    // Cluster actual
    cluster_actual = clusters_sencillos;
}


void Cjt_clusters::crear_tabla_distancias(Cjt_especies& especies)
{
    // Rellenar con ceros
    distancias.resize(clusters_ambos, vector<double>(clusters_ambos, 0.0));
    
    // Distancias sencillas
    for (int x = 0; x < clusters_sencillos; ++x)
    {
        string id_x = clusters[x].consultar_id();
        
        for (int y = x + 1; y < clusters_sencillos; ++y)
        {
            string id_y = clusters[y].consultar_id();
            
            double d = especies.distancia(id_x, id_y);
            
            distancias[x][y] = d;
            distancias[y][x] = d;
        }
    }
}

void Cjt_clusters::inicializar(Cjt_especies& especies)
{
    vaciar();
    crear_clusters(especies);
    crear_tabla_distancias(especies);
}

void Cjt_clusters::inicializa_clusters(Cjt_especies& especies)
{
    inicializar(especies);
    imprime_tabla_distancias();
}

void Cjt_clusters::imprime_tabla_distancias()
{
    Mapa::iterator it1;
    for (it1 = clusters_activos.begin(); it1 != clusters_activos.end(); ++it1)
    {
        int x = it1->second;
        
        cout << it1->first << ":";
        
        Mapa::iterator it2;
        for (it2 = it1, ++it2; it2 != clusters_activos.end(); ++it2)
        {
            int y = it2->second;
            
            cout << " " << it2->first << " (" << distancias[x][y] << ")";
        }
        
        cout << endl;
    }
}

void Cjt_clusters::imprime_cluster(const string& id)
{
    Mapa::const_iterator it = clusters_activos.find(id);
    
    if (it == clusters_activos.end())
    {
        cout << "ERROR: El cluster " << id << " no existe." << endl;
        return;
    }
    
    imprime_cluster_rec(it->second);
    cout << endl;
}

void Cjt_clusters::imprime_cluster_rec(int indice)
{
    Cluster& c = clusters[indice];
    
    if ( c.consultar_hijo_izquierdo() < 0 )
    {
        cout << "[" << c.consultar_id() << "]";
        return;
    }

    cout << "[(" << c.consultar_id() << ", " << c.consultar_distancia() << ") ";

    imprime_cluster_rec(c.consultar_hijo_izquierdo());
    imprime_cluster_rec(c.consultar_hijo_derecho());
    
    cout << "]";
}

string Cjt_clusters::combinar_ids(int x, int y)
{
    string id_x = clusters[x].consultar_id();
    string id_y = clusters[y].consultar_id();
    
    if ( id_x < id_y )
    {
        return (id_x + id_y);
    }
    else
    {
        return (id_y + id_x);
    }
}

Cluster Cjt_clusters::encontrar_distancia_minima()
{
    double min_distancia = 999.9999;
    int min_x = -1;
    int min_y = -1;
    string min_id = "???";
    
    Mapa::iterator it1;
    for (it1 = clusters_activos.begin(); it1 != clusters_activos.end(); ++it1)
    {
        int x = it1->second;
        
        Mapa::iterator it2;
        for (it2 = it1, ++it2; it2 != clusters_activos.end(); ++it2)
        {
            int y = it2->second;
            
            // Comparar:
            double distancia = distancias[x][y];
            
            if ( distancia < min_distancia )
            {
                min_distancia = distancia;
                min_x = x;
                min_y = y;
                min_id = combinar_ids(x, y);
                
            }
            else if ( distancia == min_distancia )
            {
                string id = combinar_ids(x, y);
                
                if ( id < min_id )
                {
                    min_distancia = distancia;
                    min_x = x;
                    min_y = y;
                    min_id = id;
                }
            }
        }
    }
    
    Cluster minimo;
    minimo.modificar_hijos(min_x, min_y, min_distancia);
    return minimo;
}

void Cjt_clusters::nuevo_cluster(Cluster& minimo)
{
    int x = minimo.consultar_hijo_izquierdo();
    int y = minimo.consultar_hijo_derecho();
    double distancia = minimo.consultar_distancia() / 2.0;
    
    string id_x = clusters[x].consultar_id();
    string id_y = clusters[y].consultar_id();

    if ( id_x > id_y )
    {
        swap(x, y);
    }
    
    string id = combinar_ids(x, y);
    clusters[cluster_actual].modificar_identidad(id, cluster_actual);
    clusters[cluster_actual].modificar_hijos(x, y, distancia);
    
    clusters_activos[id] = cluster_actual;
    clusters_activos.erase(id_x);
    clusters_activos.erase(id_y);

    promediar_distancias(x, y);
}

void Cjt_clusters::promediar_distancias(int x, int y)
{
    for (int i = 0; i < cluster_actual; ++i)
    {
        double d_x = distancias[x][i];
        double d_y = distancias[y][i];
        double d = (d_x + d_y) / 2.0;
        
        distancias[cluster_actual][i] = d;
        distancias[i][cluster_actual] = d;
    }
}

bool Cjt_clusters::unir_clusters()
{
    if ( clusters_activos.size() < 2 )
    {
        cout << "ERROR: num_clusters <= 1" << endl;
        return false;
    }
    
    Cluster minimo = encontrar_distancia_minima();
    
    nuevo_cluster(minimo);
    
    ++cluster_actual;
    
    return true;
}

void Cjt_clusters::ejecuta_paso_wpgma()
{
    if ( unir_clusters() )
    {
        imprime_tabla_distancias();
    }
}

void Cjt_clusters::imprime_arbol_filogenetico(Cjt_especies& especies)
{
    inicializar(especies);
    
    if (clusters_sencillos < 1)
    {
        cout << "ERROR: El conjunto de clusters es vacio." << endl;
        return;
    }

    for (int i = clusters_sencillos; i < clusters_ambos; ++i)
    {
        unir_clusters();
    }
    
    imprime_cluster_rec(cluster_actual - 1);
    cout << endl;
}