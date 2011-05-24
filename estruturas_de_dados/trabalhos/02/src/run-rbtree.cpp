#include "TRBTreeError.h"
#include "TRBTree.h"
#include <stdlib.h>

typedef struct {
	int Cod;
	char Nome[256];
} Pessoa;
      
      
int pFnComp(const void*, const void*);
void pFnGetLabel(const void*, char*);
      
      
           
//Fun�o para criar as strings do arquivo *.dot que ser�usado para a gera�o do gif da RBTree


int main(int argc, char *argv[]){

	int nPess,cod,pos;
	char nome[256];

	TRBTree *Arvore = new TRBTree(pFnComp, pFnGetLabel);
	Pessoa *p;

	FILE *pEntrada;	
	pEntrada = fopen(argv[2],"r");

	if (pEntrada == NULL)
	{
		cerr<<"Arquivo '"<<argv[2]<<"' nao existente"<<endl;
		exit(-1);
	}
	fscanf(pEntrada,"%d\n", &nPess);

	for(; nPess>0; nPess--)
	{
		p = new Pessoa;
		fscanf(pEntrada,"%d %d %[^\n]\n", &pos, &cod, nome);
		p->Cod = cod;
		strcpy(p->Nome,nome);
		Arvore->Insert((void *)p);
	}
	fclose(pEntrada);

	/*pEntrada = fopen(argv[3],"r");
	if (pEntrada == NULL){
		cerr<<"Arquivo '"<<argv[3]<<"' nao existente"<<endl;
		exit(-1);
	}
	
	*/
	
	Arvore->setTraversingDir(Arvore->sdPosOrder);
	p = new Pessoa;
	p->Cod = 1;
	Arvore->Search((void *)p);
	//Arvore->Last();
	//Arvore->dump_pCurrent();
	
	Arvore->dump_pCurrent();
	Arvore->Next();
	Arvore->dump_pCurrent();
	
	
	
	
	//************************************************************
	// RETIRAR DEPOIS
	//************************************************************
	FILE *arquivo_dot = fopen("run-rbtree.dot", "w");
	Arvore->WriteGraphvizSource(arquivo_dot);
	fclose(arquivo_dot);

	return 0;
}

//Função de Comparação
int pFnComp(const void *a, const void *b)
{
	Pessoa *pessoaA, *pessoaB;
	pessoaA = (Pessoa* ) a;
	pessoaB = (Pessoa* ) b;
	
	if ((pessoaA->Cod) < (pessoaB->Cod))
	{
		return -1;
	}
	else if ((pessoaA->Cod) > (pessoaB->Cod))
	{
		return 1;
	}
    	else return 0;
};


// Funcao que retorna o label
void pFnGetLabel(const void* Node, char* label)
{
	Pessoa *a = (Pessoa *) Node;
	sprintf(label, "%d", a->Cod);

}
