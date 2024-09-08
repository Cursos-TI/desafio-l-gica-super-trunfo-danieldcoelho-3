#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura Carta
typedef struct {
    char estado;
    char codigo[10];
    char nomeCidade[50];
    long int populacao;
    float area;
    float pib;
    long int pontosTuristicos;
    float densidade;
    float pibpercapita;
    float superPoder;
} Carta;

// Define valor inicial das variáveis
Carta clearVars() {
    Carta carta;
    carta.estado = '\0';
    carta.codigo[0] = '\0';
    carta.nomeCidade[0] = '\0';
    carta.populacao = 0;
    carta.area = 0;
    carta.pib = 0;
    carta.pontosTuristicos = 0;
    carta.densidade = 0;
    carta.pibpercapita = 0;
    carta.superPoder = 0;
    return carta;
}

// Calcula densidade populacional
float densiPopula(Carta carta) {
    if (carta.populacao == 0 || carta.area == 0) {
        return 0;
    }
    return ((float)carta.populacao * 1e6) / carta.area;
}

// Calcula PIB per capita
float PIBpercapita(Carta carta) {
    if (carta.populacao == 0 || carta.pib == 0) {
        return 0;
    }
    return (carta.pib * 1e9) / ((float)carta.populacao * 1e6);
}

// Calcula o super poder
float calcularSuperPoder(Carta carta) {
    if (carta.populacao == 0 || carta.area == 0) {
        return 0;
    }
    float densidadeInvertida = carta.area / (float)carta.populacao;
    return carta.populacao + carta.area + carta.pib + carta.pibpercapita + densidadeInvertida + carta.pontosTuristicos;
}

// Gera o código da cidade baseado no estado
void gerarCodCidades(char estado, char* codigo) {
    static int contadorCidades[4] = {0};
    int indiceEstado = estado - 'A';

    if (contadorCidades[indiceEstado] < 4) {
        contadorCidades[indiceEstado]++;

        sprintf(codigo, "%c%02d", estado, contadorCidades[indiceEstado]);
    } else {
        printf("Erro: Estado %c já atingiu o limite de 4 cidades.\n", estado);
    }
}

// Função para ler os dados para o cadastro da carta
Carta cadastrarCarta() {
    Carta carta = clearVars();
    printf("Digite o estado (1 caractere): ");
    scanf(" %c", &carta.estado);
    getchar();
    
    printf("Digite o nome da cidade: ");
    fgets(carta.nomeCidade, 50, stdin);

    printf("Digite a população: ");
    char populacaoStr[10];
    fgets(populacaoStr, 10, stdin);
    carta.populacao = atol(populacaoStr);
    
    printf("Digite a área em km²: ");
    scanf("%f", &carta.area);
    
    printf("Digite o PIB: ");
    scanf("%f", &carta.pib);
    
    printf("Digite o número de pontos turísticos: ");
    scanf("%ld", &carta.pontosTuristicos);

    carta.densidade = densiPopula(carta);
    carta.pibpercapita = PIBpercapita(carta);
    carta.superPoder = calcularSuperPoder(carta);

    return carta;
}

// Função para imprimir os dados da carta cadastrada
void exibirCarta(Carta carta) {
    char codigo[10];
    gerarCodCidades(carta.estado, codigo);
    printf("\n\n--- Dados da Carta ---\n");
    printf("Estado: %c\n", carta.estado);
    printf("Código da Carta: %s\n", codigo);
    printf("Nome da Cidade: %s", carta.nomeCidade);
    printf("População: %ld\n", carta.populacao);
    printf("Densidade populacional: %.2f pessoas/km²\n", carta.densidade);
    printf("Área: %.2f km²\n", carta.area);
    printf("PIB: %.2f bilhões de reais\n", carta.pib);
    printf("PIB per capita: %.2f reais\n", carta.pibpercapita);
    printf("Número de Pontos Turísticos: %ld\n", carta.pontosTuristicos);
    printf("Super Poder: %.2f\n", carta.superPoder);
    printf("--------------------\n\n");
}


