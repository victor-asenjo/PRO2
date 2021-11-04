/** @file Especie.cc
    @brief Código de la clase Especie
*/

#include "Especie.hh"

#ifndef NO_DIAGRAM
#include <algorithm>  // max
#include <iostream>
#endif

#define _USE_MATH_DEFINES
#include <cmath>


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

double Especie::consultar_norma() const
{
    return norma;
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
    
    // Calcular norma
    double norma_sq = 0.0;
    
    Meros::iterator it;
    for (it = meros.begin(); it != meros.end(); ++it)
    {
        int ocur = it->second;
        norma_sq += ocur * ocur;
    }
    
    this->norma = sqrt(norma_sq);
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
    double producto_escalar = 0.0;
    
    Meros::iterator it;
    for (it = meros.begin(); it != meros.end(); ++it)
    {
        string mero = it->first;
        int ocur1 = ocurrencias_mero(mero);
        int ocur2 = other.ocurrencias_mero(mero);

        producto_escalar += ocur1 * ocur2;
    }
    
    double norma2 = other.consultar_norma();
    
    double arg = producto_escalar / norma / norma2;
    
    double sustraendo = acos(arg) * M_1_PI;
    
    return (( 1.0 - sustraendo ) * 100.0);
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
