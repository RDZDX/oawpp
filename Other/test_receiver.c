#include "test_receiver.h"

VMCHAR my_string1[100] = {0};
VMCHAR my_string2[100] = {0};
VMWCHAR my_stringw1[100] = {0};
VMWCHAR my_stringw2[100] = {0};

VMUINT8 *layer_buf0 = NULL;
char *tmp_qr_res = NULL;
int font_height = 16;
VMWCHAR oneDisplay[40][61];
VMFILE f_read;

void vm_main(void) {

	layer_hdl[0] = -1;	
        vm_gb2312_to_ucs2(my_stringw1, 100, "My test");
        vm_font_set_font_size(VM_SMALL_FONT);
	vm_reg_sysevt_callback(handle_sysevt);
	vm_reg_keyboard_callback(handle_keyevt);
}

void handle_sysevt(VMINT message, VMINT param) {

	//if (message == VM_MSG_CREATE && param){ vm_wstrcpy(my_stringw1, (VMWSTR)param);	}

#ifdef		SUPPORT_BG	

	switch (message) {
	case VM_MSG_CREATE:
                if (param) {vm_wstrcpy(my_stringw1, (VMWSTR)param);}
		break;
	case VM_MSG_PAINT:
		layer_hdl[0] = vm_graphic_create_layer(0, 0, vm_graphic_get_screen_width(), vm_graphic_get_screen_height(), -1);	
		vm_graphic_set_clip(0, 0, vm_graphic_get_screen_width(), vm_graphic_get_screen_height());
		draw_hello1();
		break;
	case VM_MSG_HIDE:	
		if( layer_hdl[0] != -1 )
		{
			vm_graphic_delete_layer(layer_hdl[0]);
			layer_hdl[0] = -1;
		}
		break;
	case VM_MSG_QUIT:
		if( layer_hdl[0] != -1 )
		{
			vm_graphic_delete_layer(layer_hdl[0]);
			layer_hdl[0] = -1;
		}
		break;
	}
#else
	switch (message) {
	case VM_MSG_CREATE:
                if (param) {vm_wstrcpy(my_stringw1, (VMWSTR)param);}
	case VM_MSG_ACTIVE:
		layer_hdl[0] = vm_graphic_create_layer(0, 0, vm_graphic_get_screen_width(), vm_graphic_get_screen_height(), -1);	
		vm_graphic_set_clip(0, 0, vm_graphic_get_screen_width(), vm_graphic_get_screen_height());
		break;
	case VM_MSG_PAINT:
		draw_hello1();
		break;
	case VM_MSG_INACTIVE:
		if( layer_hdl[0] != -1 )
			vm_graphic_delete_layer(layer_hdl[0]);
		break;	
	case VM_MSG_QUIT:
		if( layer_hdl[0] != -1 )
			vm_graphic_delete_layer(layer_hdl[0]);
		break;	
	}
#endif
}

void handle_keyevt(VMINT event, VMINT keycode) {

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_LEFT_SOFTKEY) {
       checkFileExist();
    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_RIGHT_SOFTKEY) {
        if (layer_hdl[0] != -1) {
            vm_graphic_delete_layer(layer_hdl[0]);
            layer_hdl[0] = -1;
        }
        vm_exit_app();
    }

}

