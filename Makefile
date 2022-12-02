export

COMMONDIR := common
SUBDIRS := $(wildcard */.)
SUBDIRS := $(filter-out $(COMMONDIR)/.,$(SUBDIRS))
SRCS = $(wildcard */*.c )
COMMONSRCS = $(wildcard $(COMMONDIR)/*.c )
COMMONOBJS = $(patsubst %.c,%.o,$(COMMONSRCS))
ABS_COMMONOBJS = $(foreach obj,$(COMMONOBJS),$(realpath $(obj)))

CFLAGS+=-O2 -Wall -Wextra
CFLAGS+=-I${INCL_DIRS} -D_FORTIFY_SOURCE=2
CFLAGS+=-Wformat -Wformat-security -Werror=format-security
CFLAGS+=-Wshadow

all : clean $(SUBDIRS)

$(SUBDIRS): $(COMMONDIR)
	@$(MAKE) -C $@

$(COMMONDIR): $(COMMONOBJS)

%.o: %.c
	@echo -e "\033[0;33m[CC] \t\033[0m$<"
	@${CC} -o $@ -c $< ${CFLAGS} ${DEPFLAGS}

clean:
	@echo -e "\033[0;32m[RM] \t\033[0mClean directory objects"
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f Makefile $@; \
	done
	@-${RM} ${ABS_COMMONOBJS}


.PHONY: all $(SUBDIRS) tidy format cppcheck $(COMMONDIR) clean

# clang-tidy
tidy:
	@for src in $(SRCS) ; do \
		echo "Running tidy on $$src..." ; \
		clang-tidy \
			"$$src" \
			-header-filter= \
			-- \
			${CFLAGS} ;\
	done

# clang-format
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
