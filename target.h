/* File:   target.h
Author: Ben Snalam, Kirsten Middelkoop, U
Date:   3 Aug 2010
Descr:  Common configuration definitions.
*/


#ifndef TARGET_H
#define TARGET_H


/* Motor Driver Interface */
#define MOTOR_ENLEFT  PIO_DEFINE(PORT_B, 1)
#define MOTOR_ENRIGHT PIO_DEFINE(PORT_B, 2)
#define MOTOR_EN {MOTOR_ENLEFT, MOTOR_ENRIGHT}

#define MOTOR_DRLEFT  PIO_DEFINE(PORT_D, 0)
#define MOTOR_DRRIGHT PIO_DEFINE(PORT_D, 1)
#define MOTOR_DR {MOTOR_DRLEFT, MOTOR_DRRIGHT}

/* Sensors inputs */
#define SENSOR0 PIO_DEFINE(PORT_C, 0)
#define SENSOR1 PIO_DEFINE(PORT_C, 1)
#define SENSOR2 PIO_DEFINE(PORT_C, 2)
#define SENSORS {SENSOR0, SENSOR1, SENSOR2}

#endif
