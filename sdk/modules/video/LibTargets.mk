############################################################################
# sdk/modules/video/LibTargets.mk
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
############################################################################
#
# This Makefile included from Makefile in the top of SDK directory.
# SDK build system uses below variables to control build.
#
# SDKLIBS      - Library files to be linked.
# SDKMODDIRS   - Module directories.
# SDKCLEANDIRS - Clean directories. It must be added whenever configured or not.
# CONTEXTDIRS  - Directories for target in context build stage. This variable can be omitted.
#                If you want to do prepare for build, add it and write context target in the Makefile.
# 

ifeq ($(CONFIG_VIDEO),y)
SDKLIBS += lib$(DELIM)libvideo$(LIBEXT)
SDKMODDIRS += modules$(DELIM)video
endif
SDKCLEANDIRS += modules$(DELIM)video

# Below 2 rules are mandatory, replace all of 'video' to your library name or directory.

modules$(DELIM)video$(DELIM)libvideo$(LIBEXT): context
	$(Q) $(MAKE) -C modules$(DELIM)video TOPDIR="$(TOPDIR)" SDKDIR="$(SDKDIR)" libvideo$(LIBEXT)

lib$(DELIM)libvideo$(LIBEXT): modules$(DELIM)video$(DELIM)libvideo$(LIBEXT)
	$(Q) install $< $@
