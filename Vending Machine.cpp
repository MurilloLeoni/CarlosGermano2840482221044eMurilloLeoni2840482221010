//Carlos Germano Gasparelho de Souza (RA: 2840482221044) e Murillo Leoni (RA: 2840482221010)
//Projeto Avaliativo Semestral - Vending Machine

#include <iostream>

#define MAX 5

using namespace std;
  
//Função para mostrar menu do ADM
int menuAdministrador() {
    int op;
    cout << "* * * * * ADIMINISTRADOR * * * * *\n"
         << "\n\n1-Repor produtos\n"
         << "2-Listar Produtos\n"
         << "3-Faturamento da Máquina\n"
         << "4-Sacar dinheiro\n"
         << "9-Sair\n"
         << "Sua opção: \n";

    cin >> op;
    return op;
}
//Função para mostrar menu do usuário
int menuUsuario() {  
    int op;
    cout << "\n\n1-Comprar Produto\n"
         << "9-Sair\n"
         << "Sua opção: ";
    cin >> op;
    return op;
}
//Função para limpar tela
void limpatela() {    
    system("cls");
    system("clear");
}
//Função para exibir os produtos da máquina e suas qntds e preços
void exibeProdutos(string produtos[], int quantidade[], float valores[]) {
    for (int i = 0; i < MAX; i++) {
        cout << "COD: " << i + 1 << " - " << produtos[i] << " / Quantidade: " << quantidade[i] << " / Valor: R$ "
             << valores[i] << "\n";
    }
}
//Função para repor produtos do modo ADM
void reporProdutos(string produtos[], int* quantidades) {

    cout << "* * * * * Repor Produtos * * * * *" << endl;
    for (int i = 0; i < MAX; i++) {
        cout << "Digite a quantidade para o produto " << produtos[i] << ": ";
        cin >> *(quantidades + i);
    }
    limpatela();
}


struct banco {           //estrutura para armazenar historico de vendas da maquina
    float rendimentos = 0; //valor em R$
    int qtdvendidos = 0;  //numero de vendas
};

banco bancos[1];    //vetor onde é guardado o rendimento e numero de vendas

void carrinho(string produtos[], int quantidade[], float valores[]) {    //funcao de carrinho e validação de compra
    int i = 0, cod = 0;
    float pagamento = 0;
    float troco = 0;
    float renda = 0;


    cout << "* * * * Informe codigo do produto! * * * *\n\n";
    cin >> i;
    limpatela();
    cod = i - 1;                     //cod -1 para se referir a posicao do produto no vetor

    if (quantidade[cod] > 0) {    //se estoque maior que 0, ocorre a venda
        cout << "O valor de " << produtos[cod] << " eh R$ " << valores[cod] << ".\n\n";
        cout << "Coloque R$ " << valores[cod] << " na maquininha e aperte enter. \n\n";
        cout << "Esperando valor... \n";
        cin >> pagamento;

        if (pagamento >= valores[cod]) { //se valor maior que produto, vai retornar o troco
            troco = pagamento - valores[cod];
            limpatela();
            cout << "\n\n             * * * * Troco de R$ " << troco << "  * * * * \n\n";
            cout << "\n\n* * * * Obrigado por comprar! Pegue o produto na portinha! * * * *\n\n";

        } else {
            limpatela();
            cout << "Pagamento insuficiente! O valor do produto é R$ " << valores[cod] << "\n\n";
            cout << "Devoluçao de R$ " << pagamento << " na portinha";
            return;
        }  // retorna sem realizar a compra

        quantidade[cod] -= 1;    //subtrai unidade vendida do estoque

        bancos[0].rendimentos += valores[cod];   //imcrementa venda no faturamento
        bancos[0].qtdvendidos += 1;              //imcrementa venda na quantidade vendida
    } else {
        cout << "Desculpe... Produto indisponivel.\n\n";    //se estoque menor que 0, nao ocorre venda
        //exibeProdutos(produtos,quantidade,valores);
        //cout << endl << endl;
    }
}

int main() {
    string produtos[MAX] = {"PRODUTO 1", "PRODUTO 2", "PRODUTO 3", "PRODUTO 4", "PRODUTO 5"};
    int quantidade[MAX] = {5, 5, 5, 5, 5};
    float valores[MAX] = {1.00, 2.00, 3.00, 4.00, 5.00};
    int op_modo, op_usuario, op_administrador;
    
    //Laço de repetição para escolha de modo
    do {
        cout << "* * * * * ESCOLHA DE MODO * * * * *\n";
        cout << "1-Modo Usuário\n";
        cout << "2-Modo Administrador\n";
        cout << "9-Sair\n";
        cout << "Sua opção: ";
        cin >> op_modo;
        limpatela();

        switch (op_modo) {
            case 1:
                //Laço de repetição para escolha de opção modo usuário
                do {
                    cout << "* * * * * PRODUTOS * * * * *\n\n";
                    exibeProdutos(produtos, quantidade, valores);
                    op_usuario = menuUsuario();
                    //vai para Listar produtos
                    switch (op_usuario) {
                        case 1:
                            cout << endl << endl;
                            carrinho(produtos, quantidade, valores);
                            cout << endl << endl;
                            break;

                        case 9:
                            limpatela();
                            cout << "Saindo do modo usuário...\n\n";
                            break;

                        default:
                            cout << "Opção inválida!!\nTente denovo!\n";
                    }
                } while (op_usuario != 9);
                break;

            case 2:
                //Laço de repetição para escolha de opção modo ADM
                do {
                    op_administrador = menuAdministrador();
                    switch (op_administrador) {
                        case 1:
                            limpatela();
                            reporProdutos(produtos, quantidade);
                            break;

                        case 2:           //vai para Listar produtos
                            limpatela();
                            exibeProdutos(produtos, quantidade, valores);
                            cout << endl << endl;
                            break;

                        case 3:          //vai para faturamento da maquina
                            limpatela();
                            cout << "* * * * * FATURAMENTO BRUTO * * * * *\n\n";
                            cout << "* Faturamento_______R$ " << bancos[0].rendimentos << ".\n";
                            cout << "* Numero de vendas____ " << bancos[0].qtdvendidos << ".\n\n";
                            break;

                        case 4:         //opção para sacar o dinheiro do cofre
                            limpatela();
                            bancos[0].rendimentos = 0;
                            bancos[0].qtdvendidos = 0;
                            cout << "* * * * * COFRE ABERTO E ZERADO * * * * *\n\n";
                            break;

                        case 9:
                            limpatela();
                            cout << "Saindo do modo administrador...\n\n";
                            break;

                        default:
                            cout << "Opção inválida!!\nTente denovo!\n";
                    }
                } while (op_administrador != 9);
                break;
        }
    } while (op_modo != 0);

    return 0;
}
