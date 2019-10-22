#ifndef LISTA_H
#define LISTA_H


typedef struct Horario horario; //possui campos para horário no formato hh:mm:ss

typedef struct Celula celula; //Uma struct do tipo celula define um processo
typedef struct Lista lista;

lista* criaLista();
void insereNaLista(lista*l, int prior, horario chegada, char descricao[]);


#endif