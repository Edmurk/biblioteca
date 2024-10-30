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

void cadastrolivro(){
    char opc;
    struct livros livro;
    system("cls");
    

    cout << "Deseja cadastrar um livro?[S/N]: ";
        cin >> opc;
    
    while (opc=='S' || opc =='s')
    {
        cout << "Codigo:";
            cin >> livro.idlivro;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cout << "Area:";
            cin >> livro.area;
            cin.getline(livro.area, 30);

        cout << "Titulo:";
            cin >> livro.titulo;
            cin.getline(livro.titulo, 200);

        cout << "Autores:";
            cin >> livro.autores;
            cin.getline(livro.autores, 200);
        
        cout << "Editora:";
            cin >> livro.editora;
            cin.getline(livro.editora, 200);

        ofstream arquivo("dados.txt",ios::app);

        if (arquivo.is_open())
        {
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


int opcaoprinc, cod;
char opc;
struct livros livro;

int main(){

do
{
    cout << " =-=-=-=-=-=-=-=-=-=-=-=-\n";
    cout << "| 1 - cadastro           |\n";
    cout << "| 2 - alteracao          |\n";
    cout << "| 3 - excluir            |\n";
    cout << "| 4 - emprestimo         |\n";
    cout << "| 5 - devolucao          |\n";
    cout << "| 6 - consulta de livro  |\n";
    cout << "| 7 - livros disponiveis |\n";
    cout << "| 8 - listar livros      |\n";
    cout << "| 0 - sair               |\n";
    cout << " =-=-=-=-=-=-=-=-=-=-=-=-\n";
        cin >> opcaoprinc;

    switch (opcaoprinc)
    {
    case 1:
        cadastrolivro();
        break;
    
    default:
        cout << "opcao invalida, tente novamente";
        break;
    }




} while (opcaoprinc != 0);



    return 0;
}