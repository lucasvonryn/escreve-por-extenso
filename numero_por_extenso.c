#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void unidade(int u, FILE *arquivo){
    switch(u){
        case 0: fprintf(arquivo, "zero"); break;
        case 1: fprintf(arquivo, "um"); break;
        case 2: fprintf(arquivo, "dois"); break;
        case 3: fprintf(arquivo, "tres"); break;
        case 4: fprintf(arquivo, "quatro"); break;
        case 5: fprintf(arquivo, "cinco"); break;
        case 6: fprintf(arquivo, "seis"); break;
        case 7: fprintf(arquivo, "sete"); break;
        case 8: fprintf(arquivo, "oito"); break;
        case 9: fprintf(arquivo, "nove"); break;
    }
}

void dezena(int d, int u, FILE *arquivo){
    switch(d){
        case 1:
        {
            switch(u){
                case 0: fprintf(arquivo, "dez"); break;
                case 1: fprintf(arquivo, "onze"); break;
                case 2: fprintf(arquivo, "doze"); break;
                case 3: fprintf(arquivo, "treze"); break;
                case 4: fprintf(arquivo, "quatorze"); break;
                case 5: fprintf(arquivo, "quinze"); break;
                case 6: fprintf(arquivo, "dezesseis"); break;
                case 7: fprintf(arquivo, "dezessete"); break;
                case 8: fprintf(arquivo, "dezoito"); break;
                case 9: fprintf(arquivo, "dezenove"); break;
            }
            break;
        }
        case 2: fprintf(arquivo, "vinte"); break;
        case 3: fprintf(arquivo, "trinta"); break;
        case 4: fprintf(arquivo, "quarenta"); break;
        case 5: fprintf(arquivo, "cinquenta"); break;
        case 6: fprintf(arquivo, "sessenta"); break;
        case 7: fprintf(arquivo, "setenta"); break;
        case 8: fprintf(arquivo, "oitenta"); break;
        case 9: fprintf(arquivo, "noventa"); break;
    }
}

void centena(int c, int d, int u, FILE *arquivo){
    switch(c){
        case 1:
        {
            if(d > 0 || d == 0 && u > 0){
                fprintf(arquivo, "cento");
            }else{
                fprintf(arquivo, "cem");
            }
            break;
        }
        case 2: fprintf(arquivo, "duzentos"); break;
        case 3: fprintf(arquivo, "trezentos"); break;
        case 4: fprintf(arquivo, "quatrocentos"); break;
        case 5: fprintf(arquivo, "quinhentos"); break;
        case 6: fprintf(arquivo, "seiscentos"); break;
        case 7: fprintf(arquivo, "setecentos"); break;
        case 8: fprintf(arquivo, "oitocentos"); break;
        case 9: fprintf(arquivo, "novecentos"); break;
    }
}

void milhar(int m, FILE *arquivo){
    switch(m){
        case 1: fprintf(arquivo, "mil"); break;
        case 2: fprintf(arquivo, "dois mil"); break;
        case 3: fprintf(arquivo, "tres mil"); break;
        case 4: fprintf(arquivo, "quatro mil"); break;
        case 5: fprintf(arquivo, "cinco mil"); break;
        case 6: fprintf(arquivo, "seis mil"); break;
        case 7: fprintf(arquivo, "sete mil"); break;
        case 8: fprintf(arquivo, "oito mil"); break;
        case 9: fprintf(arquivo, "nove mil"); break;
    }
}

void unidade_cent(int u_centavos, FILE *arquivo){
    unidade(u_centavos, arquivo);
}

void dezena_cent(int d_centavos, int u_centavos, FILE *arquivo){
    dezena(d_centavos, u_centavos, arquivo);
}

