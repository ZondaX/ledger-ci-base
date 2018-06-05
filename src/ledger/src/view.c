/*******************************************************************************
*   (c) 2016 Ledger
*   (c) 2018 ZondaX GmbH
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
********************************************************************************/
#include <string.h>
#include "glyphs.h"
#include "view.h"
#include "view_templates.h"

ux_state_t ux;
enum UI_STATE view_uiState;

char long_text[100];

////////////////////////////////////////////////
//------ View elements

const ux_menu_entry_t menu_main[];
const ux_menu_entry_t menu_about[];

const ux_menu_entry_t menu_main[] = {
        {NULL, NULL, 0, &C_icon_app, "Example", "Demo", 32, 11},
        {menu_about, NULL, 0, NULL, "About", NULL, 0, 0},
        {NULL, os_sched_exit, 0, &C_icon_dashboard, "Quit app", NULL, 50, 29},
        UX_MENU_END
};

const ux_menu_entry_t menu_about[] = {
        {menu_main, NULL, 0, &C_icon_back, "Version", APPVERSION, 0, 0},
        UX_MENU_END
};

static const bagl_element_t bagl_ui_somedata[] = {
        UI_FillRectangle(0, 0, 0, 128, 32, 0x000000, 0xFFFFFF),
        UI_LabelLine(0x02, 0, 11, 128, 11, WHITE, BLACK, "Fixed"),
        UI_LabelLine(0x02, 0, 25, 128, 11, WHITE, BLACK, long_text),
};

void io_seproxyhal_display(const bagl_element_t* element)
{
    io_seproxyhal_display_default((bagl_element_t*) element);
}

const bagl_element_t* bagl_ui_somedata_prepro(const bagl_element_t* element)
{
    switch (element->component.userid) {
    case 0x01:UX_CALLBACK_SET_INTERVAL(2000);
        break;
    case 0x02: {
        UX_CALLBACK_SET_INTERVAL(MAX(3000, 1000+bagl_label_roundtrip_duration_ms(element, 7)));
    }
        break;
    }
    return element;
}

////////////////////////////////////////////////
//------ Event handlers

static unsigned int bagl_ui_somedata_button(
        unsigned int button_mask,
        unsigned int button_mask_counter)
{
    switch (button_mask) {
    case BUTTON_EVT_RELEASED | BUTTON_LEFT:
    case BUTTON_EVT_RELEASED | BUTTON_LEFT | BUTTON_RIGHT: {
        os_sched_exit(0);
    }
        break;
    }
    return 0;
}

////////////////////////////////////////////////
////////////////////////////////////////////////

void view_init(void)
{
    UX_INIT();
    strcpy(long_text, "Key generation is very long");
    view_uiState = UI_IDLE;
}

void view_idle(void)
{
    view_uiState = UI_IDLE;
//    UX_MENU_DISPLAY(0, menu_main, menu_main_prepro);
    UX_DISPLAY(bagl_ui_somedata, bagl_ui_somedata_prepro);
}
