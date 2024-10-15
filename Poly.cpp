#include "Poly.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>

// Construtor padrão (polinômio vazio)
Poly::Poly() : grau(-1), a(nullptr) {}

// Construtor com grau específico
Poly::Poly(int grau) : grau(grau), a(nullptr)
{
    if (grau < 0)
    {
        this->grau = -1; // Polinômio inválido
    }
    else
    {
        a = new double[grau + 1]; // Aloca espaço para os coeficientes
        for (int i = 0; i <= grau; ++i)
        {
            if (grau == 0) 
            {
                a[i] = 0.0; // Para grau zero, a0 deve ser 0.0
            }
            else 
            {
                a[i] = (i == grau) ? 1.0 : 0.0; // Último coeficiente é 1.0, os outros são 0.0
            }
        }
    }
}

// Construtor de cópia
Poly::Poly(const Poly &other) : grau(other.grau), a(nullptr)
{
    if (grau >= 0) // Verifica se o grau é válido (maior ou igual a 0)
    {
        a = new double[grau + 1]; // Aloca memória para armazenar 'grau + 1' coeficientes

        for (int i = 0; i <= grau; ++i) // Copia cada coeficiente do polinômio 'other' para o novo polinômio
        {
            a[i] = other.a[i]; // Copia o coeficiente de 'other' para o novo array 'a'
        }
    }
}

// Construtor de movimento
Poly::Poly(Poly &&other) noexcept : grau(other.grau), a(other.a)
{
    other.grau = -1; // Define o grau do polinômio 'other' como -1, indicando que ele está vazio ou inválido
    other.a = nullptr; // Define o ponteiro 'a' do polinômio 'other' como nullptr, liberando a memória anteriormente alocada
}

// Destrutor
Poly::~Poly()
{
    delete[] a; // Libera a memória alocada para o array de coeficientes 'a'
}

// Operador de atribuição por cópia
Poly& Poly::operator=(const Poly &other)
{
    if (this != &other) // Verifica se o objeto atual não é o mesmo que o objeto 'other'
    {
        delete[] a; // Libera a memória alocada para o array de coeficientes 'a' do objeto atual
        grau = other.grau; // Copia o grau do polinômio 'other' para o objeto atual
        if (grau >= 0) // Verifica se o grau é válido (não negativo)
        {
            a = new double[grau + 1]; // Aloca memória para o array de coeficientes 'a' do objeto atual
            for (int i = 0; i <= grau; ++i) // Copia cada coeficiente do polinômio 'other' para o novo array 'a'
            {
                a[i] = other.a[i]; // Copia o coeficiente de 'other' para o novo array 'a'
            }
        }
        else // Se o grau for negativo
        {
            a = nullptr; // Define o ponteiro 'a' como nullptr, indicando que não há coeficientes
        }
    }
    return *this; // Retorna o objeto atual para permitir atribuições encadeadas
}

// Operador de atribuição por movimento
Poly& Poly::operator=(Poly &&other) noexcept
{
    if (this != &other) // Verifica se o objeto atual não é o mesmo que o objeto 'other'
    {
        delete[] a; // Libera a memória alocada para o array de coeficientes 'a' do objeto atual
        grau = other.grau; // Copia o grau do polinômio 'other' para o objeto atual
        a = other.a; // Copia o ponteiro do array de coeficientes 'a' de 'other' para o objeto atual
        other.grau = -1; // Define o grau do polinômio 'other' como -1, indicando que ele está vazio ou inválido
        other.a = nullptr; // Define o ponteiro 'a' do polinômio 'other' como nullptr, liberando a memória anteriormente alocada
    }
    return *this; // Retorna o objeto atual para permitir atribuições encadeadas
}

// Método para obter o grau
int Poly::getGrau() const
{
    return grau; //Retorna o grau do polinômio
}

// Método para obter o coeficiente i
double Poly::getCoef(int i) const
{
    if (i < 0 || i > grau) return 0.0; // Se o índice for inválido, retorna 0.0
    return a[i]; // Retorna o coeficiente de índice i
}

// Método para definir o coeficiente i
void Poly::setCoef(int i, double valor)
{
    if (i < 0 || i > grau) // Se o índice for inválido
    {
        std::cerr << "Índice inválido: " << i << std::endl; 
        return;
    }
    if (i == grau && valor == 0.0 && grau > 0) // Se o índice for igual ao grau e o valor for 0.0 e o grau for maior que 0
    {
        std::cerr << "Valor inválido: " << valor << std::endl;
        return;
    }
    a[i] = valor;
}

// Sobrecarga do operador []
double Poly::operator[](int i) const
{
    return getCoef(i); // Retorna o coeficiente de índice i
}

// Método recriar
void Poly::recriar(int novoGrau)
{
    Poly temp(novoGrau); // Cria um objeto temporário 'temp' do tipo Poly com o novo grau 'novoGrau'
    *this = std::move(temp); // Move o conteúdo de 'temp' para o objeto atual usando o operador de atribuição por movimento
}

