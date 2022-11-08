#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// REGISTROS

struct fornecedor {
  int id;
  char nome[15];
  char email[30];
  char telefone[20];
};
struct produto {
  char descricaoProduto[20];
  char marca[10];
  char codigoId[10];
  int quantDisponivel;
  float precoUnitario;
  int fornecedorId;
  bool situacaoProduto;
  int quantVendida;
};

// SUBPROGRAMAS

// DEPENDENCIAS
// Programas usados para auxiliar nas funções principais

// Função para limpar a tela em todos os SOs
void clearTerminal() {
#if defined _WIN32
  system("cls");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
  system("clear");
#elif defined(__APPLE__)
  system("clear");
#endif
}

// Função auxiliar do particiona() e do quicksort
bool menorIgualCodigoId(char primeiroTermo[], char segundoTermo[]) {
  int tamanhoMenor = 0, i = 0;
  while (primeiroTermo[i] != '\0' and segundoTermo[i] != '\0') {
    tamanhoMenor++;
    i++;
  }

  for (i = 0; i < tamanhoMenor; i++) {
    if (primeiroTermo[i] != segundoTermo[i]) {
      if (primeiroTermo[i] < segundoTermo[i]) {
        return true;
      } else {
        return false;
      }
    }
  }

  return true;
}

// Função auxiliar do encontrarProduto()
bool maiorCodigoId(char primeiroTermo[], char segundoTermo[]) {
  int tamanhoMenor = 0, i = 0;
  while (primeiroTermo[i] != '\0' and segundoTermo[i] != '\0') {
    tamanhoMenor++;
    i++;
  }

  for (i = 0; i < tamanhoMenor; i++) {
    if (primeiroTermo[i] != segundoTermo[i]) {
      if (primeiroTermo[i] > segundoTermo[i]) {
        return true;
      } else {
        return false;
      }
    }
  }

  return false;
}

// Função auxiliar do encontrarProduto()
bool igualCodigoId(char primeiroTermo[], char segundoTermo[]) {
  int tamanho = 0, i = 0;
  while (primeiroTermo[i] != '\0' and segundoTermo[i] != '\0') {
    tamanho++;
    i++;
  }

  for (i = 0; i < tamanho; i++) {
    if (primeiroTermo[i] != segundoTermo[i]) {
      return false;
    }
  }

  return true;
}

// Função responsável por verificar se um fornecedor já está na lista de fornecedores
int encontrarFornecedor(char nomeInformado[], fornecedor *listaForn,
                        int tamListaFornecedores) {
  int i = 0, tamanhoNome = 0, cont = 0;
  while (nomeInformado[i] != '\0') {
    tamanhoNome++;
    i++;
    }

  for (i = 0; i < tamListaFornecedores; i++) {
    cont = 0;
    for (int j = 0; j < tamanhoNome; j++) {
      if (nomeInformado[j] == listaForn[i].nome[j]) {
        cont++;
      }
    }
    if (cont == tamanhoNome) {
      return i;
    }
  }
  return -1;
}

// QUICK SORT - Ordenação do vetor de produtos

int particiona(produto *listaElementos, int c, int f) {
  produto pivo = listaElementos[c];
  int i = c + 1, j = f;
  while (i <= j) {
    if (menorIgualCodigoId(listaElementos[i].codigoId, pivo.codigoId))
      // listaElementos[i].codigoId <= pivo.codigoId
      i++;
    else if (menorIgualCodigoId(pivo.codigoId, listaElementos[j].codigoId))
      // pivo.codigoId <= listaElementos[j].codigoId
      j--;
    else {
      swap(listaElementos[i], listaElementos[j]);
      i++;
      j--;
    }
  }
  listaElementos[c] = listaElementos[j];
  listaElementos[j] = pivo;
  return j;
}

void quicksort(produto *lsElementos, int pos_pivo, int fim) {
  int pos_novo_pivo;
  if (pos_pivo < fim) {
    pos_novo_pivo = particiona(lsElementos, pos_pivo, fim);
    quicksort(lsElementos, pos_pivo, pos_novo_pivo - 1);
    quicksort(lsElementos, pos_novo_pivo + 1, fim);
  }
}

// Estratégia de aumento do vetor produto

produto *aumentoVetorProdutos(produto *vetor, int tamanho) {
  produto *vetorNovo = new produto[tamanho + 3];
  for (int i = 0; i < tamanho; i++) {
    vetorNovo[i] = vetor[i];
  }
  delete[] vetor;

  return vetorNovo;
}

