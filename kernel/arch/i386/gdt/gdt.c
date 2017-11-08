#include <kernel/gdt.h>

extern void load_gdt(struct gdt_ptr *gdt_ptr);

/* Define our GDT that we'll use - We know everything upfront, so we just
 * initalize it with the correct settings.
 *
 * This sets up the NULL, entry, and then the kernel's CS and DS segments,
 * which just span all 4GB of memory. */
struct GDT_entry GDT[GDT_SIZE] = {
	[_GDT_NULL] = { 0 /* NULL GDT entry - Required */ },
	[_KERNEL_CS] = GDT_ENTRY(GDT_EXE | GDT_READ, 0, 0xFFFFFFFF, DPL_KERNEL),
	[_KERNEL_DS] = GDT_ENTRY(GDT_WRITE,          0, 0xFFFFFFFF, DPL_KERNEL)
};

void gdt_init() {
	struct gdt_ptr gdt_ptr;

	gdt_ptr.base = (uint32_t)GDT;
	gdt_ptr.limit = sizeof(GDT);
	load_gdt(&gdt_ptr);
}
