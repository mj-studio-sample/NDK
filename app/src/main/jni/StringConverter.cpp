//
// Created by 문명주 on 2019-11-17.
//

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