/// LISTA DE ADJACÊNCIA

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define VERTICE_INVALIDO NULL
#define AN -1
#define PESO_NULO 0

typedef int TipoPeso;

typedef struct est{
    est* prox;
}NO;

typedef struct taresta {
    int vdest;
    TipoPeso peso;
    struct taresta * prox;
} TipoAresta;

typedef TipoAresta* TipoApontador;

typedef struct {
    TipoApontador *listaADJ;
    int numV;
    int numA;
} TipoGrafo;

/************************ CÓDIGOS DE GRAFO ****************************/

bool inicializaGrafo(TipoGrafo*grafo, int numV){
    int i;
    if(numV<=0){
        printf("Erro ao inicializar");
    }
    else{
        grafo->numV = numV;
	    grafo->numA = 0;

        grafo->listaADJ = (TipoApontador*) calloc(numV+1,sizeof(TipoApontador));
        for(i = 1; i<= grafo->numV; i++){
            TipoApontador q;
            q->prox=VERTICE_INVALIDO;
            grafo->listaADJ[i] = q;
        }
	    return true;
    }
    return false;
}

bool inicializaGrafo2(TipoGrafo *g, int nv){
    if(nv<=0){
        printf("Erro ao inicializar");
    }
    else{
        g->listaADJ = (TipoApontador*) calloc(nv+1,sizeof(TipoApontador));
	    g->numV = nv;
	    g->numA = 0;
	    return true;
    }
    return false;
}

void imprimeGrafo(TipoGrafo*grafo){
    int i = 1;
    TipoApontador p;
    while( i <= grafo->numV){
        p = grafo->listaADJ[i];
        printf("V:%d | %d", p, i);
        TipoApontador q = VERTICE_INVALIDO;
        if(p){
            q = p->prox;
        }
        while(q){
            printf(" -> (P:%d |D:%d |N:%d)", q->peso, q->vdest, q->prox);
            q = q->prox;
        }
        printf("\n");
        i++;
    }
    if(!p){
        printf("NAO EXISTE GRAFO \n");
    }
}

/************************CODIGOS DE ARESTAS****************************/

void insereAresta(TipoGrafo * g, int v1,int v2, TipoPeso peso){
    TipoApontador p= g->listaADJ[v1];
    TipoApontador q = (TipoAresta*) malloc(sizeof(TipoAresta));
    q->prox=NULL;
    q->vdest=v2;
    q->peso=peso;
    if(!p){
        g->listaADJ[v1]=q;
    }
    else{
        q->prox=p;
        g->listaADJ[v1]=q;
    }
}

bool removeAresta(TipoGrafo* g, int v){

}

/************************ CÓDIGOS DE VÉRTICES ****************************/

int obtemNrVertices(TipoGrafo* grafo){
    int i;
    int contador = 0;
    TipoApontador p;
    TipoApontador q;
    //TipoApontador q = (TipoAresta*) malloc(sizeof(TipoAresta));

    //TipoAresta* p = (TipoAresta*) malloc(sizeof(TipoAresta));
    //TipoApontador * p = (TipoApontador*) malloc(sizeof(TipoApontador));
    //TipoApontador p = (TipoApontador) malloc(sizeof(TipoApontador));

    for(i = 1; i<= grafo->numV; i++){
        p = grafo->listaADJ[i];
        if(p){
            printf("%d \n", p->vdest);
          /**
            q = grafo->listaADJ[i];
            while(q->prox){
                /*
                if(!q->vdest ){
                   break;
                }
                contador++;
                q=q->prox;
            }
        */
        }
    }

    return contador;
};

/************************ CÓDIGOS A VERIFICAR ****************************/

TipoApontador proxListaADJ(int atual, TipoGrafo* grafo){
    for(++atual; atual<=grafo->numV; atual++){
        //printf("%d",grafo->listaADJ[atual]);
        if((int)grafo->listaADJ[atual]!=AN){
            return grafo->listaADJ[atual];
        }
    }
    return (TipoApontador)AN;
}

void liberaGrafo(TipoGrafo* grafo){
    int i;
    TipoApontador p;
    for(i = 1; i<= grafo->numV; i++){
        ///libera ADJ
        while(p=grafo ->listaADJ[i]){
            grafo->listaADJ[i] = p->prox;
            p->prox = NULL;
            free(p);
        }
    }
    free(grafo->listaADJ);
    grafo->numV = 0;
    grafo->numA = 0;
    grafo->listaADJ = NULL;
}

/************************ CÓDIGO DO GRAPHVIZ ****************************/

void escreveArquivoGraphviz(TipoGrafo* g){
    FILE* f= fopen("grafo.gv","w+");
    fprintf(f,"digraph G{\n");
    int i,j;
    for(j=1;j<=g->numV;j++){
        fprintf(f,"%d;\n",j);
    }
    for(i=1;i<=g->numV;i++){
        TipoApontador p= g->listaADJ[i];
        while(p){
            fprintf(f,"%d -> %d [label=%d];\n",i,p->vdest,p->peso);
            p=p->prox;

        }
    }
    fprintf(f,"}");
    fclose(f);

}

int main()
{
    TipoGrafo grafo;
    inicializaGrafo(&grafo, 10);

    insereAresta(&grafo, 5,7,12);
    insereAresta(&grafo, 5,3,12);
    insereAresta(&grafo, 4,3,12);

    //int resp = obtemNrVertices(&grafo);
    //printf("\n%d\n",resp);

    imprimeGrafo(&grafo);

    escreveArquivoGraphviz(&grafo);
    printf("Hello world  1! \n");

    return 0;
}
