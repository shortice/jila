#ifdef __ANDROID__
#include "components/system/jila_android.hpp"
#include "jni.h"
#include "SDL3/SDL_system.h"

namespace Jila {

bool android_IsExternalStorageManager() {
    JNIEnv* env = (JNIEnv*)SDL_GetAndroidJNIEnv();

    jobject activity = (jobject)SDL_GetAndroidActivity();
    jclass activityClass(env->GetObjectClass(activity));

    // find the identifier of the method to call
    jmethodID method_id = env->GetMethodID(
        activityClass, 
        "isExternalStorageManager", "()Z"
    );

    // effectively call the Java method
    jboolean result = env->CallBooleanMethod(
        activity, 
        method_id
    );

    // clean up the local references.
    env->DeleteLocalRef(activity);
    env->DeleteLocalRef(activityClass);

    return result;
}

void android_RequestExternalStorageManager() {
    JNIEnv* env = (JNIEnv*)SDL_GetAndroidJNIEnv();

    jobject activity = (jobject)SDL_GetAndroidActivity();
    jclass activityClass(env->GetObjectClass(activity));

    // find the identifier of the method to call
    jmethodID method_id = env->GetMethodID(
        activityClass, 
        "requestExternalStorageManager", 
        "()V"
    );

    // effectively call the Java method
    env->CallVoidMethod(
        activity,
        method_id
    );

    // clean up the local references.
    env->DeleteLocalRef(activity);
    env->DeleteLocalRef(activityClass);
}

std::string android_getExternalStoragePath() {
    JNIEnv* env = (JNIEnv*)SDL_GetAndroidJNIEnv();

    jobject activity = (jobject)SDL_GetAndroidActivity();
    jclass activityClass(env->GetObjectClass(activity));

    // find the identifier of the method to call
    jmethodID method_id = env->GetMethodID(
        activityClass, 
        "getExternalStoragePath", 
        "()Ljava/lang/String;"
    );

    // effectively call the Java method
    jstring result = (jstring)env->CallObjectMethod(
        activity,
        method_id
    );

    const char* path_ = env->GetStringUTFChars(result, nullptr);
    std::string path = path_;

    // clean up the local references.
    env->ReleaseStringUTFChars(result, path_);
    env->DeleteLocalRef(result);
    env->DeleteLocalRef(activity);
    env->DeleteLocalRef(activityClass);

    return path;
}

/*
void PushNotification(String title, String text)
(Ljava/lang/String;Ljava/lang/String;)V
*/
void android_PushNotification(
    std::string title, 
    std::string text
) {
    JNIEnv* env = (JNIEnv*)SDL_GetAndroidJNIEnv();

    jobject activity = (jobject)SDL_GetAndroidActivity();
    jclass activityClass(env->GetObjectClass(activity));

    // find the identifier of the method to call
    jmethodID method_id = env->GetMethodID(
        activityClass, 
        "PushNotification", 
        "(Ljava/lang/String;Ljava/lang/String;)V"
    );

    jstring param1 = env->NewStringUTF(title.c_str());
    jstring param2 = env->NewStringUTF(text.c_str());

    // effectively call the Java method
    env->CallVoidMethod(
        activity,
        method_id,
        param1,
        param2
    );

    env->DeleteLocalRef(param1);
    env->DeleteLocalRef(param2);
    env->DeleteLocalRef(activity);
    env->DeleteLocalRef(activityClass);
}

}
#endif
