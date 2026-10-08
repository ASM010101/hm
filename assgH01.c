#include <stdio.h>
#include <math.h>
#include <time.h>

long hnonly(int n){
    long hn0=1;
    long ln0=0;
    long hn1,ln1;
    int i;
    for(i=1;i<=n;i++){
        hn1=2*hn0+ln0;
        ln1=hn0+ln0;
        hn0=hn1;
        ln0=ln1;
    }
    return hn0;
}

long lnonly(int n){
    long hn0=1;
    long ln0=0;
    long hn1,ln1;
    int i;
    for(i=1;i<=n;i++){
        hn1=2*hn0+ln0;
        ln1=hn0+ln0;
        hn0=hn1;
        ln0=ln1;
    }
    return ln0;
}

void hnandln(int n,long *hnvalue,long *lnvalue){
    long hn0=1;
    long ln0=0;
    long hn1,ln1;
    int i;
    for(i=1;i<=n;i++){
        hn1=2*hn0+ln0;
        ln1=hn0+ln0;
        hn0=hn1;
        ln0=ln1;
    }
    *hnvalue=hn0;
    *lnvalue=ln0;
}

void hnlnclosed(int n,double *hnvalue,double *lnvalue){
    double root5=sqrt(5.0);
    double p1=(5+root5)/10.0;
    double p2=pow((3-root5)/2.0,n+1);
    double p3=(5-root5)/10.0;
    double p4=pow((3+root5)/2.0,n+1);
    double h=p1*p2+p3*p4;

    double p5=(-5-3*root5)/10.0;
    double p6=(3*root5-5)/10.0;
    double l=p5*p2+p6*p4;

    *hnvalue=h;
    *lnvalue=l;
}

typedef struct{
    long a,b,c,d;
}Mat;

Mat multiplyMat(Mat x,Mat y){
    Mat res;
    res.a=x.a*y.a+x.b*y.c;
    res.b=x.a*y.b+x.b*y.d;
    res.c=x.c*y.a+x.d*y.c;
    res.d=x.c*y.b+x.d*y.d;
    return res;
}

Mat powMat(Mat base,int p){
    Mat result;
    result.a=1;result.b=0;result.c=0;result.d=1;
    while(p>0){
        if(p%2==1){
            result=multiplyMat(result,base);
        }
        base=multiplyMat(base,base);
        p=p/2;
    }
    return result;
}

void hnlnlog(int n,long *hnvalue,long *lnvalue){
    Mat m;
    m.a=2;m.b=1;m.c=1;m.d=1;
    Mat res=powMat(m,n);
    *hnvalue=res.a;
    *lnvalue=res.c;
}

int main(){
    int n;
    printf("enter value of n: ");
    scanf("%d",&n);

    struct timespec start,end;
    double timetaken;

    timespec_get(&start,TIME_UTC);
    long hnval1=hnonly(n);
    timespec_get(&end,TIME_UTC);
    timetaken=(end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1000000000.0;
    printf("Hn value using recurrence function hnonly = %ld\n",hnval1);
    printf("time taken = %f seconds\n\n",timetaken);

    timespec_get(&start,TIME_UTC);
    long lnval1=lnonly(n);
    timespec_get(&end,TIME_UTC);
    timetaken=(end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1000000000.0;
    printf("Ln value using recurrence function lnonly = %ld\n",lnval1);
    printf("time taken = %f seconds\n\n",timetaken);

    long hnval2,lnval2;
    timespec_get(&start,TIME_UTC);
    hnandln(n,&hnval2,&lnval2);
    timespec_get(&end,TIME_UTC);
    timetaken=(end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1000000000.0;
    printf("Hn = %ld  Ln = %ld using function hnandln\n",hnval2,lnval2);
    printf("time taken = %f seconds\n\n",timetaken);

    double hnval3,lnval3;
    timespec_get(&start,TIME_UTC);
    hnlnclosed(n,&hnval3,&lnval3);
    timespec_get(&end,TIME_UTC);
    timetaken=(end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1000000000.0;
    printf("Hn = %f  Ln = %f using closed form function hnlnclosed\n",hnval3,lnval3);
    printf("time taken = %f seconds\n\n",timetaken);

    long hnval4,lnval4;
    timespec_get(&start,TIME_UTC);
    hnlnlog(n,&hnval4,&lnval4);
    timespec_get(&end,TIME_UTC);
    timetaken=(end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1000000000.0;
    printf("Hn = %ld  Ln = %ld using log n function hnlnlog\n",hnval4,lnval4);
    printf("time taken = %f seconds\n\n",timetaken);

    return 0;
}