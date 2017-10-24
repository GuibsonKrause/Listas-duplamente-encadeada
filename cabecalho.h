#ifndef CABECALHO_H
#define CABECALHO_H

//========================================| Estruturas de Dados |========================================//
typedef struct ListaDisciplina
{
    char nome [30];
    float frequencia, nota;
    struct ListaDisciplina *prox;
}TDisciplina;

typedef struct Aluno
{
    char nome[40];
    char sexo;
    TDisciplina *cadastradosD;
    struct Aluno *prox, *ante;
}TALuno;

typedef struct Cursos
{
    char nome [30];
    char coordenador [30];
    TALuno *cadastradosA;
    struct Cursos *prox,*ante;
}TCursos;

typedef struct Listacursos
{
    TCursos *inicioC, *fimC;
}TLista;

//========================================| Chamada das Funções |========================================//
void free_geral(TLista *L);
void inicializaTlista(TLista *L);
void inserir_curso(TLista *L);
void listar_cursos(TLista L);
void consultar_cursos_especifico(TLista *L);
void excluir_curso_especifico(TLista *L);
void inserir_aluno_em_curso(TLista *L);
void listar_alunos_em_curso(TLista *L);
void excluir_aluno_especifico(TLista *L);
void consultar_aluno_especifico(TLista *L);
void inserir_disciplina_para_aluno(TLista *L);
void excluir_disciplina_especifica(TLista *L);
void consultar_disciplina_especifica(TLista *L);
void Exibir_notas_e_freq_de_alunos_em_disciplina_especifica(TLista *L);

#endif // CABECALHO_H
