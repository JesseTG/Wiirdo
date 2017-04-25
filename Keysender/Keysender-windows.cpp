#include "Keysender.hpp"

#ifdef Q_OS_WIN

#include <QKeyEvent>
#include <QtGlobal>

#include <winuser.h>

namespace wiirdo {

// Some values for the Windows constants are shared between the VK_* series and the APPCOMMAND_*
// series, so we need this enum to distinguish them.
enum CommandType : uint8_t {
  Vk,
  AppCommand
};

Keysender::Keysender(QObject *parent) : QObject(parent)
{
}

Keysender::~Keysender() {
}

bool Keysender::keyPress(Qt::Key key, Qt::KeyboardModifiers modifiers) {
  return false;
}

bool Keysender::keyRelease(Qt::Key key, Qt::KeyboardModifiers modifiers) {
  return false;
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


// taken from /qtbase/src/plugins/platforms/windows/qwindowskeymapper.cpp
QPair<uint8_t, CommandType> Keysender::qtKeyToNativeKey(unsigned int qtKey) {
  switch (qtKey) {
  case Qt::Key_0: return {VK_NUMPAD0, Vk};
  case Qt::Key_1: return {VK_NUMPAD1, Vk};
  case Qt::Key_2: return {VK_NUMPAD2, Vk};
  case Qt::Key_3: return {VK_NUMPAD3, Vk};
  case Qt::Key_4: return {VK_NUMPAD4, Vk};
  case Qt::Key_5: return {VK_NUMPAD5, Vk};
  case Qt::Key_6: return {VK_NUMPAD6, Vk};
  case Qt::Key_7: return {VK_NUMPAD7, Vk};
  case Qt::Key_8: return {VK_NUMPAD8, Vk};
  case Qt::Key_9: return {VK_NUMPAD9, Vk};
//  case Qt::Key_Alt: return {VK_LMENU, Vk};
  case Qt::Key_Alt: return {VK_MENU, Vk};
//  case Qt::Key_Alt: return {VK_RMENU, Vk};
  case Qt::Key_Asterisk: return {VK_MULTIPLY, Vk};
  case Qt::Key_AudioForward: return {APPCOMMAND_MEDIA_FAST_FORWARD, AppCommand};
  case Qt::Key_AudioRewind: return {APPCOMMAND_MEDIA_REWIND, AppCommand};
//  case Qt::Key_Back: return {APPCOMMAND_BROWSER_BACKWARD, AppCommand};
  case Qt::Key_Back: return {VK_BROWSER_BACK, Vk};
  case Qt::Key_Backspace: return {VK_BACK, Vk};
  case Qt::Key_BassBoost: return {APPCOMMAND_BASS_BOOST, AppCommand};
  case Qt::Key_BassDown: return {APPCOMMAND_BASS_DOWN, AppCommand};
  case Qt::Key_BassUp: return {APPCOMMAND_BASS_UP, AppCommand};
  case Qt::Key_Cancel: return {VK_CANCEL, Vk};
  case Qt::Key_CapsLock: return {VK_CAPITAL, Vk};
  case Qt::Key_ChannelDown: return {APPCOMMAND_MEDIA_CHANNEL_DOWN, AppCommand};
  case Qt::Key_ChannelUp: return {APPCOMMAND_MEDIA_CHANNEL_UP, AppCommand};
  case Qt::Key_Clear: return {VK_CLEAR, Vk};
//  case Qt::Key_Clear: return {VK_OEM_CLEAR, Vk};
  case Qt::Key_Close: return {APPCOMMAND_CLOSE, AppCommand};
  case Qt::Key_Comma: return {VK_SEPARATOR, Vk};
  case Qt::Key_Control: return {VK_CONTROL, Vk};
//  case Qt::Key_Control: return {VK_LCONTROL, Vk};
//  case Qt::Key_Control: return {VK_RCONTROL, Vk};
  case Qt::Key_Copy: return {APPCOMMAND_COPY, AppCommand};
  case Qt::Key_Cut: return {APPCOMMAND_CUT, AppCommand};
  case Qt::Key_Delete: return {VK_DELETE, Vk};
  case Qt::Key_Down: return {VK_DOWN, Vk};
  case Qt::Key_End: return {VK_END, Vk};
  case Qt::Key_Escape: return {VK_ESCAPE, Vk};
  case Qt::Key_Execute: return {VK_EXECUTE, Vk};
  case Qt::Key_F10: return {VK_F10, Vk};
  case Qt::Key_F11: return {VK_F11, Vk};
  case Qt::Key_F12: return {VK_F12, Vk};
  case Qt::Key_F13: return {VK_F13, Vk};
  case Qt::Key_F14: return {VK_F14, Vk};
  case Qt::Key_F15: return {VK_F15, Vk};
  case Qt::Key_F16: return {VK_F16, Vk};
  case Qt::Key_F17: return {VK_F17, Vk};
  case Qt::Key_F18: return {VK_F18, Vk};
  case Qt::Key_F19: return {VK_F19, Vk};
  case Qt::Key_F1: return {VK_F1, Vk};
  case Qt::Key_F20: return {VK_F20, Vk};
  case Qt::Key_F21: return {VK_F21, Vk};
  case Qt::Key_F22: return {VK_F22, Vk};
  case Qt::Key_F23: return {VK_F23, Vk};
  case Qt::Key_F24: return {VK_F24, Vk};
  case Qt::Key_F2: return {VK_F2, Vk};
  case Qt::Key_F3: return {VK_F3, Vk};
  case Qt::Key_F4: return {VK_F4, Vk};
  case Qt::Key_F5: return {VK_F5, Vk};
  case Qt::Key_F6: return {VK_F6, Vk};
  case Qt::Key_F7: return {VK_F7, Vk};
  case Qt::Key_F8: return {VK_F8, Vk};
  case Qt::Key_F9: return {VK_F9, Vk};
//  case Qt::Key_Favorites: return {APPCOMMAND_BROWSER_FAVORITES, AppCommand};
  case Qt::Key_Favorites: return {VK_BROWSER_FAVORITES, Vk};
  case Qt::Key_Find: return {APPCOMMAND_FIND, AppCommand};
//  case Qt::Key_Forward: return {APPCOMMAND_BROWSER_FORWARD, AppCommand};
  case Qt::Key_Forward: return {VK_BROWSER_FORWARD, Vk};
//  case Qt::Key_Help: return {APPCOMMAND_HELP, AppCommand};
  case Qt::Key_Help: return {VK_HELP, Vk};
//  case Qt::Key_Home: return {APPCOMMAND_BROWSER_HOME, AppCommand};
  case Qt::Key_Home: return {VK_HOME, Vk};
  case Qt::Key_HomePage: return {VK_BROWSER_HOME, Vk};
  case Qt::Key_Insert: return {VK_INSERT, Vk};
//  case Qt::Key_Launch0: return {APPCOMMAND_LAUNCH_APP1, AppCommand};
  case Qt::Key_Launch0: return {VK_LAUNCH_APP1, Vk};
//  case Qt::Key_Launch1: return {APPCOMMAND_LAUNCH_APP2, AppCommand};
  case Qt::Key_Launch1: return {VK_LAUNCH_APP2, Vk};
//  case Qt::Key_LaunchMail: return {APPCOMMAND_LAUNCH_MAIL, AppCommand};
  case Qt::Key_LaunchMail: return {VK_LAUNCH_MAIL, Vk};
//  case Qt::Key_LaunchMedia: return {APPCOMMAND_LAUNCH_MEDIA_SELECT, AppCommand};
  case Qt::Key_LaunchMedia: return {VK_LAUNCH_MEDIA_SELECT, Vk};
  case Qt::Key_Left: return {VK_LEFT, Vk};
  case Qt::Key_MailForward: return {APPCOMMAND_FORWARD_MAIL, AppCommand};
  case Qt::Key_Massyo: return {VK_OEM_FJ_MASSHOU, Vk};
//  case Qt::Key_MediaNext: return {APPCOMMAND_MEDIA_NEXTTRACK, AppCommand};
  case Qt::Key_MediaNext: return {VK_MEDIA_NEXT_TRACK, Vk};
  case Qt::Key_MediaPause: return {APPCOMMAND_MEDIA_PAUSE, AppCommand};
  //case Qt::Key_MediaPlay: return {APPCOMMAND_MEDIA_PLAY, AppCommand};
  case Qt::Key_MediaPlay: return {VK_MEDIA_PLAY_PAUSE, Vk};
  //case Qt::Key_MediaPrevious: return {APPCOMMAND_MEDIA_PREVIOUSTRACK, AppCommand};
  case Qt::Key_MediaPrevious: return {VK_MEDIA_PREV_TRACK, Vk};
  case Qt::Key_MediaRecord: return {APPCOMMAND_MEDIA_RECORD, AppCommand};
//  case Qt::Key_MediaStop: return {APPCOMMAND_MEDIA_STOP, AppCommand};
  case Qt::Key_MediaStop: return {VK_MEDIA_STOP, Vk};
  case Qt::Key_MediaTogglePlayPause: return {APPCOMMAND_MEDIA_PLAY_PAUSE, AppCommand};
  case Qt::Key_Menu: return {VK_APPS, Vk};
  case Qt::Key_Meta: return {VK_LWIN, Vk};
//  case Qt::Key_Meta: return {VK_RWIN, Vk};
  case Qt::Key_MicMute: return {APPCOMMAND_MICROPHONE_VOLUME_MUTE, AppCommand};
  case Qt::Key_MicVolumeDown: return {APPCOMMAND_MICROPHONE_VOLUME_DOWN, AppCommand};
  case Qt::Key_MicVolumeUp: return {APPCOMMAND_MICROPHONE_VOLUME_UP, AppCommand};
  case Qt::Key_Minus: return {VK_SUBTRACT, Vk};
  case Qt::Key_Mode_switch: return {VK_MODECHANGE, Vk};
  case Qt::Key_New: return {APPCOMMAND_NEW, AppCommand};
  case Qt::Key_NumLock: return {VK_NUMLOCK, Vk};
  case Qt::Key_Open: return {APPCOMMAND_OPEN, AppCommand};
  case Qt::Key_PageDown: return {VK_NEXT, Vk};
  case Qt::Key_PageUp: return {VK_PRIOR, Vk};
  case Qt::Key_Paste: return {APPCOMMAND_PASTE, AppCommand};
  case Qt::Key_Pause: return {VK_PAUSE, Vk};
  case Qt::Key_Period: return {VK_DECIMAL, Vk};
  case Qt::Key_Play: return {VK_PLAY, Vk};
  case Qt::Key_Plus: return {VK_ADD, Vk};
  case Qt::Key_Print: return {VK_SNAPSHOT, Vk};
  //case Qt::Key_Printer: return {APPCOMMAND_PRINT, AppCommand};
  case Qt::Key_Printer: return {VK_PRINT, Vk};
  case Qt::Key_Redo: return {APPCOMMAND_REDO, AppCommand};
 // case Qt::Key_Refresh: return {APPCOMMAND_BROWSER_REFRESH, AppCommand};
  case Qt::Key_Refresh: return {VK_BROWSER_REFRESH, Vk};
  case Qt::Key_Reply: return {APPCOMMAND_REPLY_TO_MAIL, AppCommand};
  case Qt::Key_Return: return {VK_RETURN, Vk};
  case Qt::Key_Right: return {VK_RIGHT, Vk};
  case Qt::Key_Save: return {APPCOMMAND_SAVE, AppCommand};
  case Qt::Key_ScrollLock: return {VK_SCROLL, Vk};
  //case Qt::Key_Search: return {APPCOMMAND_BROWSER_SEARCH, AppCommand};
  case Qt::Key_Search: return {VK_BROWSER_SEARCH, Vk};
  case Qt::Key_Select: return {VK_SELECT, Vk};
  case Qt::Key_Send: return {APPCOMMAND_SEND_MAIL, AppCommand};
  //case Qt::Key_Shift: return {VK_LSHIFT, Vk};
  //case Qt::Key_Shift: return {VK_RSHIFT, Vk};
  case Qt::Key_Shift: return {VK_SHIFT, Vk};
  case Qt::Key_Slash: return {VK_DIVIDE, Vk};
  case Qt::Key_Sleep: return {VK_SLEEP, Vk};
  case Qt::Key_Space: return {VK_SPACE, Vk};
  case Qt::Key_Spell: return {APPCOMMAND_SPELL_CHECK, AppCommand};
 // case Qt::Key_Stop: return {APPCOMMAND_BROWSER_STOP, AppCommand};
  case Qt::Key_Stop: return {VK_BROWSER_STOP, Vk};
  case Qt::Key_Tab: return {VK_TAB, Vk};
  case Qt::Key_Touroku: return {VK_OEM_FJ_TOUROKU, Vk};
  case Qt::Key_TrebleDown: return {APPCOMMAND_TREBLE_DOWN, AppCommand};
  case Qt::Key_TrebleUp: return {APPCOMMAND_TREBLE_UP, AppCommand};
  case Qt::Key_Undo: return {APPCOMMAND_UNDO, AppCommand};
  case Qt::Key_Up: return {VK_UP, Vk};
 // case Qt::Key_VolumeDown: return {APPCOMMAND_VOLUME_DOWN, AppCommand};
  case Qt::Key_VolumeDown: return {VK_VOLUME_DOWN, Vk};
 // case Qt::Key_VolumeMute: return {APPCOMMAND_VOLUME_MUTE, AppCommand};
  case Qt::Key_VolumeMute: return {VK_VOLUME_MUTE, Vk};
 // case Qt::Key_VolumeUp: return {APPCOMMAND_VOLUME_UP, AppCommand};
  case Qt::Key_VolumeUp: return {VK_VOLUME_UP, Vk};
  case Qt::Key_Zoom: return {VK_ZOOM, Vk};
  default: return {qtKey, Vk};
  // The ASCII keys (A, 6, F, etc.) take their ASCII values and are treated as VK_*'s
  }
}

}
#else
#error "Keysender-windows.cpp can only be built on Windows"
#endif
