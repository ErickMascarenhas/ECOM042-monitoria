/*******************************************************************
 * @file main.c
 *
 * @brief Main file.
 * @author João Matheus Nascimento Dias (jmnd@ic.ufal.br)
 * @author Erick Mascarenhas (edlm@ic.ufal.br)
 * @version 0.1
 * @date 26/09/2026
 *******************************************************************/

#include <stddef.h>

#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>

#include "command.h"
#include "commands.h"

int main(void)
{
	size_t count = 0;
	const struct command *table = commands_get_table(&count);

	/* O último rótulo não está na tabela: exercita o caminho de erro. */
	static const char *const requests[] = {
		"led_on", "uptime", "led_off", "reboot", "shutdown",
	};

	for (size_t i = 0; i < ARRAY_SIZE(requests); i++) {
		const char *name = requests[i];
		enum command_status result = command_dispatch(table, count, name);

		if (result != COMMAND_OK) {
			printk("Comando \"%s\" nao executado (%d)\n", name, result);
		}
	}

	return 0;
}
