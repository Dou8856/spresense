############################################################################
# externals/cmsis/dsp/Makefile
#
#   Copyright 2018 Sony Semiconductor Solutions Corporation
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
# 3. Neither the name of Sony Semiconductor Solutions Corporation nor
#    the names of its contributors may be used to endorse or promote
#    products derived from this software without specific prior written
#    permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
###########################################################################

-include $(TOPDIR)/.config
-include $(TOPDIR)/Make.defs
-include $(SDKDIR)/Make.defs

# CMSIS DSP

CMSIS_DSP = libarm_cortexM4lf_math$(LIBEXT)
BIN = $(CMSIS_DSP)

# CFLAGS definitions

include ../LibIncludes.mk

ifeq ($(CONFIG_EXTERNALS_CMSIS_DSP_ARM_MATH_MATRIX_CHECK),y)
CFLAGS += -DARM_MATH_MATRIX_CHECK
endif
ifeq ($(CONFIG_EXTERNALS_CMSIS_DSP_ARM_MATH_ROUNDING),y)
CFLAGS += -DARM_MATH_ROUNDING
endif
CFLAGS += -fno-strict-aliasing -ffunction-sections -fdata-sections
CFLAGS += -ffast-math

CMSIS_ROOT = ../CMSIS_5/CMSIS

SUBDIRS := $(dir $(wildcard $(CMSIS_ROOT)/DSP/Source/*/))

VPATH   := $(SUBDIRS)
DEPPATH := $(foreach dir,$(SUBDIRS), --dep-path $(dir))

CSRCS := $(notdir $(foreach dir,$(SUBDIRS), $(wildcard $(dir)/*.c)))
ASRCS := $(notdir $(foreach dir,$(SUBDIRS), $(wildcard $(dir)/*.S)))
CXXSRCS :=

AOBJS = $(ASRCS:.S=$(OBJEXT))
COBJS = $(CSRCS:.c=$(OBJEXT))
CXXOBJS = $(CXXSRCS:$(CXXEXT)=$(OBJEXT))

SRCS = $(ASRCS) $(CSRCS) $(CXXSRCS)
LIB_OBJS = $(AOBJS) $(COBJS) $(CXXOBJS)

all: $(BIN)
.PHONY: context depend preconfig clean distclean

$(AOBJS): %$(OBJEXT): %.S
	$(call ASSEMBLE, $<, $@)

$(COBJS): %$(OBJEXT): %.c
	$(call COMPILE, $<, $@)

$(CXXOBJS): %$(OBJEXT): %$(CXXEXT)
	$(call COMPILE, $<, $@)

$(BIN): $(LIB_OBJS)
	$(call ARCHIVE, $@, $(LIB_OBJS))

.depend: Makefile $(SRCS)
	$(Q) $(MKDEP) $(DEPPATH) "$(CC)" -- $(CFLAGS) -- $(ASRCS) $(CSRCS) >Make.dep
	$(Q) $(MKDEP) $(DEPPATH) "$(CC)" -- $(CXXFLAGS) -- $(CXXSRCS) >>Make.dep
	$(Q) touch $@

depend: .depend

context:

clean_context:

clean:
	$(call DELFILE, $(BIN))
	$(call CLEAN)

distclean: clean clean_context
	$(call DELFILE, .context)
	$(call DELFILE, Make.dep)
	$(call DELFILE, .depend)

-include Make.dep
