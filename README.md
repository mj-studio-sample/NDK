# NDK

<img src='1.jpg' width = 400/>

### native.h
```c++
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
```

### native.cpp
```c++
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

```

### StringConverter.h
```c++
#ifndef NDK_STRINGCONVERTER_H
#define NDK_STRINGCONVERTER_H

#include <cstring>

class StringConverter {
private:
public:
    StringConverter();
    void reverseString(char* src, char* dest);
};


#endif //NDK_STRINGCONVERTER_H
```

### StringConverter.cpp
```c++
#include "StringConverter.h"
#include "native.h"

StringConverter::StringConverter() = default;

void StringConverter::reverseString(char *src, char *dest) {
    size_t len = strlen(src);

    LOGE("len : %d",len);

    int i = 0;

    while(src[i] != '\0') {
        dest[len - i - 1] = src[i];
        i++;
    }
}
```

### NativeLib.kt
```kotlin
interface Callback {
    fun onStringReversed(str: String)
}

class NativeLib : Callback {

    private val TAG = NativeLib::class.java.simpleName

    companion object {
        init {
            System.loadLibrary("native")
        }
    }

    private val callbacks = mutableListOf<Callback>()

    fun addCallback(callback: Callback) {
        callbacks.add(callback)
    }

    fun removeCallback(callback: Callback): Boolean {
        return callbacks.remove(callback)
    }


    external fun printLog()

    external fun returnString(): String

    external fun reverseString(str: String): String

    external fun reverseStringWithCallback(str: String)

    override fun onStringReversed(str: String) {
        callbacks.forEach {
            it.onStringReversed(str)
        }
    }
}
```

### MainActivity.kt
```kotlin
class MainActivity : AppCompatActivity() {

    private val TAG = MainActivity::class.java.simpleName

    private val native = NativeLib()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        native.addCallback(object : Callback {
            override fun onStringReversed(str: String) {
                reverseText2.text = str
            }
        })

        reverse.setOnClickListener {
            reverseText.text = native.reverseString(original.text.toString())
        }

        reverse2.setOnClickListener {
            native.reverseStringWithCallback(original2.text.toString())
        }
    }
}
```

