#include <iostream>
#include <termios.h>
#include <unistd.h>

char getKey() {
    struct termios oldt, newt;
    char ch;
    
    tcgetattr(STDIN_FILENO, &oldt);  // Salva configurações atuais do terminal
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);  // Desativa buffer de linha e eco
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();  // Lê um caractere sem precisar de "Enter"

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // Restaura configurações do terminal
    return ch;
}

int main() {
    std::cout << "Pressione uma tecla (ou 'q' para sair):" << std::endl;
    while (true) {
        char tecla = getKey();
        std::cout << "Você pressionou: " << tecla << std::endl;
        if (tecla == 'q') break;
    }
    return 0;
}
