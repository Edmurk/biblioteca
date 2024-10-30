#include <iostream>
#include <fstream>
#include <limits>
#include <cstring>
#include <cstdlib>
using namespace std;

struct emprestimo
{
    char dataemp[10];
    char datadev[10];
    char usuario[200];
};

struct livros
{
    int idlivro, pagina;
    char area[30];
    char titulo[200];
    char autores[200];
    char editora[200];
    struct emprestimo emp;
};

void cadastrolivro()
{
    char opc;
    struct livros livro;
    system("cls");

    cout << "Deseja cadastrar um livro?[S/N]: ";
    cin >> opc;

    while (opc == 'S' || opc == 's') {
        cout << "Codigo: ";
        cin >> livro.idlivro;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Area: ";
        cin.getline(livro.area, 30);

        cout << "Titulo: ";
        cin.getline(livro.titulo, 200);

        cout << "Autores: ";
        cin.getline(livro.autores, 200);

        cout << "Editora: ";
        cin.getline(livro.editora, 200);

        ofstream arquivo("dados.txt", ios::app | ios::binary);

        if (arquivo.is_open()) {
            arquivo.write(reinterpret_cast<char*>(&livro), sizeof(livro));
            cout << "Livro cadastrado com sucesso!!\n";
        } else {
            cout << "Erro ao abrir arquivo\n";
        }
        arquivo.close();

        cout << "Deseja cadastrar um novo livro? [S/N] ";
        cin >> opc;
    }
    system("cls");
}

void alterarLivro() {
    bool encontrado = false;
    struct livros livro;
    int codigo;
    
    cout << "Digite o codigo do livro que deseja alterar: ";
    cin >> codigo;

    fstream arquivo("dados.txt", ios::in | ios::out | ios::binary);
    if (!arquivo) {
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    while (arquivo.read(reinterpret_cast<char*>(&livro), sizeof(livro))) {
        if (livro.idlivro == codigo) {
            encontrado = true;
            cout << "Digite os novos dados:\n";
            cout << "Area: ";
            cin.ignore();
            cin.getline(livro.area, 30);
            cout << "Titulo: ";
            cin.getline(livro.titulo, 200);
            cout << "Autores: ";
            cin.getline(livro.autores, 200);
            cout << "Editora: ";
            cin.getline(livro.editora, 200);

            arquivo.seekp(-static_cast<int>(sizeof(livro)), ios::cur);
            arquivo.write(reinterpret_cast<char*>(&livro), sizeof(livro));
            cout << "Livro alterado com sucesso!" << endl;
            break;
        }
    }
    if (!encontrado) {
        cout << "Livro não encontrado!" << endl;
    }
    arquivo.close();
}

void excluirLivro() {
    int codigo;
    struct livros livro;
    cout << "Digite o codigo do livro que deseja excluir: ";
    cin >> codigo;

    ifstream arquivo("dados.txt", ios::binary);
    ofstream arquivoTemp("temp.txt", ios::binary);

    if (!arquivo || !arquivoTemp) {
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    bool excluido = false;
    while (arquivo.read(reinterpret_cast<char*>(&livro), sizeof(livro))) {
        if (livro.idlivro != codigo) {
            arquivoTemp.write(reinterpret_cast<char*>(&livro), sizeof(livro));
        } else {
            excluido = true;
        }
    }
    arquivo.close();
    arquivoTemp.close();

    remove("dados.txt");
    rename("temp.txt", "dados.txt");

    if (excluido) {
        cout << "Livro excluído com sucesso!" << endl;
    } else {
        cout << "Livro não encontrado!" << endl;
    }
}

void listarLivros() {
    struct livros livro;
    ifstream arquivo("dados.txt", ios::binary);
    if (!arquivo) {
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    cout << "\n=== Listagem de Livros ===\n";
    while (arquivo.read(reinterpret_cast<char*>(&livro), sizeof(livro))) {
        cout << "Codigo: " << livro.idlivro << "\n";
        cout << "Titulo: " << livro.titulo << "\n";
        cout << "Autor: " << livro.autores << "\n";
        cout << "Editora: " << livro.editora << "\n";
        cout << "-------------------------------------\n";
    }
    arquivo.close();
}

int opcao;
int main() {
    do {
        cout << " =-=-=-=-=-=-=-=-=-=-=-=-\n";
        cout << "| 1 - Cadastro           |\n";
        cout << "| 2 - Alteracao          |\n";
        cout << "| 3 - Excluir            |\n";
        cout << "| 4 - Listar Livros      |\n";
        cout << "| 0 - Sair               |\n";
        cout << " =-=-=-=-=-=-=-=-=-=-=-=-\n";
        cin >> opcao;

        switch (opcao) {
            case 1:
                cadastrolivro();
                break;
            case 2:
                alterarLivro();
                break;
            case 3:
                excluirLivro();
                break;
            case 4:
                listarLivros();
                break;
            case 0:
                cout << "Saindo do sistema..." << endl;
                break;
            default:
                cout << "Opcao invalida, tente novamente." << endl;
                break;
        }
    } while (opcao != 0);

    return 0;
}
