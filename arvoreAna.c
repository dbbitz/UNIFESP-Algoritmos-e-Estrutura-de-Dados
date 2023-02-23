#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct{
    char nome[20];
    int assassinatos;
} TipoAssassino;

struct ArvAssassinos{
  TipoAssassino assassino;
  struct nohArvore *subArvoreEsq;
  struct nohArvore *subArvoreDir;
};

struct ArvMortos{
  char morto[20];
  struct nohArvore *subArvoreEsq;
  struct nohArvore *subArvoreDir;
};

typedef struct ArvAssassinos TipoNohArvoreAss;
typedef struct ArvMortos TipoNohArvoreMor;

typedef TipoNohArvoreAss *Assassinos;//typedef TipoNohArvore *TipoArvore;
typedef TipoNohArvoreMor *Mortos;//

int arvAssVazia(Assassinos);
int arvMorVazia(Mortos);

Assassinos inicializaArvAss();
Mortos inicializaArvMor();

Assassinos destroiArvoreAss(Assassinos);
Mortos destroiArvoreMor(Mortos);

Assassinos instanciaArvAss(TipoAssassino);
Mortos instanciaArvMor(char nomeDoMorto[20]);

Assassinos insereSubArvEsqAss(Assassinos,Assassinos);
Assassinos insereSubArvDirAss(Assassinos,Assassinos);

Mortos insereSubArvEsqMor(Mortos,Mortos);
Mortos insereSubArvDirMor(Mortos,Mortos);

Assassinos montaArvAss(Assassinos,Assassinos,Assassinos);
Mortos montaArvMor(Mortos,Mortos,Mortos);

void imprimeArvorePreOrdem(TipoArvore);
void imprimeArvoreEmOrdem(TipoArvore);
void imprimeArvorePosOrdem(Assassinos);

Assassinos inserirAssassino(Assassinos a, TipoAssassino vilao);
Mortos inserirMorto(Mortos a, char nomeDoMorto[20]);


int main(){
    Assassinos *Assassinos = NULL;
    Mortos *Mortos = NULL;
    char vilao[20], vitma[20];

    while(scanf("%s %s", vilao, vitma) != EOF) {

        TipoAssassino assassino;
        assassino.nome[20] = "";
        assassino.assassinatos = 0;
        strcpy(assassino.nome, vilao);
        Assassinos = inserirAssassino(Assassinos, assassino);
        Mortos = inserirMorto(Mortos, vitma);
    }
    printf("HALL OF MURDERERS\n");
    imprime(Assassinos, Mortos);
}

int arvAssVazia(Assassinos arvore){
  return arvore==NULL;
}
int arvMorVazia(Mortos arvore){
  return arvore==NULL;
}

//Inicializa
Assassinos inicializaArvAss(){
  return NULL;
}

Mortos inicializaArvMor(){
  return NULL;
}
// Destroi
Assassinos destroiArvoreAss(Assassinos arvore){
  if(!arvAssVazia(arvore)){
    arvore->subArvoreEsq = destroiArvoreAss(arvore->subArvoreEsq);
    arvore->subArvoreDir = destroiArvoreAss(arvore->subArvoreDir);
    free(arvore);
  }
  return NULL;
}
Mortos destroiArvoreMor(Mortos arvore){
  if(!arvMorVazia(arvore)){
    arvore->subArvoreEsq = destroiArvoreMor(arvore->subArvoreEsq);
    arvore->subArvoreDir = destroiArvoreMor(arvore->subArvoreDir);
    free(arvore);
  }
  return NULL;
}


//Instanciar
Assassinos instanciaArvAss(TipoAssassino vilao){
  Assassinos arvore = (Assassinos) malloc(sizeof(Assassinos));
  arvore->subArvoreEsq = NULL;
  arvore->subArvoreDir = NULL;
//  arvore->assassino = vilao;
  return arvore;
}
Mortos instanciaArvMor(char nomeDoMorto[20]){
  Mortos arvore = (Mortos) malloc(sizeof(TipoNohArvoreMor));
  arvore->subArvoreEsq = NULL;
  arvore->subArvoreDir = NULL;
  arvore->morto[20] = nomeDoMorto;
  return arvore;
}


//Inserir a esquerda - Assassino
Assassinos insereSubArvEsqAss(Assassinos raiz,Assassinos subArvoreEsq){
  if(!arvAssVazia(raiz)){
    raiz->subArvoreEsq = subArvoreEsq;
    return raiz;
  }
  return NULL;
}
//Inserir a direita - Assassino
Assassinos insereSubArvDirAss(Assassinos raiz,Assassinos subArvoreDir){
  if(!arvAssVazia(raiz)){
    raiz->subArvoreDir = subArvoreDir;
    return raiz;
  }
  return NULL;
}



//Inserir a esquerda - Morto
Mortos insereSubArvEsqMor(Mortos raiz,Mortos subArvoreEsq){
  if(!arvMorVazia(raiz)){
    raiz->subArvoreEsq = subArvoreEsq;
    return raiz;
  }
  return NULL;
}
//Inserir a direita - Morto
Mortos insereSubArvDirMor(Mortos raiz,Mortos subArvoreDir){
  if(!arvMorVazia(raiz)){
    raiz->subArvoreDir = subArvoreDir;
    return raiz;
  }
  return NULL;
}