// Função auxiliar para imprimir o resultado da comparação (usando operador ternário)
void imprimirResultado(const char* nomeCaracteristica, float valor1, float valor2, int* pontosCarta1, int* pontosCarta2) {
    printf("\n\n%s:\n", nomeCaracteristica);
    printf("Carta 1: %.2f\n", valor1);
    printf("Carta 2: %.2f\n", valor2);
    
    // Usando operador ternário para comparar e atualizar os pontos
    (valor1 > valor2) ? ((*pontosCarta1)++, printf("\nResultado: Carta 1 venceu nessa comparação.\n\n")) :
    (valor1 < valor2) ? ((*pontosCarta2)++, printf("\nResultado: Carta 2 venceu nessa comparação.\n\n")) :
    printf("\nResultado: Empate nessa comparação.\n\n");
}

// Função para comparar duas cartas com base em duas características selecionadas
void compararCartas(Carta carta1, Carta carta2, int caracteristica1, int caracteristica2) {
    int pontosCarta1 = 0;
    int pontosCarta2 = 0;

    // Comparar a primeira característica escolhida
    switch (caracteristica1) {
        case 1:
            imprimirResultado("Densidade populacional", carta1.densidade, carta2.densidade, &pontosCarta1, &pontosCarta2);
            break;
        case 2:
            imprimirResultado("PIB", carta1.pib, carta2.pib, &pontosCarta1, &pontosCarta2);
            break;
        case 3:
            imprimirResultado("PIB per capita", carta1.pibpercapita, carta2.pibpercapita, &pontosCarta1, &pontosCarta2);
            break;
        case 4:
            imprimirResultado("Área", carta1.area, carta2.area, &pontosCarta1, &pontosCarta2);
            break;
        case 5:
            imprimirResultado("Número de Pontos Turísticos", (float)carta1.pontosTuristicos, (float)carta2.pontosTuristicos, &pontosCarta1, &pontosCarta2);
            break;
        case 6:
            imprimirResultado("Super Poder", carta1.superPoder, carta2.superPoder, &pontosCarta1, &pontosCarta2);
            break;
        default:
            printf("Característica inválida para a primeira comparação.\n");
            return;
    }

    // Comparar a segunda característica escolhida
    switch (caracteristica2) {
        case 1:
            imprimirResultado("Densidade populacional", carta1.densidade, carta2.densidade, &pontosCarta1, &pontosCarta2);
            break;
        case 2:
            imprimirResultado("PIB", carta1.pib, carta2.pib, &pontosCarta1, &pontosCarta2);
            break;
        case 3:
            imprimirResultado("PIB per capita", carta1.pibpercapita, carta2.pibpercapita, &pontosCarta1, &pontosCarta2);
            break;
        case 4:
            imprimirResultado("Área", carta1.area, carta2.area, &pontosCarta1, &pontosCarta2);
            break;
        case 5:
            imprimirResultado("Número de Pontos Turísticos", (float)carta1.pontosTuristicos, (float)carta2.pontosTuristicos, &pontosCarta1, &pontosCarta2);
            break;
        case 6:
            imprimirResultado("Super Poder", carta1.superPoder, carta2.superPoder, &pontosCarta1, &pontosCarta2);
            break;
        default:
            printf("Característica inválida para a segunda comparação.\n");
            return;
    }

    // Determina a carta vencedora com base nos pontos
    (pontosCarta1 > pontosCarta2) ? printf("\nResultado Final: A Carta 1 é a vencedora!\n") :
    (pontosCarta1 < pontosCarta2) ? printf("\nResultado Final: A Carta 2 é a vencedora!\n") :
    printf("\nResultado Final: As duas cartas são equivalentes!\n");
}

int main() {
    Carta cartas[2];
    int opcao;

    do {
        printf("\n--- Menu ---\n");
        printf("1. Comparar duas cartas\n");
        printf("2. Fechar o programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                for (int cont = 0; cont < 2; cont++) {
                    printf("Cadastro da carta %d\n", cont + 1);
                    cartas[cont] = cadastrarCarta();
                    exibirCarta(cartas[cont]);
                }

                int caracteristica1, caracteristica2;
                printf("Selecione duas características para comparar:\n");
                printf("1. Densidade populacional\n");
                printf("2. PIB\n");
                printf("3. PIB per capita\n");
                printf("4. Área\n");
                printf("5. Número de Pontos Turísticos\n");
                printf("6. Super Poder\n");

                printf("Escolha a primeira característica: ");
                scanf("%d", &caracteristica1);
                printf("Escolha a segunda característica: ");
                scanf("%d", &caracteristica2);

                // Comparar as duas cartas com base nas características selecionadas
                compararCartas(cartas[0], cartas[1], caracteristica1, caracteristica2);
                break;

            case 2:
                printf("Fechando o programa...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 2);

    return 0;
}