SUBDIRS := $(wildcard */.)
SRCS = ${wildcard */*.c }

all : $(SUBDIRS)
$(SUBDIRS):
	@$(MAKE) -C $@

.PHONY: all $(SUBDIRS) tidy format cppcheck

tidy:
	@for src in $(SRCS) ; do \
		echo "Running tidy on $$src..." ; \
		clang-tidy \
			"$$src" \
			-header-filter= \
			-- \
			${CFLAGS} ;\
	done

format:
	@for src in $(SRCS) ; do \
		echo "Running format on $$src..." ; \
		clang-format \
			-i "$$src"; \
	done

# cppcheck
CPPCHECK_FLAGS = --xml --xml-version=2 --enable=all
REPORT_DIR = reports/
CPPCHECK_DIR = cppcheck/
CPPCHECK_HTML_DIR = html/


cppcheck: cppcheck.out.xml
cppcheck.out.xml: cppcheck_clean
	@mkdir -p $(REPORT_DIR)$(CPPCHECK_DIR)$(CPPCHECK_HTML_DIR)
	@cppcheck $(CPPCHECK_FLAGS) $(SRCS) 2> $(REPORT_DIR)$(CPPCHECK_DIR)$@
	@cppcheck-htmlreport --file=$(REPORT_DIR)$(CPPCHECK_DIR)$@ \
		--report-dir=$(REPORT_DIR)$(CPPCHECK_DIR)$(CPPCHECK_HTML_DIR) \
		--source-dir=.

cppcheck_clean:s
	@rm -rf $(REPORT_DIR)
