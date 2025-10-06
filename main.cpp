#include <iostream>  
#include <string>
#include <iomanip>   

using namespace std;


class ContaBancaria;


class Cliente {
private:
   
    string nome;
    string cpf;

public:
    
    Cliente(string n, string c) : nome(n), cpf(c) {}

   
    string getNome() const {
        return nome;
    }

    string getCpf() const {
        return cpf;
    }
};


class ContaBancaria {
private:
    
    int numero;
    double saldo;
    Cliente titular; 

public:
    
    ContaBancaria(int num, const Cliente& cli, double sal = 0.0) 
        : numero(num), titular(cli), saldo(sal) {}

    
    void depositar(double valor) {
        if (valor > 0) {
            saldo += valor;
      
            cout << "Depósito de R$ " << fixed << setprecision(2) << valor 
                 << " realizado na conta " << numero << "." << endl;
        } 
    }

    void sacar(double valor) {
        if (valor > 0) {
            if (saldo >= valor) {
                saldo -= valor;
                cout << "Saque de R$ " << fixed << setprecision(2) << valor 
                     << " realizado na conta " << numero << "." << endl;
            } else {
                cout << "ERRO: Saldo insuficiente na conta " << numero 
                     << ". Saldo atual: R$ " << fixed << setprecision(2) << saldo << endl;
            }
        }
    }

    void transferir(double valor, ContaBancaria& destino) {
        if (valor > 0 && saldo >= valor) {
            saldo -= valor;
            destino.depositarInterno(valor);
            
            
            cout << "Transferido: R$ " << fixed << setprecision(2) << valor 
                 << " da conta " << numero << " para a conta " << destino.numero << endl;
        } else if (valor > 0) {
            cout << "ERRO: Saldo insuficiente para transferir R$ " << fixed << setprecision(2) << valor 
                 << " da conta " << numero << "." << endl;
        }
    }

    void transferir(double valor, ContaBancaria& destino1, ContaBancaria& destino2) {
        if (valor > 0 && saldo >= valor) {
            double valorPorConta = valor / 2.0; 
            
            saldo -= valor;
            
            destino1.depositarInterno(valorPorConta);
            destino2.depositarInterno(valorPorConta);
            
            
            cout << "Transferido: R$ " << fixed << setprecision(2) << valorPorConta 
                 << " para cada conta (" << destino1.numero << " e " << destino2.numero 
                 << ") da conta " << numero << endl;
        } else if (valor > 0) {
            cout << "ERRO: Saldo insuficiente para transferir R$ " << fixed << setprecision(2) << valor 
                 << " da conta " << numero << " (para duas contas)." << endl;
        }
    }
    void exibirSaldo() const {
        cout << "Saldo atual da conta " << setfill('0') << setw(4) << numero 
             << ": R$ " << fixed << setprecision(2) << saldo << endl;
    }
    void exibirInformacoes() const {
        cout << "Titular: " << titular.getNome() 
             << ", CPF: " << titular.getCpf() << endl;
        cout << "Número da Conta: " << setfill('0') << setw(4) << numero 
             << ", Saldo: R$ " << fixed << setprecision(2) << saldo << endl;
    }

private:
    void depositarInterno(double valor) {
        if (valor > 0) {
            saldo += valor;
        }
    }
};
int main() {
    
    Cliente cliente1("Ana", "111.111.111-11");
    Cliente cliente2("Bruno", "222.222.222-22");
    Cliente cliente3("Carla", "333.333.333-33");

    ContaBancaria conta1(1001, cliente1, 1000.0); 
    ContaBancaria conta2(1002, cliente2);        
    ContaBancaria conta3(1003, cliente3);        

    
    conta1.exibirSaldo(); 
    conta1.transferir(200.0, conta2);

   
    conta1.transferir(300.0, conta2, conta3);
    cout << endl;

    conta1.exibirInformacoes(); 
    conta2.exibirInformacoes(); 
    conta3.exibirInformacoes(); 
    
    return 0;
}