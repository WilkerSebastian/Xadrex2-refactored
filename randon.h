#ifndef RANDON_H_INCLUDED
#define RANDON_H_INCLUDED

#define MIN 1
#define MAX 1000
#define QTDE 10000  //precisa ser menor que MAX

int rand_int(int n) {
    int limit = RAND_MAX - RAND_MAX % n;
    int rnd;

    do {
        rnd = rand();
    } while (rnd >= limit);
    return rnd % n;
}

#endif
