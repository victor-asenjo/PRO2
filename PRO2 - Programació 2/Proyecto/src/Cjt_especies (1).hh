/**
    @file Cjt_especies.hh
    @brief Especificación de la clase Cjt_especies
*/

#ifndef CONJ_ESPECIES_HH
#define CONJ_ESPECIES_HH

#include "Especie.hh"

#ifndef NO_DIAGRAM
#include <map>
#include <string>
#endif

using namespace std;

/**
	@class Cjt_especies
	@brief Representa la información y las operaciones asociadas a un conjunto de especies.
	@brief Tipo de módulo: datos.
*/

class Cjt_especies
{

private:
	/**
	@brief Diccionario de especies donde la clave es el identificador de la especie y el valor la especie.
	*/
    typedef map<string, Especie> Especies;
    Especies especies;

public:

	/* Constructoras */

	/**
	@brief Constructora por defecto.
	\pre Cierto.
	\post El resultado es un conjunto de especies vacío.
	*/
	Cjt_especies();

	/* Destructora */

	/**
	@brief Destructora de Cjt_especies.
	*/
	~Cjt_especies();
	 

	/* Modificadoras */

	/**
	@brief Añadir especie al conjunto.
	\pre El parámetro implícito no contiene ninguna especie con el identificador dado.
	\post Se ha añadido la especie "e" al parámetro implícito.
	*/
    void anyadir_especie(const string& id, const string& gen);

	/**
	@brief Eliminar especie del conjunto.
	\pre El parámetro implícito contiene una especie con el identificador dado.
	\post Se ha eliminado la especie "e" del parámetro implícito.
	*/
	void elimina_especie(const string id);
 
	/**
	@brief Vacía conjunto de especies.
	\pre Hay un conjunto de especies no vacío.
	\post Devuelve un conjunto de especies vacío.
	*/
	void vaciar_cjt();
	
	
	/* Consultoras */
	
	/**
	@brief Obtener gen a partir de un identificador dado.
	\pre El id proporcionado existe, de lo contrario devolverá un error.
	\post El resultado es el gen asociado a la especie.
	*/
	string obtener_gen(string id) const;

	/**
	@brief Obtener todos los identificadores.
	\pre Cierto.
	\post El resultado es un vector de strings con todas las id del conjunto.
	*/
	vector<string> obtener_ids() const;

	/**
	@brief ¿Existe alguna especie con este ID?.
	\pre Cierto.
	\post Devuelve cierto si la especie existe y falso si no existe.
	*/  
	bool existe_especie(string id) const;

	/**
	@brief A partir de dos especies calcula la distancia que hay entre ellas.
	\pre Cierto.
	\post El resultado es la distancia entre las especies a menos que una de las dos no exista.
	*/
    double distancia(string id1, string id2);
	  
	/* Lectura y escritura */

	/**
	@brief Lee por el canal estándar de entrada la longitud de los meros.
	\pre Cierto.
	\post Cierto.
	*/ 
	void lee_k();
	
	/**
	@brief Lee por el canal estándar de entrada una especie (par id-gen)
	\pre Cierto.
	\post El resultado es una especie con el ID y gen entrados.
	*/ 
	void lee_especie();
	
	/**
	@brief Borra el conjunto de especies que había y lee un listado de especies por el canal estándar de entrada.
	\pre Cierto.
	\post Cierto.
	*/ 
	void lee_cjt_especies();

    /**
	@brief Imprime SI o NO según existe la especie.
	\pre Cierto.
	\post SI o NO dependiendo de si la especie del parámetro explícito existe dentro del conjunto.
	*/ 
    void verifica_especie(const string& id);
    
	/**
	@brief Imprime el cjt_especies.
	\pre Cierto.
	\post Se han escrito por el canal estándar de salida las especies del parámetro implícito.
	*/   
	void imprime_cjt_especies() const;

	/**
	@brief Imprime la tabla de distancias entre cada par de especies del conjunto especies si el conjunto no es vacío.
	\pre Cierto.
	\post Se han escrito por el canal estándar de salida la tabla de distancias entre cada par de especies del conjunto especies.
	*/   
	void imprime_tabla_distancias();
};

#endif
