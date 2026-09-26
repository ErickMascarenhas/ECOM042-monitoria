/*******************************************************************
 * @file command.c
 *
 * @brief Despachante genérico de comandos (Command Pattern).
 * @author Erick Mascarenhas (edlm@ic.ufal.br)
 * @version 0.1
 * @date 26/09/2026
 *******************************************************************/

#include <stddef.h>
#include <string.h>

#include "command.h"

enum command_status command_dispatch(const struct command *table, size_t count, const char *name)
{
	if (table == NULL || name == NULL) {
		return COMMAND_INVALID;
	}

	for (size_t i = 0; i < count; i++) {
		const struct command *entry = &table[i];

		if (entry->name == NULL || strcmp(entry->name, name) != 0) {
			continue;
		}

		if (entry->execute == NULL) {
			return COMMAND_INVALID;
		}

		entry->execute(entry);

		return COMMAND_OK;
	}

	return COMMAND_NOT_FOUND;
}
