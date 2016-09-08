#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x83df6f39, "struct_module" },
	{ 0xf2a644fb, "copy_from_user" },
	{ 0x1d26aa98, "sprintf" },
	{ 0xad5de75c, "create_proc_entry" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0x1b7d4074, "printk" },
	{ 0x999e8297, "vfree" },
	{ 0xbfa8cebd, "remove_proc_entry" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

