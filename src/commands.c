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

/** LED sobre o qual os comandos de acender e apagar atuam. */
static const char led_alvo[] = "verde";

/**
 * Acender e apagar diferem só pelo estado pedido, então compartilham a
 * implementação e cada comando entra na tabela como uma ação própria.
 */
static void led_set(bool on)
{
	printk("LED %s %s\n", led_alvo, on ? "aceso" : "apagado");
}

static void led_on_execute(void)
{
	led_set(true);
}

static void led_off_execute(void)
{
	led_set(false);
}

static void uptime_execute(void)
{
	printk("Uptime: %lld ms\n", k_uptime_get());
}

static void reboot_execute(void)
{
	printk("Reiniciando o sistema\n");
}

/**
 * Acrescentar um comando é acrescentar a ação acima e uma linha aqui. O
 * despachante em command.c não muda.
 */
static const command_t table[] = {
	{.name = "led_on", .execute = led_on_execute},
	{.name = "led_off", .execute = led_off_execute},
	{.name = "uptime", .execute = uptime_execute},
	{.name = "reboot", .execute = reboot_execute},
};

const command_t *commands_get_table(size_t *count)
{
	if (count == NULL) {
		return NULL;
	}

	*count = ARRAY_SIZE(table);

	return table;
}