static void draw_hello1(void) {

    VMWCHAR fullPath[100] = {0};
    VMWCHAR my_stringw[100] = {0};
    int x, y, x1, y1;
    int wstr_width;
    int wstr_width1;
    vm_graphic_color color;

    vm_get_exec_filename(fullPath);
    vm_get_filename(fullPath, my_stringw);

    wstr_width = vm_graphic_get_string_width(my_stringw);
    wstr_width1 = vm_graphic_get_string_width(my_stringw1);
    x = (vm_graphic_get_screen_width() - wstr_width) / 2;
    y = (vm_graphic_get_screen_height() - vm_graphic_get_character_height()) / 2;
    x1 = (vm_graphic_get_screen_width() - wstr_width1) / 2;
    y1 = (vm_graphic_get_screen_height() - vm_graphic_get_character_height()) / 8;

    color.vm_color_565 = VM_COLOR_WHITE;
    vm_graphic_setcolor(&color);
    vm_graphic_fill_rect_ex(layer_hdl[0], 0, 0, vm_graphic_get_screen_width(), vm_graphic_get_screen_height());
    color.vm_color_565 = VM_COLOR_BLACK;
    vm_graphic_setcolor(&color);
    vm_graphic_textout_to_layer(layer_hdl[0], x, y1, my_stringw, wstr_width);
    vm_graphic_textout_to_layer(layer_hdl[0], x1, y, my_stringw1, wstr_width1);
    vm_graphic_flush_layer(layer_hdl, 1);
}

static void draw_hello2(void) {

    VMWCHAR fullPath[100] = {0};
    VMWCHAR my_stringw[100] = {0};
    int x, y, x1, y1;
    int wstr_width;
    int wstr_width1;
    vm_graphic_color color;

    vm_get_exec_filename(fullPath);
    vm_get_filename(fullPath, my_stringw);

    wstr_width = vm_graphic_get_string_width(my_stringw);
    wstr_width1 = vm_graphic_get_string_width(my_stringw2);

    x = (vm_graphic_get_screen_width() - wstr_width) / 2;
    y = (vm_graphic_get_screen_height() - vm_graphic_get_character_height()) / 3;
    x1 = (vm_graphic_get_screen_width() - wstr_width1) / 2;
    y1 = (vm_graphic_get_screen_height() - vm_graphic_get_character_height()) / 8;

    color.vm_color_565 = VM_COLOR_WHITE;
    vm_graphic_setcolor(&color);
    vm_graphic_fill_rect_ex(layer_hdl[0], 0, 0, vm_graphic_get_screen_width(), vm_graphic_get_screen_height());
    color.vm_color_565 = VM_COLOR_BLACK;
    vm_graphic_setcolor(&color);
    //vm_graphic_textout_to_layer(layer_hdl[0], x, y1, my_stringw, wstr_width);
    vm_graphic_textout_to_layer(layer_hdl[0], x1, y, my_stringw2, wstr_width1);
    vm_graphic_flush_layer(layer_hdl, 1);
}

//----------------------------Todo-----------------------------

