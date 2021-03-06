/* inspired by http://stackoverflow.com/questions/19596375/intercepting-fortran-stop-from-c */

#include <setjmp.h>
#include <stdlib.h>
#include <stdbool.h>
#include <complex.h>

volatile bool please_dont_exit = false;
int stopped = 0;
jmp_buf jenv;

static void fortran_stop_handler()
{
    if (please_dont_exit) {
        atexit(fortran_stop_handler);
        stopped = 1;
        longjmp(jenv, 1);
    }
}

void fortran_stop_handler_init() 
{
    atexit(fortran_stop_handler);
}

int has_stopped()
{
    int r;
    r = stopped;
    stopped = 0;
    return r;
}


void dsexpv_(
        int *n, int*m, double *t, double *v, double *w, double *tol,
        double *anorm, double *wsp, int *lwsp, int *iwsp, int *liwsp, 
        void (*matvec)(double*, double*), int *itrace, int *iflag, void** arg);

void dgexpv_(
        int *n, int*m, double *t, double *v, double *w, double *tol,
        double *anorm, double *wsp, int *lwsp, int *iwsp, int *liwsp, 
        void (*matvec)(double*, double*), int *itrace, int *iflag, void** arg);

void zhexpv_(
        int *n, int*m, double *t, double complex *v, double complex *w, double *tol,
        double *anorm, double complex *wsp, int *lwsp, int *iwsp, int *liwsp, 
        void (*matvec)(double complex*, double complex*), int *itrace, int *iflag, void** arg);

void zgexpv_(
        int *n, int*m, double *t, double complex *v, double complex *w, double *tol,
        double *anorm, double complex *wsp, int *lwsp, int *iwsp, int *liwsp, 
        void (*matvec)(double complex*, double complex*), int *itrace, int *iflag, void** arg);

void dsphiv_(
        int *n, int*m, double *t, double *u, double *v, double *w, double *tol,
        double *anorm, double *wsp, int *lwsp, int *iwsp, int *liwsp, 
        void (*matvec)(double*, double*), int *itrace, int *iflag, void** arg);

void dgphiv_(
        int *n, int*m, double *t, double *u, double *v, double *w, double *tol,
        double *anorm, double *wsp, int *lwsp, int *iwsp, int *liwsp, 
        void (*matvec)(double*, double*), int *itrace, int *iflag, void** arg);

void zhphiv_(
        int *n, int*m, double *t, double complex *u, double complex *v, double complex *w, double *tol,
        double *anorm, double complex *wsp, int *lwsp, int *iwsp, int *liwsp, 
        void (*matvec)(double complex*, double complex*), int *itrace, int *iflag, void** arg);

void zgphiv_(
        int *n, int*m, double *t, double complex *u, double complex *v, double complex *w, double *tol,
        double *anorm, double complex *wsp, int *lwsp, int *iwsp, int *liwsp, 
        void (*matvec)(double complex*, double complex*), int *itrace, int *iflag, void** arg);



void dsexpv_wrap(
        int *n, int*m, double *t, double *v, double *w, double *tol,
        double *anorm, double *wsp, int *lwsp, int *iwsp, int *liwsp, 
        void (*matvec)(double*, double*), int *itrace, int *iflag, void** arg)
{
    please_dont_exit = true;
    if (!setjmp(jenv)) {
         dsexpv_(n, m, t, v, w, tol, anorm, wsp, lwsp, iwsp, liwsp, matvec, itrace, iflag, arg);
    }
    please_dont_exit = false;
}

void dgexpv_wrap(
        int *n, int*m, double *t, double *v, double *w, double *tol,
        double *anorm, double *wsp, int *lwsp, int *iwsp, int *liwsp, 
        void (*matvec)(double*, double*), int *itrace, int *iflag, void** arg)
{
    please_dont_exit = true;
    if (!setjmp(jenv)) {
         dgexpv_(n, m, t, v, w, tol, anorm, wsp, lwsp, iwsp, liwsp, matvec, itrace, iflag, arg);
    }
    please_dont_exit = false;
}

void zhexpv_wrap(
        int *n, int*m, double *t, double complex *v, double complex *w, double *tol,
        double *anorm, double complex *wsp, int *lwsp, int *iwsp, int *liwsp, 
        void (*matvec)(double complex*, double complex*), int *itrace, int *iflag, void** arg)
{
    please_dont_exit = true;
    if (!setjmp(jenv)) {
         zhexpv_(n, m, t, v, w, tol, anorm, wsp, lwsp, iwsp, liwsp, matvec, itrace, iflag, arg);
    }
    please_dont_exit = false;
}

void zgexpv_wrap(
        int *n, int*m, double *t, double complex *v, double complex *w, double *tol,
        double *anorm, double complex *wsp, int *lwsp, int *iwsp, int *liwsp, 
        void (*matvec)(double complex*, double complex*), int *itrace, int *iflag, void** arg)
{
    please_dont_exit = true;
    if (!setjmp(jenv)) {
         zgexpv_(n, m, t, v, w, tol, anorm, wsp, lwsp, iwsp, liwsp, matvec, itrace, iflag, arg);
    }
    please_dont_exit = false;
}

void dsphiv_wrap(
        int *n, int*m, double *t, double *u, double *v, double *w, double *tol,
        double *anorm, double *wsp, int *lwsp, int *iwsp, int *liwsp, 
        void (*matvec)(double*, double*), int *itrace, int *iflag, void** arg)
{
    please_dont_exit = true;
    if (!setjmp(jenv)) {
         dsphiv_(n, m, t, u, v, w, tol, anorm, wsp, lwsp, iwsp, liwsp, matvec, itrace, iflag, arg);
    }
    please_dont_exit = false;
}

void dgphiv_wrap(
        int *n, int*m, double *t, double *u, double *v, double *w, double *tol,
        double *anorm, double *wsp, int *lwsp, int *iwsp, int *liwsp, 
        void (*matvec)(double*, double*), int *itrace, int *iflag, void** arg)
{
    please_dont_exit = true;
    if (!setjmp(jenv)) {
         dgphiv_(n, m, t, u, v, w, tol, anorm, wsp, lwsp, iwsp, liwsp, matvec, itrace, iflag, arg);
    }
    please_dont_exit = false;
}

void zhphiv_wrap(
        int *n, int*m, double *t, double complex *u, double complex *v, double complex *w, double *tol,
        double *anorm, double complex *wsp, int *lwsp, int *iwsp, int *liwsp, 
        void (*matvec)(double complex*, double complex*), int *itrace, int *iflag, void** arg)
{
    please_dont_exit = true;
    if (!setjmp(jenv)) {
         zhphiv_(n, m, t, u, v, w, tol, anorm, wsp, lwsp, iwsp, liwsp, matvec, itrace, iflag, arg);
    }
    please_dont_exit = false;
}

void zgphiv_wrap(
        int *n, int*m, double *t, double complex *u, double complex *v, double complex *w, double *tol,
        double *anorm, double complex *wsp, int *lwsp, int *iwsp, int *liwsp, 
        void (*matvec)(double complex*, double complex*), int *itrace, int *iflag, void** arg)
{
    please_dont_exit = true;
    if (!setjmp(jenv)) {
         zgphiv_(n, m, t, u, v, w, tol, anorm, wsp, lwsp, iwsp, liwsp, matvec, itrace, iflag, arg);
    }
    please_dont_exit = false;
}



