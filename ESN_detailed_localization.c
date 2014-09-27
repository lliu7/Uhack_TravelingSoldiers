/*
 ============================================================================
 Name        : ESN_RFID.c
 Author      : Girish Kamath
 Date		 : 11/27/2013
 Version     : v1.0
 Copyright   : Your copyright notice
 Description : To calculate the co-ordinates of the reference tags when the
  	  	  	  	transmitted power and details are given
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NO_REF_TAGS 5							// define the no of tags

float Pr1[NO_REF_TAGS], Pt1, Gt1, Gr1, lambda1, d1[NO_REF_TAGS]={1,2,3,4,NO_REF_TAGS}, L1;	// Power related to reference tags
float Pr2[NO_REF_TAGS], Pt2, Gt2, Gr2, lambda2, d2[NO_REF_TAGS]={1,2,3,4,NO_REF_TAGS}, L2;	// Power related to object tags
float Ej[NO_REF_TAGS] = {0,0,0,0,0};
float sum1=0,sum2=0;
float w[NO_REF_TAGS]= {0,0,0,0,0};
int x=0,y=0;
int x_ref[NO_REF_TAGS] = {0,1,2,3,4};
int y_ref[NO_REF_TAGS] = {0,1,2,3,4};

int main_detail(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	printf("Enter the values for the reference tags input- Pt1,Gt1,Gr1,lambda1,L1\n");
	scanf("%f %f %f %f %f",&Pt1, &Gt1, &Gr1, &lambda1, &L1);
	printf("Enter the values for the object tags input- Pt2,Gt2,Gr2,lambda2,L2\n");
	scanf("%f %f %f %f %f",&Pt2, &Gt2, &Gr2, &lambda2, &L2);

	int i,j,k;
	for (i = 0; i < NO_REF_TAGS; i++)
	{
		Pr1[i] = (Pt1 * Gt1 * Gr1 * lambda1 * lambda1)/ ((4 * M_PI * 4 * M_PI) * d1[i] * d1[i] * L1); // free space path loss model
		Pr2[i] = (Pt2 * Gt1 * Gr2 * lambda2 * lambda2)/ ((4 * M_PI * 4 * M_PI) * d2[i] * d2[i] * L2); // free space path loss model
		sum1 += ((Pr1[i]-Pr2[i])*(Pr1[i]-Pr2[i]));
		Ej[i] = sqrt(sum1); 							// Euclidian distance in signal strengths
	}


	// weight factors of each power based on Euclidian distance
	for(j =0; j < NO_REF_TAGS; j++)
	{
		sum2 += (Ej[j] * Ej[j]);
		w[j]= (1/(Ej[j] * Ej[j]))/(1/sum2);
	}

	// kNN method to find the coordinate (x,y) of unknown tag

	for(k=0; k<NO_REF_TAGS; k++)
	{
		x += (w[k] * x_ref[k] * y_ref[k]);
		y += (w[k] * x_ref[k] * y_ref[k]);
	}

	printf("The (x,y) coordinates of the unknown tag are \n");
	printf("(%d,%d)\n",x,y);

	return EXIT_SUCCESS;
	}
