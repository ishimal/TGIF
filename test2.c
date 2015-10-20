#include<stdio.h>
#include<stdlib.h>

FILE *fp1,*fp2;
double point[7600][37000];
double afterDeterminPoints[7600][37000];


typedef struct
{
	double x;
	double y;
}errorPoint;

void initialize(){
	fprintf(fp2,"#VRML V2.0 utf8\nNavigationInfo {\n\ttype [ \"EXAMINE\", \"ANY\" ]\n}\n\n");
}

void draw(){
	int i,j;
	fprintf(fp2, "Shape {\n\tgeometry PointSet{\n\t\tcoord Coordinate{\n\t\t\tpoint[");
	for(i=0;i<7600;i++){
		for(j=0;j<37000;j++){
			if(point[i][j]>0){
				fprintf(fp2, "%d %d %f", -1*i,-1*j,point[i][j]);
				fprintf(fp2, ",");
			}
		}
	}
	fprintf(fp2, "]\n\t\t}\n\t}\n}\n");
}

void errorDraw(errorPoint errorPoints[],int k){
	int i;
	for (i=0;i<k;i++)
	{
		fprintf(fp2, "Transform{\n\ttranslation %f %f %f\n\tchildren[Shape {geometry Sphere{radius 1}\nappearance Appearance{material Material{diffuseColor 1 0 0}}}]\n\t}\n",-1*errorPoints[i].x,-1*errorPoints[i].y,0.0);
	}
}

int main(void){
	int i,j,k=0,ret,x,y;
	double tmpx=0,tmpy=0;
	double z=0;
	errorPoint errorPoints[10000];
	errorPoint ePoint;

	for(i=0;i<7600;i++){
		for(j=0;j<37000;j++){
			point[i][j] = -1;
		}
	}

	if((fp1 = fopen("53394640_dsm_1m.dat","r")) == NULL){
		printf("file1 open error!!\n");
		exit(-1);
	}
	if((fp2 = fopen("test.wrl","w")) == NULL){
		printf("file2 open error!!\n");
		exit(-1);
	}

	while((ret = fscanf(fp1,"%lf %lf %lf",&tmpx,&tmpy,&z))!=EOF){
		x = tmpx * -1;
		y = tmpy * -1;
		point[x][y] = z;
		if (z==-9999.99)
		{
			ePoint.x = x;
			ePoint.y = y;
			errorPoints[k++] = ePoint;
		}
	}


	initialize();
	draw();
	errorDraw(errorPoints,k);

	fclose(fp1);
	fclose(fp2);
	return 0;
} //aaaa

//bbbbbbb