void numeroPorExtenso(int u, int d, int c, int m, int u_centavos, int d_centavos, FILE *arquivo){

    // IMPRIME OS REAIS POR EXTENSO
    int mais_de_um_real = m > 0 || c > 0 || d > 0 || u > 1;
    int so_unidade = m == 0 && c == 0 && d == 0;
    int so_dezena_e_unidade = m == 0 && c == 0;
    int so_nao_tem_milhar = m == 0;

    if(so_unidade){ // testa se so tem unidade
        unidade(u, arquivo);
    }
    else if(so_dezena_e_unidade){ // testa se so tem dezena com ou sem unidade
        dezena(d, u, arquivo);
        if(d != 1 && u > 0){
            fprintf(arquivo, " e ");
            unidade(u, arquivo);
        }
    }
    else if(so_nao_tem_milhar){ // testa se so tem centena com ou sem dezena e unidade
        centena(c, d, u, arquivo);
        if(d != 0){ // testa se tem dezena para imprimir
            fprintf(arquivo, " e ");
            dezena(d, u, arquivo);
            if(u != 0 && d != 1){ // testa se tem unidade para imprimir
                fprintf(arquivo, " e ");
                unidade(u, arquivo);
            }
        }
        else if(u > 0){ // se nao tiver centena e tiver unidade
            fprintf(arquivo, " e ");
            unidade(u, arquivo);
        }
    }else{ // se tiver milhar...
        milhar(m, arquivo);
        if(c != 0){ // testa se tem centena
            if(d == 0 && u == 0){
                fprintf(arquivo, " e ");
            }else{
                fprintf(arquivo, " ");
            }
            centena(c, d, u, arquivo);
            if(d != 0){ // quando tem a dezena
                fprintf(arquivo, " e ");
                dezena(d, u, arquivo);
                if(u != 0 && d  != 1){
                    fprintf(arquivo, " e ");
                    unidade(u, arquivo);
                }
            }
            else if(u != 0){ // quando nao tem a dezena mas tem a unidade
                fprintf(arquivo, " e ");
                unidade(u, arquivo);
            }
        }
        else if(d != 0){ // testa se tem dezena
            fprintf(arquivo, " e ");
            dezena(d, u, arquivo);
            if(u != 0 && d != 1){
                fprintf(arquivo, " e ");
                unidade(u, arquivo);
            }
        }
        else if(u != 0){ // testa se tem unidade
            fprintf(arquivo, " e ");
            unidade(u, arquivo);
        }
    }
    if(mais_de_um_real){
        fprintf(arquivo, " reais");
    }else{
        fprintf(arquivo, " real");
    }

    // IMPRIME OS CENTAVOS POR EXTENSO
    if(d_centavos > 0){
        fprintf(arquivo, " e ");
        if(d_centavos == 1){
            dezena_cent(d_centavos, u_centavos, arquivo);
        }else{
            dezena_cent(d_centavos, u_centavos, arquivo);
            if(u_centavos > 0){
                fprintf(arquivo, " e ");
                unidade_cent(u_centavos, arquivo);
            }
        }
    }
    else if(u_centavos > 0){
        fprintf(arquivo, " e ");
        unidade_cent(u_centavos, arquivo);
    }else{
        fprintf(arquivo, " e zero");
    }
    if(d_centavos > 0 || u_centavos > 1 || u_centavos == 0){
        fprintf(arquivo, " centavos.");
    }else{
        fprintf(arquivo, " centavo.");
    }
    fprintf(arquivo, "\n");
}

void sair(){
    printf("\nPrograma finalizado! Saindo...\n\n");
    exit(0);
}

