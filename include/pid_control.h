// pid_control.h

// implementation of a SISO PID controller

#ifndef PID_CONTROL_H
#define PID_CONTROL_H

#include <stdlib.h>
#include <stdio.h>

#define U_MAX 10.0f

float k_p, k_i, k_d;
float integral,derivative,last_err;

void pid_init(float _k_p, float _k_i, float _k_d) {
	k_p = _k_p;
	k_i = _k_i;
	k_d = _k_d;

	integral = 0.0f;
	derivative = 0.0f;
	last_err = 0.0f;
}

float pid_step(float _err) {
	integral = integral + _err;
	derivative = _err - last_err;
	float u = k_p*_err + k_i*integral + k_d*derivative;

	if (u>U_MAX) u=U_MAX;
	return u;
}


#endif