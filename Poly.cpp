#include "Poly.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <string>

// Construtor padrão (polinômio vazio)
Poly::Poly() : grau(-1), a(nullptr) {}

// Construtor com grau específico
Poly::Poly(int grau) : grau(grau), a(nullptr)
{
    if (grau < 0)
    {
        this->grau = -1;
        a = nullptr;
    }
    else
    {
        a = new double[grau + 1];
        for (int i = 0; i <= grau; ++i)
        {
            a[i] = (i == grau) ? 1.0 : 0.0;  // Último coeficiente 1.0, os outros 0.0
        }
    }
}

// Construtor de cópia
Poly::Poly(const Poly &other) : grau(other.grau), a(nullptr)
{
    if (grau >= 0)
    {
        a = new double[grau + 1];
        for (int i = 0; i <= grau; ++i)
        {
            a[i] = other.a[i];
        }
    }
}

// Construtor de movimento
Poly::Poly(Poly &&other) noexcept : grau(other.grau), a(other.a)
{
    other.grau = -1;
    other.a = nullptr;
}

// Destrutor
Poly::~Poly()
{
    delete[] a;
}

// Operador de atribuição por cópia
Poly& Poly::operator=(const Poly &other)
{
    if (this != &other)
    {
        delete[] a;
        grau = other.grau;
        if (grau >= 0)
        {
            a = new double[grau + 1];
            for (int i = 0; i <= grau; ++i)
            {
                a[i] = other.a[i];
            }
        }
        else
        {
            a = nullptr;
        }
    }
    return *this;
}

// Operador de atribuição por movimento
Poly& Poly::operator=(Poly &&other) noexcept
{
    if (this != &other)
    {
        delete[] a;
        grau = other.grau;
        a = other.a;
        other.grau = -1;
        other.a = nullptr;
    }
    return *this;
}

// Método para obter o grau
int Poly::getGrau() const
{
    return grau;
}

// Método para obter o coeficiente i
double Poly::getCoef(int i) const
{
    if (i < 0 || i > grau) return 0.0;
    return a[i];
}

// Método para definir o coeficiente i
void Poly::setCoef(int i, double valor)
{
    if (i < 0 || i > grau)
    {
        std::cerr << "Invalido indice: " << i << std::endl;
        return;
    }
    a[i] = valor;
}

// Operador unário de negação
Poly Poly::operator-() const
{
    Poly resultado(grau);
    for (int i = 0; i <= grau; ++i)
    {
        resultado.a[i] = -a[i];
    }
    return resultado;
}

// Operador de soma
Poly Poly::operator+(const Poly &other) const
{
    int maxGrau = std::max(grau, other.grau);
    Poly resultado(maxGrau);
    for (int i = 0; i <= maxGrau; ++i)
    {
        resultado.a[i] = this->getCoef(i) + other.getCoef(i);
    }
    return resultado;
}

// Operador de subtração
Poly Poly::operator-(const Poly &other) const
{
    int maxGrau = std::max(grau, other.grau);
    Poly resultado(maxGrau);
    for (int i = 0; i <= maxGrau; ++i)
    {
        resultado.a[i] = this->getCoef(i) - other.getCoef(i);
    }
    return resultado;
}

// Operador de multiplicação
Poly Poly::operator*(const Poly &other) const
{
    if (this->empty() || other.empty()) return Poly();
    int newGrau = this->grau + other.grau;
    Poly resultado(newGrau);
    for (int i = 0; i <= newGrau; ++i) resultado.a[i] = 0.0;
    for (int i = 0; i <= this->grau; ++i)
    {
        for (int j = 0; j <= other.grau; ++j)
        {
            resultado.a[i + j] += this->a[i] * other.a[j];
        }
    }
    return resultado;
}

// Operadores de igualdade
bool Poly::operator==(const Poly &other) const
{
    if (grau != other.grau) return false;
    for (int i = 0; i <= grau; ++i)
    {
        if (a[i] != other.a[i]) return false;
    }
    return true;
}

// Operador de desigualdade
bool Poly::operator!=(const Poly &other) const
{
    return !(*this == other);
}

// Sobrecarga do operador []
double Poly::operator[](int i) const
{
    return getCoef(i);
}

// Sobrecarga do operador ()
double Poly::operator()(double x) const
{
    if (a == nullptr) return 0.0;
    double resultado = 0.0;
    double potenciaX = 1.0;  // Inicializa x^0
    for (int i = 0; i <= grau; ++i)
    {
        resultado += a[i] * potenciaX;
        potenciaX *= x;  // Atualiza a potência de x
    }
    return resultado;
}


// Método recriar
void Poly::recriar(int novoGrau)
{
    delete[] a;
    grau = novoGrau;
    if (grau < 0)
    {
        a = nullptr;
    }
    else
    {
        a = new double[grau + 1];
        for (int i = 0; i <= grau; ++i)
        {
            a[i] = (i == grau) ? 1.0 : 0.0;
        }
    }
}

// Função de impressão
std::ostream& operator<<(std::ostream &out, const Poly &p)
{
    if (p.empty()) return out;
    for (int i = p.grau; i >= 0; --i)
    {
        if (p.a[i] != 0)
        {
            if (i != p.grau && p.a[i] > 0) out << "+";
            if (i == 0 || std::abs(p.a[i]) != 1.0) out << p.a[i];
            if (i > 0) out << "x";
            if (i > 1) out << "^" << i;
        }
    }
    return out;
}

// Operador de entrada
std::istream& operator>>(std::istream &in, Poly &p)
{
    for (int i = p.grau; i >= 0; --i)
    {
        std::cout << "x^" << i << ": ";
        in >> p.a[i];
    }
    return in;
}

// Salvar o polinômio em arquivo
bool Poly::salvar(const std::string &filename) const
{
    std::ofstream file(filename);
    if (!file) return false;
    file << "POLY " << grau << "\n";
    for (int i = 0; i <= grau; ++i)
    {
        file << a[i] << " ";
    }
    file << "\n";
    return true;
}

// Ler o polinômio de arquivo
bool Poly::ler(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file) return false;
    std::string header;
    file >> header;
    if (header != "POLY") return false;
    int newGrau;
    file >> newGrau;
    recriar(newGrau);
    for (int i = 0; i <= grau; ++i)
    {
        file >> a[i];
    }
    return true;
}

// Métodos utilitários
bool Poly::empty() const
{
    return grau < 0;
}

bool Poly::isZero() const
{
    return grau == 0 && a[0] == 0.0;
}

// Avaliar o valor do polinômio para um dado x
double Poly::getValor(double x) const
{
    if (empty()) return 0.0;
    double resultado = 0.0;
    for (int i = 0; i <= grau; ++i)
    {
        resultado += a[i] * std::pow(x, i);
    }
    return resultado;
}
