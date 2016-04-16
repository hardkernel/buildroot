################################################################################
#
# perf
#
################################################################################

LINUX_TOOLS += perf

PERF_DEPENDENCIES = host-flex host-bison

ifeq ($(KERNEL_ARCH),x86_64)
PERF_ARCH=x86
else
PERF_ARCH=$(KERNEL_ARCH)
endif

PERF_MAKE_FLAGS = \
	$(LINUX_MAKE_FLAGS) \
	ARCH=$(PERF_ARCH) \
	NO_LIBAUDIT=1 \
	NO_NEWT=1 \
	NO_GTK2=1 \
	NO_LIBPERL=1 \
	NO_LIBPYTHON=1 \
	DESTDIR=$(TARGET_DIR) \
	prefix=/usr \
	WERROR=0 \
	ASCIIDOC=

# The call to backtrace() function fails for ARC, because for some
# reason the unwinder from libgcc returns early. Thus the usage of
# backtrace() should be disabled in perf explicitly: at build time
# backtrace() appears to be available, but it fails at runtime: the
# backtrace will contain only several functions from the top of stack,
# instead of the complete backtrace.
ifeq ($(BR2_arc),y)
PERF_MAKE_FLAGS += NO_BACKTRACE=1
endif

ifeq ($(BR2_PACKAGE_SLANG),y)
PERF_DEPENDENCIES += slang
endif

ifeq ($(BR2_PACKAGE_LIBUNWIND),y)
PERF_DEPENDENCIES += libunwind
endif

ifeq ($(BR2_PACKAGE_NUMACTL),y)
PERF_DEPENDENCIES += numactl
endif

ifeq ($(BR2_PACKAGE_ELFUTILS),y)
PERF_DEPENDENCIES += elfutils
else
PERF_MAKE_FLAGS += NO_LIBELF=1 NO_DWARF=1
endif

# O must be redefined here to overwrite the one used by Buildroot for
# out of tree build. We build perf in $(@D)/tools/perf/ and not just
# $(@D) so that it isn't built in the root directory of the kernel
# sources.
define PERF_BUILD_CMDS
	$(Q)if test ! -f $(@D)/tools/perf/Makefile ; then \
		echo "Your kernel version is too old and does not have the perf tool." ; \
		echo "At least kernel 2.6.31 must be used." ; \
		exit 1 ; \
	fi
	$(Q)if test "$(BR2_PACKAGE_ELFUTILS)" = "" ; then \
		if ! grep -q NO_LIBELF $(@D)/tools/perf/Makefile* ; then \
			if ! test -r $(@D)/tools/perf/config/Makefile ; then \
				echo "The perf tool in your kernel cannot be built without libelf." ; \
				echo "Either upgrade your kernel to >= 3.7, or enable the elfutils package." ; \
				exit 1 ; \
			fi \
		fi \
	fi
	$(TARGET_MAKE_ENV) $(MAKE1) $(PERF_MAKE_FLAGS) \
		-C $(@D)/tools/perf O=$(@D)/tools/perf/
endef

# After installation, we remove the Perl and Python scripts from the
# target.
define PERF_INSTALL_TARGET_CMDS
	$(TARGET_MAKE_ENV) $(MAKE1) $(PERF_MAKE_FLAGS) \
		-C $(@D)/tools/perf O=$(@D)/tools/perf/ install
	$(RM) -rf $(TARGET_DIR)/usr/libexec/perf-core/scripts/
endef
