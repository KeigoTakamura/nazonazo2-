#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<float.h>
#include<math.h>
#define random_cont_max 12 //rndで12回繰り返す
#define Calculation_count 100000 //100000回実行するマクロ



/*
・関数解説
float nor_rand() rnd算出用関数
int dblcmpt  小数の精密比較用関数、苦労して調べて実装した割に普通の書き方でよかった感があって微妙


 */


float nor_rand(){
	float nrm=0.0;
	for(int random_cont=0;random_cont< random_cont_max;random_cont++){ //nor_rand()と同じ
		   nrm+= (float)rand()/(float)RAND_MAX;//0から1までの浮動小数点乱数を12回足す
		}

    return nrm-6.0;//nrmから6引く
}


int dblcmpt(double x, double y, double tolerance) {
   return (x > y + tolerance) ? 1 : (y > x + tolerance) ? -1 : 0;
}




int main(){

 srand((int)time(NULL));
 float *rnd,*nnd,*ls_hd;

rnd = (float*)malloc(Calculation_count*sizeof(float)*2);//メモリ空間の動的配列宣言　rndはなんか動かすと原因不明の領域エラーがおこるからひとまずメモリ空間二倍取っておいた
nnd = (float*)malloc(Calculation_count*sizeof(float));
ls_hd = (float*)malloc(Calculation_count*sizeof(float));

 float nnd_sum=0;//nndの平均値算出用
 float max_nnd,min_nnd;//nndの最大値最小値
 float max_nrd,min_nrd;
 float rnd_sum;// rndの平均値を求める。

for (size_t i = 0; i < Calculation_count ; i++){//１０万回繰り返す
	rnd[i] = nor_rand();
	nnd[i] = (float)rand()/(float)(RAND_MAX);//0-1の乱数
	ls_hd[i] = 256 * nor_rand() +1024;
	nnd_sum+=nnd[i];//nndの合計値算出　平均値を取るのに使える。
	rnd_sum+=rnd[i];
//	printf("%f \n",nnd[i]);
}



float v=0;
for (int i = 0; i < (Calculation_count-1); i++)//nndをソートする ソートした後nnd[n/2]すると(nは配列サイズ)中央値が求まる
{	
	for (int k = Calculation_count-1; k >= i; k--)
	{
			if(fabsf( fmaxf(nnd[k],nnd[k+1])-nnd[k] ) > FLT_EPSILON  ){
				v= nnd[k];
				nnd[k]=nnd[k+1];
				nnd[k+1]=v;		
			}
	}

}

v=0;

for (int i = 0; i < (Calculation_count); i++)//rndをソートする ソートした後rnd[n/2]すると(nは配列サイズ)中央値が求まる
{	
	for (int k = Calculation_count-1; k >= i; k--)
	{
			if(fabsf( fmaxf(rnd[k],rnd[k+1])-rnd[k] ) > FLT_EPSILON  ){
				v= rnd[k];
				rnd[k]=rnd[k+1];
				rnd[k+1]=v;		
			}
	}

}









printf("rnd_average %f\n",rnd_sum/Calculation_count);//rnd平均値
printf("rnd_min %f \n",rnd[0]);  //rnd最小値
printf("rnd_max %f \n",rnd[Calculation_count]); //rnd最大値
printf("rnd_mid%f \n\n",rnd[Calculation_count/2]);  //rnd中央値




printf("nnd_average %f\n",nnd_sum/Calculation_count);//nndの平均値
printf("nnd_min %f \n",nnd[0]);//nndの最小値
printf("nnd_max %f \n",nnd[Calculation_count-1]);//nndの最大値
printf("nnd_mid %f \n",nnd[Calculation_count/2]);//nndの中央値



free(rnd);//メモリ解放
free(nnd);//メモリ解放
free(ls_hd);//解放
}


//実行に二分ぐらいかかる
