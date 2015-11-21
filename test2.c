#include<stdio.h>
#include<stdlib.h>
int n = 2000, m = 2000; //nがx,mがyの配列の最大
FILE *fpIn1,*fpIn2,*fpOut;
double point[2000][2000];
int map1MinX=0,map1MinY=0;
int borderArray[2000][2000]; //(境界なら1,そうでなければ0,点データがない場合は-1を格納する配列でグローバルにおく)

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

void judgeBorder(){
    int alpha = 10;
    int i,j,k,x,y,res;
    double centerZ = 0.0,diff = 0.0,abusDiff = 0.0;
    
    for(j=0;j<m;j++){
        for(i=0;i<n;i++){
            borderArray[i][j] = -1;
        }
    }
    
    for (j=0; j<m; j++) {
        for (i=0; i<n; i++) {
            if (point[i][j] <= -100) {
                continue;
            }
            res = 0;
            centerZ = point[i][j];
            x=i;
            y=j+1;
            for(k=0;k<4;k++){
                if(x<0 || y<0){
                    continue;
                }else if(point[x][y] <= -100){
                    continue;
                }
                diff = point[x][y] - centerZ;
                abusDiff = (diff >= 0) ? diff:(-1*diff);
                if (alpha < abusDiff) {
                    res = 1;
                }
                if (k==0 || k == 2) {
                    x--;
                    y--;
                }else if(k==1){
                    x += 2;
                }
            }
            borderArray[i][j] = res;
        }
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
    initialize();
    draw();
    judgeBorder();
    
    fclose(fpIn1);
    fclose(fpIn2);
    fclose(fpOut);
    
	return 0;
}