#ifndef HORARIO_H
#define HORARIO_H

typedef struct Horario {
	int hh;
	int mm;
	int ss;
} horario;

int menorQueHorario(horario a, horario b);
int igualHorario (horario a, horario b);


#endif