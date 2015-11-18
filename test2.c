#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
int n = 2000, m = 2000; //nがx,mがyの配列の最大
FILE *fpIn1,*fpIn2,*fpOut;
double point[2000][2000];
int map1MinX=0,map1MinY=0;
int borderArray[2000][2000] //(境界なら1,そうでなければ0,点データがない場合は-1を格納する配列でグローバルにおく)

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

<<<<<<< HEAD
int main(void){
	int n = 7600, m = 37000;
	int i,j,k=0,ret,x,y;
	double tmpx=0,tmpy=0;
	double z=0;
	errorPoint errorPoints[10000];
	errorPoint ePoint;

	point = malloc(sizeof(double *)*n);
	base_point= malloc(sizeof(double *)*n*m);
	for (i = 0; i < n; i++) {
		point[i] = base_point + i*m;

	}
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

	while((ret = fscanf("%lf %lf %lf",&tmpx,&tmpy,&z))!=EOF){
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

=======
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

void errorRestore(void){
    int i,j,s,t,cnt1,cnt2,sum=0;
    double avg;
    for(j=0;j<n;j++){
        for(i=0;i<m;i++){
            if(point[i][j]<-1000){
                sum=0;
                cnt=0;
                if(point[i-1][j-1]!<-1000){/*エラー点で弾かれなかったやつは配列aに入れる*/
                    sum+=point[i-1][j-1];
                    cnt1++;
                }
                if(point[i-1][j]!<-1000){
                    sum+=point[i-1][j];
                    cnt1++;
                }
                if(point[i-1][j+1]!<-1000){
                    sum+=point[i-1][j+1];
                    cnt1++;
                }
                if(point[i][j-1]!<-1000){
                    sum+=point[i][j-1];
                    cnt1++;
                }
                if(point[i][j+1]!<-1000){
                    sum+=point[i][j+1];
                    cnt1++;
                }
                if(point[i+1][j-1]!<-1000){
                    sum+=point[i+1][j-1];
                    cnt1++;
                }
                if(point[i+1][j]!<-1000){
                    sum+=point[i+1][j];
                    cnt1++;
                }
                if(point[i+1][j+1]!<-1000){
                    sum+=point[i+1][j+1];
                    cnt1++;
                }
                //平均出したところまで
                avg=sum/cnt1;
                sum=0;
                cnt1=0;
                //配列aを使ってavgより大きいかどうかを決め、cnt1,cnt2に各々入れていく
                if(point[i-1][j-1]<avg) cnt1++;
                else cnt2++;
                if(point[i-1][j]<avg) cnt1++;
                else cnt2++;
                if(point[i-1][j+1]<avg) cnt1++;
                else cnt2++;
                if(point[i][j-1]<avg) cnt1++;
                else cnt2++;
                if(point[i][j+1]<avg) cnt1++;
                else cnt2++;
                if(point[i+1][j-1]<avg) cnt1++;
                else cnt2++;
                if(point[i+1][j]<avg) cnt1++;
                else cnt2++;
                if(point[i+1][j+1]<avg) cnt1++;
                else cnt2++;
            }
        }
    }
}
>>>>>>> b92c2056171151e1be22aa2edb363b452d9bc328

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
    initialize();
    draw();
    //errorDraw(errorPoints,k);
    
    fclose(fpIn1);
    fclose(fpIn2);
    fclose(fpOut);
    
	return 0;
}