// Operador de igualdade
bool Poly::operator==(const Poly &other) const
{
    if (grau != other.grau) return false; // Verifica se os graus dos dois polinômios são diferentes; se forem, retorna false
    for (int i = 0; i <= grau; ++i) // Itera sobre todos os coeficientes dos polinômios
    {
        if (a[i] != other.a[i]) return false; // Verifica se algum coeficiente correspondente é diferente; se for, retorna false
    }
    return true; // Se todos os coeficientes forem iguais, retorna true
}

// Operador de desigualdade
bool Poly::operator!=(const Poly &other) const
{
    return !(*this == other); // Retorna o valor inverso da comparação de igualdade entre o objeto atual e 'other'
}

// Método empty
bool Poly::empty() const
{
    return grau < 0; // Retorna verdadeiro se o grau for menor que 0
}

// Método isZero
bool Poly::isZero() const
{
    return grau == 0 && a[0] == 0.0; // Retorna true se o polinômio for de grau 0 e o coeficiente a[0] for 0.0, indicando que o polinômio é zero
}

// Método getValor
double Poly::getValor(double x) const
{
    if (empty()) return 0.0; // Se o polinômio estiver vazio, retorna 0.0
    double resultado = 0.0; // Inicializa a variável 'resultado' com 0.0
    double potenciaX = 1.0;  // Inicializa a variável 'potenciaX' com 1.0, representando x^0
    for (int i = 0; i <= grau; ++i) // Itera sobre todos os coeficientes do polinômio
    {
        resultado += a[i] * potenciaX; // Adiciona o termo a[i] * x^i ao resultado
        potenciaX *= x;  // Atualiza a potência de x para a próxima iteração (x^(i+1))
    }
    return resultado; // Retorna o valor calculado do polinômio para o valor de x fornecido
}

// Sobrecarga do operador ()
double Poly::operator()(double x) const
{
    return getValor(x); // Chama o método getValor(x) para calcular e retornar o valor do polinômio para o valor de x fornecido
}

// Sobrecarga do operador <<
std::ostream& operator<<(std::ostream &out, const Poly &p)
{
    if (p.empty()) return out; // Se o polinômio estiver vazio, retorna o stream de saída sem modificar
    for (int i = p.grau; i >= 0; --i) // Itera sobre os coeficientes do polinômio do maior grau para o menor
    {
        if (p.a[i] != 0.0) // Se o coeficiente não for zero
        {
            if (i != p.grau && p.a[i] > 0.0) out << "+"; // Adiciona um sinal de mais se não for o primeiro termo e o coeficiente for positivo
            if (i == 0 || std::abs(p.a[i]) != 1.0) out << std::abs(p.a[i]); // Adiciona o coeficiente se for o termo constante ou se o coeficiente não for 1 ou -1
            if (i > 0) out << "x"; // Adiciona 'x' se o grau for maior que 0
            if (i > 1) out << "^" << i; // Adiciona '^' seguido do grau se o grau for maior que 1
        }
    }
    return out; // Retorna o stream de saída modificado
}

// Sobrecarga do operador >>
std::istream& operator>>(std::istream &in, Poly &p)
{
    if (p.empty()) return in; // Se o polinômio estiver vazio, retorna o stream de entrada sem modificar
    for (int i = p.grau; i >= 0; --i) // Itera sobre os coeficientes do polinômio do maior grau para o menor
    {
        double coef; // Declara uma variável para armazenar o coeficiente
        do {
            std::cout << "x^" << i << ": "; // Solicita ao usuário para inserir o coeficiente do termo x^i
            in >> coef; // Lê o coeficiente do stream de entrada
            if (i == p.grau && coef == 0.0 && p.grau > 0) // Verifica se o coeficiente do maior grau é zero e o grau é maior que 0
            {
                std::cerr << "Coeficiente de maior grau não pode ser 0.0. Digite novamente.\n"; // Exibe uma mensagem de erro
            }
            else
            {
                break; // Sai do loop se o coeficiente for válido
            }
        } while (true); // Continua solicitando até que um coeficiente válido seja inserido
        p.a[i] = coef; // Atribui o coeficiente ao array de coeficientes do polinômio
    }
    return in; // Retorna o stream de entrada modificado
}

// Método salvar
bool Poly::salvar(const std::string &filename) const
{
    std::ofstream file(filename); // Abre um arquivo de saída com o nome especificado por 'filename'
    if (!file) return false; // Verifica se o arquivo foi aberto com sucesso; se não, retorna false
    file << "POLY " << grau << "\n"; // Escreve a string "POLY" seguida do grau do polinômio no arquivo
    for (int i = 0; i <= grau; ++i) // Itera sobre todos os coeficientes do polinômio
    {
        file << a[i] << " "; // Escreve cada coeficiente no arquivo, separado por um espaço
    }
    file << "\n"; // Escreve uma nova linha no final do arquivo
    return true; // Retorna true indicando que a operação foi bem-sucedida
}