VMINT parseTextToArr(void) {

    VMWSTR sKonv_stringas = {0};
    VMCHAR vns_simbl[2] = {0};
    VMCHAR value10[2000] = {0};
    VMCHAR nauj_strng[61] = {0};
    VMCHAR konv_stringas[124] = {0};

    //VMWCHAR vns_simbl[2] = {};
    //VMWCHAR value10[(380 + 1) * 2] = {}; //761 + 60 ?
    //VMWCHAR nauj_strng[(380 + 1) * 2] = {}
    //VMWCHAR *ptr;

    //int i, strng_plot, isve_i_ekr_eil_sk, nauj_strng_ilg;
    int strng_plot, isve_i_ekr_eil_sk, nauj_strng_ilg;
    
    strng_plot = 0;
    isve_i_ekr_eil_sk = 0;
    nauj_strng_ilg = 0;

    memset(oneDisplay, 0, sizeof(oneDisplay[0][0]) * 40 * 61);

    sprintf(value10, "%s", tmp_qr_res);

        char *ptr = value10;
        //ptr = my_stringw1;

        while (*ptr != '\0') {

/*                                               For working with UCS2 data
        while (*ptr != L'\0') {


          if (*ptr == L'\r') {
               //vm_vibrator_once();
               counter = counter + 1;
               ptr++;
            }

            if (*ptr != L'\n') {
               vm_wstrncpy(vns_simbl, value10 + counter, 1);
               vm_wstrcat(nauj_strng, vns_simbl);
            }

          ilgism = wstrlen(nauj_strng); //ilgism = wstrlen(nauj_strng); ++++++++++++++++++++++++++++++++++++++++++

            if (ilgism > 14 || *ptr == L'\n' || *ptr == L'\0' || prasisk_count1 != 0) {
            strng_plot = vm_graphic_get_string_width(nauj_strng);
            }

            if (strng_plot > 235 && isve_i_ekr_eil_sk < 20 || *ptr == L'\n' && isve_i_ekr_eil_sk < 20){

                vertical_scrolling_ucs2_text(nauj_strng);
                isve_i_ekr_eil_sk = isve_i_ekr_eil_sk + 1;
                vm_wstrcpy(nauj_strng, (VMWSTR)"");
                strng_plot = 0;
            }

            counter = counter + 1;
            ptr++;
        }

*/

            sprintf(vns_simbl, "%c", *ptr);
            strcat(nauj_strng, vns_simbl);
            vm_chset_convert(VM_CHSET_UTF8, VM_CHSET_UCS2, nauj_strng, konv_stringas, (strlen(nauj_strng) + 1) * 2);
            sKonv_stringas = (VMWSTR)konv_stringas;
            strng_plot = vm_graphic_get_string_width(sKonv_stringas);

            if (strng_plot > 235) {
                vm_wstrcpy((VMWSTR)&oneDisplay[isve_i_ekr_eil_sk - 1][61], sKonv_stringas);
                nauj_strng_ilg = strlen(nauj_strng) - 1;
                isve_i_ekr_eil_sk = isve_i_ekr_eil_sk + 1;
                strcpy(nauj_strng, "");
                ptr - 2;
            }

            if (isve_i_ekr_eil_sk == 40) {
                break;
            }

            ptr++;
        }

        strcpy(value10, nauj_strng);
        strcpy(nauj_strng, "");
 
        if (isve_i_ekr_eil_sk < 40 && strng_plot == 235 || isve_i_ekr_eil_sk < 40 && strng_plot < 235) {
            vm_wstrcpy((VMWSTR)&oneDisplay[isve_i_ekr_eil_sk - 1][61], sKonv_stringas);
        }

    nauj_strng_ilg = 0;
    strcpy(vns_simbl, "");
    strcpy(nauj_strng, "");
    strcpy(value10, "");
    strcpy(konv_stringas, "");

    return 0;
}

