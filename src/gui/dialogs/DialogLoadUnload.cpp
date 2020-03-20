#include "DialogLoadUnload.hpp"
#include "DialogLoadUnload.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus
int16_t WINDOW_CLS_DLG_LOADUNLOAD = 0;
#ifdef __cplusplus
}
#endif //__cplusplus

static const char *txt_none = "";
static const char *txt_stop = "STOP";
static const char *txt_cont = "CONTINUE";
static const char *txt_disa = "DISABLE SENSOR";
static const char *txt_yes = "YES";
static const char *txt_no = "NO";

static const PhaseTexts ph_txt_stop = { txt_stop, txt_none, txt_none, txt_none };
static const PhaseTexts ph_txt_cont = { txt_cont, txt_none, txt_none, txt_none };
static const PhaseTexts ph_txt_disa = { txt_disa, txt_none, txt_none, txt_none };
static const PhaseTexts ph_txt_none = { txt_none, txt_none, txt_none, txt_none };
static const PhaseTexts ph_txt_yesno = { txt_yes, txt_no, txt_none, txt_none };

static const char *txt_parking = "Parking";
static const char *txt_wait_temp = "Waiting for temp.";
static const char *txt_prep_ram = "Preparing to ram";
static const char *txt_ram = "Ramming";
static const char *txt_unload = "Unloading";
static const char *txt_push_fil = "Press CONTINUE and\npush filament into\nthe extruder.     ";
static const char *txt_make_sure_inserted = "Make sure the     \nfilament is       \ninserted through  \nthe sensor.       ";
static const char *txt_inserting = "Inserting";
static const char *txt_loading = "Loading to nozzle";
static const char *txt_purging = "Purging";
static const char *txt_is_color = "Is color correct?";

static const RadioButton::window_t radio_win = { gui_defaults.font_big, gui_defaults.color_back, IDialogStateful::get_radio_button_size() };

static DialogLoadUnload::States LoadUnloadFactory() {
    DialogLoadUnload::States ret = {
        DialogLoadUnload::State { txt_parking, RadioButton(radio_win, DialogCommands::GetCommands(PhasesLoadUnload::Parking), ph_txt_stop, true) },
        DialogLoadUnload::State { txt_wait_temp, RadioButton(radio_win, DialogCommands::GetCommands(PhasesLoadUnload::WaitingTemp), ph_txt_stop, true) },
        DialogLoadUnload::State { txt_prep_ram, RadioButton(radio_win, DialogCommands::GetCommands(PhasesLoadUnload::PreparingToRam), ph_txt_stop, false) },
        DialogLoadUnload::State { txt_ram, RadioButton(radio_win, DialogCommands::GetCommands(PhasesLoadUnload::Ramming), ph_txt_stop, false) },
        DialogLoadUnload::State { txt_unload, RadioButton(radio_win, DialogCommands::GetCommands(PhasesLoadUnload::Unloading), ph_txt_stop, false) },
        DialogLoadUnload::State { txt_unload, RadioButton(radio_win, DialogCommands::GetCommands(PhasesLoadUnload::Unloading2), ph_txt_stop, false) },
        DialogLoadUnload::State { txt_push_fil, RadioButton(radio_win, DialogCommands::GetCommands(PhasesLoadUnload::UserPush), ph_txt_cont, true) },
        DialogLoadUnload::State { txt_make_sure_inserted, RadioButton(radio_win, DialogCommands::GetCommands(PhasesLoadUnload::MakeSureInserted), ph_txt_cont, false) },
        DialogLoadUnload::State { txt_inserting, RadioButton(radio_win, DialogCommands::GetCommands(PhasesLoadUnload::Inserting), ph_txt_stop, false) },
        DialogLoadUnload::State { txt_loading, RadioButton(radio_win, DialogCommands::GetCommands(PhasesLoadUnload::Loading), ph_txt_stop, false) },
        DialogLoadUnload::State { txt_purging, RadioButton(radio_win, DialogCommands::GetCommands(PhasesLoadUnload::Purging), ph_txt_stop, false) },
        DialogLoadUnload::State { txt_purging, RadioButton(radio_win, DialogCommands::GetCommands(PhasesLoadUnload::Purging2), ph_txt_none, false) },
        DialogLoadUnload::State { txt_is_color, RadioButton(radio_win, DialogCommands::GetCommands(PhasesLoadUnload::IsColor), ph_txt_yesno, true) },
        DialogLoadUnload::State { txt_purging, RadioButton(radio_win, DialogCommands::GetCommands(PhasesLoadUnload::Purging3), ph_txt_yesno, false) },
    };
    return ret;
}

DialogLoadUnload::DialogLoadUnload(const char *name)
    : DialogStateful<CountPhases<PhasesLoadUnload>()>(name, WINDOW_CLS_DLG_LOADUNLOAD, LoadUnloadFactory()) {}

void DialogLoadUnload::c_draw(window_t *win) {
    IDialog *ptr = cast(win);
    DialogLoadUnload *ths = dynamic_cast<DialogLoadUnload *>(ptr);
    ths->draw();
}

void DialogLoadUnload::c_event(window_t *win, uint8_t event, void *param) {
    IDialog *ptr = cast(win);
    DialogLoadUnload *ths = dynamic_cast<DialogLoadUnload *>(ptr);
    ths->event(event, param);
}

const window_class_dlg_statemachine_t window_class_dlg_statemachine = {
    {
        WINDOW_CLS_USER,
        sizeof(DialogLoadUnload),
#warning is this right?
        0, //(window_init_t *)window_dlg_statemachine_init,
        0,
        (window_draw_t *)DialogLoadUnload::c_draw,
        (window_event_t *)DialogLoadUnload::c_event,
    },
};
