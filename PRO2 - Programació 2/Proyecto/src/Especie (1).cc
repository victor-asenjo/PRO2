/** @file Especie.cc
    @brief Código de la clase Especie
*/

#include "Especie.hh"

#ifndef NO_DIAGRAM
#include <algorithm>  // max
#include <iostream>
#endif

/* Estáticas */

int Especie::k = 3;  // Valor por defecto

void Especie::modifica_k(int k)
{
    Especie::k = k;
}

int Especie::consulta_k()
{
    return Especie::k;
}

/* No estáticas */

Especie::Especie()
{
}

Especie::Especie(string id, string gen)
{
	this->id = id;
	this->gen = gen;
    generar_meros();
}

Especie::~Especie()
{
}


string Especie::consultar_id() const
{
	return id;
}

string Especie::consultar_gen() const
{
	return gen;
}

int Especie::num_meros()
{
    int num = gen.size() + 1 - Especie::k;
    return max(num, 0);
}

void Especie::generar_meros()
{
    meros.clear();
    
	for (int i = 0; i < num_meros(); ++i)
	{
        string mero = gen.substr(i, Especie::k);
        Meros::iterator it = meros.find(mero);

        if (it == meros.end())
        {
            meros[mero] = 1;
        }
        else
        {
            ++meros[mero];
        }
	}
}

int Especie::ocurrencias_mero(string mero)
{
	Meros::iterator it = meros.find(mero);
	if (it == meros.end())
	{
        return 0;
	}
	return meros[mero];
}

double Especie::distancia(Especie& other)
{
    int num_interseccion = 0;
    
    Meros::iterator it;
    for (it = meros.begin(); it != meros.end(); ++it)
    {
        string mero = it->first;
        int ocur1 = ocurrencias_mero(mero);
        int ocur2 = other.ocurrencias_mero(mero);

        num_interseccion += min(ocur1, ocur2);
    }
    
    int num_union = num_meros() + other.num_meros() - num_interseccion;
    
    //cout << num_interseccion << "/" << num_union << "=";
    
    double fraccion = (double) num_interseccion / (double) num_union;
    
    return (( 1.0 - fraccion ) * 100.0);
}

void Especie::lee()
{
	cin >> id;
    cin >> gen;
	generar_meros();
}

void Especie::imprime() const
{
    cout << id << " " << gen << endl;
}