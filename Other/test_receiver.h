#ifndef _VRE_APP_WIZARDTEMPLATE_
#define	_VRE_APP_WIZARDTEMPLATE_

#define		SUPPORT_BG

#include "vmsys.h"
#include "vmio.h"
#include "vmgraph.h"
#include "vmchset.h"
#include "vmstdlib.h"
#include "ResID.h"
#include "vm4res.h"
#include "vmsm.h"
#include <string.h>
#include "vmappcomm.h"
#include "vmmm.h"
#include <stdlib.h>
#include "stdio.h"
#include "vmpromng.h"
#include "stdint.h"

VMINT		layer_hdl[1];

void handle_sysevt(VMINT message, VMINT param);
void handle_keyevt(VMINT event, VMINT keycode);
static void draw_hello1(void);
static void draw_hello2(void);
VMINT parseTextToArr(void);
void fromArrToDisplay(void);
void checkFileExist(void);
void read_file_to_input(VMWSTR path);
void save_text(VMINT state, VMWSTR text);

#endif



