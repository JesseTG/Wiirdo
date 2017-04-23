#include "Keysender.hpp"

#ifdef Q_OS_LINUX
#include <QtDebug>
#include <QtGlobal>
#include <X11/keysym.h>
#include <X11/XF86keysym.h>
#include <X11/extensions/XTest.h>

// regex: (?!\/\/)((?>X[KF]|0x)[\w\d_]+),\s*(Qt::[\w\d_]+),
namespace wiirdo {

unsigned int qtKeyToNativeKey(unsigned int qtKey);
bool keyEvent(Display* x11, Qt::Key key, Qt::KeyboardModifiers modifiers, bool down);

Keysender::Keysender(QObject *parent) : QObject(parent), x11(XOpenDisplay(nullptr))
{
  // XTestFakeKeyEvent(x11, 0, 0, 0); TODO: Do a proper test and throw if it fails
}

Keysender::~Keysender() {
  XCloseDisplay(x11);
}

bool Keysender::keyPress(Qt::Key key, Qt::KeyboardModifiers modifiers) {
  return keyEvent(x11, key, modifiers, true);
}

bool Keysender::keyRelease(Qt::Key key, Qt::KeyboardModifiers modifiers) {
  return keyEvent(x11, key, modifiers, false);
}

bool Keysender::keyShortcutOverride(const QKeyEvent& event) {
  return false;
}

bool Keysender::mouseEvent(const QMouseEvent& event) {
  return false;
}

bool Keysender::wheelEvent(const QWheelEvent& event) {
  return false;
}

bool Keysender::shortcutEvent(const QShortcutEvent& event) {
  return false;
}

bool keyEvent(Display* x11, Qt::Key key, Qt::KeyboardModifiers modifiers, bool down) {
  // TODO: Support modifiers

  if (x11 == nullptr) {
    // If we don't have a valid X11 display to begin with...
    return false;
  }
  else if (key == Qt::Key_unknown) {
    // Else if we're using an entirely foreign key...
    return false;
  }

  KeyCode code = XKeysymToKeycode(x11, qtKeyToNativeKey(key));

  if (code == 0) {
    // If the key code we want to send out is unknown...
    return false;
  }

  if (!XTestFakeKeyEvent(x11, code, down, 0)) {
    // If the key event failed...
    return false;
  }
  XFlush(x11);

  return true;
}

// taken from qtbase/src/plugins/platforms/xcb/qxcbkeyboard.cpp
unsigned int qtKeyToNativeKey(unsigned int qtKey) {

  // misc keys
  switch (qtKey) {
  case Qt::Key_Escape: return XK_Escape;
  case Qt::Key_Tab: return XK_Tab;
  case Qt::Key_Backtab: return XK_ISO_Left_Tab;
  case Qt::Key_Backspace: return XK_BackSpace;
  case Qt::Key_Return: return XK_Return;
  case Qt::Key_Insert: return XK_Insert;
  case Qt::Key_Delete: return XK_Delete;
    //    case Qt::Key_Delete: return XK_Clear;
  case Qt::Key_Pause: return XK_Pause;
  case Qt::Key_Print: return XK_Print;
    //    case Qt::Key_SysReq: return 0x1005FF60;         // hardcoded Sun SysReq
  case Qt::Key_SysReq: return 0x1007ff00;         // hardcoded X386 SysReq

    // cursor movement

  case Qt::Key_L: return XK_L;
  case Qt::Key_Home: return XK_Home;
  case Qt::Key_End: return XK_End;
  case Qt::Key_Left: return XK_Left;
  case Qt::Key_Up: return XK_Up;
  case Qt::Key_Right: return XK_Right;
  case Qt::Key_Down: return XK_Down;
  case Qt::Key_PageUp: return XK_Prior;
  case Qt::Key_PageDown: return XK_Next;

    // modifiers
  case Qt::Key_Shift: return XK_Shift_L;
    //    case Qt::Key_Shift: return XK_Shift_R;
    //    case Qt::Key_Shift: return XK_Shift_Lock;
  case Qt::Key_Control: return XK_Control_L;
    //    case Qt::Key_Control: return XK_Control_R;
  case Qt::Key_Meta: return XK_Meta_L;
    //    case Qt::Key_Meta: return XK_Meta_R;
  case Qt::Key_Alt: return XK_Alt_L;
    //    case Qt::Key_Alt: return XK_Alt_R;
  case Qt::Key_CapsLock: return XK_Caps_Lock;
  case Qt::Key_NumLock: return XK_Num_Lock;
  case Qt::Key_ScrollLock: return XK_Scroll_Lock;
  case Qt::Key_Super_L: return XK_Super_L;
  case Qt::Key_Super_R: return XK_Super_R;
  case Qt::Key_Menu: return XK_Menu;
  case Qt::Key_Hyper_L: return XK_Hyper_L;
  case Qt::Key_Hyper_R: return XK_Hyper_R;
  case Qt::Key_Help: return XK_Help;
    //    case Qt::Key_Backtab: return 0x1000FF74;        // hardcoded HP backtab
  case Qt::Key_F11: return 0x1005FF10;            // hardcoded Sun F36 (labeled F11)
  case Qt::Key_F12: return 0x1005FF11;            // hardcoded Sun F37 (labeled F12)

    // numeric and function keypad keys

  case Qt::Key_Space: return XK_KP_Space;
    //    case Qt::Key_Tab: return XK_KP_Tab;
  case Qt::Key_Enter: return XK_KP_Enter;
    //case Qt::Key_F1: return XK_KP_F1;
    //case Qt::Key_F2: return XK_KP_F2;
    //case Qt::Key_F3: return XK_KP_F3;
    //case Qt::Key_F4: return XK_KP_F4;
    //    case Qt::Key_Home: return XK_KP_Home;
    //    case Qt::Key_Left: return XK_KP_Left;
    //    case Qt::Key_Up: return XK_KP_Up;
    //    case Qt::Key_Right: return XK_KP_Right;
    //    case Qt::Key_Down: return XK_KP_Down;
    //    case Qt::Key_PageUp: return XK_KP_Prior;
    //    case Qt::Key_PageDown: return XK_KP_Next;
    //    case Qt::Key_End: return XK_KP_End;
  case Qt::Key_Clear: return XK_KP_Begin;
    //    case Qt::Key_Insert: return XK_KP_Insert;
    //    case Qt::Key_Delete: return XK_KP_Delete;
  case Qt::Key_Equal: return XK_KP_Equal;
  case Qt::Key_Asterisk: return XK_KP_Multiply;
  case Qt::Key_Plus: return XK_KP_Add;
  case Qt::Key_Comma: return XK_KP_Separator;
  case Qt::Key_Minus: return XK_KP_Subtract;
  case Qt::Key_Period: return XK_KP_Decimal;
  case Qt::Key_Slash: return XK_KP_Divide;

    // International input method support keys

    // International & multi-key character composition
  case Qt::Key_AltGr: return XK_ISO_Level3_Shift;
  case Qt::Key_Multi_key: return XK_Multi_key;
  case Qt::Key_Codeinput: return XK_Codeinput;
  case Qt::Key_SingleCandidate: return XK_SingleCandidate;
  case Qt::Key_MultipleCandidate: return XK_MultipleCandidate;
  case Qt::Key_PreviousCandidate: return XK_PreviousCandidate;

    // Misc Functions
  case Qt::Key_Mode_switch: return XK_Mode_switch;
    //    case Qt::Key_Mode_switch: return XK_script_switch;

    // Japanese keyboard support
  case Qt::Key_Kanji: return XK_Kanji;
  case Qt::Key_Muhenkan: return XK_Muhenkan;
    //case Qt::Key_Henkan_Mode: return XK_Henkan_Mode;
  case Qt::Key_Henkan: return XK_Henkan_Mode;
    //    case Qt::Key_Henkan: return XK_Henkan;
  case Qt::Key_Romaji: return XK_Romaji;
  case Qt::Key_Hiragana: return XK_Hiragana;
  case Qt::Key_Katakana: return XK_Katakana;
  case Qt::Key_Hiragana_Katakana: return XK_Hiragana_Katakana;
  case Qt::Key_Zenkaku: return XK_Zenkaku;
  case Qt::Key_Hankaku: return XK_Hankaku;
  case Qt::Key_Zenkaku_Hankaku: return XK_Zenkaku_Hankaku;
  case Qt::Key_Touroku: return XK_Touroku;
  case Qt::Key_Massyo: return XK_Massyo;
  case Qt::Key_Kana_Lock: return XK_Kana_Lock;
  case Qt::Key_Kana_Shift: return XK_Kana_Shift;
  case Qt::Key_Eisu_Shift: return XK_Eisu_Shift;
  case Qt::Key_Eisu_toggle: return XK_Eisu_toggle;
    //case Qt::Key_Kanji_Bangou: return XK_Kanji_Bangou;
    //case Qt::Key_Zen_Koho: return XK_Zen_Koho;
    //case Qt::Key_Mae_Koho: return XK_Mae_Koho;
    //    case Qt::Key_Codeinput: return XK_Kanji_Bangou;
    //    case Qt::Key_MultipleCandidate: return XK_Zen_Koho;
    //    case Qt::Key_PreviousCandidate: return XK_Mae_Koho;

#ifdef XK_KOREAN
    // Korean keyboard support
  case Qt::Key_Hangul: return XK_Hangul;
  case Qt::Key_Hangul_Start: return XK_Hangul_Start;
  case Qt::Key_Hangul_End: return XK_Hangul_End;
  case Qt::Key_Hangul_Hanja: return XK_Hangul_Hanja;
  case Qt::Key_Hangul_Jamo: return XK_Hangul_Jamo;
  case Qt::Key_Hangul_Romaja: return XK_Hangul_Romaja;
    //case Qt::Key_Hangul_Codeinput: return XK_Hangul_Codeinput;
    //    case Qt::Key_Codeinput: return XK_Hangul_Codeinput;
  case Qt::Key_Hangul_Jeonja: return XK_Hangul_Jeonja;
  case Qt::Key_Hangul_Banja: return XK_Hangul_Banja;
  case Qt::Key_Hangul_PreHanja: return XK_Hangul_PreHanja;
  case Qt::Key_Hangul_PostHanja: return XK_Hangul_PostHanja;
    //case Qt::Key_Hangul_SingleCandidate: return XK_Hangul_SingleCandidate;
    //case Qt::Key_Hangul_MultipleCandidate: return XK_Hangul_MultipleCandidate;
    //case Qt::Key_Hangul_PreviousCandidate: return XK_Hangul_PreviousCandidate;
    //    case Qt::Key_SingleCandidate: return XK_Hangul_SingleCandidate;
    //    case Qt::Key_MultipleCandidate: return XK_Hangul_MultipleCandidate;
    //    case Qt::Key_PreviousCandidate: return XK_Hangul_PreviousCandidate;
  case Qt::Key_Hangul_Special: return XK_Hangul_Special;
    //case Qt::Key_Hangul_switch: return XK_Hangul_switch;
    //    case Qt::Key_Mode_switch: return XK_Hangul_switch;
#endif  // XK_KOREAN

    // dead keys
  case Qt::Key_Dead_Grave: return XK_dead_grave;
  case Qt::Key_Dead_Acute: return XK_dead_acute;
  case Qt::Key_Dead_Circumflex: return XK_dead_circumflex;
  case Qt::Key_Dead_Tilde: return XK_dead_tilde;
  case Qt::Key_Dead_Macron: return XK_dead_macron;
  case Qt::Key_Dead_Breve: return XK_dead_breve;
  case Qt::Key_Dead_Abovedot: return XK_dead_abovedot;
  case Qt::Key_Dead_Diaeresis: return XK_dead_diaeresis;
  case Qt::Key_Dead_Abovering: return XK_dead_abovering;
  case Qt::Key_Dead_Doubleacute: return XK_dead_doubleacute;
  case Qt::Key_Dead_Caron: return XK_dead_caron;
  case Qt::Key_Dead_Cedilla: return XK_dead_cedilla;
  case Qt::Key_Dead_Ogonek: return XK_dead_ogonek;
  case Qt::Key_Dead_Iota: return XK_dead_iota;
  case Qt::Key_Dead_Voiced_Sound: return XK_dead_voiced_sound;
  case Qt::Key_Dead_Semivoiced_Sound: return XK_dead_semivoiced_sound;
  case Qt::Key_Dead_Belowdot: return XK_dead_belowdot;
  case Qt::Key_Dead_Hook: return XK_dead_hook;
  case Qt::Key_Dead_Horn: return XK_dead_horn;

    // Special keys from X.org - This include multimedia keys,
    // wireless/bluetooth/uwb keys, special launcher keys, etc.
  case Qt::Key_Back: return XF86XK_Back;
  case Qt::Key_Forward: return XF86XK_Forward;
  case Qt::Key_Stop: return XF86XK_Stop;
  case Qt::Key_Refresh: return XF86XK_Refresh;
  case Qt::Key_Favorites: return XF86XK_Favorites;
  case Qt::Key_LaunchMedia: return XF86XK_AudioMedia;
  case Qt::Key_OpenUrl: return XF86XK_OpenURL;
  case Qt::Key_HomePage: return XF86XK_HomePage;
  case Qt::Key_Search: return XF86XK_Search;
  case Qt::Key_VolumeDown: return XF86XK_AudioLowerVolume;
  case Qt::Key_VolumeMute: return XF86XK_AudioMute;
  case Qt::Key_VolumeUp: return XF86XK_AudioRaiseVolume;
  case Qt::Key_MediaPlay: return XF86XK_AudioPlay;
  case Qt::Key_MediaStop: return XF86XK_AudioStop;
  case Qt::Key_MediaPrevious: return XF86XK_AudioPrev;
  case Qt::Key_MediaNext: return XF86XK_AudioNext;
  case Qt::Key_MediaRecord: return XF86XK_AudioRecord;
  case Qt::Key_MediaPause: return XF86XK_AudioPause;
  case Qt::Key_LaunchMail: return XF86XK_Mail;
  case Qt::Key_Launch0: return XF86XK_MyComputer;  // ### Qt 6: remap properly
  case Qt::Key_Launch1: return XF86XK_Calculator;
  case Qt::Key_Memo: return XF86XK_Memo;
  case Qt::Key_ToDoList: return XF86XK_ToDoList;
  case Qt::Key_Calendar: return XF86XK_Calendar;
  case Qt::Key_PowerDown: return XF86XK_PowerDown;
  case Qt::Key_ContrastAdjust: return XF86XK_ContrastAdjust;
  case Qt::Key_Standby: return XF86XK_Standby;
  case Qt::Key_MonBrightnessUp: return XF86XK_MonBrightnessUp;
  case Qt::Key_MonBrightnessDown: return XF86XK_MonBrightnessDown;
  case Qt::Key_KeyboardLightOnOff: return XF86XK_KbdLightOnOff;
  case Qt::Key_KeyboardBrightnessUp: return XF86XK_KbdBrightnessUp;
  case Qt::Key_KeyboardBrightnessDown: return XF86XK_KbdBrightnessDown;
  case Qt::Key_PowerOff: return XF86XK_PowerOff;
  case Qt::Key_WakeUp: return XF86XK_WakeUp;
  case Qt::Key_Eject: return XF86XK_Eject;
  case Qt::Key_ScreenSaver: return XF86XK_ScreenSaver;
  case Qt::Key_WWW: return XF86XK_WWW;
  case Qt::Key_Sleep: return XF86XK_Sleep;
  case Qt::Key_LightBulb: return XF86XK_LightBulb;
  case Qt::Key_Shop: return XF86XK_Shop;
  case Qt::Key_History: return XF86XK_History;
  case Qt::Key_AddFavorite: return XF86XK_AddFavorite;
  case Qt::Key_HotLinks: return XF86XK_HotLinks;
  case Qt::Key_BrightnessAdjust: return XF86XK_BrightnessAdjust;
  case Qt::Key_Finance: return XF86XK_Finance;
  case Qt::Key_Community: return XF86XK_Community;
  case Qt::Key_AudioRewind: return XF86XK_AudioRewind;
  case Qt::Key_BackForward: return XF86XK_BackForward;
  case Qt::Key_ApplicationLeft: return XF86XK_ApplicationLeft;
  case Qt::Key_ApplicationRight: return XF86XK_ApplicationRight;
  case Qt::Key_Book: return XF86XK_Book;
  case Qt::Key_CD: return XF86XK_CD;
  case Qt::Key_Calculator: return XF86XK_Calculater;
    //    case Qt::Key_Clear: return XF86XK_Clear;
  case Qt::Key_ClearGrab: return XF86XK_ClearGrab;
  case Qt::Key_Close: return XF86XK_Close;
  case Qt::Key_Copy: return XF86XK_Copy;
  case Qt::Key_Cut: return XF86XK_Cut;
  case Qt::Key_Display: return XF86XK_Display;
  case Qt::Key_DOS: return XF86XK_DOS;
  case Qt::Key_Documents: return XF86XK_Documents;
  case Qt::Key_Excel: return XF86XK_Excel;
  case Qt::Key_Explorer: return XF86XK_Explorer;
  case Qt::Key_Game: return XF86XK_Game;
  case Qt::Key_Go: return XF86XK_Go;
  case Qt::Key_iTouch: return XF86XK_iTouch;
  case Qt::Key_LogOff: return XF86XK_LogOff;
  case Qt::Key_Market: return XF86XK_Market;
  case Qt::Key_Meeting: return XF86XK_Meeting;
  case Qt::Key_MenuKB: return XF86XK_MenuKB;
  case Qt::Key_MenuPB: return XF86XK_MenuPB;
  case Qt::Key_MySites: return XF86XK_MySites;
  case Qt::Key_New: return XF86XK_New;
  case Qt::Key_News: return XF86XK_News;
  case Qt::Key_OfficeHome: return XF86XK_OfficeHome;
  case Qt::Key_Open: return XF86XK_Open;
  case Qt::Key_Option: return XF86XK_Option;
  case Qt::Key_Paste: return XF86XK_Paste;
  case Qt::Key_Phone: return XF86XK_Phone;
  case Qt::Key_Reply: return XF86XK_Reply;
  case Qt::Key_Reload: return XF86XK_Reload;
  case Qt::Key_RotateWindows: return XF86XK_RotateWindows;
  case Qt::Key_RotationPB: return XF86XK_RotationPB;
  case Qt::Key_RotationKB: return XF86XK_RotationKB;
  case Qt::Key_Save: return XF86XK_Save;
  case Qt::Key_Send: return XF86XK_Send;
  case Qt::Key_Spell: return XF86XK_Spell;
  case Qt::Key_SplitScreen: return XF86XK_SplitScreen;
  case Qt::Key_Support: return XF86XK_Support;
  case Qt::Key_TaskPane: return XF86XK_TaskPane;
  case Qt::Key_Terminal: return XF86XK_Terminal;
  case Qt::Key_Tools: return XF86XK_Tools;
  case Qt::Key_Travel: return XF86XK_Travel;
  case Qt::Key_Video: return XF86XK_Video;
  case Qt::Key_Word: return XF86XK_Word;
  case Qt::Key_Xfer: return XF86XK_Xfer;
  case Qt::Key_ZoomIn: return XF86XK_ZoomIn;
  case Qt::Key_ZoomOut: return XF86XK_ZoomOut;
  case Qt::Key_Away: return XF86XK_Away;
  case Qt::Key_Messenger: return XF86XK_Messenger;
  case Qt::Key_WebCam: return XF86XK_WebCam;
  case Qt::Key_MailForward: return XF86XK_MailForward;
  case Qt::Key_Pictures: return XF86XK_Pictures;
  case Qt::Key_Music: return XF86XK_Music;
  case Qt::Key_Battery: return XF86XK_Battery;
  case Qt::Key_Bluetooth: return XF86XK_Bluetooth;
  case Qt::Key_WLAN: return XF86XK_WLAN;
  case Qt::Key_UWB: return XF86XK_UWB;
  case Qt::Key_AudioForward: return XF86XK_AudioForward;
  case Qt::Key_AudioRepeat: return XF86XK_AudioRepeat;
  case Qt::Key_AudioRandomPlay: return XF86XK_AudioRandomPlay;
  case Qt::Key_Subtitle: return XF86XK_Subtitle;
  case Qt::Key_AudioCycleTrack: return XF86XK_AudioCycleTrack;
  case Qt::Key_Time: return XF86XK_Time;
  case Qt::Key_Select: return XF86XK_Select;
  case Qt::Key_View: return XF86XK_View;
  case Qt::Key_TopMenu: return XF86XK_TopMenu;
  case Qt::Key_Red: return XF86XK_Red;
  case Qt::Key_Green: return XF86XK_Green;
  case Qt::Key_Yellow: return XF86XK_Yellow;
  case Qt::Key_Blue: return XF86XK_Blue;
    //    case Qt::Key_Bluetooth: return XF86XK_Bluetooth;
  case Qt::Key_Suspend: return XF86XK_Suspend;
  case Qt::Key_Hibernate: return XF86XK_Hibernate;
  case Qt::Key_TouchpadToggle: return XF86XK_TouchpadToggle;
  case Qt::Key_TouchpadOn: return XF86XK_TouchpadOn;
  case Qt::Key_TouchpadOff: return XF86XK_TouchpadOff;
  case Qt::Key_MicMute: return XF86XK_AudioMicMute;
  case Qt::Key_Launch2: return XF86XK_Launch0; // ### Qt 6: remap properly
  case Qt::Key_Launch3: return XF86XK_Launch1;
  case Qt::Key_Launch4: return XF86XK_Launch2;
  case Qt::Key_Launch5: return XF86XK_Launch3;
  case Qt::Key_Launch6: return XF86XK_Launch4;
  case Qt::Key_Launch7: return XF86XK_Launch5;
  case Qt::Key_Launch8: return XF86XK_Launch6;
  case Qt::Key_Launch9: return XF86XK_Launch7;
  case Qt::Key_LaunchA: return XF86XK_Launch8;
  case Qt::Key_LaunchB: return XF86XK_Launch9;
  case Qt::Key_LaunchC: return XF86XK_LaunchA;
  case Qt::Key_LaunchD: return XF86XK_LaunchB;
  case Qt::Key_LaunchE: return XF86XK_LaunchC;
  case Qt::Key_LaunchF: return XF86XK_LaunchD;
  case Qt::Key_LaunchG: return XF86XK_LaunchE;
  case Qt::Key_LaunchH: return XF86XK_LaunchF;
  default: return qtKey; // XK_VoidSymbol
}
};

}
#else
#error "Keysender-linux.cpp can only be built on Linux"
#endif
