/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * FreeRDP Mac OS X Server (Input)
 *
 * Copyright 2013 Corey Clayton <can.of.tuna@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>

#include <winpr/windows.h>

#include "mf_input.h"
#include "mf_info.h"

static const CGKeyCode keymap[256] = {
	0xFF, //0x0
	0xFF, //0x1
	kVK_ANSI_1, //0x2
	kVK_ANSI_2, //0x3
	kVK_ANSI_3, //0x4
	kVK_ANSI_4, //0x5
	kVK_ANSI_5, //0x6
	kVK_ANSI_6, //0x7
	kVK_ANSI_7, //0x8
	kVK_ANSI_8, //0x9
	kVK_ANSI_9, //0xa
	kVK_ANSI_0, //0xb
	0xFF, //0xc
	0xFF, //0xd
	kVK_Delete, //0xe
	0xFF, //0xf
	kVK_ANSI_Q, //0x10
	kVK_ANSI_W, //0x11
	kVK_ANSI_E, //0x12
	kVK_ANSI_R, //0x13
	kVK_ANSI_T, //0x14
	kVK_ANSI_Y, //0x15
	kVK_ANSI_U, //0x16
	kVK_ANSI_I, //0x17
	kVK_ANSI_O, //0x18
	kVK_ANSI_P, //0x19
	kVK_ANSI_LeftBracket, //0x1a
	kVK_ANSI_RightBracket, //0x1b
	0xFF, //0x1c
	0xFF, //0x1d
	kVK_ANSI_A, //0x1e
	kVK_ANSI_S, //0x1f
	kVK_ANSI_D, //0x20
	kVK_ANSI_F, //0x21
	kVK_ANSI_G, //0x22
	kVK_ANSI_H, //0x23
	kVK_ANSI_J, //0x24
	kVK_ANSI_K, //0x25
	kVK_ANSI_L, //0x26
	kVK_ANSI_Semicolon, //0x27
	kVK_ANSI_Quote, //0x28
	kVK_ANSI_Grave, //0x29
	0xFF, //0x2a
	kVK_ANSI_Backslash, //0x2b
	0xFF, //0x2c
	0xFF, //0x2d
	0xFF, //0x2e
	0xFF, //0x2f
	0xFF, //0x30
	0xFF, //0x31
	0xFF, //0x32
	0xFF, //0x33
	0xFF, //0x34
	0xFF, //0x35
	0xFF, //0x36
	0xFF, //0x37
	0xFF, //0x38
	0xFF, //0x39
	0xFF, //0x3a
	0xFF, //0x3b
	0xFF, //0x3c
	0xFF, //0x3d
	0xFF, //0x3e
	0xFF, //0x3f
	0xFF, //0x40
	0xFF, //0x41
	0xFF, //0x42
	0xFF, //0x43
	0xFF, //0x44
	0xFF, //0x45
	0xFF, //0x46
	0xFF, //0x47
	0xFF, //0x48
	0xFF, //0x49
	0xFF, //0x4a
	0xFF, //0x4b
	0xFF, //0x4c
	0xFF, //0x4d
	0xFF, //0x4e
	0xFF, //0x4f
	0xFF, //0x50
	0xFF, //0x51
	0xFF, //0x52
	0xFF, //0x53
	0xFF, //0x54
	0xFF, //0x55
	0xFF, //0x56
	0xFF, //0x57
	0xFF, //0x58
	0xFF, //0x59
	0xFF, //0x5a
	0xFF, //0x5b
	0xFF, //0x5c
	0xFF, //0x5d
	0xFF, //0x5e
	0xFF, //0x5f
	0xFF, //0x60
	0xFF, //0x61
	0xFF, //0x62
	0xFF, //0x63
	0xFF, //0x64
	0xFF, //0x65
	0xFF, //0x66
	0xFF, //0x67
	0xFF, //0x68
	0xFF, //0x69
	0xFF, //0x6a
	0xFF, //0x6b
	0xFF, //0x6c
	0xFF, //0x6d
	0xFF, //0x6e
	0xFF, //0x6f
	0xFF, //0x70
	0xFF, //0x71
	0xFF, //0x72
	0xFF, //0x73
	0xFF, //0x74
	0xFF, //0x75
	0xFF, //0x76
	0xFF, //0x77
	0xFF, //0x78
	0xFF, //0x79
	0xFF, //0x7a
	0xFF, //0x7b
	0xFF, //0x7c
	0xFF, //0x7d
	0xFF, //0x7e
	0xFF, //0x7f
	0xFF, //0x80
	0xFF, //0x81
	0xFF, //0x82
	0xFF, //0x83
	0xFF, //0x84
	0xFF, //0x85
	0xFF, //0x86
	0xFF, //0x87
	0xFF, //0x88
	0xFF, //0x89
	0xFF, //0x8a
	0xFF, //0x8b
	0xFF, //0x8c
	0xFF, //0x8d
	0xFF, //0x8e
	0xFF, //0x8f
	0xFF, //0x90
	0xFF, //0x91
	0xFF, //0x92
	0xFF, //0x93
	0xFF, //0x94
	0xFF, //0x95
	0xFF, //0x96
	0xFF, //0x97
	0xFF, //0x98
	0xFF, //0x99
	0xFF, //0x9a
	0xFF, //0x9b
	0xFF, //0x9c
	0xFF, //0x9d
	0xFF, //0x9e
	0xFF, //0x9f
	0xFF, //0xa0
	0xFF, //0xa1
	0xFF, //0xa2
	0xFF, //0xa3
	0xFF, //0xa4
	0xFF, //0xa5
	0xFF, //0xa6
	0xFF, //0xa7
	0xFF, //0xa8
	0xFF, //0xa9
	0xFF, //0xaa
	0xFF, //0xab
	0xFF, //0xac
	0xFF, //0xad
	0xFF, //0xae
	0xFF, //0xaf
	0xFF, //0xb0
	0xFF, //0xb1
	0xFF, //0xb2
	0xFF, //0xb3
	0xFF, //0xb4
	0xFF, //0xb5
	0xFF, //0xb6
	0xFF, //0xb7
	0xFF, //0xb8
	0xFF, //0xb9
	0xFF, //0xba
	0xFF, //0xbb
	0xFF, //0xbc
	0xFF, //0xbd
	0xFF, //0xbe
	0xFF, //0xbf
	0xFF, //0xc0
	0xFF, //0xc1
	0xFF, //0xc2
	0xFF, //0xc3
	0xFF, //0xc4
	0xFF, //0xc5
	0xFF, //0xc6
	0xFF, //0xc7
	0xFF, //0xc8
	0xFF, //0xc9
	0xFF, //0xca
	0xFF, //0xcb
	0xFF, //0xcc
	0xFF, //0xcd
	0xFF, //0xce
	0xFF, //0xcf
	0xFF, //0xd0
	0xFF, //0xd1
	0xFF, //0xd2
	0xFF, //0xd3
	0xFF, //0xd4
	0xFF, //0xd5
	0xFF, //0xd6
	0xFF, //0xd7
	0xFF, //0xd8
	0xFF, //0xd9
	0xFF, //0xda
	0xFF, //0xdb
	0xFF, //0xdc
	0xFF, //0xdd
	0xFF, //0xde
	0xFF, //0xdf
	0xFF, //0xe0
	0xFF, //0xe1
	0xFF, //0xe2
	0xFF, //0xe3
	0xFF, //0xe4
	0xFF, //0xe5
	0xFF, //0xe6
	0xFF, //0xe7
	0xFF, //0xe8
	0xFF, //0xe9
	0xFF, //0xea
	0xFF, //0xeb
	0xFF, //0xec
	0xFF, //0xed
	0xFF, //0xee
	0xFF, //0xef
	0xFF, //0xf0
	0xFF, //0xf1
	0xFF, //0xf2
	0xFF, //0xf3
	0xFF, //0xf4
	0xFF, //0xf5
	0xFF, //0xf6
	0xFF, //0xf7
	0xFF, //0xf8
	0xFF, //0xf9
	0xFF, //0xfa
	0xFF, //0xfb
	0xFF, //0xfc
	0xFF, //0xfd
	0xFF, //0xfe
};



