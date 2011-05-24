#include "TRBTree.h"
#include "TRBTreeError.h"

      //Construtor
      TRBTree::TRBTree(int (*fnCompare)(const void *data, const void *data),void(*getLabel)(const void *data,char *text)){

		pFnComp = fnCompare;
		pFnGetLabel = getLabel;

		pRoot = pCurrent = NULL;
		FCount = 0;
		FTraversingDir = sdInOrder;
	};

	//Destrutor
	TRBTree::~TRBTree(){};

	//Retorna a forma de cria�o da �vore
	TRBTree::TraversingDir TRBTree::getTraversingDir() { return FTraversingDir; }

	//Define uma forma de cria�o da �vore
	void TRBTree::setTraversingDir (TraversingDir value) { FTraversingDir = value; }	

	//Funcao de APOIO apra gera o rotulo do no no arquivo .DOT
	void TRBTree::_geraIDNo(RBNode *no, char *label)
	{
		if(no == NULL)
		{
			strcpy(label, "NULL");
		}
		else
		{
			sprintf(label, "%d", no);
		}
	}

	//Insere um novo elemento na �vore
	void TRBTree::Insert(void *data)
	{
		int comparacao;

		if(data == NULL) { throw TRBTreeError("Insert", "Insert (NULL) isn't allowed."); }

		//Instancia novos nos, para navegar pela arvore
		RBNode *navegador = new RBNode;
		RBNode *pai_navegador = new RBNode;

		//Cria o novo no
		RBNode *novo_no = new RBNode;
		novo_no->Data = data;
		novo_no->Color = cRed;
		novo_no->pLeft = novo_no->pRight = novo_no->pFather = NULL;

		//Navega pela arvore, descendo
		navegador = pRoot;
		pai_navegador = NULL;

		while (navegador != NULL)
		{
			pai_navegador = navegador;

			comparacao = pFnComp((void*) novo_no->Data, (void *) navegador->Data);

			switch(comparacao)
			{
				case -1:
				  navegador = navegador->pLeft;
				  break;

				case 1:
				  navegador = navegador->pRight;
				  break;

				case 0:
				  throw TRBTreeError("Insert", "Duplicate insertion isn't allowed.");
				  break;
			}
		}

		//
		// pai_navegador é a ultima folha nao nula, decendo na arvore
		//

		novo_no->pFather = pai_navegador;

		//Arvore vazia??
		if( pai_navegador == NULL )
		{
			pRoot = novo_no;
		}
		else
		{
			//Encontra a posicao do novo no
			comparacao = pFnComp((void*) novo_no->Data, (void *) pai_navegador->Data);

			switch(comparacao)
			{
				case -1:
				  pai_navegador->pLeft = novo_no;
				  break;

				case 1:
				  pai_navegador->pRight = novo_no;
				  break;

				case 0:
				  throw TRBTreeError("Insert", "Duplicate insertion isn't allowed.");
				  break;
			}
		}

		//Restaura as propriedades
		RBTreeInsertFixup(novo_no);

		
		//Atualiza o numero de nos
		FCount++;
		//std::cout<<"novo_no no insert"<<std::endl;
		//dumpNode(novo_no);
	}

	
	
	//Deleta o ponteiro para um n, caso ele exista
	bool TRBTree::Delete(void *data){};

	
	
	//Deleta o ponteiro e o dado de um n, caso ele exista
	bool TRBTree::Destroy(void *data){};

	
	
	//Procura um n na �vore
	void* TRBTree::Search(void *data)
	{
		int comparacao;

		if(data == NULL) { throw TRBTreeError("Insert", "Search (NULL) isn't allowed."); }
		
		//nó para guardar o valor de pCurrent, caso data->Cod não exista na TRBTree
		RBNode *tmp = pCurrent;
		
		
		//pCurrent = ao 1º na travessia escolhida
		
		GoToRoot();
		comparacao = pFnComp(data, (void *) pCurrent->Data);
		
		while((pCurrent != NULL)&&(comparacao != 0))
		{
			if (comparacao == 1)
			{
				pCurrent = pCurrent->pRight;
			}
			else
			{
				pCurrent = pCurrent->pLeft;
			}
			comparacao = pFnComp(data, (void *) pCurrent->Data);
		}
		if (pCurrent == NULL)
		{
			pCurrent = tmp;
		}
		
	}

	
	
	//Atualiza pCurrent para o ultimo no, de acordo com FTraversingDir
	void TRBTree::Last()
	{
		//Navega
		switch(FTraversingDir)
		{
			case sdInOrder:
			  pCurrent = Max(pRoot);
			  break;

			case sdPreOrder:
			  pCurrent = Max(pRoot);
			  while(pCurrent->pLeft != NULL)
			  {
				pCurrent = Max(pCurrent->pLeft);
			  }
			  break;

			case sdPosOrder:
			  pCurrent = pRoot;
			  break;
		
		}
	}

	
	//Atualiza pCurrent para o primeiro no, de acordo com FTraversingDir
	void TRBTree::First()
	{
		//Navega
		switch(FTraversingDir)
		{
			case sdInOrder:
			  pCurrent = Min(pRoot);
			  break;

			case sdPreOrder:
			  pCurrent = pRoot;
			  break;

			case sdPosOrder:
			  pCurrent = Min(pRoot);
			  while(pCurrent->pRight != NULL)
			  {
			  	pCurrent = Min(pCurrent->pRight);
			  }
			  break;
		
		}
	}

	
	
	//Atualiza pCurrent para o próximo no, de acordo com FTraversingDir
	void TRBTree::Next()
	{
		//Volta para o primeiro
		if(pCurrent == NULL)
		{
			First();
			return;
		}
		
		//Navega
		switch(FTraversingDir)
		{
			case sdInOrder:
			  Successor();
			  break;

			case sdPreOrder:
			  //O Proximo é o filho à esquerda
			  
			  if(pCurrent->pLeft != NULL)
			  {
			  	pCurrent = pCurrent->pLeft;
				break;
			  }
			  //ou o filho a direita
			  else if(pCurrent->pRight != NULL)
			  {
			  	pCurrent = pCurrent->pRight;
				break;
			  }
			  	//Nao tem filhos
				else
				{	
					//acha um sucessor com filho a direita
					while (pCurrent->pRight == NULL)
					{
						Successor();
					}
					if (pCurrent == NULL)
					{
						return;
					}
					//Next() é o filho a direita de pCurrent
					pCurrent = pCurrent->pRight;
					
				}
			  break;

			case sdPosOrder:
			  //se é raiz
			  if (pCurrent->pFather == NULL)
			  {
			  	pCurrent = NULL;break;
			  }
			  //se ele é filho a direita, o next() é o pai dele
			  if(pCurrent == pCurrent->pFather->pRight)
			  {
			  	pCurrent = pCurrent->pFather;break;
			  }
			  //se é filho a esquerda
			  if(pCurrent == pCurrent->pFather->pLeft)
			  {
			  	//se o Tio de pCurrent é null, Next() é o pai de pCurrent
			  	if(pCurrent->pFather->pRight == NULL)
				{
					pCurrent = pCurrent->pFather;
				}
				else 
				{
					//pCurrent passa a ser seu tio
					pCurrent = pCurrent->pFather->pRight;
					//se o filho a direita é uma folha e o ultimo 
					if ((pCurrent->pRight == NULL)&&(pCurrent->pLeft==NULL))
					{
						break;
					}
					//senao procura o successor (ou seu filho a direita)do pCurrent ou o maior 
					else
					{
						if(pCurrent->pLeft != NULL)
						{
							while ((pCurrent->pLeft == NULL)&&(pCurrent->pRight != NULL))
							{
								pCurrent=pCurrent->pRight;
								pCurrent=Min(pCurrent);
							}
						}
						else
						{
							Successor();
							while(pCurrent->pRight != NULL)
							{
								pCurrent = pCurrent->pRight;
							}
						}	
					}	
				}
			  }
			  break;
		
		}
	}

	
	
	//Atualiza pCurrent para o nó anterior, de acordo com FTraversingDir
	void TRBTree::Prior()
	{
		//Volta para o primeiro
		if(pCurrent == NULL)
		{
			Last();
		}

		//Navega
		switch(FTraversingDir)
		{
			case sdInOrder:
			  Antecessor();
			  break;

			case sdPreOrder:
//			  Antecessor();
			  break;

			case sdPosOrder:
			  break;
		
		}
	}

	
	
	//Retorna pCurrent -> Data
	void* TRBTree::getCurrent(){ return pCurrent->Data; }

	
	
	//Delete() para todos os ns da �vore
	void TRBTree::DeleteAll(){};

	
	
	//Destroy() para todos os ns da �vore
	void TRBTree::DestroyAll(){};

	
	
	//Retorna o tamanho da arvore
	int TRBTree::getCount() { return FCount; }

	
	
	//Retorna pCurrent -> pFather
	bool TRBTree::GoToFather()
	{
		if(pCurrent != NULL && pCurrent->pFather != NULL)
		{
			pCurrent = pCurrent->pFather;
			return true;
		}

		return false;
	}

	
	
	//Retorna pCurrent -> pLeft
	bool TRBTree::GoToLeft()
	{
		if(pCurrent != NULL && pCurrent->pLeft != NULL)
		{
			pCurrent = pCurrent->pLeft;
			return true;
		}

		return false;
	}

	
	
	//Retorna pCurrent -> pRight
	bool TRBTree::GoToRight()
	{
		if(pCurrent != NULL && pCurrent->pRight != NULL)
		{
			pCurrent = pCurrent->pRight;
			return true;
		}

		return false;
	}

	
	
	//Retorna pRoot
	bool TRBTree::GoToRoot()
	{
		pCurrent = pRoot;
		return (pRoot != NULL);
	}

	
	//Retorna o menor elemento relativo a raiz informada
	TRBTree::RBNode *TRBTree::Min( TRBTree::RBNode *raiz )
	{
		//Minimo de nada
		if(raiz == NULL) { return raiz; }

		//Nao possui filhos à esquerda
		if(raiz->pLeft == NULL) { return raiz; }
		
		//Possui
		return Min(raiz->pLeft);
	}


	//Retorna o maior elemento relativo a raiz informada
	TRBTree::RBNode *TRBTree::Max( TRBTree::RBNode *raiz )
	{
		//maximo de nada
		if(raiz == NULL) { return raiz; }
		pCurrent = raiz;
		//Nao possui filhos à direita
		if(GoToRight()) { return TRBTree::Max(pCurrent); }
		
		return (raiz);
		//Possui
		//return TRBTree::Max(raiz->pRight);
	}


	//Atualiza pCurrent para seu Sucessor
	void TRBTree::Successor()
	{
		//Nao faz nada
		if(pCurrent == NULL) { return; }
		
		

		//Se possui filho à direita, o sucessor é o menor deles
		if(pCurrent->pRight != NULL)
		{ 
			pCurrent = Min(pCurrent->pRight); 
			return;
		}

		
		//Caso contrario, sobe à esquerda até achar uma caminhao à direita :P
		while(pRoot != pCurrent && pCurrent == pCurrent->pFather->pRight)
		{
			pCurrent = pCurrent->pFather;
		}

		//Aponta para o sucessor
		pCurrent = pCurrent->pFather;
	}

	
	
	//Atualiza pCurrent para seu Antecessor
	void TRBTree::Antecessor()
	{
		
		//Nao faz nada
		if(pCurrent == NULL) { return; }
		
		//Se possui filho à esquerda, o antecessor é o maior deles
		if(pCurrent->pLeft != NULL )
		{
			pCurrent = TRBTree::Max(pCurrent->pLeft);
			return;
		}
		
		
		//Caso contrario, sobe à direita até achar uma caminhao à esquerda :P
		while((pCurrent->pFather != NULL) && (pCurrent == pCurrent->pFather->pLeft))
		{
			pCurrent = pCurrent->pFather;
			
		}

		//Aponta para o antecessor
		pCurrent = pCurrent->pFather;
	}


	//Cria o arquivo na linguagem DOT (*.dot) para a cria�o do gif da RBTree
	void TRBTree::WriteGraphvizSource(FILE *f, bool blackwhite)
	{


		//setTraversingDir(sdPreOrder);
		char label[256];
		char color[20];

		//Inicia a geracao do .DOT
		fprintf(f, "digraph rbtree{\n");
		fprintf(f, "\tgraph[fontname=\"Times-Roman\", fontcolor=black, fontsize=12, label=\"Trabalho 2\"];\n");
		
		//Cria as formas dos nos 
		if(blackwhite)
		{
			fprintf(f, "\tnode[shape=record, fontcolor=black, color=black, style=filled, width=.50];\n");
		}
		else
		{
			fprintf(f, "\tnode[shape=record, fontcolor=white, color=white, style=filled, width=.50];\n");
		}
		
		//Define T q apontara para a raiz da arvore
		fprintf(f, "\n\tT[label=\"T\", fontcolor=black, color=white];\n");

		//arvore não vazia
		if(pRoot != NULL)
		{
			//nó NULL
			fprintf(f, "\tNULL[label=\"\", color=white, fillcolor=black, shape=circle];\n");

			//
			// Percorre a arvore0	123	Abda
			//
			First();

			//caracteristicas dos nós
			while(pCurrent != NULL)
			{
				if (blackwhite)
				{
					strcpy(color, (pCurrent->Color == cRed) ? "white" : "gray");
				}
				else
				{
					strcpy(color, (pCurrent->Color == cRed) ? "red" : "black");
				}

				pFnGetLabel((void*) pCurrent->Data, label);
				fprintf(f, "\t%d[label=\"<f0> | <f1> ", *pCurrent);
				fprintf(f, label);
				fprintf(f, " | <f2> \", fillcolor=");
				fprintf(f, color);
				fprintf(f, "];\n");
				dump_pCurrent();
				Next();
			}
            
			//aponta o T para a raiz
			fprintf(f, "\tT");
			fprintf(f, "->");
			fprintf(f, "%d:f1\n\n", *pRoot);
	
			First();
			//First();

			//crias as arestas do nos
			while(pCurrent != NULL)
			{

				//define a cor do nó de acordo com blackwhite
				if (blackwhite)
				{
					strcpy(color, (pCurrent->Color == cRed) ? "white" : "gray");
				}
				else
				{
					strcpy(color, (pCurrent->Color == cRed) ? "red" : "black");
				}

				pFnGetLabel((void*) pCurrent->Data, label);
				
				//Cria o NO
				if ((pCurrent->pFather) != NULL)
				 {

//				 dump_pCurrent();

					if(pCurrent == pCurrent->pFather->pLeft)
					{
						fprintf(f,"\t%d:f0", *(pCurrent->pFather));
						fprintf(f, "->");
						fprintf(f, "%d:f1\n",*pCurrent);

						fprintf(f,"\t%d:f1", *pCurrent);
						fprintf(f, "->");
						fprintf(f, "%d:f0\n",*(pCurrent->pFather));
					}
					else if (pCurrent == pCurrent->pFather->pRight)
					{
						fprintf(f,"\t%d:f2", *(pCurrent->pFather));
						fprintf(f, "->");
						fprintf(f, "%d:f1\n",*pCurrent);                

						fprintf(f,"\t%d:f1", *pCurrent);
						fprintf(f, "->");
						fprintf(f, "%d:f2\n",*(pCurrent->pFather));
					}
				}

				if ((pCurrent->pLeft == NULL)&&(pCurrent->pRight == NULL))
				{
					fprintf(f,"\t%d:f0", *pCurrent);
					fprintf(f, "->");
					fprintf(f, "NULL\n");

					fprintf(f,"\t%d:f2", *pCurrent);
					fprintf(f, "->");
					fprintf(f, "NULL\n");
				}
				if ((pCurrent->pLeft != NULL)&&(pCurrent->pRight == NULL))
				{
					fprintf(f,"\t%d:f2", *pCurrent);
					fprintf(f, "->");
					fprintf(f, "NULL\n");
				}

				if ((pCurrent->pRight != NULL)&&(pCurrent->pLeft == NULL))
				{
					fprintf(f,"\t%d:f0", *pCurrent);
					fprintf(f, "->");
					fprintf(f, "NULL\n");
				}

				Next();
            		}
		}

		fprintf(f, "}\n");
	}


      //M�odos para balanceamento da RBTree
      void LeftRotate(TRBTree::RBNode *node){};
      
      void RightRotate(TRBTree::RBNode *node){};
