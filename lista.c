#include "cabecalho.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//========================================| Corpo do Programa |==========================================//
void inicializaTlista(TLista *L)
{
    L->inicioC = NULL;
    L->fimC = NULL;
}

void menu()
{
    printf("\t \t  ------------------------------------------------------------ \n");
    printf("\t \t | 0-Sair (Encerrar Aplicativo):                              |\n");
    printf("\t \t | 1-Inserir Curso:                                           |\n");
    printf("\t \t | 2-Listar Cursos:                                           |\n");
    printf("\t \t | 3-Excluir Curso Especifico:                                |\n");
    printf("\t \t | 4-Consultar Curso Especifico:                              |\n");
    printf("\t \t | 5-Inserir Aluno (Em curso):                                |\n");
    printf("\t \t | 6-Listar Alunos (Em curso):                                |\n");
    printf("\t \t | 7-Excluir Aluno Específico:                                |\n");
    printf("\t \t | 8-Consultar Aluno Especifico:                              |\n");
    printf("\t \t | 9-Inserir Disciplina Para Aluno:                           |\n");
    printf("\t \t | 10-Excluir Disciplina Especifica:                          |\n");
    printf("\t \t | 11-Consultar Disciplina Especifica:                        |\n");
    printf("\t \t | 12-Exibir Notas e Freq de Alunos em Disciplina Especifica: |\n");
    printf("\t \t  ------------------------------------------------------------ \n");
    printf("\t \t  \t \t \t \t Opcao: \n");
    printf("\t \t \t \t \t \t \t");
}

void free_geral(TLista *L)
{
    TDisciplina *auxD;
    TALuno *auxA;
    TCursos *atualC = L->inicioC;
    TALuno *atualA;
    TDisciplina *atualD;
    
    while (atualC->nome != NULL)
    {
        atualA = atualC->cadastradosA;
        while (atualA != NULL)
        {
            atualD = atualA->cadastradosD;
            while (atualD != NULL)
            {
                auxD = atualD->prox;
                free(atualD);
                atualD = auxD;
            }//while
            auxA = atualA->prox;
            free(atualA);
            atualA = auxA->prox;
        }//while
        L->inicioC = atualC->prox;
        free(atualC);
        atualC = L->inicioC;
    }//while
}

void inserir_curso(TLista *L)
{
    printf("\E[2J\E[2H");
    char nome[30];
    char coordenador [30];
    
    getchar();
    printf("Informe o nome do Curso \n");
    gets(nome);
    printf("Informe o nome do Coordenador \n");
    gets(coordenador);
    
    TCursos *novo = (TCursos *)malloc(sizeof(TCursos));
    TCursos *atual;
    novo->cadastradosA = NULL;
    
    atual = L->inicioC;
    
    strcpy(novo->nome, nome);
    strcpy(novo->coordenador, coordenador);
    novo->ante = NULL;
    novo->prox = NULL;
    
    if(atual == NULL)
    {
        L->inicioC = novo;
        L->fimC = novo;
    }//if
    else
    {
        while(atual != NULL)
        {
            if(strcmp(atual->nome, nome) == 1)
            {
                if(atual == L->inicioC)
                {
                    L->inicioC = novo;
                    novo->prox = atual;
                    atual->ante = novo;
                }//if
                else
                {
                    novo->prox = atual;
                    atual->ante->prox = novo;
                    atual->ante = novo;
                    break;
                }//else
            }//if
            else
            {
                if (atual->prox == NULL)
                {
                    atual->prox = novo;
                    novo->ante = atual;
                    novo->prox = NULL;
                    L->fimC = novo;
                    break;
                }//if
            }
            atual = atual->prox;
        }//while
    }//else
    printf("\E[2J\E[2H");
}

void listar_cursos(TLista L)
{
    printf("\E[2J\E[2H");
    TCursos *atual = (TCursos*)malloc(sizeof(TCursos));
    atual = L.inicioC;

    if (atual == NULL)
    {
        printf("A lista 'cursos' esta vazia!\n");
        return;
    }
    
    while(atual != NULL)
    {
        printf("\nNome: %s\nCoordenador(a): %s \n",atual->nome,
               atual->coordenador);
        atual = atual->prox;
    }//while
}