void mf_input_keyboard_event(rdpInput* input, UINT16 flags, UINT16 code)
{
	CGEventSourceRef source = CGEventSourceCreate (kCGEventSourceStateCombinedSessionState);
	
	BOOL keyDown = TRUE;
	CGEventRef kbEvent;
	
	if (flags & KBD_FLAGS_RELEASE)
	{
		keyDown = FALSE;
	}
	kbEvent = CGEventCreateKeyboardEvent(source, keymap[code], keyDown);
	CGEventPost(kCGSessionEventTap, kbEvent);
	CFRelease(kbEvent);
	CFRelease(source);
	
	printf("keypress: down = %d, SCAN=%#0X, VK=%#0X\n", keyDown, code, keymap[code]);
	/*
	 INPUT keyboard_event;
	 
	 keyboard_event.type = INPUT_KEYBOARD;
	 keyboard_event.ki.wVk = 0;
	 keyboard_event.ki.wScan = code;
	 keyboard_event.ki.dwFlags = KEYEVENTF_SCANCODE;
	 keyboard_event.ki.dwExtraInfo = 0;
	 keyboard_event.ki.time = 0;
	 
	 if (flags & KBD_FLAGS_RELEASE)
	 keyboard_event.ki.dwFlags |= KEYEVENTF_KEYUP;
	 
	 if (flags & KBD_FLAGS_EXTENDED)
	 keyboard_event.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
	 
	 SendInput(1, &keyboard_event, sizeof(INPUT));
	 */
}

