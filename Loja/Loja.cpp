#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstring>

#pragma warning(disable : 4996)
using namespace std;

FILE* ArqProduto;

typedef struct Produto {
	char Marca[20];
	char Descricao[30];
	long int Codigo;
	int Quantidade;
	float PC, PV;
} RegProduto;

RegProduto Prod;

void Menu();
void Limpar();
void Cadastrar();
void Relatorio();
void Busca();


int main(int argc, char** argv) {
	setlocale(LC_ALL, "Portuguese");
	Menu();
	return 0;
}

void Cadastrar() {
	char opcao;
	ArqProduto = fopen("arquivo.dat", "ab");
	if (ArqProduto == NULL) {
		cout << "Erro na abertura do arquivo\n";
		system("pause");
		exit(1);
	}

	do {
		cout << "\n **********************************************************************************************************************\n";
		cout << "\n                                         --- ADICIONAR UM NOVO PRODUTO ---";
		cout << "\n";
		cout << "\n **********************************************************************************************************************\n";
		cout << "\n Código do Produto: ";
		cin >> Prod.Codigo;
		if (Prod.Codigo == 0) {
			cout << " !!! Campo Código vazio. Digite novamente: ";
			cin >> Prod.Codigo;
		}
		cin.ignore(80, '\n');
		cout << " Marca: ";
		cin.getline(Prod.Marca, sizeof(Prod.Marca));
		if (strlen(Prod.Marca) == 0) {
			cout << " !!! Campo Marca vazio. Digite novamente: ";
			cin.getline(Prod.Marca, sizeof(Prod.Marca));
		}
		cout << " Descrição: ";
		cin.getline(Prod.Descricao, sizeof(Prod.Descricao));
		if (strlen(Prod.Descricao) == 0) {
			cout << " !!! Campo Descrição vazio. Digite novamente: ";
			cin.getline(Prod.Descricao, sizeof(Prod.Descricao));
		}
		cout << " Quantidade: ";
		cin >> Prod.Quantidade;
		if (Prod.Quantidade == 0) {
			cout << " !!! Campo Quantidade vazio. Digite novamente: ";
			cin >> Prod.Quantidade;
		}
		cout << " Preço de Custo: ";
		cin >> Prod.PC;
		if (Prod.PC == 0) {
			cout << " !!! Campo Preço de Custo vazio. Digite novamente: ";
			cin >> Prod.PC;
		}
		cout << " Preço de Venda: ";
		cin >> Prod.PV;
		if (Prod.PV == 0) {
			cout << " !!! Campo Preço de Venda vazio. Digite novamente: ";
			cin >> Prod.PV;
		}

		fwrite(&Prod, sizeof(Prod), 1, ArqProduto);
		cout << "Adicionar outro produto (S/N)?";
		cin >> opcao;

	} while (toupper(opcao) == 'S');
	fclose(ArqProduto);
	system("cls");
}

void Relatorio() {
	char opcao;
	system("cls");

	ArqProduto = fopen("arquivo.dat", "rb");
	if (ArqProduto == NULL) {
		cout << "Erro na abertura do arquivo\n";
		system("pause");
		exit(1);
	}
	cout << "\n **********************************************************************************************************************\n";
	cout << "\n                                           --- PRODUTOS CADASTRADOS ---";
	cout << "\n";
	cout << "\n **********************************************************************************************************************\n";
	cout << setw(8) << "Código";
	cout << setw(14) << "Marca";
	cout << setw(20) << "Descrição";
	cout << setw(14) << "Quantidade";
	cout << setw(16) << "Preço Custo";
	cout << setw(16) << "Preço Venda";
	cout << setw(20) << "Data de Cadastro";


	while (fread(&Prod, sizeof(Prod), 1, ArqProduto) != NULL) {
		cout << "\n";
		cout << setw(8) << Prod.Codigo;
		cout << setw(14) << Prod.Marca;
		cout << setw(20) << Prod.Descricao;
		cout << setw(14) << Prod.Quantidade;
		cout << setw(16) << Prod.PC;
		cout << setw(16) << Prod.PV;

		time_t currentTime = time(0);
		char* currentDate = ctime(&currentTime);
		currentDate[strlen(currentDate) - 1] = '\0';

		cout << setw(28) << currentDate;
	}
	fclose(ArqProduto);
}

long int BuscarProduto(int cod) {
	char opcao;
	system("cls");
	ArqProduto = fopen("arquivo.dat", "rb");
	if (ArqProduto == NULL) {
		cout << "Erro na abertura do arquivo\n";
		system("pause");
		exit(1);
	}
	while (fread(&Prod, sizeof(Prod), 1, ArqProduto) != NULL) {
		if (Prod.Codigo == cod) {
			int posicao = ftell(ArqProduto) - sizeof(Prod);
			fclose(ArqProduto);
			return posicao;
		}
	}
	fclose(ArqProduto);
	system("cls");
	return -1;
}

void Busca() {
	int c;
	long int pos;
	cout << "\n\nQual o código que deseja encontrar: ";
	cin >> c;
	pos = BuscarProduto(c);
	if (pos == -1) {
		cout << "\nProduto não cadastrado";
	}
	else {
		ArqProduto = fopen("arquivo.dat", "rb");
		fseek(ArqProduto, pos, 0);
		fread(&Prod, sizeof(Prod), 1, ArqProduto);
		cout << "\n                                                     RELATORIO           \n";
		cout << "\n **********************************************************************************************************************\n";
		cout << "\n Código: " << Prod.Codigo;
		cout << "\n Marca: " << Prod.Marca;
		cout << "\n Descrição: " << Prod.Descricao;
		cout << "\n Quantidade: " << Prod.Quantidade;
		cout << "\n Preço de Compra: " << "R$" << Prod.PC;
		cout << "\n Preço de Venda: " << "R$" << Prod.PV;
	}
}

void Limpar() {
	char opcao;
	cout << " Deseja limpar o arquivo do relatório? (S/N)";
	cin >> opcao;
	if (toupper(opcao) == 'S') {
		char opcao2;
		cout << " CERTEZA? Você perderá todos os registros de produtos. (S/N)";
		cin >> opcao2;
		if (toupper(opcao2) == 'S') {
			ArqProduto = fopen("arquivo.dat", "wb");
			fclose(ArqProduto);
			cout << "Arquivo removido\n";
		}
		system("pause");
		system("cls");
	}
}

void Menu() {
	int escolha;

	do {
		cout << "\n";
		cout << "\n **********************************************************************************************************************\n";
		cout << "\n                                          GERENCIADOR DE PRODUTOS - MENU           \n";
		cout << "\n **********************************************************************************************************************\n";
		cout << " Escolha uma opção:\n";
		cout << " 1 - Limpar\n";
		cout << " 2 - Cadastrar\n";
		cout << " 3 - Relatório\n";
		cout << " 4 - Busca\n";
		cout << " 5 - Sair\n";
		cout << "\n **********************************************************************************************************************\n";
		cout << "\n Opção: ";
		cin >> escolha;

		switch (escolha) {
		case 1:
			system("cls");
			Limpar();
			break;
		case 2:
			system("cls");
			Cadastrar();
			break;
		case 3:
			system("cls");
			Relatorio();
			break;
		case 4:
			system("cls");
			Busca();
			break;
		case 5:
			system("cls");
			break;
		default:
			system("cls");
			cout << " Opção inválida. Tente novamente.\n";
			break;
		}
	} while (escolha != 5);
}