void excluir_curso_especifico(TLista *L)
{
    printf("\E[2J\E[2H");
    char nomeCurso [50];
    int aux = 0;
    TCursos *atualC = L->inicioC;
    TCursos *anteC = NULL;
    TDisciplina *atualD;
    TALuno *atualA;
    TDisciplina *auxD;
    TALuno *auxA;

    getchar();
    printf("Digite o nome do Curso que voce deseja excluir\n");
    gets(nomeCurso);

    while (atualC != NULL)
    {
        anteC = atualC->ante;

        if (strcmp(atualC->nome, nomeCurso) == 0)
        {
            aux += 1;

            atualA = atualC->cadastradosA;
            while (atualA != NULL)
            {
                atualD = atualA->cadastradosD;
                while (atualD != NULL)
                {
                    auxD = atualD->prox;
                    free(atualD);
                    atualD = auxD;
                }//while
                auxA = atualA->prox;
                free(atualA);
                atualA = auxA;
            }//while
            if(atualC == L->inicioC)
            {
                if(atualC->prox == NULL)
                {
                    L->inicioC = NULL;
                    L->fimC = NULL;
                    free(atualC);
                    printf("O curso (%s) foi excluido com sucesso!\n", nomeCurso);
                    break;
                }//if
                else
                {
                    L->inicioC = atualC->prox;
                    free(atualC);
                    atualC = L->inicioC;
                    printf("O curso (%s) foi excluido com sucesso!\n", nomeCurso);
                    break;
                }//else
            }
            else
            {
                if(atualC->prox != NULL)
                {
                    anteC->prox = atualC->prox;
                    free(atualC);
                    printf("O curso (%s) foi excluido com sucesso!\n", nomeCurso);
                    break;
                }//if

            }//else
            if(atualC == L->fimC)
            {
                anteC->prox = NULL;
                L->fimC = anteC;
                free(atualC);
                printf("O curso (%s) foi excluido com sucesso!\n", nomeCurso);
                break;
            }//if
        }//if
        anteC = atualC;
        atualC = atualC->prox;
    }//while
    if(aux == 0) printf("O curso (%s) nao existe!\n", nomeCurso);
}

void consultar_cursos_especifico(TLista *L)
{
    printf("\E[2J\E[2H");
    char nomeCurso[50];
    TCursos *atual = L->inicioC;
    TALuno *atualA;
    
    getchar();
    printf("Digite o nome do curso que voce deseja consultar\n");
    gets(nomeCurso);

    if (atual == NULL)
    {
        printf("A lista 'cursos' esta vazia!\n");
        return;
    }//if
    
    while(atual != NULL)
    {
        if (strcmp(atual->nome, nomeCurso) == 0)
        {
            printf("\nCurso: %s\nCoordenador(a): %s\n\n",atual->nome,
                   atual->coordenador);
            printf("Alunos:\n");
            atualA = atual->cadastradosA;

            if (atualA == NULL)
            {
                printf("A lista 'alunos' esta vazia!\n");
                return;
            }//if

            while (atualA != NULL)
            {
                printf("Nome: %s, sexo: %c\n", atualA->nome,
                       atualA->sexo);
                atualA = atualA->prox;
            }//while
        }//if
        atual = atual->prox;
    }//while
}

void inserir_aluno_em_curso(TLista *L)
{
    printf("\E[2J\E[2H");
    char nomeCurso [50];
    char nomeAluno [50];
    char sexo;
    int aux = 0;
    
    TALuno *novo = (TALuno *)malloc(sizeof(TALuno));
    
    getchar();
    printf("Digite o nome do curso que voce deseja inserir o Aluno.\n");
    gets(nomeCurso);
    
    TCursos *atualC = L->inicioC;
    TALuno *atualA = NULL;
    
    while(atualC != NULL)
    {
        if (strcmp(atualC->nome, nomeCurso) == 0)
        {
            aux += 1;
            printf("Digite o nome do Aluno que voce deseja inserir.\n");
            gets(nomeAluno);
            printf("Sexo 'M' ou 'F'\n");
            scanf("%c", &sexo);
            strcpy(novo->nome, nomeAluno);
            novo->sexo = sexo;
            novo->prox = NULL;
            novo->cadastradosD = NULL;
            novo->ante = NULL;
            
            if(atualC->cadastradosA == NULL)
            {
                atualC->cadastradosA = novo;
                printf("\E[2J\E[2H");
                printf("O(a) aluno(a) %s foi inserido(a) no curso %s com "
                       "sucesso.\n", nomeAluno, nomeCurso);
                break;
            }//if
            else
            {
                atualA = atualC->cadastradosA;
                while (atualA->prox != NULL)
                {
                    atualA = atualA->prox;
                }//while
                atualA->prox = novo;
                novo->ante = atualA;
                printf("\E[2J\E[2H");
                printf("O(a) aluno(a) %s foi inserido(a) no curso %s com "
                       "sucesso.\n", nomeAluno, nomeCurso);
                break;
            }//else
        }//if
        atualC = atualC->prox;
    }//while
    if(aux == 0) printf("O curso (%s) nao existe!\n", nomeCurso);
}