void mf_input_unicode_keyboard_event(rdpInput* input, UINT16 flags, UINT16 code)
{
	/*
	 INPUT keyboard_event;
	 
	 keyboard_event.type = INPUT_KEYBOARD;
	 keyboard_event.ki.wVk = 0;
	 keyboard_event.ki.wScan = code;
	 keyboard_event.ki.dwFlags = KEYEVENTF_UNICODE;
	 keyboard_event.ki.dwExtraInfo = 0;
	 keyboard_event.ki.time = 0;
	 
	 if (flags & KBD_FLAGS_RELEASE)
	 keyboard_event.ki.dwFlags |= KEYEVENTF_KEYUP;
	 
	 SendInput(1, &keyboard_event, sizeof(INPUT));
	 */
}

void mf_input_mouse_event(rdpInput* input, UINT16 flags, UINT16 x, UINT16 y)
{
	float width, height;
	
	if (flags & PTR_FLAGS_WHEEL)
	{
		/*
		 mouse_event.mi.dwFlags = MOUSEEVENTF_WHEEL;
		 mouse_event.mi.mouseData = flags & WheelRotationMask;
		 
		 if (flags & PTR_FLAGS_WHEEL_NEGATIVE)
		 mouse_event.mi.mouseData *= -1;
		 
		 SendInput(1, &mouse_event, sizeof(INPUT));
		 */
	}
	else
	{
		
		mfInfo * mfi;
		CGEventSourceRef source = CGEventSourceCreate (kCGEventSourceStateCombinedSessionState);
		CGEventType mouseType = kCGEventNull;
		CGMouseButton mouseButton = kCGMouseButtonLeft;
		
		
		mfi = mf_info_get_instance();
		
		//width and height of primary screen (even in multimon setups
		width = (float) mfi->servscreen_width;
		height = (float) mfi->servscreen_height;
		
		x += mfi->servscreen_xoffset;
		y += mfi->servscreen_yoffset;
		
		if (flags & PTR_FLAGS_MOVE)
		{
			if (mfi->mouse_down_left == TRUE)
			{
				mouseType = kCGEventLeftMouseDragged;
			}
			else if (mfi->mouse_down_right == TRUE)
			{
				mouseType = kCGEventRightMouseDragged;
			}
			else if (mfi->mouse_down_other == TRUE)
			{
				mouseType = kCGEventOtherMouseDragged;
			}
			else
			{
				mouseType = kCGEventMouseMoved;
			}
			
			CGEventRef move = CGEventCreateMouseEvent(source,
								  mouseType,
								  CGPointMake(x, y),
								  mouseButton // ignored for just movement
								  );
			
			CGEventPost(kCGHIDEventTap, move);
			
			CFRelease(move);
		}
		
		if (flags & PTR_FLAGS_BUTTON1)
		{
			mouseButton = kCGMouseButtonLeft;
			if (flags & PTR_FLAGS_DOWN)
			{
				mouseType = kCGEventLeftMouseDown;
				mfi->mouse_down_left = TRUE;
			}
			else
			{
				mouseType = kCGEventLeftMouseUp;
				mfi->mouse_down_right = FALSE;
			}
		}
		else if (flags & PTR_FLAGS_BUTTON2)
		{
			mouseButton = kCGMouseButtonRight;
			if (flags & PTR_FLAGS_DOWN)
			{
				mouseType = kCGEventRightMouseDown;
				mfi->mouse_down_right = TRUE;
			}
			else
			{
				mouseType = kCGEventRightMouseUp;
				mfi->mouse_down_right = FALSE;
			}
			
		}
		else if (flags & PTR_FLAGS_BUTTON3)
		{
			mouseButton = kCGMouseButtonCenter;
			if (flags & PTR_FLAGS_DOWN)
			{
				mouseType = kCGEventOtherMouseDown;
				mfi->mouse_down_other = TRUE;
			}
			else
			{
				mouseType = kCGEventOtherMouseUp;
				mfi->mouse_down_other = FALSE;
			}
			
		}
		
		
		CGEventRef mouseEvent = CGEventCreateMouseEvent(source,
								mouseType,
								CGPointMake(x, y),
								mouseButton
								);
		CGEventPost(kCGSessionEventTap, mouseEvent);
		
		CFRelease(mouseEvent);
		CFRelease(source);
	}
}

