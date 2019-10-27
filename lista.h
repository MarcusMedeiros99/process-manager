#ifndef LISTA_H
#define LISTA_H
#include "horario.h"

#define MAX_DESCR 51

//tipos de ornenação (por prioridade ou horáio)
enum {P, T, N};

typedef struct Lista lista;

lista* criaLista();
void insereNaLista(lista*l, int prior, horario chegada, char descricao[]);
void printLista(lista* l, int tipoOrdena);
void printNext(lista* l, int tipoOrdena);
void destroiLista(lista* l);

#endif