#ifdef __ANDROID__
#include "misc.hpp"
#include "SDL3/SDL_system.h"
#include "jila-android.hpp"
#endif

namespace Jila {

#ifdef __ANDROID__
void Init_Jila_Android_Context() {
    JNIEnv* env = (JNIEnv*)SDL_GetAndroidJNIEnv();
    jobject activity = (jobject)SDL_GetAndroidActivity();
    jclass activityClass = env->GetObjectClass(activity);
    jmethodID getApplicationContext = env->GetMethodID(
        activityClass, 
        "getApplicationContext", 
        "()Landroid/content/Context;"
    );
    jobject context = env->CallObjectMethod(activity, getApplicationContext);

    Jila_Android_InitContext(env, context);

    // Clear jni resources
    env->DeleteLocalRef(activity);
    env->DeleteLocalRef(activityClass);
}
#endif

}

