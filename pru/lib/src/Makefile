SUBDIRS=rpmsg_lib

all: $(SUBDIRS)

$(SUBDIRS):
	@$(MAKE) PRU_CGT=/usr/share/ti/cgt-pru -C $@

clean:
	@for d in $(SUBDIRS); do (cd $$d; $(MAKE) PRU_CGT=/usr/share/ti/cgt-pru clean ); done

.PHONY: all clean $(SUBDIRS)