// Método ler
bool Poly::ler(const std::string &filename)
{
    std::ifstream file(filename); // Abre um arquivo de entrada com o nome especificado por 'filename'
    if (!file) return false; // Verifica se o arquivo foi aberto com sucesso; se não, retorna false

    std::string header; // Declara uma string para armazenar o cabeçalho
    int newGrau; // Declara uma variável para armazenar o novo grau do polinômio
    file >> header >> newGrau; // Lê o cabeçalho e o novo grau do arquivo

    if (header != "POLY" || !file) // Verifica se o cabeçalho é "POLY" e se a leitura do arquivo foi bem-sucedida
    {
        return false; // Se não, retorna false
    }

    double *newA = nullptr; // Declara um ponteiro para armazenar o novo array de coeficientes
    if (newGrau >= 0) // Verifica se o novo grau é válido (não negativo)
    {
        newA = new double[newGrau + 1]; // Aloca memória para o novo array de coeficientes
        for (int i = 0; i <= newGrau; ++i) // Itera sobre todos os coeficientes do novo polinômio
        {
            if (!(file >> newA[i])) // Lê cada coeficiente do arquivo; se a leitura falhar
            {
                delete[] newA; // Libera a memória alocada para o novo array
                return false; // Retorna false
            }
        }
        if (newGrau > 0 && newA[newGrau] == 0.0) // Verifica se o coeficiente do maior grau é zero e o grau é maior que 0
        {
            delete[] newA; // Libera a memória alocada para o novo array
            return false; // Retorna false
        }
    }

    delete[] a; // Libera a memória alocada para o array de coeficientes atual
    grau = newGrau; // Atualiza o grau do polinômio
    a = newA; // Atualiza o array de coeficientes
    return true; // Retorna true indicando que a operação foi bem-sucedida
}

// Operador unário de negação
Poly Poly::operator-() const
{
    if (empty()) return Poly(); // Se o polinômio estiver vazio, retorna um polinômio vazio
    Poly resultado(grau); // Cria um novo polinômio 'resultado' com o mesmo grau do polinômio atual
    for (int i = 0; i <= grau; ++i) // Itera sobre todos os coeficientes do polinômio atual
    {
        resultado.a[i] = -a[i]; // Define cada coeficiente de 'resultado' como o negativo do coeficiente correspondente do polinômio atual
    }
    return resultado; // Retorna o novo polinômio 'resultado'
}

// Operador binário de soma
Poly Poly::operator+(const Poly &other) const
{
    if (empty()) return other;
    if (other.empty()) return *this;

    int maxGrau = std::max(grau, other.grau);
    Poly resultado(maxGrau);
    for (int i = 0; i <= maxGrau; ++i)
    {
        resultado.a[i] = this->getCoef(i) + other.getCoef(i);
    }

    // Ajustar o grau do polinômio resultante
    while (resultado.grau > 0 && resultado.a[resultado.grau] == 0.0)
    {
        resultado.grau--;
    }

    return resultado;
}

// Operador binário de subtração
Poly Poly::operator-(const Poly &other) const
{
    if (empty()) return other; // Se o polinômio atual estiver vazio, retorna o polinômio 'other'
    if (other.empty()) return *this; // Se o polinômio 'other' estiver vazio, retorna o polinômio atual

    int maxGrau = std::max(grau, other.grau); // Determina o grau máximo entre os dois polinômios
    Poly resultado(maxGrau); // Cria um novo polinômio 'resultado' com o grau máximo

    for (int i = 0; i <= maxGrau; ++i) // Itera sobre todos os coeficientes até o grau máximo
    {
        resultado.a[i] = this->getCoef(i) + other.getCoef(i); // Soma os coeficientes correspondentes dos dois polinômios e armazena no polinômio 'resultado'
    }

    // Ajustar o grau do polinômio resultante
    while (resultado.grau > 0 && resultado.a[resultado.grau] == 0.0) // Reduz o grau do polinômio resultante se os coeficientes de maior grau forem zero
    {
        resultado.grau--; // Decrementa o grau do polinômio resultante
    }

    return resultado; // Retorna o polinômio resultante
}

// Operador binário de multiplicação
Poly Poly::operator*(const Poly &other) const
{
    if (empty() || other.empty()) return Poly(); // Se qualquer um dos polinômios estiver vazio, retorna um polinômio vazio
    if (isZero() || other.isZero()) return Poly(0); // Se qualquer um dos polinômios for zero, retorna um polinômio de grau 0

    int newGrau = grau + other.grau; // Calcula o grau do polinômio resultante como a soma dos graus dos dois polinômios
    Poly resultado(newGrau); // Cria um novo polinômio 'resultado' com o grau calculado

    for (int i = 0; i <= newGrau; ++i) // Inicializa todos os coeficientes do polinômio resultante com zero
    {
        resultado.a[i] = 0.0; // Inicializa com zeros
    }

    for (int i = 0; i <= grau; ++i) // Itera sobre todos os coeficientes do polinômio atual
    {
        for (int j = 0; j <= other.grau; ++j) // Itera sobre todos os coeficientes do polinômio 'other'
        {
            resultado.a[i + j] += a[i] * other.a[j]; // Multiplica os coeficientes correspondentes e adiciona ao coeficiente apropriado do polinômio resultante
        }
    }

    return resultado; // Retorna o polinômio resultante
}