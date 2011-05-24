#ifndef TRBTree_h
#define TRBTree_h

#include <iostream>
using namespace std;

class TRBTree {
      
public:

      //Traversing Direction
      enum TraversingDir {
           sdInOrder,
           sdPreOrder,
           sdPosOrder
      };
      
      //Color of the nodes
      enum RBColor {
           cRed,
           cBlack
      };
      
      typedef struct node {
              void *Data;
              struct node *pRight, *pLeft, *pFather;
              RBColor Color;
      } RBNode;

//
// METODOS PRIVADOS
//
  private:
      
	//Ponteiros da �vore
	RBNode *pRoot, *pCurrent;

	//Tamanho da �vore
	int FCount;

	//Caminho para procura na RBTree. (Default = 'In Order')
	TraversingDir FTraversingDir;
	
	//Fun�o para compara�o de dois ns da �vore
	int(*pFnComp)(const void*, const void*);

	//Fun�o para criar as strings do arquivo *.dot que ser�usado para a gera�o do gif da RBTree
	void(*pFnGetLabel)(const void*, char*);

	//M�odos para balanceamento da RBTree
	void LeftRotate(RBNode *node);
	void RightRotate(RBNode *node);
	
	//Restaura as propriedades da RBTree
	void RBTreeInsertFixup(RBNode *novo_no){};

	//Retorna o menor elemento relativo a raiz informada
	RBNode *Min( RBNode *raiz );

	//Retorna o menor elemento relativo a raiz informada
	RBNode *Max( RBNode *raiz );

	//Funcao de APOIO apra gera o rotulo do no no arquivo .DOT
	void _geraIDNo(RBNode *no, char *label);
//
// METODOS PUBLICOS
//
  public:  
  	void dumpNode(RBNode *node)
	{
		if(node == NULL)
		{
			std::cout<<"* nó NULL\n"<<std::endl;
			return;
		}
		
		char label[256];
		
		
		pFnGetLabel((void*) node->Data, label);
		std::cout<<"* ["<< node << "]" << label<<std::endl;

		if(node->pFather == NULL)
		{
			strcpy(label,"NULL");
		}
		else {pFnGetLabel((void*) node->pFather->Data, label);}
		
		std::cout<<"* father["<< node << "]" << label<<std::endl;		
		
		if(node->pLeft == NULL)
		{
			strcpy(label,"NULL");
		}
		else {pFnGetLabel((void*) node->pLeft->Data, label);}

		std::cout<<"* left["<<node->pLeft<<"]"<<label<<std::endl;

		if(node->pRight == NULL)
		{
			strcpy(label,"NULL");
		}
		else {pFnGetLabel((void*) node->pRight->Data, label);}

		std::cout<<"* right["<<node->pRight<<"]"<<label<<std::endl;

		std::cout<<std::endl;
	}

	void dump_pCurrent()
	{
		dumpNode(pCurrent);
	}
	         
      
      //Construtor
      TRBTree (int (*fnCompare)(const void*, const void*),void (*getLabel)(const void*,char*));

      //Destrutor
      ~TRBTree ();
      
      //Retorna a forma de cria�o da �vore
      TraversingDir getTraversingDir();
      
      //Define uma forma de cria�o da �vore
      void setTraversingDir (TraversingDir value);

      //Insere um n na �vore
      void Insert(void *data);

      //Deleta o ponteiro para um n, caso ele exista
      bool Delete(void *data);

      //Deleta o ponteiro e o dado de um n, caso ele exista
      bool Destroy(void *data);

      //Procura um n na �vore
      void* Search(void *data);
      
      //Atualiza pCurrent para o ltimo n
      void Last();
      
      //Atualiza pCurrent para o primeiro n
      void First();
      
      //Atualiza pCurrent para o prximo n
      void Next();
      
      //Atualiza pCurrent para o n anterior
      void Prior();
      
      //Retorna pCurrent -> Data
      void* getCurrent();

      //Delete() para todos os ns da �vore
      void DeleteAll();
      
      //Destroy() para todos os ns da �vore
      void DestroyAll();
      
      //Retorna o tamanho da �vore
      int getCount();
      
      //Retorna pCurrent -> pFather
      bool GoToFather();
      
      //Retorna pCurrent -> pLeft
      bool GoToLeft();
      
      //Retorna pCurrent -> pRight
      bool GoToRight();
      
      //Retorna pRoot
      bool GoToRoot();
      
      //Atualiza pCurrent para seu Sucessor
      void Successor();
      
      //Atualiza pCurrent para seu Antecessor
      void Antecessor();
      
      //Cria o arquivo na linguagem DOT (*.dot) para a cria�o do gif da RBTree
      void WriteGraphvizSource(FILE *f, bool blackwhite=true);
      
      
};

#endif