void mf_input_extended_mouse_event(rdpInput* input, UINT16 flags, UINT16 x, UINT16 y)
{
	/*
	 if ((flags & PTR_XFLAGS_BUTTON1) || (flags & PTR_XFLAGS_BUTTON2))
	 {
	 INPUT mouse_event;
	 ZeroMemory(&mouse_event, sizeof(INPUT));
	 
	 mouse_event.type = INPUT_MOUSE;
	 
	 if (flags & PTR_FLAGS_MOVE)
	 {
	 float width, height;
	 wfInfo * wfi;
	 
	 wfi = wf_info_get_instance();
	 //width and height of primary screen (even in multimon setups
	 width = (float) GetSystemMetrics(SM_CXSCREEN);
	 height = (float) GetSystemMetrics(SM_CYSCREEN);
	 
	 x += wfi->servscreen_xoffset;
	 y += wfi->servscreen_yoffset;
	 
	 //mouse_event.mi.dx = x * (0xFFFF / width);
	 //mouse_event.mi.dy = y * (0xFFFF / height);
	 mouse_event.mi.dx = (LONG) ((float) x * (65535.0f / width));
	 mouse_event.mi.dy = (LONG) ((float) y * (65535.0f / height));
	 mouse_event.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	 
	 SendInput(1, &mouse_event, sizeof(INPUT));
	 }
	 
	 mouse_event.mi.dx = mouse_event.mi.dy = mouse_event.mi.dwFlags = 0;
	 
	 if (flags & PTR_XFLAGS_DOWN)
	 mouse_event.mi.dwFlags |= MOUSEEVENTF_XDOWN;
	 else
	 mouse_event.mi.dwFlags |= MOUSEEVENTF_XUP;
	 
	 if (flags & PTR_XFLAGS_BUTTON1)
	 mouse_event.mi.mouseData = XBUTTON1;
	 else if (flags & PTR_XFLAGS_BUTTON2)
	 mouse_event.mi.mouseData = XBUTTON2;
	 
	 SendInput(1, &mouse_event, sizeof(INPUT));
	 }
	 else
	 {
	 mf_input_mouse_event(input, flags, x, y);
	 }
	 */
}


void mf_input_keyboard_event_dummy(rdpInput* input, UINT16 flags, UINT16 code)
{
}

void mf_input_unicode_keyboard_event_dummy(rdpInput* input, UINT16 flags, UINT16 code)
{
}

void mf_input_mouse_event_dummy(rdpInput* input, UINT16 flags, UINT16 x, UINT16 y)
{
}

void mf_input_extended_mouse_event_dummy(rdpInput* input, UINT16 flags, UINT16 x, UINT16 y)
{
}