// Estratégia de aumento do vetor fornecedores

fornecedor *aumentoVetorFornecedor(fornecedor *vetor, int tamanho) {
  fornecedor *vetorNovo = new fornecedor[tamanho + 3];
  for (int i = 0; i < tamanho; i++) {
    vetorNovo[i] = vetor[i];
  }
  delete[] vetor;

  return vetorNovo;
}

//==============================================================

// FUNÇÕES PRINCIPAIS

// Função Cadastrar fornecedor

void cadastrarFornecedor(fornecedor *listaFornecedores, int &fornecedores,
                         produto *listaProdutos, int elementos, int &contFornecedor) {
  fornecedor fornecedorAux;
  int posFornecedor;

  cout << "Nome do Fornecedor: ";
  cin.ignore();
  cin.getline(fornecedorAux.nome, 15);

  posFornecedor =
      encontrarFornecedor(fornecedorAux.nome, listaFornecedores, fornecedores);

  if (posFornecedor == -1) {
    cout << "E-mail do Fornecedor: ";
    cin.getline(fornecedorAux.email, 30);
    cout << "Telefone do Fornecedor: ";
    cin >> fornecedorAux.telefone;
    fornecedores++;
    fornecedorAux.id = fornecedores;
    listaFornecedores[fornecedores-1] = fornecedorAux;
    listaProdutos[elementos-1].fornecedorId = listaFornecedores[fornecedores-1].id;
    contFornecedor++;
  } else {
    cout << "Preenchimento Automático! Fornecedor já cadastrado." << endl;
    listaProdutos[elementos-1].fornecedorId = listaFornecedores[posFornecedor].id;
  }

}

// Função Cadastrar produto

void cadastrarProduto(produto *listaProdutos, int &elementos, bool &cadastroSucesso) {

  int j = 0, cont = 0;
  bool codIgual = false;
  string aux; // auxiliar para o booleano codIgual

  cout << "Descrição do Produto: ";
  cin.ignore();
  cin.getline(listaProdutos[elementos].descricaoProduto, 20);
  cout << "Marca: ";
  cin >> listaProdutos[elementos].marca;

  cout << "Código do Produto: ";
  cin >> listaProdutos[elementos].codigoId;

  for (int i = 0; i < elementos; i++) {

    // compara caracter por caracter
    while (listaProdutos[elementos].codigoId[j] != '\0') {
      if (listaProdutos[elementos].codigoId[j] ==
          listaProdutos[i].codigoId[j]) {
        cont++;
      }
      j++;
    }

    if (cont == j) {
      cout << "ERRO: Produto já cadastrado." << endl;
      elementos--;
      codIgual = true;
      i = elementos;
    }

    cont = 0;
    j = 0;
  }

  if (codIgual == false) {
    cout << "Quantidade Disponivel: ";
    cin >> listaProdutos[elementos].quantDisponivel;
    cout << "Preço Unitario (com ponto): ";
    cin >> listaProdutos[elementos].precoUnitario;

    cout << "Situacao do Produto: ";
    cin >> aux;
    if (aux == "ativo") {
      listaProdutos[elementos].situacaoProduto = true;
    } else {
      listaProdutos[elementos].situacaoProduto = false;
    }
    listaProdutos[elementos].quantVendida = 0;
    cadastroSucesso = true;
  }
}

// Encontra a posicao do produto por meio de busca binária
// Para isso, foram criadas mais 2 funções que auxiliam a encontrá-lo:
// igualCodigoId() e maiorCodigoId()

int encontrarProduto(produto *listaProdutos, int elementos, char codigo[]) {
  int meio, posicao = -1, posInicial = 0, posFinal = elementos - 1;

  while (posInicial <= posFinal) {
    meio = (posInicial + posFinal) / 2;

    if (igualCodigoId(codigo, listaProdutos[meio].codigoId)) {
      posicao = meio;
      posInicial = posFinal + 1;
    } else {
      if (maiorCodigoId(codigo, listaProdutos[meio].codigoId)) {
        posInicial = meio + 1;
      } else {
        posFinal = meio - 1;
      }
    }
  }

  return posicao;
}

// MAIN

