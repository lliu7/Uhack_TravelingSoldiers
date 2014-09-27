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

#define TYPE_GRID  1
#define TYPE_TOXA  0
#define TYPE 0

#define num_gp 4 /*number of groups*/
#define NO_REF_TAGS 4 /*define the no of tags in each group*/
#define num_reader 4 /*number of readers*/
#define num_obj 10 /*number of objects/targets*/
#define num_gp_toxa 3 /*number of groups*/
#define num_obj_toxa 7 /*number of objects/targets*/

int main_rough1(void) {
	int i, j, k, n;
	int max_reader, gp_number;
	float p_object[num_obj][num_reader]; /*the received signal from the object to four readers*/
	float p_ref[num_gp][NO_REF_TAGS][num_reader];
	float temp, temp1, sum_temp, max_temp;
	FILE *fp_object, *fp_ref;


	/*read signal from files*/
	if (TYPE == TYPE_GRID) {
		fp_object = fopen("object_10.txt", "r");
		if (fp_object == NULL )
			printf("Can not open file");
		else {
			for (n = 0; n < num_obj; n++) {
				for (i = 0; i < num_reader; i++) {
					fscanf(fp_object, "%f\n", &p_object[n][i]);
				}
			}
		}

		fclose(fp_object);
		fp_ref = fopen("ref_1.txt", "r");
		for (i = 0; i < num_gp; i++) {
			for (j = 0; j < NO_REF_TAGS; j++) {
				for (k = 0; k < num_reader; k++) {
					fscanf(fp_ref, "%f", &p_ref[i][j][k]);
				}
			}
		}
		fclose(fp_ref);

		for (n = 0; n < num_obj; n++) {
			/*Choose the reader which is closest to the object if the object is far closer to one reader */
			sum_temp = 0.0;
			max_temp = 0.0;
			max_reader = -1;
			gp_number = -1;
			for (i = 0; i < num_reader; i++) {
				if (p_object[n][i] > max_temp) {
					max_temp = p_object[n][i];
					max_reader = i;
				}
				sum_temp += p_object[n][i];
			}
			temp = 100000000000.0;
			if (max_temp / sum_temp > 0.4) {
				for (i = 0; i < num_gp; i++) {
					temp1 = 0.0;
					for (j = 0; j < NO_REF_TAGS; j++) {
						temp1 += (p_ref[i][j][max_reader]
								- p_object[n][max_reader])
								* (p_ref[i][j][max_reader]
										- p_object[n][max_reader]);
						if (temp1 < temp) {
							temp = temp1;
							gp_number = i;
						}
					}
				}
			} else /*No reader is far closer to object, therefore all readers' information are used*/
			{
				for (i = 0; i < num_gp; i++) {
					temp1 = 0.0;
					for (j = 0; j < NO_REF_TAGS; j++) {
						for (k = 0; k < num_reader; k++) {
							temp1 += (p_ref[i][j][max_reader]
									- p_object[n][max_reader])
									* (p_ref[i][j][max_reader]
											- p_object[n][max_reader]);
							if (temp1 < temp) {
								temp = temp1;
								gp_number = i;
							}
						}
					}
				}
			}
			printf("Object %d is in Group %d\n", n + 1, gp_number);

		}
	} else if (TYPE == TYPE_TOXA) {
		fp_object = fopen("object_7.txt", "r");
		if (fp_object == NULL )
			printf("Can not open file");
		else {
			for (n = 0; n < num_obj; n++) {
				for (i = 0; i < num_reader; i++) {
					fscanf(fp_object, "%f\n", &p_object[n][i]);
				}
			}
		}

		fclose(fp_object);
		fp_ref = fopen("ref_2.txt", "r");
		for (i = 0; i < num_gp_toxa; i++) {
			for (j = 0; j < NO_REF_TAGS; j++) {
				for (k = 0; k < num_reader; k++) {
					fscanf(fp_ref, "%f", &p_ref[i][j][k]);
				}
			}
		}
		fclose(fp_ref);

		for (n = 0; n < num_obj_toxa; n++) {
			/*Choose the reader which is closest to the object if the object is far closer to one reader */
			sum_temp = 0.0;
			max_temp = 0.0;
			max_reader = -1;
			gp_number = -1;
			for (i = 0; i < num_reader; i++) {
				if (p_object[n][i] > max_temp) {
					max_temp = p_object[n][i];
					max_reader = i;
				}
				sum_temp += p_object[n][i];
			}
			temp = 100000000000.0;
			if (max_temp / sum_temp > 0.4) {
				for (i = 0; i < num_gp; i++) {
					temp1 = 0.0;
					for (j = 0; j < NO_REF_TAGS; j++) {
						temp1 += (p_ref[i][j][max_reader]
								- p_object[n][max_reader])
								* (p_ref[i][j][max_reader]
										- p_object[n][max_reader]);
						if (temp1 < temp) {
							temp = temp1;
							gp_number = i;
						}
					}
				}
			} else /*No reader is far closer to object, therefore all readers' information are used*/
			{
				for (i = 0; i < num_gp_toxa; i++) {
					temp1 = 0.0;
					for (j = 0; j < NO_REF_TAGS; j++) {
						for (k = 0; k < num_reader; k++) {
							temp1 += (p_ref[i][j][max_reader]
									- p_object[n][max_reader])
									* (p_ref[i][j][max_reader]
											- p_object[n][max_reader]);
							if (temp1 < temp) {
								temp = temp1;
								gp_number = i;
							}
						}
					}
				}
			}
			switch (gp_number)
			{
			case 0:
						printf("Object %d is in Group Apparel\n", n + 1);
						break;
			case 1:
						printf("Object %d is in Group Vegetable\n", n + 1);
						break;
			case 2:
						printf("Object %d is in Group Dairy\n", n + 1);
						break;
			}

		}
	}

	return gp_number;
}
