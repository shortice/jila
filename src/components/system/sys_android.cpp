#include "components/system/sys_android.hpp"
#ifdef __ANDROID__
#include "SDL3/SDL_events.h"
#include "components/system/jila_android.hpp"
#endif

namespace Jila {

#ifdef __ANDROID__
void _PermissionCallback(
    void* userdata, 
    const char* permission,
    bool granted
) {
    SDL_Event event;
    SDL_zero(event);
    event.type = SDL_EVENT_USER;

    if (granted) {
        event.user.code = 1003;
    } else {
        event.user.code = 1004;
    }

    event.user.data1 = NULL;
    event.user.data2 = NULL;
    
    SDL_PushEvent(&event);
}

bool android_RequestPermission(std::string permission) {
    return SDL_RequestAndroidPermission(
        permission.data(), 
        &_PermissionCallBack, 
        NULL
    ) != -1;
}
#endif


void bindSysAndroid(sol::state* state) {
    #ifdef __ANDROID__
    state -> set_function(
        "android_IsExternalStorageManager",
        &android_IsExternalStorageManager
    );

    state -> set_function(
        "android_RequestExternalStorageManager",
        &android_RequestExternalStorageManager
    );

    state -> set_function(
        "android_PushNotification",
        &android_PushNotification
    );

    state -> set_function(
        "android_RequestPermission",
        &android_RequestPermission
    )
    #endif
}

}
