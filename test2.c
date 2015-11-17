#include<stdio.h>
#include<stdlib.h>
int n = 2000, m = 2000;
FILE *fpIn1,*fpIn2,*fpOut;
double point[2000][2000];
int map1MinX=0,map1MinY=0;
//double afterDeterminPoints[7600][37000];

typedef struct
{
	double x;
	double y;
}errorPoint;


void initialize(){
	fprintf(fpOut,"#VRML V2.0 utf8\nNavigationInfo {\n\ttype [ \"EXAMINE\", \"ANY\" ]\n}\n\n");
}

void draw(){
	int i,j;
	fprintf(fpOut, "Shape {\n\tgeometry PointSet{\n\t\tcoord Coordinate{\n\t\t\tpoint[");
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			if(point[i][j]>0){
				fprintf(fpOut, "%d %d %f",  (i+map1MinX),(j+map1MinY),point[i][j]);
				fprintf(fpOut, ",");
			}
		}
	}
	fprintf(fpOut, "]\n\t\t}\n\t}\n}\n");
}

void errorDraw(errorPoint errorPoints[],int k){
	int i;
	for (i=0;i<k;i++)
	{
		fprintf(fpOut, "Transform{\n\ttranslation %f %f %f\n\tchildren[Shape {geometry Sphere{radius 1}\nappearance Appearance{material Material{diffuseColor 1 0 0}}}]\n\t}\n",-1*errorPoints[i].x,-1*errorPoints[i].y,0.0);
	}
}

void inputPoints(void){
    int ret,x,y,i,j;
    double tmpx=0,tmpy=0,z=0;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            point[i][j] = -100;
        }
    }
    printf("done initialize\n");
    while((ret = fscanf(fpIn1,"%lf %lf %lf",&tmpx,&tmpy,&z)) != EOF){
        if(tmpx < map1MinX) map1MinX=tmpx;
        if(tmpy < map1MinY) map1MinY=tmpy;
    }
    while((ret = fscanf(fpIn2,"%lf %lf %lf",&tmpx,&tmpy,&z))!=EOF){
        x = tmpx - map1MinX;
        y = tmpy - map1MinY;
        point[x][y] = z;
    }
}



int main(void){
    if((fpIn1 = fopen("map1.dat","r")) == NULL){
        printf("fpIn1 open error!!\n");
        exit(-1);
    }
    if((fpIn2 = fopen("map1.dat","r")) == NULL){
        printf("fpIn2 open error!!\n");
        exit(-1);
    }
    printf("done open\n");
    if((fpOut = fopen("test.wrl","w")) == NULL){
        printf("fpOut open error!!\n");
        exit(-1);
    }
    
    inputPoints();
    printf("");
    initialize();
    draw();
    //errorDraw(errorPoints,k);
    
    fclose(fpIn1);
    fclose(fpIn2);
    fclose(fpOut);
    
	return 0;
}