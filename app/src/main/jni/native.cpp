//
// Created by 문명주 on 2019-11-17.
//


#include "native.h"


extern "C" {

auto stringConverter = StringConverter();

JNIEXPORT void JNICALL Java_happy_mjstudio_ndk_NativeLib_printLog(JNIEnv *jEnv, jobject thiz) {
    __android_log_print(ANDROID_LOG_ERROR, __FUNCTION__, "Hello World!");
}

JNIEXPORT jstring JNICALL
Java_happy_mjstudio_ndk_NativeLib_returnString(JNIEnv *jEnv, jobject thiz) {
    jstring str = jEnv->NewStringUTF("Hello World");

    return str;
}

JNIEXPORT jstring JNICALL
Java_happy_mjstudio_ndk_NativeLib_reverseString(JNIEnv *jEnv, jobject thiz, jstring str) {
    int len = jEnv->GetStringUTFLength(str);

    char *cString = new char[len + 1];
    char *convertedString = new char[len + 1];

    jEnv->GetStringUTFRegion(str, 0, len, cString);

    cString[len] = '\0';
    convertedString[len] = '\0';

    stringConverter.reverseString(cString, convertedString);

    LOGE("%s", cString);
    LOGE("%s", convertedString);

    return jEnv->NewStringUTF(convertedString);
}

/**
 * Sleep 5 Seconds and reverse string
 * @param jEnv
 * @param thiz
 * @param str
 */
JNIEXPORT void JNICALL
Java_happy_mjstudio_ndk_NativeLib_reverseStringWithCallback(JNIEnv *jEnv, jobject thiz,
                                                            jstring str) {

    sleep(5);

    jclass clazz = jEnv->GetObjectClass(thiz);
    jmethodID methodId = jEnv->GetMethodID(clazz, "onStringReversed", "(Ljava/lang/String;)V");

    jsize len = jEnv->GetStringUTFLength(str);

    char *src = new char[len + 1];
    char *dest = new char[len + 1];
    src[len] = '\0';
    dest[len] = '\0';
    jEnv->GetStringUTFRegion(str, 0, len, src);

    stringConverter.reverseString(src,dest);

    jEnv->CallVoidMethod(thiz,methodId,jEnv->NewStringUTF(dest));
}

}