int main(){
    int opcao = 1, u, d, c, m, inteiro;
    int u_centavos, d_centavos;
    float num;
    double decimal = 0.0;

    // ABRE O ARQUIVO COMO MODO "W" PARA LIMPA-LO
    FILE *arquivo = fopen("guarda_numero.txt", "w");
    if (arquivo == NULL) { // verifica se nao ha erros na criacao do arquivo
        printf("Erro ao criar ou abrir arquivo.\n");
        return 1;
    }
    fclose(arquivo); // fecha o arquivo

    while(opcao != 3){
        printf("-----------------------------------------------------\n");
        printf("[ 1 ] ESCREVER UM NUMERO POR EXTENSO\n");
        printf("[ 2 ] IMPRIMIR TODOS OS NUMEROS DO ARQUIVO EM TELA\n");
        printf("[ 3 ] SAIR\n");
        printf("-----------------------------------------------------\n\n");
        printf("Digite uma das opcoes: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
            {
                m = 0, c = 0, d = 0, u = 0, u_centavos = 0, d_centavos = 0;

                printf("Digite um numero de 0 a 9999.99: ");
                scanf("%f", &num);

                inteiro = floor(num); // separa a parte inteira de num
                decimal = (int)(((num - inteiro) * 100)); // separa a parte decimal de num
                // algumas vezes a parte decimal sai com um a mais ou um a menos por conta de arredondamento errado

                // SEPARA MILHAR, CENTENA, DEZENA E UNIDADE DOS REAIS
                while(inteiro > 0){
                    if(inteiro >= 1000 && inteiro <= 9999){
                        inteiro -= 1000;
                        m++;
                    }
                    else if(inteiro >= 100 && inteiro <= 999){
                        inteiro -= 100;
                        c++;
                    }
                    else if(inteiro >= 10 && inteiro <= 99){
                        inteiro -= 10;
                        d++;
                    }
                    else if(inteiro > 0 && inteiro <= 9){
                        inteiro -= 1;
                        u++;
                    }
                }

                // SEPARA DEZENA E UNIDADE DOS CENTAVOS
                while(decimal > 0){
                    if(decimal >= 10 && decimal <= 99){
                        decimal -= 10;
                        d_centavos++;
                    }
                    else if(decimal > 0 && decimal <= 9){
                        decimal -= 1;
                        u_centavos++;
                    }
                }

                // ABRE O ARQUIVO1 E GRAVA QUAL FOI O NUMERO DIGITADO
                FILE *arquivo1 = fopen("mostra_numero.txt", "w");
                if(arquivo1 == NULL){ // verifica se nao ha erros na criacao do arquivo
                    printf("Erro ao criar ou abrir arquivo.\n");
                    return 1;
                }
                numeroPorExtenso(u, d, c, m, u_centavos, d_centavos, arquivo);
                fclose(arquivo1); // fecha o arquivo

                // ABRE O ARQUIVO1 E MOSTRA PARA O USUARIO QUAL FOI O NUMERO DIGITADO
                arquivo1 = fopen("mostra_numero.txt", "r");
                if(arquivo1 == NULL){
                    printf("Erro ao criar ou abrir o arquivo.\n");
                    return 1;
                }
                char linha[100];
                printf("\nNumero digitado por extenso: ");
                while(fgets(linha, sizeof(linha), arquivo) != NULL){
                    printf("%s", linha);
                }
                printf("\n");
                fclose(arquivo1);

                // ABRE O ARQUIVO PARA ESCREVER NELE (MODO "A" PARA IR ADICIONANDO OS NUMEROS POR EXTENSO)
                FILE *arquivo = fopen("guarda_numero.txt", "a");
                if(arquivo == NULL){ // verifica se nao ha erros na criacao do arquivo
                    printf("Erro ao criar ou abrir arquivo.\n");
                    return 1;
                }
                numeroPorExtenso(u, d, c, m, u_centavos, d_centavos, arquivo); // chama o procedimento para escrever
                fclose(arquivo); // fecha o arquivo

                break;
            }
            case 2:
            {
                // ABRE O ARQUIVO ONDE ESTAO GUARDADOS OS NUMEROS E OS LE
                printf("\n");
                FILE *arquivo;
                arquivo = fopen("guarda_numero.txt", "r");

                if(arquivo == NULL){
                    printf("Erro ao abrir o arquivo.\n");
                    return 1;
                }
                char linha[100];
                printf("Os numeros digitados por extenso foram:\n\n");
                while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                    printf("%s", linha);
                }
                printf("\n");
                fclose(arquivo); // fecha o arquivo

                break;
            }
            case 3:
            {
                sair();
                break;
            }
            default:
                printf("Opcao invalida! Tente novamente...\n\n");
        }
    }
    
    system("pause");
    return 0;
}