void fromArrToDisplay(void) {

    VMWCHAR s[100 + 23];
    int w;
    VMINT g_mre_curr_y = 1;

    layer_buf0 = vm_graphic_get_layer_buffer(layer_hdl[0]);
    vm_graphic_fill_rect(layer_buf0, 0, 0, vm_graphic_get_screen_width(),
    vm_graphic_get_screen_height(), VM_COLOR_WHITE, VM_COLOR_WHITE);

    vm_wstrcpy(s, (VMWSTR)&oneDisplay[0][0]);
    w = vm_graphic_get_string_width(s);
    vm_graphic_textout_by_baseline(layer_buf0, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_BLACK, 12);

    memset(s, 0, 100);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[1][0]);
    g_mre_curr_y = g_mre_curr_y + font_height;
    vm_graphic_textout_by_baseline(layer_buf0, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_BLACK, 12);

    memset(s, 0, 100);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[2][0]);
    g_mre_curr_y = g_mre_curr_y + font_height;
    vm_graphic_textout_by_baseline(layer_buf0, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_BLACK, 12);

    memset(s, 0, 100);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[3][0]);
    g_mre_curr_y = g_mre_curr_y + font_height;
    vm_graphic_textout_by_baseline(layer_buf0, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_BLACK, 12);

    memset(s, 0, 100);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[4][0]);
    g_mre_curr_y = g_mre_curr_y + font_height;
    vm_graphic_textout_by_baseline(layer_buf0, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_BLACK, 12);

    memset(s, 0, 100);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[5][0]);
    g_mre_curr_y = g_mre_curr_y + font_height;
    vm_graphic_textout_by_baseline(layer_buf0, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_BLACK, 12);

    memset(s, 0, 100);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[6][0]);
    g_mre_curr_y = g_mre_curr_y + font_height;
    vm_graphic_textout_by_baseline(layer_buf0, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_BLACK, 12);

    memset(s, 0, 100);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[7][0]);
    g_mre_curr_y = g_mre_curr_y + font_height;
    vm_graphic_textout_by_baseline(layer_buf0, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_BLACK, 12);

    memset(s, 0, 100);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[8][0]);
    g_mre_curr_y = g_mre_curr_y + font_height;
    vm_graphic_textout_by_baseline(layer_buf0, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_BLACK, 12);

    memset(s, 0, 100);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[9][0]);
    g_mre_curr_y = g_mre_curr_y + font_height;
    vm_graphic_textout_by_baseline(layer_buf0, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_BLACK, 12);

    memset(s, 0, 100);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[10][0]);
    g_mre_curr_y = g_mre_curr_y + font_height;
    vm_graphic_textout_by_baseline(layer_buf0, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_BLACK, 12);

    memset(s, 0, 100);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[11][0]);
    g_mre_curr_y = g_mre_curr_y + font_height;
    vm_graphic_textout_by_baseline(layer_buf0, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_BLACK, 12);

    memset(s, 0, 100);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[12][0]);
    g_mre_curr_y = g_mre_curr_y + font_height;
    vm_graphic_textout_by_baseline(layer_buf0, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_BLACK, 12);

    memset(s, 0, 100);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[13][0]);
    g_mre_curr_y = g_mre_curr_y + font_height;
    vm_graphic_textout_by_baseline(layer_buf0, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_BLACK, 12);

    memset(s, 0, 100);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[14][0]);
    g_mre_curr_y = g_mre_curr_y + font_height;
    vm_graphic_textout_by_baseline(layer_buf0, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_BLACK, 12);

    memset(s, 0, 100);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[15][0]);
    g_mre_curr_y = g_mre_curr_y + font_height;
    vm_graphic_textout_by_baseline(layer_buf0, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_BLACK, 12);

    memset(s, 0, 100);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[16][0]);
    g_mre_curr_y = g_mre_curr_y + font_height;
    vm_graphic_textout_by_baseline(layer_buf0, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_BLACK, 12);

    memset(s, 0, 100);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[17][0]);
    g_mre_curr_y = g_mre_curr_y + font_height;
    vm_graphic_textout_by_baseline(layer_buf0, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_BLACK, 12);

    memset(s, 0, 100);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[18][0]);
    g_mre_curr_y = g_mre_curr_y + font_height;
    vm_graphic_textout_by_baseline(layer_buf0, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_BLACK, 12);

    memset(s, 0, 100);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[19][0]);
    g_mre_curr_y = g_mre_curr_y + font_height;
    vm_graphic_textout_by_baseline(layer_buf0, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_BLACK, 12);

    vm_graphic_flush_layer(layer_hdl, 1);
}

void checkFileExist(void) {

    f_read = vm_file_open(my_stringw1, MODE_READ, FALSE);

    if (f_read < 0) {
        vm_file_close(f_read);
        vm_ascii_to_ucs2(my_stringw2, (strlen("File not found !") + 1) * 2, "File not found !");
        draw_hello2();
    } else {
        vm_file_close(f_read);
        read_file_to_input(my_stringw1);
    }
}

void read_file_to_input(VMWSTR path) {

   VMCHAR ascii_data[2000];
   VMWCHAR ucs2_data[2000];
   VMUINT nread;

   if (vm_file_get_attributes(path) != -1) {
      f_read = vm_file_open(path, MODE_READ, FALSE);
      vm_file_read(f_read, ascii_data, 2000, &nread);
      ascii_data[nread] = '\0';
      vm_file_close(f_read);
      vm_ascii_to_ucs2(ucs2_data, (strlen(ascii_data) + 1) * 2, ascii_data);
      vm_input_text3(ucs2_data, 2000, 8, save_text);
   }
}

void save_text(VMINT state, VMWSTR text) {
  
    vm_exit_app();
}