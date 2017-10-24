#include "cabecalho.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int opcao;
    TLista L;
    inicializaTlista(&L);

    do
    {
        menu();
        scanf("%d", &opcao);
        switch(opcao)
        {
        case 0:
            free_geral(&L);
            break;
        case 1:
            inserir_curso(&L);
            printf("Curso Inserido com Sucesso!\n");
            break;
        case 2:
            listar_cursos(L);
            break;
        case 3:
            excluir_curso_especifico(&L);
            break;
        case 4:
            consultar_cursos_especifico(&L);
            break;
        case 5:
            inserir_aluno_em_curso(&L);
            break;
        case 6:
            listar_alunos_em_curso(&L);
            break;
        case 7:
            excluir_aluno_especifico(&L);
            break;
        case 8:
            consultar_aluno_especifico(&L);
            break;
        case 9:
            inserir_disciplina_para_aluno(&L);
            break;
        case 10:
            excluir_disciplina_especifica(&L);
            break;
        case 11:
            consultar_disciplina_especifica(&L);
            break;
        case 12:
            Exibir_notas_e_freq_de_alunos_em_disciplina_especifica(&L);
            break;
        }
    }while(opcao != 0);

    return 0;
}
