SUBDIRS := $(wildcard */.)

all clean: $(SUBDIRS)
$(SUBDIRS):
	@$(MAKE) -C $@

.PHONY: all $(SUBDIRS)