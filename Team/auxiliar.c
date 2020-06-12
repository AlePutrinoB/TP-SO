/*
 * auxiliar.c
 *
 *  Created on: 9 may. 2020
 *      Author: utnso
 */
#include "auxiliar.h"

/*
 * @NAME: distancia
 * @DESC: Dados un entrenador y un appeared_pokemon, nos devuelve
 * 		  la distancia entre estos dos.
 */
u_int32_t distancia(t_entrenador* entrenador, t_appeared_pokemon* appeared_pokemon){
	u_int32_t diferencia_en_x = entrenador->posicion->x - appeared_pokemon->posicion->x;
	u_int32_t diferencia_en_y = entrenador->posicion->y - appeared_pokemon->posicion->y;
	return abs(diferencia_en_x) + abs(diferencia_en_y);
}

/*
 * @NAME: list_flatten
 * @DESC: Dada una lista de listas, crea una nueva lista y
 * 		  guarda en ella el resultado de aplanar la lista
 * 		  pasada por parametro.
 */
t_list* list_flatten(t_list* listas){

	t_list* lista = list_create();

	for(int i = 0; i < list_size(listas); i++){
		t_list* sublista = list_get(listas,i);
		for(int j = 0; j < list_size(sublista); j++){
			char* pokemon = list_get(sublista,j);
			list_add(lista, pokemon);
		}
	}

	return lista;
}

/*
 * @NAME: list_elem
 * @DESC: Dados un elemento (tipo string) y una lista, me dice si ese
 * 	      elemento se encuentra en la lista.
 */
bool list_elem(char* elemento, t_list* lista){
	bool encontrado = false;
	for(int i = 0; i < list_size(lista) && !encontrado; i++){
		char* pokemon = list_get(lista, i);
		encontrado = string_equals_ignore_case(pokemon, elemento);
	}
	return encontrado;
}

/* Se puede eliminar?
 * @NAME: eliminar_repetidos
 * @DESC: Dada la lista que representa el objetivo global,
 *        elimina sus repetidos y la devuelve.
 */
t_list* eliminar_repetidos(t_list* objetivo_global){

	t_list* lista_aplanada = list_flatten(objetivo_global);
	t_list* especies_requeridas = list_create();

	for(int i = 0; i < list_size(lista_aplanada); i++){
		char* pokemon = list_get(lista_aplanada, i);
		if(!list_elem(pokemon, especies_requeridas)){
			list_add(especies_requeridas, pokemon);
		}
	}

	list_destroy(lista_aplanada);

	return especies_requeridas;
}

/* Se puede eliminar?
 * @NAME: agregar_a_la_lista
 * @DESC: Dada una lista de pokemons y un pokemon (en formato string),
 * 	      lo agrega a la lista
 */
void agregar_a_la_lista(t_list* lista_pokemon, char* pokemon){
	if (pokemon != NULL) list_add(lista_pokemon, pokemon);
}

char** get_array_value(char* string){
	int length_value = strlen(string) - 1;
	int contador = 2;

	for(int i = 0; i < length_value; i++){
		if (string[i] == ',') contador++;
	}

	char** read_array = malloc(sizeof(char*) * contador);
	read_array[0] = string_new();

	int j = 0;
	for (int i = 1; i < length_value; i++){
		if (string[i] == ','){
			j++;
			read_array[j] = string_new();
		} else {
			string_append_with_format(&(read_array[j]), "%c", string[i]);
		}
	}

	read_array[contador - 1] = NULL;
	return read_array;
}

/*
 * @NAME: pasar_a_lista_de_pokemon
 * @DESC: Dados un config y una cadena, crea una lista
 * 		  con los pokemons leidos en el valor de la cadena especificada
 * 		  dentro del config.
 */
t_list* pasar_a_lista_de_pokemon(t_config* config, char* cadena) {
  //char** read_array = config_get_array_value(config, cadena);
	char* suplente = config_get_string_value(config, cadena);

	char** read_array = get_array_value(suplente);

  t_list* pokemon = list_create();
  t_list* sublista;

  void _a_la_lista(char *poke) {
    if (poke != NULL) {
      list_add(sublista, poke);
    }
  }

  void _dividir(char *string) {
	sublista = list_create();
    if(string != NULL) {
      char** pokes = string_split(string, "|");
      string_iterate_lines(pokes, _a_la_lista);
      free(pokes);
    } else exit(1);
    list_add(pokemon,sublista);
  }

  string_iterate_lines(read_array, _dividir);

  string_iterate_lines(read_array, (void*) free);

  free(read_array);
  return pokemon;
}

/*
 * @NAME: pasar_a_lista_de_pokemon
 * @DESC: Dados un config y una cadena, crea una lista
 * 		  con las posiciones dadas en el valor de la cadena especificada
 * 		  dentro del config.
 */
t_list* pasar_a_lista_de_posiciones(t_config* config, char* cadena) {
  char** read_array = config_get_array_value(config, cadena);

  t_list* posiciones = list_create();
  t_posicion* posicion;

  void _dividir(char *string) {
    if(string != NULL) {
      char** punto = string_split(string, "|");
      u_int32_t x = atoi(punto[0]);
      u_int32_t y = atoi(punto[1]);
      posicion = posicion_create(x,y);
      string_iterate_lines(punto, (void*) free);
      free(punto);
    } else exit(1);
    list_add(posiciones,posicion);
  }

  string_iterate_lines(read_array, _dividir);

  string_iterate_lines(read_array, (void*) free);

  free(read_array);



  return posiciones;
}

