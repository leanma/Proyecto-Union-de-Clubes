#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Union de Clubes.h"


void crearArchSociosA_ALU(char* nombreArchBin)
{
    t_socio vecSocio[]={
                        {16001129,"Wilkerson Berk",1},
                        {16200214,"Clark Scott",2},
                        {16230902,"Boyd Chaney",3},
                        {16231024,"Guerra Oliver",4},
                        {16540430,"Brennan Lee",5},
                        {16621004,"Mcclain Ronan",6},
                        {16660110,"Dale Isaac",7},
                        {16780215,"Sosa Zeph",8},
                        {16860403,"Gibbs Clinton",9},
                        {16870210,"Cole Coby",1},
                        {16900207,"Gallegos Nash",2},
                        {16940212,"Hunter Rajah",3},
                        };
    int ce=12;

    ordenarVecGen_ALU(vecSocio,ce,sizeof(t_socio),compararPorDni);

    FILE*archBin=fopen(nombreArchBin,"wb");
    if(!archBin)
        exit(ERROR_ARCH);

    for(t_socio*i=vecSocio;i<vecSocio+ce;i++)
    {
        printf("%ld|%s|%d\n",i->dni,i->apyn,i->antiguedad);
        fwrite(i,sizeof(t_socio),1,archBin);
    }

    fclose(archBin);
}


void ordenarVecGen_ALU(void* vec,int ce,size_t tamElem,Cmp cmp)
{
    void*m;
    void*ult=(char*)vec+(ce-1)*tamElem;

    for(char*i=(char*)vec;i<(char*)ult;i+=tamElem)
    {
        m=buscarMenor_ALU(i,ult,tamElem,cmp);
        if(i!=m)
            intercambiar_ALU(i,m,tamElem);
    }
}


void* buscarMenor_ALU(void*ini,void*fin,size_t tamElem,Cmp cmp)
{
    void*m=ini;
    for(char*j=(char*)ini+tamElem;j<=(char*)fin;j+=tamElem)
    {
        if(cmp(j,m)<0)
            m=j;
    }
    return m;
}

int compararPorDni(void*x,void*y)
{
    t_socio socioX=*(t_socio*)x;
    t_socio socioY=*(t_socio*)y;

    if(socioX.dni>socioY.dni)
        return 1;
    if(socioX.dni<socioY.dni)
        return -1;
    return 0;
}

void intercambiar_ALU(void*x,void*y,size_t tamElem)
{
    void*xTemp=malloc(tamElem);
    memcpy(xTemp,x,tamElem);
    memcpy(x,y,tamElem);
    memcpy(y,xTemp,tamElem);
    free(xTemp);
}


t_socio*descargarArchEnVectorSociosB_ALU(char*nombreArchTxt,int*ce)
{
    FILE* archTxt=fopen(nombreArchTxt,"rt");
    if(!archTxt)
        exit(ERROR_ARCH);

    t_socio* vecSocios=malloc(TAM_VEC_MAX*sizeof(t_socio));
    if(!vecSocios)
        exit(ERROR_MEM);

    t_socio*vec_ptr=vecSocios;
    char linea[TAM_LIN];

    fgets(linea,TAM_LIN,archTxt);

    while(!feof(archTxt) && vec_ptr<vecSocios+TAM_VEC_MAX)
    {
        txtABin_ALU(linea,vec_ptr);
        vec_ptr++;
        (*ce)++;
        fgets(linea,TAM_LIN,archTxt);
    }

    fclose(archTxt);

    t_socio* vecSociosF=malloc(*ce*sizeof(t_socio));
    if(!vecSociosF)
        exit(ERROR_MEM);
    memcpy(vecSociosF,vecSocios,*ce*sizeof(t_socio));
    free(vecSocios);

    return vecSociosF;
}

void txtABin_ALU(char*linea,t_socio* socio)
{
    char* act=strchr(linea,'\n');
    if(!act)
        exit(ERROR_LINEA);

    *act='\0';
    act=strrchr(linea,'|');
    sscanf(act+1,"%d",&socio->antiguedad);

    *act='\0';
    act=strrchr(linea,'|');
    strcpy(socio->apyn,act+1);

    *act='\0';
    sscanf(linea,"%ld",&socio->dni);
}


void unificar_clubes_ALU(char* nombreArchSociosA,t_socio* vecSociosB,int ce,char* nombreArchSociosUni)
{
    FILE* archA=fopen(nombreArchSociosA,"rb");
    if(!archA)
        exit(ERROR_ARCH);
    FILE* archUni=fopen(nombreArchSociosUni,"wt");
    if(!archUni)
        exit(ERROR_ARCH);

    t_socio*vec_ptr=vecSociosB;
    t_socio socioAact;

    fread(&socioAact,sizeof(t_socio),1,archA);
    while(!feof(archA) && vec_ptr<vecSociosB+ce)
    {
        int comp=(int)socioAact.dni-(int)vec_ptr->dni;
        if(comp==0)
        {
            if(socioAact.antiguedad<vec_ptr->antiguedad)
            {
                socioAact.antiguedad=vec_ptr->antiguedad;
            }
            fprintf(archUni,"%ld|%s|%d\n",socioAact.dni,socioAact.apyn,socioAact.antiguedad);
            fread(&socioAact,sizeof(t_socio),1,archA);
            vec_ptr++;
        }
        if(comp<0)
        {
            fprintf(archUni,"%ld|%s|%d\n",socioAact.dni,socioAact.apyn,socioAact.antiguedad);
            fread(&socioAact,sizeof(t_socio),1,archA);
        }
        if(comp>0)
        {
            fprintf(archUni,"%ld|%s|%d\n",vec_ptr->dni,vec_ptr->apyn,vec_ptr->antiguedad);
            vec_ptr++;
        }
    }

    while(!feof(archA))
    {
        fprintf(archUni,"%ld|%s|%d\n",socioAact.dni,socioAact.apyn,socioAact.antiguedad);
        fread(&socioAact,sizeof(t_socio),1,archA);
    }

    while(vec_ptr<vecSociosB+ce)
    {
        fprintf(archUni,"%ld|%s|%d\n",vec_ptr->dni,vec_ptr->apyn,vec_ptr->antiguedad);
        vec_ptr++;
    }

    fclose(archA);
    fclose(archUni);
}

void mostrar_archivo_socios_final_ALU(char* nombreArchTxt)
{
    FILE*archTxt=fopen(nombreArchTxt,"rt");
    if(!archTxt)
        exit(ERROR_ARCH);

    char linea[TAM_LIN];
    t_socio socioAct;

    fgets(linea,TAM_LIN,archTxt);
    while(!feof(archTxt))
    {
        txtABin_ALU(linea,&socioAct);
        printf("%-9ld%-30s%3d\n",socioAct.dni,socioAct.apyn,socioAct.antiguedad);
        fgets(linea,TAM_LIN,archTxt);
    }
    fclose(archTxt);
}