void listar_alunos_em_curso(TLista *L)
{
    printf("\E[2J\E[2H");
    char nomeCurso [50];
    int aux = 0;
    
    getchar();
    printf("Digite o nome do curso que voce deseja listar os Alunos.\n");
    gets(nomeCurso);
    
    TCursos *atualC = L->inicioC;
    TALuno *atualA = NULL;
    
    while(atualC != NULL)
    {
        if (strcmp(atualC->nome, nomeCurso) == 0)
        {
            aux += 1;
            atualA = atualC->cadastradosA;
            printf("\E[2J\E[2H");
            printf("Segue a lista de alunos do curso %s:\n", nomeCurso);
            if (atualA == NULL)
            {
                printf("\E[2J\E[2H");
                printf("A lista esta vazia\n");
                return;
            }//if
            while (atualA != NULL)
            {
                printf("Nome: %s, sexo: %c\n", atualA->nome, atualA->sexo);
                atualA = atualA->prox;
            }//while
        }//if
        atualC = atualC->prox;
    }//while
    
    if(aux == 0) printf("O curso (%s) nao existe!\n", nomeCurso);
}

void excluir_aluno_especifico(TLista *L)
{
    printf("\E[2J\E[2H");
    char nomeCurso [50];
    char nomeAluno [50];
    int aux = 0, aux1 = 0;
    TCursos *atualC = L->inicioC;
    TALuno *anteA = NULL;
    TDisciplina *atualD;
    TALuno *atualA;
    TDisciplina *auxD;

    getchar();
    printf("Digite o nome do Curso que esta o aluno.\n");
    gets(nomeCurso);

    while (atualC != NULL)
    {
        if (strcmp(atualC->nome, nomeCurso) == 0)
        {
            aux += 1;
            printf("Digite o nome do aluno que voce deseja excluir.\n");
            gets(nomeAluno);

            atualA = atualC->cadastradosA;
            anteA = atualC->cadastradosA->ante;
            while (atualA != NULL)
            {
                if(strcmp(atualA->nome, nomeAluno) == 0)
                {
                    aux1 += 1;
                    atualD = atualA->cadastradosD;
                    while (atualD != NULL)
                    {
                        auxD = atualD->prox;
                        free(atualD);
                        atualD = auxD;
                    }//while
                    if(anteA == NULL )
                    {
                        if(atualA->prox == NULL)
                        {
                            free(atualA);
                            atualA = NULL;
                            printf("\E[2J\E[2H");
                            printf("O(a) aluno(a) (%s) foi excluido(a) com sucesso!\n", nomeAluno);
                            return;
                        }//if
                        else
                        {
                            anteA = atualA->prox;
                            free(atualA);
                            atualA = anteA;
                            atualA->ante = NULL;
                            printf("\E[2J\E[2H");
                            printf("O(a) aluno(a) (%s) foi excluido(a) com sucesso!\n", nomeAluno);
                            return;
                        }//else
                    }//if
                    else
                    {
                        if(atualA->prox != NULL)
                        {
                            anteA = atualA->prox;
                            anteA->ante = atualA->ante;
                            free(atualA);
                            atualA = anteA;
                            printf("\E[2J\E[2H");
                            printf("O(a) aluno(a) (%s) foi excluido(a) com sucesso!\n", nomeAluno);
                            return;
                        }//if

                    }//else
                    if(atualA->prox == NULL)
                    {
                        anteA->prox = NULL;
                        free(atualA);
                        printf("\E[2J\E[2H");
                        printf("O(a) aluno(a) (%s) foi excluido(a) com sucesso!\n", nomeAluno);
                        return;
                    }
                }//if
                anteA = atualA;
                atualA = atualA->prox;
            }//while
        }//if
    }//while
    if(aux == 0) printf("O curso (%s) nao existe!\n", nomeCurso);
    if(aux1 == 0) printf("O aluno (%s) nao existe!\n", nomeAluno);
}

