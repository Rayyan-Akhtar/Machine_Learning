#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define ROW 200

void gradientDescent(double *theta0, double *theta1, double alpha, double data[][2], int row);
void calculateError(double *theta0, double *theta1, double alpha, double data[][2], int row);
double data[ROW][2];
char input[8];

int main(int argc, char *argv[])
{
    FILE *fp;
    int row =0;
    char ch; int i=0;
    double f;
    char* filename = "inputdata.txt";
    if((fp=fopen(filename,"r"))==NULL)
    {
        printf("File not opened\n");
        return -1;
    }

   while((ch=fgetc(fp))!=EOF)
    {
        if(ch=='\t')
        {
            input[i++]='\0';
            f = atof(input);
            data[row][0] = f;
            memset((char*)input,0,sizeof(input));
            i=0;
        }
        if(ch=='\n')
        {
            input[i++]='\0';
            f = atof(input);
            data[row++][1] = f;
            memset((char*)input,0,sizeof(input));
            i=0;
        }
        input[i++]=ch;
    }
    double theta0 = 0.5;
    double theta1 = 1;
    double alpha = 0.0001;
    gradientDescent(&theta0, &theta1, alpha, data, row);
}

void gradientDescent(double *theta0, double *theta1, double alpha, double data[][2], int row)
{
    int iterations=0;
    double newtheta0, newtheta1;
    newtheta0 = *theta0;
    newtheta1 = *theta1;
    calculateError(theta0,theta1,alpha,data,row);

    while((fabs(newtheta0-*theta0)>0.001)&&(fabs(newtheta1-*theta1)>0.001))
    {
        newtheta0 = *theta0;
        newtheta1 = *theta1;
        calculateError(theta0, theta1, alpha, data, row);
        iterations = iterations + 1;
    }

    printf("Got the result\n");
    printf("Iterations: %d\n",iterations);
    printf("Theta0, Theta1: %f, %f",*theta0, *theta1);
}

void calculateError(double *theta0, double *theta1, double alpha, double data[][2], int row)
{
    double constant;
    constant = alpha/(row+1);
    int sum = 0;
    for (int i=0; i<=row; i++)
    {
        sum = sum + (*theta0 + (((*theta1)*data[i][0])- data[i][1]));
    }
    *theta0 = *theta0 - (constant*sum);

    sum = 0;
    for (int i=0; i<=row; i++)
    {
        sum = sum + (*theta0 + ((((*theta1)*data[i][0])- data[i][1])*data[i][1]));
    }
    *theta1 = *theta1 - (constant*sum);
}

