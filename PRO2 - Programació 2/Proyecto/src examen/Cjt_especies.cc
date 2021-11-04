/** @file Cjt_especies.cc
    @brief Código de la clase Cjt_especies
*/

#include "Cjt_especies.hh"
#ifndef NO_DIAGRAM
#include <iostream>
#include <algorithm>
#endif

Cjt_especies::Cjt_especies()
{
}
  
Cjt_especies::~Cjt_especies()
{
}

double Cjt_especies::distancia(string id1, string id2)
{
    // Detección errores
    if (not existe_especie(id1))
    {
        if (existe_especie(id2) or id1 == id2)
        {
            cout << "ERROR: La especie " << id1 << " no existe." << endl;
            return -1.0;
        }
        else
        {
            cout << "ERROR: La especie " << id1 << " y la especie " << id2 << " no existen." << endl;
            return -1.0;
        }
    }
    else if (not existe_especie(id2))
    {
        cout << "ERROR: La especie " << id2 << " no existe." << endl;
        return -1.0;
    }
    
    // Caso trivial
    if (id1 == id2)
    {
        return 0.0;
    }

    // Caso general
    Especies::iterator it1 = especies.find(id1);
    Especie& e1 = it1->second;
    
    Especies::iterator it2 = especies.find(id2);
    Especie& e2 = it2->second;
    
    double dist = e1.distancia(e2);
    
    return dist;
}


void Cjt_especies::elimina_especie(const string id)
{
    if (not existe_especie(id))
    {
        cout << "ERROR: La especie " << id << " no existe." << endl;
    }
    else
    {
        especies.erase(id);
    }
}

void Cjt_especies::vaciar_cjt()
{
    especies.clear();
}

string Cjt_especies::obtener_gen(string id) const
{
    if (not existe_especie(id))
    {
        cout << "ERROR: La especie " << id << " no existe." << endl;
        return "";
    }
    else
    {
        Especies::const_iterator it = especies.find(id);
        return it->second.consultar_gen();
    }
}

vector<string> Cjt_especies::obtener_ids() const
{
    vector<string> ids;
    Especies::const_iterator it;
    for (it = especies.begin(); it != especies.end(); ++it)
    {
        ids.push_back(it->second.consultar_id());
    }
    return ids;
}

bool Cjt_especies::existe_especie(string id) const
{
    Especies::const_iterator it = especies.find(id);
    return (it != especies.end());
}

void Cjt_especies::lee_k()
{
    int k;
    cin >> k;
    
    Especie::modifica_k(k);
}

void Cjt_especies::anyadir_especie(const string& id, const string& gen)
{
  if (existe_especie(id))
  {
      cout << "ERROR: La especie " << id << " ya existe." << endl;
  }
  
  else
  {
      Especie e(id, gen);
      especies[id] = e;
  }
}

void Cjt_especies::lee_especie()
{
    Especie e;
    e.lee();

    string id = e.consultar_id();
    string gen = e.consultar_gen();
    
    anyadir_especie(id, gen);
}

void Cjt_especies::lee_cjt_especies()
{
    vaciar_cjt();
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        lee_especie();
    }
}

void Cjt_especies::verifica_especie(const string& id)
{    
    if (existe_especie(id))
    {
        cout << "SI" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
}

void Cjt_especies::imprime_cjt_especies() const
{
    Especies::const_iterator it;
    for (it = especies.begin(); it != especies.end(); ++it)
    {
        it->second.imprime();
    }
}

void Cjt_especies::imprime_tabla_distancias()
{
    Especies::iterator it1;
    for (it1 = especies.begin(); it1 != especies.end(); ++it1)
    {
        Especie& e1 = it1->second;
        cout << "" << e1.consultar_id() << ":";
        
        Especies::iterator it2;
        for (it2 = it1, ++it2; it2 != especies.end(); ++it2)
        {
            Especie& e2 = it2->second;
            cout << " " << e2.consultar_id() << " ";
            
            double dist = e1.distancia(e2);
            cout << "(" << dist << ")";
        }
        
        cout << endl;
    }
}