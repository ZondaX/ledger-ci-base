#*******************************************************************************
#   Ledger App
#   (c) 2017 Ledger
#   (c) 2018 ZondaX GmbH
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#*******************************************************************************

ifeq ($(BOLOS_SDK),)
$(error BOLOS_SDK is not set)
endif

SCRIPT_LD:=$(CURDIR)/script.ld

include $(BOLOS_SDK)/Makefile.defines

# Main app configuration

APPNAME = "EXAMPLE"
APPVERSION_M=0
APPVERSION_N=0
APPVERSION_P=1

#APP_LOAD_PARAMS = --appFlags 0x00 --delete --signApp --signPrivateKey 0130a1c6fa9154cad78d91a8ecbbdbba7e1efbff01840997949130bba5cb38cd $(COMMON_LOAD_PARAMS)
APP_LOAD_PARAMS = --appFlags 0x00 --delete $(COMMON_LOAD_PARAMS)

ICONNAME=$(CURDIR)/glyphs/icon_app.gif

############
# Platform

DEFINES   += UNUSED\(x\)=\(void\)x

APPVERSION=$(APPVERSION_M).$(APPVERSION_N).$(APPVERSION_P)
DEFINES += LEDGER_MAJOR_VERSION=$(APPVERSION_M) LEDGER_MINOR_VERSION=$(APPVERSION_N) LEDGER_PATCH_VERSION=$(APPVERSION_P)
DEFINES   += APPVERSION=\"$(APPVERSION)\"

DEFINES += OS_IO_SEPROXYHAL IO_SEPROXYHAL_BUFFER_SIZE_B=128
DEFINES += HAVE_IO_USB HAVE_L4_USBLIB IO_USB_MAX_ENDPOINTS=7 IO_HID_EP_LENGTH=64 HAVE_USB_APDU

DEFINES += HAVE_BAGL HAVE_SPRINTF
DEFINES += PRINTF\(...\)=


SDK_SOURCE_PATH += lib_u2f
DEFINES   += HAVE_U2F HAVE_IO_U2F
DEFINES   += U2F_PROXY_MAGIC=\"TST\"
DEFINES   += U2F_MAX_MESSAGE_SIZE=264 #257+5+2

DEFINES   += USB_SEGMENT_SIZE=64
#DEFINES   += BLE_SEGMENT_SIZE=32 #max MTU, min 20

DEFINES   += HAVE_BOLOS_APP_STACK_CANARY
DEFINES   += LEDGER_SPECIFIC
DEFINES   += TESTING_ENABLED

# Compiler, assembler, and linker

ifneq ($(BOLOS_ENV),)
$(info BOLOS_ENV=$(BOLOS_ENV))
CLANGPATH := $(BOLOS_ENV)/clang-arm-fropi/bin/
GCCPATH := $(BOLOS_ENV)/gcc-arm-none-eabi-5_3-2016q1/bin/
else
$(info BOLOS_ENV is not set: falling back to CLANGPATH and GCCPATH)
endif

ifeq ($(CLANGPATH),)
$(info CLANGPATH is not set: clang will be used from PATH)
endif

ifeq ($(GCCPATH),)
$(info GCCPATH is not set: arm-none-eabi-* will be used from PATH)
endif

#########################

CC := $(CLANGPATH)clang
CFLAGS += -O3 -Os

AS := $(GCCPATH)arm-none-eabi-gcc
AFLAGS +=

LD       := $(GCCPATH)arm-none-eabi-gcc
LDFLAGS  += -O3 -Os -s
LDLIBS   += -lm -lgcc -lc

##########################

APP_SOURCE_PATH += src
SDK_SOURCE_PATH += lib_stusb lib_stusb_impl

#include $(BOLOS_SDK)/Makefile.glyphs

all: default

load: all
	python -m ledgerblue.loadApp $(APP_LOAD_PARAMS)

delete:
	python -m ledgerblue.deleteApp $(COMMON_DELETE_PARAMS)

package: all
	./pkgdemo.sh ${APPNAME} ${APPVERSION} ${ICONNAME}


# Import generic rules from the SDK

include $(BOLOS_SDK)/Makefile.rules

#add dependency on custom makefile filename
dep/%.d: %.c Makefile.genericwallet
