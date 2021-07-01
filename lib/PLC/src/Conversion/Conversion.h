#ifndef Conversion_h
#define Conversion_h
// NORM_X Normaliser
#define NORM_X(MIN, VALUE, MAX) ((VALUE - MIN) / (MAX - MIN))

// SCALE_X Mise à l'échelle
#define SCALE_X(MIN, VALUE, MAX) ((VALUE * (MAX - MIN)) + MIN)

// LIMIT Contraindre une valeur
#define LIMIT(MIN, VALUE, MAX) (VALUE)<(MIN)?(MIN):((VALUE)>(MAX)?(MAX):(VALUE)))
#endif