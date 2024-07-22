#include "oawpp.h"

VMWCHAR fullPath[100] = {0};
VMWCHAR file_pathw[100];
VMWCHAR file_pathq[100];
VMWCHAR title_name[100];
VMFILE f_read;
VMINT trigerisX = 0;

VMUINT8 *buffer;
VMINT trigeris = 1;
VMINT trigerisx = 1;
VMINT trigerisy = 0;
VMINT trigeris1 = 0;
VMINT trigeris2 = 0;
VMINT trigeris3 = 0;
VMINT trigeris4 = 0;

VMCHAR new_data[100];
VMWCHAR ucs2_data[100] = {0};

VMWCHAR auto_filename[100];

void vm_main(void) {

    layer_hdl[0] = -1;
    vm_reg_sysevt_callback(handle_sysevt);
    vm_font_set_font_size(VM_SMALL_FONT);
    vm_ascii_to_ucs2(title_name, (strlen("Parameter text:") + 1) * 2, "Parameter text:");
    vm_input_set_editor_title(title_name);
    vm_get_exec_filename(fullPath);
    checkFileExist();

}

void handle_sysevt(VMINT message, VMINT param) {

    switch (message) {
        case VM_MSG_CREATE:
        case VM_MSG_ACTIVE:
            layer_hdl[0] =
                vm_graphic_create_layer(0, 0, vm_graphic_get_screen_width(),
                                        vm_graphic_get_screen_height(), -1);
            vm_graphic_set_clip(0, 0, vm_graphic_get_screen_width(),
                                vm_graphic_get_screen_height());
            buffer = vm_graphic_get_layer_buffer(layer_hdl[0]);
            vm_switch_power_saving_mode(turn_off_mode);
            break;

        case VM_MSG_PAINT:
            vm_switch_power_saving_mode(turn_off_mode);
            if (trigerisx == 0 && trigerisy == 0) {vm_exit_app();}
            if (trigeris1 == 1) {trigeris2 = 1;}
            if (trigeris == 0) {trigeris1 = 1;}
            if (trigeris2 == 1 && trigeris3 == 0) {
               trigeris3 = 1;
               vm_input_text3(NULL, 100, 32, save_text);}
            else if (trigeris4 == 1){
               read_file_to_input(file_pathw);
               trigeris4 = 0;
            }
            else{}

            break;

        case VM_MSG_INACTIVE:

            vm_switch_power_saving_mode(turn_on_mode);
            if (layer_hdl[0] != -1) vm_graphic_delete_layer(layer_hdl[0]);
            break;

        case VM_MSG_QUIT:
            if (layer_hdl[0] != -1) vm_graphic_delete_layer(layer_hdl[0]);
            break;
    }
}

void checkFileExist(void) {

    VMWCHAR appTxtName[100];

    create_app_txt_filename(appTxtName);
    create_auto_full_path_name(file_pathw, appTxtName);
  
    vm_input_set_editor_title(title_name);

    f_read = vm_file_open(file_pathw, MODE_READ, FALSE);

    if (f_read < 0) {
        vm_file_close(f_read);
        trigeris = vm_selector_run(0, 0, file);
    } else {
        vm_file_close(f_read);
        read_file_to_input(file_pathw);
       
    }
    return;
}

void save_text(VMINT state, VMWSTR text) {

    int lenght;

    lenght = wstrlen(text);

    if (state == VM_INPUT_OK && lenght > 0) {

       vm_wstrcpy(ucs2_data, text);

       trigerisx = vm_selector_run(0, 0, file1);

    } else { vm_exit_app(); }

}

VMINT file(VMWCHAR *FILE_PATH, VMINT wlen) {

    trigeris = 1;
    trigeris1 = 0;
    trigeris2 = 0;

    vm_wstrcpy(file_pathw, FILE_PATH);
    trigeris4 = 1;
    return 0;
}

VMINT file1(VMWCHAR *FILE_PATH, VMINT wlen) {

    VMCHAR ascii_data[100] = {0};
    VMCHAR ascii_data1[100] = {0};

    trigerisy = 1;

    vm_ucs2_to_ascii(ascii_data, wstrlen(FILE_PATH) + 1, FILE_PATH);
    strncpy(ascii_data1, ascii_data + (strlen(ascii_data) - 4), 4);

    if (vm_string_equals_ignore_case(ascii_data1, ".vxp") == 0) {

       if (vm_wstrcmp(FILE_PATH, fullPath) != 0) {

          //vm_audio_play_beep();;
          vm_start_app_with_para(FILE_PATH, 0, 0, ucs2_data, (vm_wstrlen(ucs2_data) + 1) * 2);

       } else { vm_vibrator_once(); }

    } else { vm_vibrator_once(); }

    trigerisy = 0;

    return 0;
}

void create_auto_full_path_name(VMWSTR result, VMWSTR fname) {

    VMINT drv;
    VMCHAR fAutoFileName[100];
    VMWCHAR wAutoFileName[100];

    if ((drv = vm_get_removable_driver()) < 0) {
       drv = vm_get_system_driver();
    }

    sprintf(fAutoFileName, "%c:\\", drv);
    vm_ascii_to_ucs2(wAutoFileName, (strlen(fAutoFileName) + 1) * 2, fAutoFileName);
    vm_wstrcat(wAutoFileName, fname);
    vm_wstrcpy(result, wAutoFileName);

}

void create_app_txt_filename(VMWSTR text) {

    VMWCHAR fullPath[100];
    VMWCHAR appName[100];
    VMCHAR asciiAppName[100];
    VMCHAR file_name[100];

    vm_get_exec_filename(fullPath);
    vm_get_filename(fullPath, appName);
    vm_ucs2_to_ascii(asciiAppName, wstrlen(appName) + 1, appName);
    memcpy(file_name, asciiAppName, strlen(asciiAppName) - 3);
    file_name[strlen(asciiAppName) - 3] = '\0';
    strcat(file_name, "txt");
    vm_ascii_to_ucs2(text, (strlen(file_name) + 1) * 2, file_name);

}

void read_file_to_input(VMWSTR path) {


   VMCHAR ascii_data[100];
   //VMCHAR UTF8_data[100];

   VMUINT nread;

   f_read = vm_file_open(path, MODE_READ, FALSE);
   vm_file_read(f_read, ascii_data, 100, &nread);
   ascii_data[nread] = '\0';
   vm_file_close(f_read);

   //vm_chset_convert(VM_CHSET_UTF8, VM_CHSET_UCS2, ascii_data, UTF8_data, (strlen(ascii_data) + 1) *2); //utf8
   //vm_wstrcpy(ucs2_data, (VMWSTR)UTF8_data);

   vm_ascii_to_ucs2(ucs2_data, (strlen(ascii_data) + 1) * 2, ascii_data); //+

   trigerisX = 1;
   vm_input_text3(ucs2_data, 100, 32, save_text);
}

void timer(int a) {
     vm_delete_timer_ex(a);
     vm_exit_app();
}

void create_app_new_path(VMWSTR text, VMSTR My_vxp) {

    VMWCHAR fullPath[100] = {0};
    VMWCHAR appName[100] = {0};
    VMWCHAR wfile_extension[100] = {0};

    vm_get_exec_filename(fullPath);
    vm_get_filename(fullPath, appName);
    vm_ascii_to_ucs2(wfile_extension, (strlen(My_vxp) + 1) * 2, My_vxp);
    vm_wstrncpy(text, fullPath, vm_wstrlen(fullPath) - wstrlen(appName));
    vm_wstrcat(text, wfile_extension);

}