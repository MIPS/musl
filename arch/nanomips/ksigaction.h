struct k_sigaction {
	void (*handler)(int);
	unsigned flags;
	unsigned long mask[2];
	/* The following field is past the end of the structure the
	 * kernel will read or write, and exists only to avoid having
	 * mips-specific preprocessor conditionals in sigaction.c. */
	void (*restorer)();
};

void __restore(), __restore_rt();