void consultar_aluno_especifico(TLista *L)
{
    printf("\E[2J\E[2H");
    char nomeCurso [50];
    char nomeAluno [50];
    int aux = 0;
    
    getchar();
    printf("Digite o nome do curso que voce deseja consultar os Alunos.\n");
    gets(nomeCurso);
    
    TCursos *atualC = L->inicioC;
    TALuno *atualA = NULL;
    TDisciplina *atualD;
    
    while(atualC != NULL)
    {
        if (strcmp(atualC->nome, nomeCurso) == 0)
        {
            aux += 1;
            atualA = atualC->cadastradosA;
            if (atualA == NULL)
            {
                printf("A lista de alunos esta vazia\n");
                return;
            }//if
            printf("Digite o nome do aluno que voce deseja consultar.\n");
            gets(nomeAluno);
            while (atualA != NULL)
            {
                if (strcmp(atualA->nome, nomeAluno) == 0)
                {
                    printf("Nome: %s, sexo: %c\n\n", atualA->nome, atualA->sexo);
                    printf("Disciplinas:\n");
                    atualD = atualA->cadastradosD;
                    
                    if (atualD == NULL)
                    {
                        printf("A lista de disciplinas esta vazia\n");
                        return;
                    }//if
                    
                    while (atualD != NULL)
                    {
                        printf("%s nota: %.2f frequencia %.2f\n", atualD->nome,
                               atualD->nota, atualD->frequencia);
                        atualD = atualD->prox;
                    }//while
                }//if
                atualA = atualA->prox;
            }//while
        }//if
        
        atualC = atualC->prox;
    }//while
    if(aux == 0) printf("O curso (%s) nao existe!\n", nomeCurso);
}

void inserir_disciplina_para_aluno(TLista *L)
{
    printf("\E[2J\E[2H");
    char nomeAluno [50];
    char nomeDisciplina [50];
    char nomeCurso [50];
    int aux1 = 0, aux2 = 0;
    float nota, frequencia;
    
    TDisciplina *novo = (TDisciplina *)malloc(sizeof(TDisciplina));
    
    TALuno *atualA = NULL;
    TCursos *atualC = L->inicioC;
    TDisciplina *atualD = NULL;
    
    getchar();
    printf("Digite o nome do Curso que esta o aluno.\n");
    gets(nomeCurso);
    
    while(atualC != NULL)
    {
        if (strcmp(atualC->nome, nomeCurso) == 0)
        {
            aux1 += 1;
            printf("Digite o nome do Aluno(a) que voce deseja inserir a "
                   "Disciplina.\n");
            gets(nomeAluno);
            
            atualA = atualC->cadastradosA;
            while(atualA != NULL)
            {
                if (strcmp(atualA->nome, nomeAluno) == 0)
                {
                    aux2 += 1;
                    printf("Digite o nome da Disciplina que voce deseja "
                           "inserir para o aluno(a) %s.\n", nomeAluno);
                    gets(nomeDisciplina);
                    printf("Nota\n");
                    scanf("%f", &nota);
                    printf("Frenquencia\n");
                    scanf("%f", &frequencia);
                    strcpy(novo->nome, nomeDisciplina);
                    novo->nota = nota;
                    novo->frequencia = frequencia;
                    novo->prox = NULL;
                    if(atualA->cadastradosD == NULL)
                    {
                        atualA->cadastradosD= novo;
                        printf("\E[2J\E[2H");
                        printf("A Disciplina %s foi inserida para o(a) aluno(a) "
                               "%s com sucesso.\n", nomeDisciplina, nomeAluno);
                        break;
                    }//if
                    else
                    {
                        atualD = atualA->cadastradosD;
                        while (atualD->prox != NULL)
                        {
                            atualD = atualD->prox;
                        }//while
                        atualD->prox = novo;
                        printf("\E[2J\E[2H");
                        printf("A Disciplina %s foi inserida para o(a) aluno(a) %s "
                               "com sucesso.\n", nomeDisciplina, nomeAluno);
                        break;
                    }//else
                }//if
                atualA = atualA->prox;
            }//while
        }//if
        atualC = atualC->prox;
    }//while
    
    if (aux1 == 0) printf("O Aluno (%s) nao existe!\n", nomeAluno);
    if (aux2 == 0) printf("O Curso (%s) nao existe!\n", nomeCurso);
}

