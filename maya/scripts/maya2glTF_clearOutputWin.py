# https://www.highend3d.com/maya/script/clear-output-window-for-maya
# Clears maya output window by Zohar
from ctypes import *
#import win32con

user32 = windll.user32
EnumWindowsProc = WINFUNCTYPE(c_int, c_int, c_int)

# Returns handles to windows with matching titles
def get_handle(title, parent = None):
	rHwnd = []
	def EnumCB(hwnd, lparam, match = title.lower(), rHwnd = rHwnd):
		# child
		if lparam == 1:
			rHwnd.append(hwnd)
			return False
	
		title = c_buffer(' ' * 256)
		user32.GetWindowTextA(hwnd, title, 255)
		if title.value.lower() == match:
			rHwnd.append(hwnd)
			#print "Matched", title.value
			return False
		return True

	if parent is not None:
		user32.EnumChildWindows(parent, EnumWindowsProc(EnumCB), 1)
	else:
		user32.EnumWindows(EnumWindowsProc(EnumCB), 0)
	return rHwnd

def clear():
	print "Clearing Maya output window"
	out = get_handle("Output Window")
	if not out:
		print "Output window wasn't found"
	else:	
		ch = get_handle("", out[0])
		if ( ch[0] ):
			#user32.SendMessageA(ch[0], win32con.EM_SETSEL, 0, -1)
			#user32.SendMessageA(ch[0], win32con.EM_REPLACESEL, 1, "")
			user32.SendMessageA(ch[0], 0x00B1, 0, -1)
			user32.SendMessageA(ch[0], 0x00C2, 1, "")			
		else:
			print "Child window wasn't found"

clear()
