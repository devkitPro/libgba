
#include <stddef.h>
#include <sys/iosupport.h>

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <mgba.h>

#define MGBA_DEBUG_ENABLE *(vu16*) 0x4FFF780
#define MGBA_DEBUG_FLAGS  *(vu16*) 0x4FFF700
#define MGBA_DEBUG_STRING  (char*) 0x4FFF600

static bool __mgba_opened = false;

//---------------------------------------------------------------------------------
bool mgba_open(void) {
//---------------------------------------------------------------------------------
	MGBA_DEBUG_ENABLE = 0xC0DE;
	__mgba_opened = MGBA_DEBUG_ENABLE == 0x1DEA;
	return __mgba_opened;
}


//---------------------------------------------------------------------------------
void mgba_close(void) {
//---------------------------------------------------------------------------------
	MGBA_DEBUG_ENABLE = 0;
}

//---------------------------------------------------------------------------------
static void mgba_write(int level, const char *ptr, size_t len) {
//---------------------------------------------------------------------------------
	level &= 0x7;
	memcpy(MGBA_DEBUG_STRING, ptr, len);
	MGBA_DEBUG_FLAGS =  level | 0x100;
}

//---------------------------------------------------------------------------------
ssize_t mgba_stdout_write(struct _reent* r __attribute__((unused)), void* fd __attribute__((unused)), const char* ptr, size_t len) {
//---------------------------------------------------------------------------------

	if (len>0x100) len = 0x100;
	mgba_write(LIBGBA_LOG_INFO, ptr,len);

	return len;
}

//---------------------------------------------------------------------------------
ssize_t mgba_stderr_write(struct _reent* r __attribute__((unused)), void* fd __attribute__((unused)), const char* ptr, size_t len) {
//---------------------------------------------------------------------------------
	if (len>0x100) len = 0x100;
	mgba_write(LIBGBA_LOG_ERROR, ptr, len);

	return len;
}

//---------------------------------------------------------------------------------
void mgba_log(int level, const char* ptr, ...) {
//---------------------------------------------------------------------------------

	if (!__mgba_opened) mgba_open();

	level &= 0x7;
	va_list args;
	va_start(args, ptr);
	vsnprintf(MGBA_DEBUG_STRING, 0x100, ptr, args);
	va_end(args);
	MGBA_DEBUG_FLAGS = level | 0x100;
}

static const devoptab_t dotab_mgba_stdout = {
	"mgba_stdout",
	0,
	NULL,
	NULL,
	mgba_stdout_write
};

static const devoptab_t dotab_mgba_stderr = {
	"mgba_stderr",
	0,
	NULL,
	NULL,
	mgba_stderr_write
};

//---------------------------------------------------------------------------------
bool mgba_console_open(void) {
//---------------------------------------------------------------------------------
	if (!mgba_open()) {
		return false;
	}
	devoptab_list[STD_OUT] = &dotab_mgba_stdout;
	devoptab_list[STD_ERR] = &dotab_mgba_stderr;
	return true;
}