void excluir_disciplina_especifica(TLista *L)
{
    printf("\E[2J\E[2H");
    char nomeDisciplina [50];
    int aux = 0;
    TCursos *atualC = L->inicioC;
    TDisciplina *anteD = NULL;
    TDisciplina *atualD;
    TALuno *atualA;

    getchar();
    printf("Digite a disciplina que voce deseja excluir.\n");
    gets(nomeDisciplina);

    if (atualC == NULL)
    {
        printf("A lista 'Cursos' esta vazia!\n");
        return;
    }//if

    while (atualC != NULL)
    {
        atualA = atualC->cadastradosA;
        if (atualA == NULL)
        {
            printf("A lista 'Alunos' esta vazia!\n");
            return;
        }//if

        while (atualA != NULL)
        {
            atualD = atualA->cadastradosD;
            if (atualD == NULL)
            {
                printf("A lista 'Disciplina' esta vazia!\n");
                return;
            }//if

            while (atualD != NULL)
            {
                if (strcmp(atualD->nome, nomeDisciplina) == 0)
                {
                    aux +=1;
                    if (strcmp(atualD->nome, atualA->cadastradosD->nome) == 0)
                    {
                        if(atualD->prox != NULL)
                        {
                            atualA->cadastradosD = atualA->cadastradosD->prox;
                            free(atualD);
                            atualD = NULL;
                            printf("\E[2J\E[2H");
                            printf("A disciplina (%s) foi excluida com sucesso!\n", nomeDisciplina);
                            break;
                        }//if
                        else
                        {
                            atualA->cadastradosD = NULL;
                            free(atualD);
                            printf("\E[2J\E[2H");
                            printf("A disciplina (%s) foi excluida com sucesso!\n", nomeDisciplina);
                            break;
                        }//else
                    }//if
                    if(atualD->prox == NULL)
                    {
                        anteD->prox = NULL;
                        free(atualD);
                        atualD = NULL;
                        printf("\E[2J\E[2H");
                        printf("A disciplina (%s) foi excluida com sucesso!\n", nomeDisciplina);
                        break;
                    }//if
                    if(atualD->prox != NULL)
                    {
                        anteD->prox = atualD->prox;
                        atualD = NULL;
                        free(atualD);
                        printf("\E[2J\E[2H");
                        printf("A disciplina (%s) foi excluida com sucesso!\n", nomeDisciplina);
                        break;
                    }//if
                }//if
                anteD = atualD;
                atualD = atualD->prox;
            }//while
            atualA = atualA->prox;
        }//while
        atualC = atualC->prox;
    }//while

    if (aux == 0) printf("A Disciplina (%d) nao existe!\n", aux);
}

void consultar_disciplina_especifica(TLista *L)
{
    printf("\E[2J\E[2H");
    char nomeDisciplina [50];
    int aux = 0;
    TCursos *atualC = L->inicioC;
    TDisciplina *atualD;
    TALuno *atualA;
    
    getchar();
    printf("Digite a disciplina que voce deseja consultar.\n");
    gets(nomeDisciplina);
    
    if (atualC == NULL)
    {
        printf("A lista 'Cursos' esta vazia!\n");
        return;
    }//if
    
    while (atualC != NULL)
    {
        atualA = atualC->cadastradosA;
        if (atualA == NULL)
        {
            printf("A lista 'Alunos' esta vazia!\n");
            return;
        }//if
        
        while (atualA != NULL)
        {
            atualD = atualA->cadastradosD;
            while (atualD != NULL)
            {
                if (strcmp(atualD->nome, nomeDisciplina) == 0)
                {
                    aux += 1;
                    printf("Nome: %s\n", atualA->nome);
                    break;
                }//if
                atualD = atualD->prox;
            }//while
            atualA = atualA->prox;
        }//while
        atualC = atualC->prox;
    }//while
    if (aux == 0) printf("A Disciplina (%d) nao existe!\n", aux);
}

void Exibir_notas_e_freq_de_alunos_em_disciplina_especifica(TLista *L)
{
    printf("\E[2J\E[2H");
    char nomeDisciplina [50];
    int aux = 0;
    TCursos *atualC = L->inicioC;
    TDisciplina *atualD;
    TALuno *atualA;

    getchar();
    printf("Digite a disciplina que voce deseja consultar.\n");
    gets(nomeDisciplina);

    if (atualC == NULL)
    {
        printf("A lista 'Cursos' esta vazia.\n");
        return;
    }//if

    while (atualC != NULL)
    {
        atualA = atualC->cadastradosA;
        if (atualA == NULL)
        {
            printf("A lista 'Alunos' esta vazia.\n");
            return;
        }//if

        while (atualA != NULL)
        {
            atualD = atualA->cadastradosD;
            if (atualD == NULL)
            {
                printf("A lista 'Disciplina' esta vazia.\n");
                return;
            }//if

            while (atualD != NULL)
            {
                if (strcmp(atualD->nome, nomeDisciplina) == 0)
                {
                    aux += 1;
                    printf("\E[2J\E[2H");
                    printf("Aluno: %s\nDisciplina: %s\nNota: %.2f, Frequencia: %.2f\n\n",
                           atualA->nome, atualA->cadastradosD->nome, atualA->cadastradosD->nota,
                           atualA->cadastradosD->frequencia);
                    break;
                }//if
                atualD = atualD->prox;
            }//while
            atualA = atualA->prox;
        }//while
        atualC = atualC->prox;
    }//while
    if (aux == 0) printf("A Disciplina (%d) nao existe!\n", aux);
}
