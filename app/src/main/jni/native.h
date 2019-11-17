//
// Created by 문명주 on 2019-11-17.
//

#ifndef NDK_NATIVE_H
#define NDK_NATIVE_H

#include <jni.h>
#include "android/log.h"

using namespace std;

#include <iostream>
#include <cstring>
#include "StringConverter.h"
#include <stdlib.h>
#include <unistd.h>

#define LOGTAG "Native"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOGTAG,__VA_ARGS__)

extern "C" {
JNIEXPORT void JNICALL Java_happy_mjstudio_ndk_NativeLib_printLog(JNIEnv *jEnv, jobject thiz);
JNIEXPORT jstring JNICALL Java_happy_mjstudio_ndk_NativeLib_returnString(JNIEnv *jEnv, jobject thiz);
JNIEXPORT jstring JNICALL Java_happy_mjstudio_ndk_NativeLib_reverseString(JNIEnv *jEnv, jobject thiz, jstring str);
JNIEXPORT void JNICALL Java_happy_mjstudio_ndk_NativeLib_reverseStringWithCallback(JNIEnv *jEnv, jobject thiz, jstring str);
}

#endif //NDK_NATIVE_H

