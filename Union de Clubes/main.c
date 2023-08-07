#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Union de Clubes.h"


int main(int argc,char*argv[])
{
    if(argc!=4)
        return ERROR_ARG;



    printf("\n\n*********SOCIOS A***********\n");

    crearArchSociosA_ALU(argv[1]);

    printf("\n*********FIN SOCIOS A***********\n\n");


    printf("\n\n*********SOCIOS B***********\n");

    int ce=0;
    t_socio* vecSociosB=descargarArchEnVectorSociosB_ALU(argv[2],&ce);

    for(t_socio*i=vecSociosB;i<vecSociosB+ce;i++)
    {
        printf("%ld|%s|%d\n",i->dni,i->apyn,i->antiguedad);
    }
    printf("\n");

    ordenarVecGen_ALU(vecSociosB,ce,sizeof(t_socio),compararPorDni);

    printf("\n*********FIN SOCIOS B***********\n\n");


    unificar_clubes_ALU(argv[1], vecSociosB,ce, argv[3]);

    printf("\n\n*********SOCIOS FINAL***********\n");

    mostrar_archivo_socios_final_ALU(argv[3]);

    printf("\n*********FIN SOCIOS FINAL***********\n\n");

    return 0;
}





