#ifndef KMATH_H
#define KMATH_H

#include<stdio.h>
#include<stdlib.h>
#define eps __DBL_EPSILON__
#define pi 3.14159265359
typedef double (*Fun) ();

double power(double x, double y);

double ab (double x)
{
	if (x>=0) return x;
	return -x;
}


double mod (double x, double y)
{
	double r=x/y;
	int z=(int) r;
	r=x-z*y;
	return r;
}

double fix (double x, int n)
{
	double y=ab(x),z,t,s;
	int i,r;
	if (x<0) t=-1;
	else 	 t=1;

	for (i=0; i<n; i++)
		y*=10;
	r=(int) y;
	z=ab(y-r);
	y=r;
	for (i=0; i<n; i++)
		t=t*0.1;
	

	if (z>=0.5-0.1*t)
		return (y+1)*t;
	return y*t;
}


double fact (int n)
{
	int i;
	double r=1;
	for (i=2; i<n+1; i++)
		r*=i;
	return r;
}


int gcd (int a, int b)
{
	int r;
	if (b>a)
	{
		r=a;
		a=b;
		b=r;
	}

	r=a%b;
	while (r)
	{
		a=b;
		b=r;
		r=a%b;
	}
	return b;
}


//From here on the header mostly consists of approximated functions
double ex (double x)
{
	double i=1,v=1,s=1,r=x,y=1;
	while (v>eps)
	{
		v=r/y;
		s+=v;
		i++;
		y*=i;
		r*=x;
	}
	return s;
}



double ln (double x)
{
	if (x<eps)
	{
		puts("The argument should be +ve");
		return 1/0.0;
	}

	double i=3,s=0,z,y,t,r,n=0,m=0;
	double LN2=0.693147180559945,LN10=2.302585092994046;
	while (x>=10.0)
	{
		x=x/10.0;
		n++;
	}

	while (x>=2)
	{
		x=x/2.0;
		m++;
	}

	while (x<=0.2)
	{
		x=x*2.0;
		m--;
	}

	z=(x-1)/(x+1);
	y=z;
	t=z*z*z;
	r=ab(y);
	while (r>eps)
	{
		s+=y;
		y=t/i;
		r=ab(y);
		i+=2;
		t=t*z*z;
	}

	return 2*s+m*LN2+n*LN10;
}


double power (double x, double y)
{
	double z=1,v=1;
	int i,r;
	r=(int) y;
	if (y-r<eps)
	{
		v=ab(y);
		//case of integer power
		for (i=0; i<v ; i++)
			z*=x;
	}

	else
	{
		//case of decimal power
		if (x<0)
		{
			puts("Error");
			exit(1);
		}
		else
		{
			while (v>eps)
			{
				v=z;
				z*= 1+y*ln(x)-ln(z);
				v=ab(z-v);
			}
		}
	}

	if (y<0) return 1.0/z;
	return z;
}


double sq (double t)
{
	if (t<0)
	{ 
		printf("The parameter can't be negative\n");
		return 0;
	}

	double v,r,er;
	v=t;r=t/2.0;
	er=1;
	while (er>eps)
	{
		v=r;
		r = (r+t/r)/2;
		er=ab(r-v);
	}
	return r;
}


double sine (double x)
{
	double s=0,v=1;
	int i=1,r=1;

	while (v>eps)
	{
		v=s;
		s+=r*power(x,i)/fact(i);
		r=-r; i+=2;
		v=ab(s-v);
	}

	if (s<eps && s>-eps) return 0;
	return s;
}


double cosine (double x)
{
	double s=1,v=1;
	int i=2,r=-1;
	while (v>eps)
	{
		v=s;
		s+=r*power(x,i)/fact(i);
		v=ab(s-v);
		r=-r;
		i+=2;
	}
	if (s<eps && s>-eps) return 0;
	return s;
}


double arccos (double x)
{
	if (x>1.0 || x<-1.0)
	{
		puts("The input is out of the [-1, 1] domain");
		return 0;
	}

	double y=0.5,z=1;
	while (z>eps || z<-eps)
	{
		z=(cosine(y)-x)/(sine(y));
		y+=z;
	}
	if (y<eps && y>-eps) return 0;
	return y;
}


double arcsin (double x)
{
	if (x>1.0 || x<-1.0)
	{
		puts("The input is out of the [-1, 1] domain");
		return 0;
	}
	double y=x,z=1;
	while (z>eps || z<-eps)
	{
		z=(x-sine(y))/cosine(y);
		y+=z;
	}
	if (y<eps && y>-eps) return 0;
	return y;
}

#endif 
