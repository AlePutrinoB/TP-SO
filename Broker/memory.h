/*
 * entrenador.h
 *
 *  Created on: 1 may. 2020
 *      Author: utnso
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/log.h>
#include<commons/config.h>
#include<commons/collections/list.h>
#include<commons/collections/queue.h>
#include<time.h>
#include<string.h>
#include<pthread.h>

typedef struct{
	void* base;
	uint32_t tamanio;
	t_list* particiones;
}t_memoria;

typedef struct{
	void* base;
	uint32_t tamanio;
	bool ocupada;
}t_particion;


t_memoria* crear_memoria(uint32_t);
t_particion* crear_particion(void*, uint32_t, bool);
void agregar_stream(t_memoria*, void*);
uint32_t buscar_indice_particion(t_list*, uint32_t);
void agregar_particion(t_list*, uint32_t, void*);
void mostrar_memoria(t_memoria*);


#endif /* MEMORY_H_ */