//Montar arvore Ass Mor
Assassinos montaArvAss(Assassinos raiz,Assassinos subArvoreEsq,Assassinos subArvoreDir){
  if(!arvAssVazia(raiz)){
    raiz->subArvoreEsq = subArvoreEsq;
    raiz->subArvoreDir = subArvoreDir;
    return raiz;
  }
  return NULL;
}

Mortos montaArvMor(Mortos raiz,Mortos subArvoreEsq,Mortos subArvoreDir){
  if(!arvMorVazia(raiz)){
    raiz->subArvoreEsq = subArvoreEsq;
    raiz->subArvoreDir = subArvoreDir;
    return raiz;
  }
  return NULL;
}



Assassinos inserirAssassino(Assassinos a, TipoAssassino vilao){
    if(arvAssVazia(a)){
        a = (Assassinos*) malloc(sizeof(TipoNohArvoreAss));
        a = montaArvAss(a,NULL,NULL);
        a->assassino = vilao;
        a->assassino.assassinatos++;
        return a;
    }
    else if(strcmp(vilao.nome,a->assassino.nome) == -1){
        a = insereSubArvEsqAss(a,inserirAssassino(a->subArvoreEsq,vilao));
    }
    else if(strcmp(vilao.nome,a->assassino.nome) == 1){
        a = insereSubArvDirAss(a,inserirAssassino(a->subArvoreDir,vilao));
    }else if(strcmp(vilao.nome,a->assassino.nome) == 0){
        a->assassino.assassinatos++;
    }
    return a;
}

Mortos inserirMorto(Mortos a, char nomeDoMorto[20]){
    if(arvMorVazia(a)){
        a = (Mortos*) malloc(sizeof(TipoNohArvoreMor));
        a = montaArvMor(a,NULL,NULL);
        strcpy(a->morto,nomeDoMorto);
        return a;
    }
    else if(strcmp(nomeDoMorto,a->morto) == -1){
        a = insereSubArvEsqMor(a,inserirMorto(a->subArvoreEsq,nomeDoMorto));
    }
    else if(strcmp(nomeDoMorto,a->morto) == 1){
        a = insereSubArvDirMor(a,inserirMorto(a->subArvoreDir,nomeDoMorto));
    }else if(strcmp(nomeDoMorto,a->morto) == 0){
        return a;
    }
    return a;
}

bool EstaMorto(Mortos a, char pessoa[20]){
    bool res;
    if(arvMorVazia(a)){

        return false;
    }
    if(strcmp(pessoa,a->morto) == 0){

        return true;
    }
    if(strcmp(pessoa,a->morto) == -1){
        res = EstaMorto(a->subArvoreEsq,pessoa);
    }
    else{
        res = EstaMorto(a->subArvoreDir,pessoa);
    }
}

void imprime(Assassinos arvAssassinos, Mortos arvMortos){
  if(!arvAssVazia(arvAssassinos)){
    imprime(arvAssassinos->subArvoreEsq, arvMortos);

    if(!EstaMorto(arvMortos,arvAssassinos->assassino.nome)){
        printf("%s %d\n",arvAssassinos->assassino.nome,arvAssassinos->assassino.assassinatos);
    }






    imprime(arvAssassinos->subArvoreDir, arvMortos);

  }
}

void imprimeMortos(Mortos arvMortos){
  if(!arvMorVazia(arvMortos)){
    imprimeMortos(arvMortos->subArvoreEsq);

    printf("%s\n",arvMortos->morto);

    imprimeMortos(arvMortos->subArvoreDir);

  }
}

Assassinos retiraAss(Assassinos a, TipoAssassino vilao) {
Assassinos aux, pai,f;
if (arvAssVazia(a)) {
    return NULL;
    }
else if (strcmp(a->assassino.nome,vilao.nome) == 1){
    a->subArvoreEsq = retiraAss(a->subArvoreEsq, vilao);
}

else if (strcmp(a->assassino.nome,vilao.nome) == -1){
    a->subArvoreDir = retiraAss(a->subArvoreDir, vilao);
}
else {
    if (a->subArvoreEsq==NULL && a->subArvoreDir==NULL){
        free (a);
        a = NULL;
}
else if (a->subArvoreEsq == NULL) {
        aux = a;
        a = a->subArvoreDir;
        free (aux);
} else if (a->subArvoreDir == NULL) {
        aux = a;
        a = a->subArvoreEsq;
        free (aux);

}

else {
    pai = a;
    f = a->subArvoreEsq;
while (f->subArvoreDir != NULL) {

pai = f;
f = f->subArvoreDir;
}

a->assassino = f->assassino;
    if (pai==a){
    pai->subArvoreEsq = f->subArvoreEsq;

    }
    else{
    pai->subArvoreDir = f->subArvoreEsq;
    }
}
return a;
}}



