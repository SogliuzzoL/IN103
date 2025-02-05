unsigned int sinCosDimension();
double *sinCos(double t, double *x);
double *sinCosInit();
double *oneStep(double *(*f)(double, double *), unsigned int n, double tInit, double *init, double h, double **error);
double norm2(double *x, unsigned int n);
void printVector(double *x, unsigned int n);
