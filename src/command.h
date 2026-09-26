/*******************************************************************
 * @file command.h
 *
 * @brief Interface genérica de comando (Command Pattern).
 * @author Erick Mascarenhas (edlm@ic.ufal.br)
 * @version 0.1
 * @date 26/09/2026
 *******************************************************************/

#ifndef COMMAND_H_
#define COMMAND_H_

#include <stddef.h>

/**
 * @brief Um comando que sabe executar a si mesmo.
 *
 * É tudo o que o despachante enxerga: um rótulo e uma ação. Qual ação é
 * essa, e o que ela faz por baixo, não interessa a quem despacha.
 */
typedef struct {
	/** Rótulo pelo qual o comando é invocado. */
	const char *name;
	/** Ação que o comando executa. */
	void (*execute)(void);
} command_t;

/** Resultado de uma tentativa de despacho. */
typedef enum {
	/** Comando encontrado e executado. */
	COMMAND_OK = 0,
	/** Nenhuma entrada da tabela corresponde ao rótulo pedido. */
	COMMAND_NOT_FOUND = -1,
	/** Argumento inválido, ou entrada da tabela sem ação. */
	COMMAND_INVALID = -2,
} command_status_t;

/**
 * @brief Procura @p name na tabela e executa o comando correspondente.
 *
 * Não conhece nenhum comando concreto: compara rótulos e chama o ponteiro
 * de função da entrada que casar. Comandos novos entram na tabela sem que
 * esta função precise mudar.
 *
 * @param table Tabela de comandos disponíveis.
 * @param count Número de entradas em @p table.
 * @param name Rótulo do comando pedido.
 *
 * @return COMMAND_OK, COMMAND_NOT_FOUND ou COMMAND_INVALID.
 */
command_status_t command_dispatch(const command_t *table, size_t count, const char *name);

#endif /* COMMAND_H_ */
