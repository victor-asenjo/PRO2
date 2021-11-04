/** 
    @file Especie.hh
    @brief Especificación de la clase Especie
*/

#ifndef ESPECIE_HH
#define ESPECIE_HH

#ifndef NO_DIAGRAM
#include <string>
#include <vector>
#include <map>
#endif

using namespace std;

/**
    @class Especie
    @brief Representa el conjunto de características y operaciones de las especies.
	@brief Tipo de módulo: datos.
*/

class Especie
{

private:
    /** 
	@brief Identificador de la especie.
	*/
	string id;
	/**
	@brief Gen de la especie.
	*/
    string gen;

	/**
	@brief Diccionario de los kmeros con contadores de cada mero.
	*/
    typedef map<string, int> Meros;
    Meros meros;
    
    double norma;

    /* Estáticas */
	/**
	@brief Longitud de los meros.
	*/
    static int k;
	  
public:
    /* Constructoras */

    /**
    @brief Constructora Especie vacía.
    \pre Cierto.
    \post El resultado es una especie sin parámetros.
    */
    Especie();

	/**
	@brief Constructora Especie.
	\pre Cierto.
	\post El resultado es una especie con el id y gen proporcionados.
	*/
	Especie(string id, string gen);

	/**
	@brief Destructora de Especie. 
	*/
	~Especie();
	  
    /* Estáticas */
    /**
	  obtener la longitud de los meros
	*/
    static void modifica_k(int k);
    
    static int consulta_k();
  
    /* Consultoras */
    
	/**
	@brief Consultar id de la especie del parámetro implícito.
	\pre Cierto.
	\post El resultado es el id del parámetro implícito.
	*/
	string consultar_id() const;

	/**
	@brief Consultar gen de la especie del parámetro implícito.
	\pre Cierto.
	\post El resultado es el gen del parámetro implícito.
	*/
	string consultar_gen() const;
    
    double consultar_norma() const;

	/* Cálculo */

	/**
	@brief Construir diccionario de mero a partir del gen y la longitud k.
	\pre Cierto.
	\post Cierto.
	*/
	void generar_meros();

	/**
	@brief Cantidad de meros diferentes dentro del gen implícito.
	\pre Cierto.
	\post Número de meros diferentes dentro del gen implícito.
	*/
	int num_meros();

	/**
	@brief Dado un mero devuelve el contador.
	\pre Cierto.
	\post Devuelve el contador de meros.
	*/
	int ocurrencias_mero(string mero);

	/**
	@brief A partir de dos especies calcula la distancia que hay entre ellas.
	\pre Cierto.
	\post El distancia a otra especie desde el parámetro implícito.
	*/
	double distancia(Especie& other);

	/* Lectura y escritura */
	
	/**
	@brief Lee por el canal estándar de entrada una especie (par identificador-gen).
	\pre Cierto.
	\post Cierto.
	*/
	void lee();

	/**
	@brief Imprime la especie del parámetro implícito.
	\pre Cierto.
	\post Se ha escrito por el canal estándar de salida la especie del parámetro implícito.
	*/ 
	void imprime() const;
};
#endif
