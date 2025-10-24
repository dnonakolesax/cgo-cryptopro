#define UNIX
#define IGNORE_LEGACY_FORMAT_MESSAGE_MSG
#define SIZEOF_VOID_P 8
#include "CSP_WinCrypt.h"
#include "WinCryptEx.h"
#include <stdio.h>

unsigned int acquire_provider(void *container, void *password, void *provider);
unsigned int sign(void *provider, void *payload, void *signature);
void release_provider(void *container);

