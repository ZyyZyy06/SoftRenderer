#pragma once

#include<Windows.h>
#include <gdiplus.h>
#include<cstdlib>
#include<iostream>
#include <cassert>

#include "Config.h"
#include "Global.h"

using namespace Gdiplus;

#pragma comment (lib,"Gdiplus.lib")
#pragma comment(linker, "/ENTRY:wWinMainCRTStartup")
