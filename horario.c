#include "horario.h"

int menorQueHorario (horario a, horario b) {
	return a.hh < b.hh || (a.hh == b.hh && a.mm < b.mm) || (a.hh == b.hh && a.mm == b.mm && a.ss < b.ss);
}