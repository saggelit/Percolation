#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 1001 //megethos plegmatos
#define cp 18 //plhthos pithanothtwn
#define run 1000 //plhthos prosomoiwsewn

int main()
{
  int i,j,l,n,k,temp1,temp2,pnn,r,countc;
  double num;

  srand(4366);

  FILE *dataIav;
  dataIav=fopen("dataIav1000.txt","w");
  FILE *dataIavtonos;
  dataIavtonos=fopen("dataIavtonos1000.txt","w");
  FILE *datapmax;
  datapmax=fopen("datapmax1000.txt","w");

  double p[cp]={0.1,0.2,0.3,0.4,0.5,0.55,0.56,0.57,0.58,0.59,0.6,0.61,0.62,0.63,0.64,0.65,0.7,0.8};
  int (*plegma)[N]=malloc(sizeof(int[N][N])); 
  int *size=malloc((N*N)*sizeof(int));          //kathorismos pinaka megethous
  int *label=malloc((N*N)*sizeof(int));         //kathorismos pinaka label
  double *Iav=malloc((cp)*sizeof(double));      //kathorismos pinaka Iav
  double *Iavtonos=malloc((cp)*sizeof(double)); //kathorismos pinaka Iav'
  double *pmax=malloc((cp)*sizeof(double));     //kathorismos pinaka pmax

  for (n=0;n<cp;n++) //gia tis 18 pithanothtes
    {
      for (i=0;i<cp;i++) Iav[i]=0.0;
      for (i=0;i<cp;i++) Iavtonos[i]=0.0;
      for (i=0;i<cp;i++) pmax[i]=0.0;
      
      for (r=0;r<run;r++) //gia tis run=1000 prosomoiwseis
	{
	  pnn=0;
	  for (i=0;i<N*N;i++) size[i]=0;
	  for (i=0;i<N*N;i++) label[i]=0;
	  
	  for (i=0;i<N;i++)
	    {
	      for (j=0;j<N;j++)
		{
		  num=1.0*rand()/RAND_MAX;
		  if (num<=p[n]) plegma[i][j]=1; //pithanothta p na einai monada to swmatidio tou plegmatos
		  else plegma[i][j]=0;
		  plegma[i][0]=0; //mhdenizw 1h grammh kai sthlh gia na mporw na tsekarw panw kai aristera
		  plegma[0][j]=0;
		  if (plegma[i][j]==1) pnn++; //metraw to plhthos twn monadwn sto plegma
		}
	    }
	  //printf("pnn[%d]=%d\n",n,pnn);
	  
	  k=1; //arxikopoihsh index
	  for (j=1;j<N;j++)
	    {
	      for (i=1;i<N;i++)
		{
		  if (plegma[i][j]!=0)
		    {
		      if (plegma[i][j-1]==0) //einai to index aristera 0
			{
			  if (plegma[i-1][j]==0) //einai to index panw 0
			    {
			      //k=k+1;
			      label[k]=k;
			      plegma[i][j]=label[k];
			      size[label[plegma[i][j]]]=size[label[plegma[i][j]]]+1;
			      k=k+1;
			    }
			  else
			    {
			      plegma[i][j]=label[plegma[i-1][j]];
			      size[label[plegma[i][j]]]=size[label[plegma[i][j]]]+1;
			    }
			}
		      else
			{
			  plegma[i][j]=label[plegma[i][j-1]];
			  size[label[plegma[i][j]]]=size[label[plegma[i][j]]]+1;
			  if (plegma[i-1][j]!=0 && label[plegma[i-1][j]]!=label[plegma[i][j-1]])
			    {
			      temp1=label[plegma[i-1][j]]; //xreiazetai gt theloume na allaxoume
			      //tis times isees me
			      //tou apo panw alla an allaxei to apo panw tha stamathsei
			      //na psaxnei thn prohgoumenh timh
			      label[plegma[i-1][j]]=label[plegma[i][j-1]];
			      for(l=0;l<=N*N;l++)
				{
				  if(label[l]==temp1)
				    {
				      label[l]=label[plegma[i][j-1]];
				    }
				}
			      size[label[plegma[i][j-1]]]=size[label[plegma[i][j-1]]]+size[plegma[i-1][j]];
			      size[plegma[i-1][j]]=0;
			    } //telos if &&
			} //telos if-else gia to index aristera
		    } //telos if plegma!=0
		} //telos i
	    } //telos j
	  
	  for (i=0;i<N*N;i++)
	    {
	      Iav[n]=Iav[n]+(size[i])/((float)pnn)*size[i]; //PROSOXH!!! xwris to float kanei akeraia diairesh
	    }
	  
	  int sizemax=0;
	  for(i=0;i<N*N;i++)
	    {
	      if (size[i]>sizemax) sizemax=size[i];
	    }
	  countc=0;
	  for(i=0;i<N*N;i++)
	    {
	      if (size[i]==sizemax) countc++;
	    }
	  //printf("countc=%d\n",countc);
	  for (i=0;i<N*N;i++)
	    {  //PROSOXH!!! xwris to float kanei akeraia diairesh
	      Iavtonos[n]=Iavtonos[n]+(size[i])/((float)pnn)*size[i]; //integer overflow ->to ginomeno twn size prepei na spasei
	    }
	    Iavtonos[n]=Iavtonos[n]-(countc*sizemax)/((float)pnn)*sizemax;
	    //Iavtonos[n]=Iav[n]-(countc*sizemax)/((float)pnn)*sizemax; //Giati de leitoyrgei?
	  
	  pmax[n]+=sizemax/(float)pnn;
	  
	  /* for (i=1;i<N;i++) //gia na dw ta telika plegmata
	    {
	      for (j=1;j<N;j++)
		{
		  printf("%d\t",label[plegma[i][j]]);
		}
	      printf("\n");
	    }*/
	  //printf("\n");
	}//telos 1000 run gia kathe plegma
      Iav[n]=Iav[n]/((float)run);
      Iavtonos[n]=Iavtonos[n]/((float)run);
      pmax[n]=pmax[n]/((float)run);
      //printf("Iav[%d]=%f\tIavtonos[%d]=%f\tpmax[%d]=%f\tp[%d]=%f\tm.o.pnn=%f\n",n,Iav[n],n,Iavtonos[n],n,pmax[n],n,p[n],pnn/(float)run);
      fprintf(dataIav,"%f\t%f\n",p[n],Iav[n]);
      fprintf(dataIavtonos,"%f\t%f\n",p[n],Iavtonos[n]);
      fprintf(datapmax,"%f\t%f\n",p[n],pmax[n]);
      printf("%d=\n",n);
    }//telos plegmatos
  free(plegma);
  free(size);
  free(label);
  free(Iav);
  fclose(dataIav);
  fclose(dataIavtonos);
  fclose(datapmax);
}//telos main
