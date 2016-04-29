#include <stdio.h>
#include <stdlib.h>
#include <jni.h>
#include <math.h>
#include <omp.h>
#include "JNIHeaderForLabTwo.h"


double  MonteCarloRuleParallel(double,double,int);
double  MonteCarloRuleSequential(double,double,int);

double  TrapezoidalRuleParallel(double,double,int);
double  TrapezoidalRuleSequential(double,double,int);

double  f(double,int);
double  t_start,t_end;
int     n = 500000;
JNIEXPORT jdouble JNICALL Java_mainPackage_Main_nativeDefiniteParallelIntegralCalculation(JNIEnv *env, jobject obj, jint a, jint b,jint n)
{
    omp_set_num_threads(4);

    MonteCarloRuleParallel(a,b,n);
   // TrapezoidalRuleParallel(a,b,n);
}

JNIEXPORT jdouble JNICALL Java_mainPackage_Main_nativeDefiniteSequentialIntegralCalculation(JNIEnv *env, jobject obj, jint a, jint b,jint n)
{
    MonteCarloRuleSequential(a,b,n);
  //  TrapezoidalRuleSequential(a,b,n);
}

double MonteCarloRuleParallel(double a,double b,int st)
{
    int     i,
            count=0;
    double  x,
            s=0,
            Integral;
    
    
    t_start = omp_get_wtime();  
#pragma omp parallel for reduction(+: s) shared(n, a, b, st)  private(x, i)
    for (i=0; i<n; i++)
    {
        x=a+(b-a)*rand()/RAND_MAX;
        s += f(x,st);
    }
    Integral=((b-a)*s)/n;
    
    t_end = omp_get_wtime(); 
    printf("\n res =%f\n",Integral);
    return t_end-t_start; 
}

double  MonteCarloRuleSequential(double a,double b,int st)
{
     int    i,
            count=0;
    double  x,
            s=0,
            Integral;
    t_start = omp_get_wtime();  
    for (i=0; i<n; i++)
    {
        x=a+(b-a)*rand()/RAND_MAX;
        s += f(x,st);
    }
    Integral=((b-a)*s)/n;
    
    t_end = omp_get_wtime(); 
    printf("\n res =%f\n",Integral);
    return t_end-t_start; 
}

double TrapezoidalRuleParallel(double a,double b,int st)
{
    double  sum = 0,
            step;
    int     i;
    step = (b-a)/(1.0*n);
    
    t_start = omp_get_wtime(); 
    
#pragma omp parallel for reduction(+: sum) shared(n, a, b, st, step)  private(i)
 
    for ( i = 0;i<n;i++ )
    {
        sum += f((a+i*step),st);
    }
    sum += (f(a,st) + f(b,st))/2;
    sum *= step; 
    t_end = omp_get_wtime();   
    printf("\n res =%f\n",sum);

    return t_end-t_start;
}

double TrapezoidalRuleSequential(double a,double b,int st)
{
    double  sum = 0,
            step;
    int     i;
    step = (b-a)/(1.0*n);
    
    t_start = omp_get_wtime(); 
    for ( i = 0;i<n;i++ )
    {
        sum += f((a+i*step),st);
    }
    sum += (f(a,st) + f(b,st))/2;
    sum *= step; 
    t_end = omp_get_wtime();   
    printf("\n res =%f\n",sum);

    return t_end-t_start;
}



double f(double x,int st)
{
//  степенева функція
    return pow(x,st); 
}

