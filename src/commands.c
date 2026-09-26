/*******************************************************************
 * @file commands.c
 *
 * @brief Comandos concretos e a tabela que os expõe.
 * @author Erick Mascarenhas (edlm@ic.ufal.br)
 * @version 0.1
 * @date 26/09/2026
 *******************************************************************/

#include <stdbool.h>
#include <stddef.h>

#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>

#include "command.h"
#include "commands.h"

/** Parâmetro das ações de LED, apontado por @ref command.arg. */
struct led_action {
	const char *label;
	bool on;
};

static const struct led_action acender_verde = {.label = "verde", .on = true};
static const struct led_action apagar_verde = {.label = "verde", .on = false};

/**
 * Acender e apagar são a mesma ação com dados diferentes: dois comandos,
 * uma função. É o que o Command Pattern permite e um switch não.
 */
static void led_execute(const struct command *self)
{
	const struct led_action *action = self->arg;

	printk("LED %s %s\n", action->label, action->on ? "aceso" : "apagado");
}

static void uptime_execute(const struct command *self)
{
	ARG_UNUSED(self);

	printk("Uptime: %lld ms\n", k_uptime_get());
}

static void reboot_execute(const struct command *self)
{
	ARG_UNUSED(self);

	printk("Reiniciando o sistema\n");
}

/**
 * Acrescentar um comando é acrescentar a ação acima e uma linha aqui. O
 * despachante em command.c não muda.
 */
static const struct command table[] = {
	{.name = "led_on", .execute = led_execute, .arg = &acender_verde},
	{.name = "led_off", .execute = led_execute, .arg = &apagar_verde},
	{.name = "uptime", .execute = uptime_execute, .arg = NULL},
	{.name = "reboot", .execute = reboot_execute, .arg = NULL},
};

const struct command *commands_get_table(size_t *count)
{
	if (count == NULL) {
		return NULL;
	}

	*count = ARRAY_SIZE(table);

	return table;
}
