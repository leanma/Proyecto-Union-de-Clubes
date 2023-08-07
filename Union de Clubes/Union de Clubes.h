#ifndef UNION_DE_CLUBES_H_INCLUDED
#define UNION_DE_CLUBES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



typedef struct
{
    long dni;
    char apyn[30];
    int antiguedad;
}t_socio;


#define ERROR_ARG 1
#define ERROR_ARCH 2
#define ERROR_LINEA 3
#define ERROR_MEM 4

#define TAM_VEC_MAX 50
#define TAM_LIN 60



typedef int(*Cmp)(void*,void*);

void crearArchSociosA_ALU(char* nombreArchBin);
void ordenarVecGen_ALU(void* vec,int ce,size_t tamElem,Cmp cmp);
void* buscarMenor_ALU(void*ini,void*fin,size_t tamElem,Cmp cmp);
void intercambiar_ALU(void*x,void*y,size_t tamElem);
int compararPorDni(void*x,void*y);


t_socio*descargarArchEnVectorSociosB_ALU(char*nombreArchTxt,int*ce);
void txtABin_ALU(char*linea,t_socio* socio);

void unificar_clubes_ALU(char* nombreArchSociosA,t_socio* vecSociosB,int ce,char* nombreArchSociosUni);

void mostrar_archivo_socios_final_ALU(char* nombreArchTxt);

#endif // UNION_DE_CLUBES_H_INCLUDED
