#ifndef POLY_H
#define POLY_H

#include <iostream>
#include <string>

class Poly {
private:
    int grau;        // Grau do polinômio
    double *a;       // Array dinâmico de coeficientes

public:
    // Construtores e destrutor
    Poly();                              // Construtor padrão (polinômio vazio)
    explicit Poly(int grau);             // Construtor com grau específico
    Poly(const Poly &other);             // Construtor de cópia
    Poly(Poly &&other) noexcept;         // Construtor de movimento
    ~Poly();                             // Destrutor

    // Métodos de acesso e modificação
    int getGrau() const;                 // Retorna o grau do polinômio
    double getCoef(int i) const;         // Retorna o coeficiente de índice i
    void setCoef(int i, double valor);   // Define o coeficiente de índice i

    // Operadores sobrecarregados
    Poly& operator=(const Poly &other);  // Operador de atribuição por cópia
    Poly& operator=(Poly &&other) noexcept;  // Operador de atribuição por movimento
    double operator[](int i) const;      // Acesso aos coeficientes via índice
    bool operator==(const Poly &other) const; // Comparação de igualdade
    bool operator!=(const Poly &other) const; // Comparação de desigualdade
    double operator()(double x) const;   // Avaliação do polinômio para um dado x
    Poly operator-() const;              // Operador unário de negação
    Poly operator+(const Poly &other) const; // Operador binário de soma
    Poly operator-(const Poly &other) const; // Operador binário de subtração
    Poly operator*(const Poly &other) const; // Operador binário de multiplicação

    // Métodos utilitários
    void recriar(int novoGrau);          // Redefine o polinômio para um novo grau
    bool empty() const;                  // Verifica se o polinômio é vazio
    bool isZero() const;                 // Verifica se o polinômio é nulo
    double getValor(double x) const;     // Calcula o valor do polinômio para um dado valor de x

    // Entrada e saída de dados
    friend std::ostream& operator<<(std::ostream &out, const Poly &p);
    friend std::istream& operator>>(std::istream &in, Poly &p);
    bool salvar(const std::string &filename) const; // Salva polinômio em arquivo
    bool ler(const std::string &filename);          // Lê polinômio de arquivo
};

#endif // POLY_H
