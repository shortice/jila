#pragma once
#ifdef __ANDROID__

#include <string>

namespace Jila {

bool android_IsExternalStorageManager();
void android_RequestExternalStorageManager();
std::string android_getExternalStoragePath();
void android_PushNotification(std::string title, std::string text);

}
#endif
