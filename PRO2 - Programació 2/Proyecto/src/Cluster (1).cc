/** @file Cluster.cc
    @brief Código de la clase Cluster
*/

#include "Cluster.hh"
#ifndef NO_DIAGRAM
#include <iostream>
#endif

Cluster::Cluster()
{
    this->id = "???";
    
    this->indice = -1;
    this->indice_izquierdo = -1;
    this->indice_derecho = -1;
    
    this->distancia = 0.0;
}

Cluster::~Cluster()
{
}

void Cluster::modificar_identidad(string id, int indice)
{
    this->id = id;
    this->indice = indice;
}

void Cluster::modificar_hijos(int izquierdo, int derecho, double distancia)
{
    this->indice_izquierdo = izquierdo;
    this->indice_derecho = derecho;
    
    this->distancia = distancia;
}

string Cluster::consultar_id() const
{
    return id;
}

int Cluster::consultar_hijo_izquierdo() const
{
    return indice_izquierdo;
}

int Cluster::consultar_hijo_derecho() const
{
    return indice_derecho;
}

double Cluster::consultar_distancia() const
{
    return distancia;
}