int main() {

  int opcao = 0, posBusca, elementosLista = 0, contadorProdutos = 0, elementosFornecedores = 0, contadorFornecedor = 0;  // Variáveis para controle dos vetores de fornecedores e produtos
  int contProdutosEstoque = 0; // Conta os produtos em estoque ativos (case 6)
  int qtdVendidaAux;           // Auxilia a venda (case 5)
  int SimOuNao = 0;  // Determina a condição de exclusão de produto (case 4)
  char codBusca[10]; // Auxilia na busca de produtos pelo codigo
  bool cadastroComSucesso = false; //Garante que se o código do produto estiver igual ele nao vai cadastrar
                                   //o fornecedor

  fornecedor *listaFornecedores = new fornecedor[3];
  produto *listaProdutos = new produto[3];

  ofstream escritaArqBinario("listaCadastro.dat");

  // Continua lendo enquanto o número não for igual a saída.
  while (opcao != 8) {

    // MENU PRINCIPAL

    clearTerminal();

    cout << "--------------------------------" << endl;
    cout << "|         Loja Virtual         |" << endl;
    cout << "--------------------------------" << endl << endl;
    cout << "1 - Cadastrar produto" << endl;
    cout << "2 - Consultar produto" << endl;
    cout << "3 - Listar produtos" << endl;
    cout << "4 - Excluir produto" << endl;
    cout << "5 - Efetuar venda" << endl;
    cout << "6 - Listar produtos em estoque" << endl;
    cout << "7 - Exportar produtos" << endl;
    cout << "8 - Sair" << endl << endl;

    cout << "Digite sua opção: ";
    cin >> opcao;

    switch (opcao) {

      // CADASTRO DO PRODUTO
    case 1:
      // As condições dizem respeito à alocação dinâmica
      if (contadorProdutos < 3) {
        cadastrarProduto(listaProdutos, elementosLista, cadastroComSucesso);
        contadorProdutos++;
        elementosLista++;
      } else {
        listaProdutos = aumentoVetorProdutos(listaProdutos, elementosLista);
        cadastrarProduto(listaProdutos, elementosLista, cadastroComSucesso);
        elementosLista++;
        contadorProdutos = 1;
      }
      
      if(cadastroComSucesso){
        if(contadorFornecedor < 3){
          cadastrarFornecedor(listaFornecedores, elementosFornecedores, listaProdutos, elementosLista, contadorFornecedor);
        } else {
          listaFornecedores = aumentoVetorFornecedor(listaFornecedores, elementosFornecedores);
          cadastrarFornecedor(listaFornecedores, elementosFornecedores, listaProdutos, elementosLista, contadorFornecedor);
          contadorFornecedor = 1;
        }
      }
      cadastroComSucesso = false;
      
      cout << endl;
      system("pause");

      break;

    // CONSULTA PRODUTO
    case 2:
      quicksort(listaProdutos, 0,
                elementosLista - 1); // ordenando a lista para passar pelo
                                     // encontrarProduto()

      cout << "Digite o código do produto: ";
      cin >> codBusca;
      posBusca = encontrarProduto(listaProdutos, elementosLista, codBusca);

      if (posBusca != -1) {
        cout << "Quantidade disponível: ";
        cout << listaProdutos[posBusca].quantDisponivel << endl;
        cout << "Quantidade vendida: ";
        cout << listaProdutos[posBusca].quantVendida << endl;
        cout << "Situação do produto: ";
        if (listaProdutos[posBusca].situacaoProduto) {
          cout << "Ativo" << endl;
        } else {
          cout << "Inativo" << endl;
        }
      } else {
        cout << "ERRO: Produto não encontrado." << endl;
      }

      cout << endl;
      system("pause");

      break;

    // LISTAGEM DOS PRODUTOS
    case 3:
      quicksort(listaProdutos, 0, elementosLista - 1);
      
      if (elementosLista > 0) {
        for (int i = 0; i < elementosLista; i++) {
          cout << endl;
          cout << "Código: " << listaProdutos[i].codigoId << endl;
          cout << "Descrição: " << listaProdutos[i].descricaoProduto << endl;
          cout << "Nome do Fornecedor: "
               << listaFornecedores[(listaProdutos[i].fornecedorId)-1].nome
               << endl;
          cout << "Email do Fornecedor: "
               << listaFornecedores[(listaProdutos[i].fornecedorId)-1].email
               << endl;
          if (listaProdutos[i].situacaoProduto) {
            cout << "Situação: Ativo" << endl;
            cout << "--------------------------------------------------" << endl;
          } else {
            cout << "Situação: Inativo" << endl;
            cout << "--------------------------------------------------" << endl;
          }
        }
        cout << endl;
      } else {
        cout << "Não há nenhum produto na loja." << endl;
      }

      cout << endl;
      system("pause");

      break;

    // EXCLUIR UM PRODUTO
    case 4:

      quicksort(listaProdutos, 0, elementosLista - 1); // ordenando a lista para passar pelo encontrarProduto()
      
      cout << "Digite o código do produto a ser excluído: ";
      cin >> codBusca;
      posBusca = encontrarProduto(listaProdutos, elementosLista, codBusca);

      if (posBusca != -1) {
        if (listaProdutos[posBusca].situacaoProduto == 0) {
          cout << "Produto já excluído." << endl;
        } else {
          cout << "Descrição do Produto: ";
          cout << listaProdutos[posBusca].descricaoProduto << endl;
          cout << "Confirmar exclusão? " << endl;
          cout << "1 - SIM | 2 - NÃO" << endl;
          cin >> SimOuNao;

          while (SimOuNao != 1 and SimOuNao != 2) {
            cout << "Valor Inválido. Digite novamente: ";
            cin >> SimOuNao;
          }

          if (SimOuNao == 1) {
            listaProdutos[posBusca].situacaoProduto = 0;
            if (listaProdutos[posBusca].situacaoProduto) {
              cout << "Situação: Ativo" << endl;
            } else {
              cout << "Situação: Inativo" << endl;
            }
          } else {
            if (listaProdutos[posBusca].situacaoProduto) {
              cout << "Situação: Ativo" << endl;
            } else {
              cout << "Situação: Inativo" << endl;
            }
          }
        }
      } else {
        cout << "ERRO: Produto não encontrado." << endl;
      }

      cout << endl;
      system("pause");

      break;

    // EFETUAR VENDA
    case 5:

      quicksort(listaProdutos, 0,
                elementosLista - 1); // ordenando a lista para passar pelo
                                     // encontrarProduto()
      cout << "Digite o código do produto a ser vendido: ";
      cin >> codBusca;
      posBusca = encontrarProduto(listaProdutos, elementosLista, codBusca);

      if (posBusca != -1) {
        if (listaProdutos[posBusca].situacaoProduto) {
          cout << "Descrição do Produto: ";
          cout << listaProdutos[posBusca].descricaoProduto << endl;
          cout << "Quantidade Vendida: ";
          cin >> qtdVendidaAux;
          if (listaProdutos[posBusca].quantDisponivel < qtdVendidaAux) {
            cout << "Venda Inválida. Produtos insuficientes!" << endl;
          } else {
            listaProdutos[posBusca].quantDisponivel -= qtdVendidaAux;
            listaProdutos[posBusca].quantVendida += qtdVendidaAux;
            cout << endl
                 << "Quantidade Restante em Estoque: "
                 << listaProdutos[posBusca].quantDisponivel << endl;
            cout << "Venda realizada com sucesso!" << endl;
          }
        } else {
          cout << "Venda Inválida. Produto inativo!" << endl;
        }
      } else {
        cout << "ERRO: Produto não encontrado." << endl;
      }

      cout << endl;
      system("pause");

      break;

      // LISTA DADOS DE PRODUTOS ATIVOS
    case 6:
      quicksort(listaProdutos, 0, elementosLista - 1);
      for (int i = 0; i < elementosLista; i++) {
        if (listaProdutos[i].situacaoProduto and
            listaProdutos[i].quantDisponivel != 0) {
          cout << endl;
          cout << "Codigo: " << listaProdutos[i].codigoId << endl;
          cout << "Descrição: " << listaProdutos[i].descricaoProduto << endl;
          cout << "Nome do Fornecedor: "
               << listaFornecedores[(listaProdutos[i].fornecedorId)-1].nome
               << endl;
          cout << "Email do Fornecedor: "
               << listaFornecedores[(listaProdutos[i].fornecedorId)-1].email
               << endl;
          cout << "--------------------------------------------------" << endl;
          contProdutosEstoque++;
        }
      }
      cout << endl;
      if (contProdutosEstoque == 0) {
        cout << "Não há nenhum produto no estoque." << endl;
      }

      cout << endl;
      system("pause");

      break;

    // EXPORTAR DADOS PARA ARQUIVO BINÁRIO
    case 7:

      if (elementosLista > 0) {
        escritaArqBinario.write((const char *)(listaProdutos),
                                elementosLista * sizeof(produto));
        cout << "Produtos exportados com sucesso!" << endl;
      } else {
        cout << "Falha na esportação. Não há nenhum produto na loja." << endl;
      }

      cout << endl;
      system("pause");

      break;

    case 8:
      cout << "Encerrando sistema..." << endl;
      break;

    default:
      cout << "Valor Inválido" << endl;
      cout << "Por favor, insira um valor válido";
      break;
    }
  }
}
