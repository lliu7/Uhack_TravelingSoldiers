/*
============================================================================
Name        : test.c
Author      : Lin Liu
Version     :
Copyright   : Your copyright notice
Description : Hello World in C, Ansi-style
============================================================================
*/

/*
============================================================================
Name        : ESN_RFID.c
Author      : Girish Kamath
Date	 : 11/27/2013
Version     : v1.0
Copyright   : Your copyright notice
Description : To calculate the co-ordinates of the reference tags when the
        transmitted power and details are given
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NO_REF_TAGS 4	 // define the no of reference tags

/*
float Pref0[NO_REF_TAGS], Pt1, Gt1, Gr1, lambda1, d1[NO_REF_TAGS]={1,2,3,4,NO_REF_TAGS}, L1;	// Power read from reference tag by reader 1
float Pref1[NO_REF_TAGS], Pt1, Gt1, Gr1, lambda1, d1[NO_REF_TAGS]={1,2,3,4,NO_REF_TAGS}, L1;	// Power read from reference tag by reader 2
float Pref2[NO_REF_TAGS], Pt1, Gt1, Gr1, lambda1, d1[NO_REF_TAGS]={1,2,3,4,NO_REF_TAGS}, L1;	// Power read from reference tag by reader 3
float Pref3[NO_REF_TAGS], Pt1, Gt1, Gr1, lambda1, d1[NO_REF_TAGS]={1,2,3,4,NO_REF_TAGS}, L1;	// Power read from reference tag by reader 4
*/
/*
float Ptar1, Pt2, Gt2, Gr2, lambda2, d2[NO_REF_TAGS]={1,2,3,4,NO_REF_TAGS}, L2;	// Power read from target tag by reader 1
float Ptar2, Pt2, Gt2, Gr2, lambda2, d2[NO_REF_TAGS]={1,2,3,4,NO_REF_TAGS}, L2;	// Power read from target tag by reader 2
float Ptar3, Pt2, Gt2, Gr2, lambda2, d2[NO_REF_TAGS]={1,2,3,4,NO_REF_TAGS}, L2;	// Power read from target tag by reader 3
float Ptar4, Pt2, Gt2, Gr2, lambda2, d2[NO_REF_TAGS]={1,2,3,4,NO_REF_TAGS}, L2;	// Power read from target tag by reader 4

float Ej[NO_REF_TAGS] = {0,0,0,0};
float sum1=0,sum2=0;
float w[NO_REF_TAGS]= {0,0,0,0};
int x=0,y=0;
int x_ref[NO_REF_TAGS] = {0,1,2,3};
int y_ref[NO_REF_TAGS] = {0,1,2,3};

*/

int main(void) {
setvbuf(stdout, NULL, _IONBF, 0);
setvbuf(stderr, NULL, _IONBF, 0);
/*	printf("Enter the values for the reference tags input- Pt1,Gt1,Gr1,lambda1,L1\n");
scanf("%f %f %f %f %f",&Pt1, &Gt1, &Gr1, &lambda1, &L1);
printf("Enter the values for the object tags input- Pt2,Gt2,Gr2,lambda2,L2\n");
scanf("%f %f %f %f %f",&Pt2, &Gt2, &Gr2, &lambda2, &L2);
*/

//distance calculation

float L[4]={5.1, 4.2, 4.5, 5.5};
//float d0=2.83, d1=4.47, d2=4.47, d3=5.66;
int Pt=10000000;
int Gt1=1, Gr1=1;
//int lambda1=65;
float lambda1 = 0.15;
float Pref[4][4][4];  //ref[gp][ref_gp][reader]; Pt = (Pt * Gt1 * Gr1 * lambda1 * lambda1)/ ((4 * M_PI * 4 * M_PI) * pow(d,L));
float calc;
int gp_x[4][4] = {{1,3,1,3},{5,7,5,7},{1,3,1,3},{5,7,5,7}};
int gp_y[4][4] = {{1,1,3,3},{1,1,3,3},{5,5,7,7},{5,5,7,7}};
int rd_x[4] = {0,8,0,8};
int rd_y[4] = {0,0,8,8};
int gp=0, reader=0, ref_gp=0;
calc = (Pt * Gt1 * Gr1 * lambda1 * lambda1)/ (4 * M_PI * 4 * M_PI);

printf("Calc value: %f", calc);
printf("\n");


for(gp=0;gp<4;gp++)
{
for(reader=0;reader<4;reader++)
{
for(ref_gp=0;ref_gp<4;ref_gp++)
{
Pref[gp][ref_gp][reader] = calc/ pow( (sqrt(((gp_x[gp][ref_gp] - rd_x[reader]) *(gp_x[gp][ref_gp] - rd_x[reader])) + ((gp_y[gp][ref_gp] - rd_y[reader]) *(gp_y[gp][ref_gp] - rd_y[reader])))), L[gp]); // free space path loss model - power of reference tags
}
}
}



/*
// weight factors of each power based on Euclidian distance
for(j =0; j < NO_REF_TAGS; j++)
{
sum2 += (Ej[j] * Ej[j]);          //sum of all values of reference tags -manju
}

for(j =0; j < NO_REF_TAGS; j++)
{
w[j]= (1/(Ej[j] * Ej[j]))/(1/sum2);  //w is the weighting factor to the i-th neighboring reference tag.
}

// kNN method to find the coordinate (x,y) of unknown tag

for(k=0; k<NO_REF_TAGS; k++)
{
x += (w[k] * x_ref[k] );
y += (w[k] * y_ref[k] );
}

printf("The (x,y) coordinates of the unknown tag are \n");
printf("(%d,%d)\n",x,y);
*/
printf("Reference Tag\t\tReader0\t\tReader1\t\tReader2\t\tReader3\t\n");
for(gp=0;gp<4;gp++)
{
printf("Group %d\n",gp);
for(ref_gp=0;ref_gp<4;ref_gp++)
{
printf("%d\t\t\t",ref_gp);
for(reader=0;reader<4;reader++)
{
printf("%f\t", 10*log(Pref[gp][ref_gp][reader]*1000));
}
printf("\n");
}
printf("--------");
printf("\n");
}

//Target Power detection
int tg_x[]={1,2,5,7,7,1,2,2,5,7};	//x co-ordinates
int tg_y[]={2,1,1,1,2,6,6,7,6,7};	//corresponding y co-ordinates
int r; //counter
int k=0;	//initialized all targets to group 0
int rdr;	//target power reading from all readers
float Ptar[10][4];
int group_ind[10][4];
for(r=0;r<10;r++)
{
//select group

if((tg_x[r]>4) & (tg_y[r]>4))
{
k=3;
}
if( (tg_x[r]>0) & (tg_x[r]<4))
{
if(tg_y[r]>4)
k=2;
}
if((tg_x[r]>4) & (0<tg_y[r])&(tg_y[r]<4))
{
k=1;
}
for(rdr=0;rdr<4;rdr++)
{
Ptar[r][rdr] = calc/ pow( (sqrt(((tg_x[r] - rd_x[rdr]) * (tg_x[r] - rd_x[rdr])) + ((tg_y[r] - rd_y[rdr]) *(tg_y[r] - rd_y[rdr])))), L[k]);
group_ind[r][rdr] =k;
}
}

printf("Target Tag\tReader0\t\t\tReader1\t\t\tReader2\t\t\tReader3\t\n");
for(r=0;r<10;r++)
{
printf("%d\t\t",r);
for(rdr=0;rdr<4;rdr++)
{
printf("%f\t\t", 10*log(Ptar[r][rdr]*1000));
}
printf("\n");
}

return EXIT_SUCCESS;
}
