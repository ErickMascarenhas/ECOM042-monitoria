/*******************************************************************
 * @file commands.h
 *
 * @brief Tabela dos comandos concretos da aplicação.
 * @author Erick Mascarenhas (edlm@ic.ufal.br)
 * @version 0.1
 * @date 26/09/2026
 *******************************************************************/

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <stddef.h>

#include "command.h"

/**
 * @brief Entrega a tabela de comandos concretos disponíveis.
 *
 * @param count Recebe o número de entradas da tabela.
 *
 * @return Ponteiro para a tabela, ou NULL se @p count for NULL.
 */
const struct command *commands_get_table(size_t *count);

#endif /* COMMANDS_H_ */
