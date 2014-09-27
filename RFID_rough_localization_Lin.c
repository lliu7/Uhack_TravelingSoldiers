/*
 ============================================================================
 Name        : RFID_rough_localization.c
 Author      : Lin Liu
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#include <fcntl.h>

#define num_gp 4 /*number of groups*/
#define NO_REF_TAGS 4 /*define the no of tags in each group*/
#define num_reader 4 /*number of readers*/
#define num_obj 1 /*number of objects/targets*/

int main_rough(void) {
	int i,j,k,n;
	int max_reader, gp_number;
	//float coef[num_gp]; /*alpha coefficient in different groups, range [4-6]*/
	float p_object[num_obj][num_reader]; /*the received signal from the object to four readers*/
	float p_ref[num_gp][NO_REF_TAGS][num_reader];
    float temp, temp1, sum_temp, max_temp;
	FILE *fp_object, *fp_ref;

	//srand ( time(NULL) );/* initialize random seed: */
	//for (i = 0; i < num_gp; i ++)
	//{
	//	coef[i] = (rand()%21 + 40)/10.0; /*generate a random number from 4 to 6*/
		//printf("%f\n", coef[i]);
	//}

	//coef[0] = 4.5;
	//coef[1] = 5.5;
	//coef[2] = 5.1;
	//coef[3] = 4.8;

	/*read signal from files*/
	fp_object = fopen("object_1.txt","r");
	if(fp_object == NULL)
		printf("Can not open file");
	else
	{
		for (n = 0; n < num_obj; n ++)
		{
			for (i = 0; i < num_reader; i ++)
				{
					fscanf(fp_object, "%f\n", &p_object[n][i]);
					//printf("%f\n", p_object[i]);
				}
		}
	}

	fclose(fp_object);
	fp_ref = fopen("ref.txt", "r");
	for (i = 0; i < num_gp; i++)
	{
		for (j = 0; j < NO_REF_TAGS; j++)
		{
			for (k = 0; k < num_reader; k++)
			{
				fscanf(fp_ref, "%f", &p_ref[i][j][k]);
				//printf("%f ", p_ref[i][j][k]);
			}
			//printf("\n");
		}
		//printf("\n");
	}
	fclose(fp_ref);

	for (n = 0; n < num_obj; n ++)
	{
		/*Choose the reader which is closest to the object if the object is far closer to one reader */
			sum_temp = 0.0;
			max_temp = 0.0;
			max_reader = -1;
			gp_number = -1;
			for (i = 0; i < num_reader; i ++)
			{
				if (p_object[n][i] > max_temp)
				{
					max_temp = p_object[n][i];
					max_reader = i;
				}
				sum_temp += p_object[n][i];
			}
			temp = 100000000000.0;
			if (max_temp / sum_temp > 0.4)
			{
				for (i = 0; i < num_gp; i++)
				{
					temp1 = 0.0;
					for (j = 0; j < NO_REF_TAGS; j++)
					{
						temp1 += (p_ref[i][j][max_reader] - p_object[n][max_reader]) * (p_ref[i][j][max_reader] - p_object[n][max_reader]);
						if (temp1 < temp)
						{
							temp = temp1;
							gp_number = i;
						}
					}
				}
			}
			else /*No reader is far closer to object, therefore all readers' information are used*/
			{
				for (i = 0; i < num_gp; i++)
				{
					temp1 = 0.0;
					for (j = 0; j < NO_REF_TAGS; j++)
					{
						for (k = 0; k < num_reader; k++)
						{
							temp1 += (p_ref[i][j][max_reader] - p_object[n][max_reader]) * (p_ref[i][j][max_reader] - p_object[n][max_reader]);
							if (temp1 < temp)
							{
								temp = temp1;
								gp_number = i;
							}
						}
					}
				}
			}
		    printf("Object %d is in Group %d\n", n+1, gp_number);

	}

	return gp_number;
}
