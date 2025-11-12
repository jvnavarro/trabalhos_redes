#include <fstream>
#include <iostream>
#include <string>
#include <cstring>          // Para memset()
#include <sys/socket.h>     // Para socket(), bind(), sendto(), recvfrom()
#include <netinet/in.h>     // Para a estrutura sockaddr_in
#include <arpa/inet.h>      // Para inet_pton() e htons()
#include <unistd.h>         // Para close()

const int PORTA = 8080;
const int TAM_BUFFER = 4096;
const char* IP_SERVIDOR = "127.0.0.1";

using namespace std;

struct SYN_ACK{
    int syn = 0;
    int ack = 0;
};


// Imprime mensagem de erro descritiva pra saber exatamente em qual parte do código está o erro, e qual erro de sistema é.
void die(const char *s)
{
    perror(s);
    exit(1);
}

int main()
{
    struct sockaddr_in server;
    struct SYN_ACK pacote_com;
    int sock;
    char buffer[TAM_BUFFER];
    socklen_t  server_len = sizeof(server);
    int sair_ou_ficar = 1;
    
    while(sair_ou_ficar)
    {
        //Criação socket cliente
        if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            die("Erro na criação do socket");
        }
        // Limpar e preencher estrutura do servidor
        memset(&server, 0, server_len);
        server.sin_family = AF_INET;
        server.sin_port = htons(PORTA);
        // Converte o IP de char para binário
        if(inet_pton(AF_INET, IP_SERVIDOR, &server.sin_addr))
        {
            die("Endereco IP invalida ou nao suportado");
        }
        pacote_com.syn = 1;
        pacote_com.ack = 0;
        if((sendto(sock, (char*) &pacote_com, sizeof(SYN_ACK), 0, (struct sockaddr *)&server, server_len)) < 0)
        {
            die("Falha no sendto do SYN");
        }
        
        cout << "Mensagem de Syn enviado." << endl;
        int bytes_lidos = recvfrom(sock, &pacote_com, sizeof(SYN_ACK), 0, (struct sockaddr *)&server, &server_len);
        if(bytes_lidos < 0)
        {
            die("Falha no recvfrom ")
        }


    }


    
}   